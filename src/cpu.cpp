#include <algorithm>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <memory>

#include "../include/cpu.h"
#include "../include/memory.h"
#include "../include/instruction.h"


namespace MC = MemoryConsts;

void CPU::connect_with_ram(std::shared_ptr<Memory> ram)
{
    ram_ptr = ram;
}

MemoryPtr CPU::get_ram_address() const
{
    return ram_ptr;
}

void CPU::cpu_mem_write(uint16_t address, uint8_t data) const
{
    ram_ptr.lock()->mem_write(address, data);
}

uint8_t CPU::cpu_mem_read(uint16_t address) const
{
    return ram_ptr.lock()->mem_read(address);
}

int CPU::cpu_mem_read_debug(uint16_t address) const
{
    return ram_ptr.lock()->mem_read_debug(address);
}

void CPU::perform_cycle(bool debug_mode)
{
    status.flag.unused = 1;

    if (debug_mode)
        log_debug_info();

    if (cycles_queued == 0) {
        next_instruction();
    }

    cycles_queued--;
    cycles_executed++;
}

void CPU::next_instruction()
{
    uint8_t instr_opcode {cpu_mem_read(pc)};
    pc++;

    curr_instruction = deduce_instr_from_opcode(instr_opcode);
    cycles_queued = curr_instruction.cycles;

    exec_address_mode();
    exec_instruction();
}

void CPU::exec_address_mode()
{
    using AM = Instruction::AddressingMode;
    switch (curr_instruction.address_mode) {
        case AM::immediate:   addr_mode_immediate();   break;
        case AM::zero_page:   addr_mode_zero_page();   break;
        case AM::zero_page_x: addr_mode_zero_page_x(); break;
        case AM::zero_page_y: addr_mode_zero_page_y(); break;
        case AM::relative:    addr_mode_relative();    break;
        case AM::absolute:    addr_mode_absolute();    break;
        case AM::absolute_x:  addr_mode_absolute_x();  break;
        case AM::absolute_y:  addr_mode_absolute_y();  break;
        case AM::indirect:    addr_mode_indirect();    break;
        case AM::indirect_x:  addr_mode_indirect_x();  break;
        case AM::indirect_y:  addr_mode_indirect_y();  break;
        default: break;
    }
}

void CPU::exec_instruction()
{
    using MN = Instruction::MnemonicName;
    switch (curr_instruction.mnemonic) {
        case MN::BCC: BCC(); break;
        case MN::BCS: BCS(); break;
        case MN::BEQ: BEQ(); break;
        case MN::BMI: BMI(); break;
        case MN::BNE: BNE(); break;
        case MN::BPL: BPL(); break;
        case MN::BRK: BRK(); break;
        case MN::BVC: BVC(); break;
        case MN::BVS: BVS(); break;
        case MN::CLC: CLC(); break;
        case MN::CLD: CLD(); break;
        case MN::CLI: CLI(); break;
        case MN::CLV: CLV(); break;
        case MN::DEX: DEX(); break;
        case MN::DEY: DEY(); break;
        case MN::INX: INX(); break;
        case MN::INY: INY(); break;
        case MN::NOP: NOP(); break;
        case MN::PHA: PHA(); break;
        case MN::PHP: PHP(); break;
        case MN::PLA: PLA(); break;
        case MN::PLP: PLP(); break;
        case MN::RTI: RTI(); break;
        case MN::RTS: RTS(); break;
        case MN::SEC: SEC(); break;
        case MN::SED: SED(); break;
        case MN::SEI: SEI(); break;
        case MN::TAX: TAX(); break;
        case MN::TAY: TAY(); break;
        case MN::TSX: TSX(); break;
        case MN::TXA: TXA(); break;
        case MN::TXS: TXS(); break;
        case MN::TYA: TYA(); break;
        default: break;
    }
}

Instruction CPU::deduce_instr_from_opcode(uint8_t opcode) const
{
    auto instruction_it = std::find_if(
        Lookup::instructions_table.begin(),
        Lookup::instructions_table.end(),
        [&] (const Instruction& instr) { return instr.opcode == opcode; }
        );

    return *instruction_it;
}

void CPU::hard_reset()
{
    acc = 0x00;
    x_reg = 0x00;
    y_reg = 0x00;
    stack_ptr = 0xFD;
    pc = read_reset_vector();
    status.word = 0x34;
    ram_ptr.lock()->mem_clear();
}

void CPU::soft_reset()
{
    stack_ptr -= 0x03;
    pc = read_reset_vector();
    status.flag.interrupt = 1;
}

void CPU::log_debug_info()
{
    std::cout << "[DEBUG] "
        << "CYCLE: " << std::setw(6) << std::left << cycles_executed << std::hex
        << "| OPCODE: 0x" << std::setw(3) << std::left << static_cast<short>(curr_instruction.opcode)
        << "| A: 0x" << std::setw(3) << std::left << static_cast<short>(acc)
        << "| X: 0x" << std::setw(3) << std::left << static_cast<short>(x_reg)
        << "| Y: 0x" << std::setw(3) << std::left << static_cast<short>(y_reg)
        << "| S: 0x" << std::setw(3) << std::left << static_cast<short>(stack_ptr)
        << "| PC: 0x" << std::setw(5) << std::left << static_cast<short>(pc)
        << "| P: 0b" << std::setw(9) << std::left << std::bitset<8>(status.word)
        << std::dec << "\n";
}

uint16_t CPU::read_reset_vector() const
{
    uint8_t lsb {cpu_mem_read(MC::reset_vector_lsb)};
    uint8_t msb {cpu_mem_read(MC::reset_vector_msb)};

    uint16_t address = (msb << 8) | lsb;

    return address;
}

bool CPU::check_for_zero_flag(uint8_t reg) const
{
    return reg == 0x00;
}

bool CPU::check_for_negative_flag(uint8_t reg) const
{
    return (reg & (1 << 7)) > 0;
}

bool CPU::check_for_page_crossing(uint16_t address1, uint16_t address2) const
{
    return (address1 & ~MC::zero_page_mask) != (address2 & ~MC::zero_page_mask);
}

void CPU::perform_branching()
{
    uint16_t new_pc = pc + branch_offset;

    if (check_for_page_crossing(pc, new_pc))
        cycles_queued += 2;
    else
        cycles_queued += 1;

    pc = new_pc;
}


////////////////////////
//  Addressing modes  //
////////////////////////

void CPU::addr_mode_immediate()
{
    arg_address = cpu_mem_read(pc);
    pc++;
}

void CPU::addr_mode_zero_page()
{
    arg_address = cpu_mem_read(pc);
    pc++;

    arg_address &= MC::zero_page_mask;
}

void CPU::addr_mode_zero_page_x()
{
    arg_address = cpu_mem_read(pc) | x_reg;
    pc++;

    arg_address &= MC::zero_page_mask;
}

void CPU::addr_mode_zero_page_y()
{
    arg_address = cpu_mem_read(pc) | y_reg;
    pc++;

    arg_address &= MC::zero_page_mask;
}

void CPU::addr_mode_relative()
{
    branch_offset = cpu_mem_read(pc);
    pc++;
}

void CPU::addr_mode_absolute()
{
    uint8_t lsb {cpu_mem_read(pc)};
    pc++;
    uint8_t msb {cpu_mem_read(pc)};
    pc++;

    arg_address = (msb << 8) | lsb;
}

void CPU::addr_mode_absolute_x()
{
    uint8_t lsb {cpu_mem_read(pc)};
    pc++;
    uint8_t msb {cpu_mem_read(pc)};
    pc++;

    arg_address = ((msb << 8) | lsb) | x_reg;
}

void CPU::addr_mode_absolute_y()
{
    uint8_t lsb {cpu_mem_read(pc)};
    pc++;
    uint8_t msb {cpu_mem_read(pc)};
    pc++;

    arg_address = ((msb << 8) | lsb) | y_reg;
}

void CPU::addr_mode_indirect()
{
    uint8_t lsb {cpu_mem_read(pc)};
    pc++;
    uint8_t msb {cpu_mem_read(pc)};
    pc++;

    uint16_t temp_address = (msb << 8) | lsb;

    lsb = cpu_mem_read(temp_address);
    msb = cpu_mem_read(temp_address + 1);

    arg_address = (msb << 8) | lsb;
}

void CPU::addr_mode_indirect_x()
{
    uint16_t temp_address = cpu_mem_read(pc) | x_reg;
    pc++;

    uint8_t lsb {cpu_mem_read(temp_address & MC::zero_page_mask)};
    uint8_t msb {cpu_mem_read((temp_address + 1) & MC::zero_page_mask)};

    arg_address = (msb << 8) | lsb;
}

void CPU::addr_mode_indirect_y()
{
    uint16_t temp_address = cpu_mem_read(pc);
    pc++;

    uint8_t lsb {cpu_mem_read(temp_address & MC::zero_page_mask)};
    uint8_t msb {cpu_mem_read((temp_address + 1) & MC::zero_page_mask)};

    arg_address = ((msb << 8) | lsb) | y_reg;
}


///////////////
//  Opcodes  //
///////////////

void CPU::BCC()
{
    if (status.flag.carry == 0)
        perform_branching();
}

void CPU::BCS()
{
    if (status.flag.carry == 1)
        perform_branching();
}

void CPU::BEQ()
{
    if (status.flag.zero == 1)
        perform_branching();
}

void CPU::BMI()
{
    if (status.flag.negative == 1)
        perform_branching();
}

void CPU::BNE()
{
    if (status.flag.zero == 0)
        perform_branching();
}

void CPU::BPL()
{
    if (status.flag.negative == 0)
        perform_branching();
}

void CPU::BRK()
{
    // TODO
}

void CPU::BVC()
{
    if (status.flag.overflow == 0)
        perform_branching();
}

void CPU::BVS()
{
    if (status.flag.overflow == 1)
        perform_branching();
}

void CPU::CLC()
{
    status.flag.carry = 0;
}

void CPU::CLD()
{
    status.flag.decimal = 0;
}

void CPU::CLI()
{
    status.flag.interrupt = 0;
}

void CPU::CLV()
{
    status.flag.overflow = 0;
}

void CPU::DEX()
{
    x_reg--;

    status.flag.zero = check_for_zero_flag(x_reg);
    status.flag.negative = check_for_negative_flag(x_reg);
}

void CPU::DEY()
{
    y_reg--;

    status.flag.zero = check_for_zero_flag(y_reg);
    status.flag.negative = check_for_negative_flag(y_reg);
}

void CPU::INX()
{
    x_reg++;

    status.flag.zero = check_for_zero_flag(x_reg);
    status.flag.negative = check_for_negative_flag(x_reg);
}

void CPU::INY()
{
    y_reg++;

    status.flag.zero = check_for_zero_flag(y_reg);
    status.flag.negative = check_for_negative_flag(y_reg);
}

void CPU::NOP() {}

void CPU::PHA()
{
    cpu_mem_write(MC::stack_offset + stack_ptr, acc);
    stack_ptr--;
}

void CPU::PHP()
{
    status.flag.brk = 1;
    status.flag.unused = 1;

    cpu_mem_write(MC::stack_offset + stack_ptr, status.word);
    stack_ptr--;

    status.flag.brk = 0;
    status.flag.unused = 0;
}

void CPU::PLA()
{
    stack_ptr++;
    acc = cpu_mem_read(MC::stack_offset + stack_ptr);

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::PLP()
{
    stack_ptr++;
    status.word = cpu_mem_read(MC::stack_offset + stack_ptr);
}

void CPU::RTI()
{
    // TODO: this is probably wrong

    stack_ptr++;
    status.word = cpu_mem_read(MC::stack_offset + stack_ptr);

    status.flag.brk = 0;
    status.flag.unused = 0;

    stack_ptr++;
    pc = cpu_mem_read(MC::stack_offset + stack_ptr);
}

void CPU::RTS()
{
    // TODO: same as above

    stack_ptr++;
    pc = cpu_mem_read(MC::stack_offset + stack_ptr) - 1;
}

void CPU::SEC()
{
    status.flag.carry = 1;
}

void CPU::SED()
{
    status.flag.decimal = 1;
}

void CPU::SEI()
{
    status.flag.interrupt = 1;
}

void CPU::TAX()
{
    x_reg = acc;

    status.flag.zero = check_for_zero_flag(x_reg);
    status.flag.negative = check_for_negative_flag(x_reg);
}

void CPU::TAY()
{
    y_reg = acc;

    status.flag.zero = check_for_zero_flag(y_reg);
    status.flag.negative = check_for_negative_flag(y_reg);
}

void CPU::TSX()
{
    x_reg = cpu_mem_read(MC::stack_offset + stack_ptr);

    status.flag.zero = check_for_zero_flag(x_reg);
    status.flag.negative = check_for_negative_flag(x_reg);
}

void CPU::TXA()
{
    acc = x_reg;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::TXS()
{
    cpu_mem_write(MC::stack_offset + stack_ptr, x_reg);
}

void CPU::TYA()
{
    acc = y_reg;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}
