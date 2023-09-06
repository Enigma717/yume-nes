#include "../include/cpu.h"

#include "../include/instruction.h"
#include "../include/memory.h"

#include <algorithm>
#include <bitset>
#include <iostream>
#include <iomanip>
#include <memory>


namespace MC = MemoryConsts;
namespace Masks
{
    constexpr uint8_t  carry_flag_mask    {0b0000'0001};
    constexpr uint8_t  overflow_flag_mask {0b0100'0000};
    constexpr uint8_t  negative_flag_mask {0b1000'0000};
    constexpr uint16_t zero_page_mask     {0x00FF};
}


void CPU::connect_with_memory(std::shared_ptr<Memory> ram)
{
    ram_ptr = ram;
}

void CPU::connect_with_cartridge(std::shared_ptr<Cartridge> cartridge)
{
    cartridge_ptr = cartridge;
}

MemoryPtr CPU::get_memory_pointer() const
{
    return ram_ptr;
}

CartridgePtr CPU::get_cartridge_pointer() const
{
    return cartridge_ptr;
}

void CPU::cpu_memory_write(uint16_t address, uint8_t value) const
{
    ram_ptr.lock()->memory_write(address, value);
}

uint8_t CPU::cpu_memory_read(uint16_t address) const
{
    return ram_ptr.lock()->memory_read(address);
}

void CPU::cpu_stack_push(uint8_t value)
{
    cpu_memory_write(MC::stack_offset + stack_ptr, value);
    stack_ptr--;
}

uint8_t CPU::cpu_stack_pop()
{
    stack_ptr++;
    return cpu_memory_read(MC::stack_offset + stack_ptr);
}


void CPU::perform_cycle(bool debug_mode)
{
    status.flag.unused = 1;

    if (debug_mode)
        log_debug_info();

    if (cycles_queued == 0)
        next_instruction();

    cycles_queued--;
    cycles_executed++;
}

void CPU::next_instruction()
{
    uint8_t instr_opcode {cpu_memory_read(pc)};
    pc++;

    curr_instruction = deduce_instruction_from_opcode(instr_opcode);
    cycles_queued = curr_instruction.cycles;

    exec_address_mode();
    exec_instruction();
}

void CPU::exec_address_mode()
{
    using AM = Instruction::AddressingMode;
    switch (curr_instruction.address_mode) {
        case AM::immediate:   address_mode_immediate();   break;
        case AM::zero_page:   address_mode_zero_page();   break;
        case AM::zero_page_x: address_mode_zero_page_x(); break;
        case AM::zero_page_y: address_mode_zero_page_y(); break;
        case AM::relative:    address_mode_relative();    break;
        case AM::absolute:    address_mode_absolute();    break;
        case AM::absolute_x:  address_mode_absolute_x();  break;
        case AM::absolute_y:  address_mode_absolute_y();  break;
        case AM::indirect:    address_mode_indirect();    break;
        case AM::indirect_x:  address_mode_indirect_x();  break;
        case AM::indirect_y:  address_mode_indirect_y();  break;
        default: break;
    }
}

void CPU::exec_instruction()
{
    using MN = Instruction::MnemonicName;
    switch (curr_instruction.mnemonic) {
        case MN::ADC: ADC(); break;
        case MN::AND: AND(); break;
        case MN::ASL: ASL(); break;
        case MN::BCC: BCC(); break;
        case MN::BCS: BCS(); break;
        case MN::BEQ: BEQ(); break;
        case MN::BIT: BIT(); break;
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
        case MN::CMP: CMP(); break;
        case MN::CPX: CPX(); break;
        case MN::CPY: CPY(); break;
        case MN::DEC: DEC(); break;
        case MN::DEX: DEX(); break;
        case MN::DEY: DEY(); break;
        case MN::EOR: EOR(); break;
        case MN::INC: INC(); break;
        case MN::INX: INX(); break;
        case MN::INY: INY(); break;
        case MN::JMP: JMP(); break;
        case MN::JSR: JSR(); break;
        case MN::LDA: LDA(); break;
        case MN::LDX: LDX(); break;
        case MN::LDY: LDY(); break;
        case MN::LSR: LSR(); break;
        case MN::NOP: NOP(); break;
        case MN::ORA: ORA(); break;
        case MN::PHA: PHA(); break;
        case MN::PHP: PHP(); break;
        case MN::PLA: PLA(); break;
        case MN::PLP: PLP(); break;
        case MN::ROL: ROL(); break;
        case MN::ROR: ROR(); break;
        case MN::RTI: RTI(); break;
        case MN::RTS: RTS(); break;
        case MN::SBC: SBC(); break;
        case MN::SEC: SEC(); break;
        case MN::SED: SED(); break;
        case MN::SEI: SEI(); break;
        case MN::STA: STA(); break;
        case MN::STX: STX(); break;
        case MN::STY: STY(); break;
        case MN::TAX: TAX(); break;
        case MN::TAY: TAY(); break;
        case MN::TSX: TSX(); break;
        case MN::TXA: TXA(); break;
        case MN::TXS: TXS(); break;
        case MN::TYA: TYA(); break;
        default: ILL(); break;
    }
}

Instruction CPU::deduce_instruction_from_opcode(uint8_t opcode) const
{
    auto instruction_it = std::find_if(
        Lookup::instructions_table.begin(),
        Lookup::instructions_table.end(),
        [&] (const Instruction& instr) { return instr.opcode == opcode; }
        );

    if (instruction_it == Lookup::instructions_table.end())
        instruction_it = std::prev(instruction_it, 1);

    return *instruction_it;
}


void CPU::interrupt_nmi()
{
    uint8_t pc_lsb = static_cast<uint8_t>(pc & Masks::zero_page_mask);
    uint8_t pc_msb = static_cast<uint8_t>(pc >> 8);

    status.flag.brk = 0;
    status.flag.unused = 1;
    status.flag.interrupt = 1;

    cpu_stack_push(pc_msb);
    cpu_stack_push(pc_lsb);
    cpu_stack_push(status.word);

    pc = read_nmi_vector();
}

void CPU::interrupt_irq()
{
    if (status.flag.interrupt == 0) {
        uint8_t pc_lsb = static_cast<uint8_t>(pc & Masks::zero_page_mask);
        uint8_t pc_msb = static_cast<uint8_t>(pc >> 8);

        status.flag.brk = 0;
        status.flag.unused = 1;
        status.flag.interrupt = 1;

        cpu_stack_push(pc_msb);
        cpu_stack_push(pc_lsb);
        cpu_stack_push(status.word);

        pc = read_irq_vector();
    }
}

void CPU::interrupt_reset()
{
    stack_ptr -= 0x03;
    pc = read_reset_vector();
    status.flag.interrupt = 1;
}

void CPU::hard_reset()
{
    acc = 0x00;
    x_reg = 0x00;
    y_reg = 0x00;
    stack_ptr = 0xFD;
    pc = read_reset_vector();
    status.word = 0x34;
    ram_ptr.lock()->memory_clear();
}

void CPU::log_debug_info()
{
    std::cout << "[DEBUG] "
        << "CYCLE: " << std::setw(6) << std::left << cycles_executed << std::hex << std::uppercase
        << "| OPCODE: 0x" << std::setw(3) << std::left << static_cast<short>(curr_instruction.opcode)
        << "| ARG: 0x" << std::setw(5) << std::left << static_cast<short>(arg_address)
        << "| MEM[ARG]: 0x" << std::setw(5) << std::left << static_cast<short>(cpu_memory_read(arg_address))
        << "|| A: 0x" << std::setw(3) << std::left << static_cast<short>(acc)
        << "| X: 0x" << std::setw(3) << std::left << static_cast<short>(x_reg)
        << "| Y: 0x" << std::setw(3) << std::left << static_cast<short>(y_reg)
        << "| S: 0x" << std::setw(3) << std::left << static_cast<short>(stack_ptr)
        << "| PC: 0x" << std::setw(5) << std::left << static_cast<short>(pc)
        << "| P: 0b" << std::setw(9) << std::left << std::bitset<8>(status.word)
        << std::dec << "\n";
}


uint16_t CPU::read_nmi_vector() const
{
    uint8_t lsb {cpu_memory_read(MC::nmi_vector_lsb)};
    uint8_t msb {cpu_memory_read(MC::nmi_vector_msb)};

    uint16_t address = (msb << 8) | lsb;

    return address;
}

uint16_t CPU::read_reset_vector() const
{
    uint8_t lsb {cpu_memory_read(MC::reset_vector_lsb)};
    uint8_t msb {cpu_memory_read(MC::reset_vector_msb)};

    uint16_t address = (msb << 8) | lsb;

    return address;
}

uint16_t CPU::read_irq_vector() const
{
    uint8_t lsb {cpu_memory_read(MC::irq_vector_lsb)};
    uint8_t msb {cpu_memory_read(MC::irq_vector_msb)};

    uint16_t address = (msb << 8) | lsb;

    return address;
}

bool CPU::check_for_zero_flag(uint8_t reg) const
{
    return reg == 0x00;
}

bool CPU::check_for_negative_flag(uint8_t reg) const
{
    return (reg & Masks::negative_flag_mask) > 0;
}

bool CPU::check_for_flag_with_mask(uint16_t reg, uint16_t mask) const
{
    return (reg & mask) > 0;
}

bool CPU::check_for_page_crossing(uint16_t address1, uint16_t address2) const
{
    return (address1 & ~Masks::zero_page_mask) != (address2 & ~Masks::zero_page_mask);
}

bool CPU::check_for_sign_change(bool a, bool b, bool c) const
{
    return ((a && b) && !c) || (!(a || b) && c);
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

void CPU::address_mode_immediate()
{
    arg_address = pc;
    pc++;
}

void CPU::address_mode_zero_page()
{
    arg_address = cpu_memory_read(pc);
    pc++;

    arg_address = arg_address & Masks::zero_page_mask;
}

void CPU::address_mode_zero_page_x()
{
    arg_address = cpu_memory_read(pc) + x_reg;
    pc++;

    arg_address = arg_address & Masks::zero_page_mask;
}

void CPU::address_mode_zero_page_y()
{
    arg_address = cpu_memory_read(pc) + y_reg;
    pc++;

    arg_address = arg_address & Masks::zero_page_mask;
}

void CPU::address_mode_relative()
{
    branch_offset = cpu_memory_read(pc);
    pc++;
}

void CPU::address_mode_absolute()
{
    uint8_t lsb {cpu_memory_read(pc)};
    pc++;
    uint8_t msb {cpu_memory_read(pc)};
    pc++;

    arg_address = (msb << 8) | lsb;
}

void CPU::address_mode_absolute_x()
{
    uint8_t lsb {cpu_memory_read(pc)};
    pc++;
    uint8_t msb {cpu_memory_read(pc)};
    pc++;

    uint16_t read_address = (msb << 8) | lsb;
    arg_address = read_address + x_reg;

    if (check_for_page_crossing(arg_address, read_address))
        cycles_queued += 1;

}

void CPU::address_mode_absolute_y()
{
    uint8_t lsb {cpu_memory_read(pc)};
    pc++;
    uint8_t msb {cpu_memory_read(pc)};
    pc++;

    uint16_t read_address = (msb << 8) | lsb;
    arg_address = read_address + y_reg;

    if (check_for_page_crossing(arg_address, read_address))
        cycles_queued += 1;
}

void CPU::address_mode_indirect()
{
    uint8_t lsb {cpu_memory_read(pc)};
    pc++;
    uint8_t msb {cpu_memory_read(pc)};
    pc++;

    uint16_t temp_address = (msb << 8) | lsb;

    // Original 6502 CPU's indirect jump page crossing bug reproduction:
    // https://www.nesdev.org/obelisk-6502-guide/reference.html#JMP
    if (lsb == 0xFF)
        msb = cpu_memory_read(temp_address & 0xFF00);
    else
        msb = cpu_memory_read(temp_address + 1);

    lsb = cpu_memory_read(temp_address);

    arg_address = (msb << 8) | lsb;
}

void CPU::address_mode_indirect_x()
{
    uint16_t temp_address = cpu_memory_read(pc) + x_reg;
    pc++;

    uint8_t lsb {cpu_memory_read(temp_address & Masks::zero_page_mask)};
    uint8_t msb {cpu_memory_read((temp_address + 1) & Masks::zero_page_mask)};

    arg_address = (msb << 8) | lsb;
}

void CPU::address_mode_indirect_y()
{
    uint16_t temp_address = cpu_memory_read(pc);
    pc++;

    uint8_t lsb {cpu_memory_read(temp_address & Masks::zero_page_mask)};
    uint8_t msb {cpu_memory_read((temp_address + 1) & Masks::zero_page_mask)};

    uint16_t read_address = (msb << 8) | lsb;
    arg_address = read_address + y_reg;

    if (check_for_page_crossing(arg_address, read_address))
        cycles_queued += 1;
}


////////////////////
//  Instructions  //
////////////////////

void CPU::ADC()
{
    uint8_t value {cpu_memory_read(arg_address)};
    uint16_t result = static_cast<uint16_t>(acc + value + status.flag.carry);

    bool acc_sign {check_for_flag_with_mask(acc, Masks::negative_flag_mask)};
    bool value_sign {check_for_flag_with_mask(value, Masks::negative_flag_mask)};
    bool result_sign {check_for_flag_with_mask(result, Masks::negative_flag_mask)};

    acc = static_cast<uint8_t>(result);

    status.flag.carry = check_for_flag_with_mask(result, 0xFF00);
    status.flag.zero = check_for_zero_flag(acc);
    status.flag.overflow = check_for_sign_change(acc_sign, value_sign, result_sign);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::AND()
{
    uint8_t value {cpu_memory_read(arg_address)};

    acc = acc & value;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::ASL()
{
    if (curr_instruction.address_mode == Instruction::AddressingMode::accumulator) {
        status.flag.carry = check_for_flag_with_mask(acc, Masks::negative_flag_mask);

        acc = acc << 1;

        status.flag.zero = check_for_zero_flag(acc);
        status.flag.negative = check_for_negative_flag(acc);
    }
    else {
        uint8_t result {cpu_memory_read(arg_address)};
        status.flag.carry = check_for_flag_with_mask(result, Masks::negative_flag_mask);

        result = result << 1;
        cpu_memory_write(arg_address, result);

        status.flag.zero = check_for_zero_flag(result);
        status.flag.negative = check_for_negative_flag(result);
    }
}

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

void CPU::BIT()
{
    uint8_t value {cpu_memory_read(arg_address)};
    uint8_t result = acc & value;

    status.flag.zero = check_for_zero_flag(result);
    status.flag.overflow = check_for_flag_with_mask(value, Masks::overflow_flag_mask);
    status.flag.negative = check_for_negative_flag(value);
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
    uint8_t pc_lsb = static_cast<uint8_t>(pc & Masks::zero_page_mask);
    uint8_t pc_msb = static_cast<uint8_t>(pc >> 8);

    status.flag.brk = 1;
    status.flag.unused = 1;
    status.flag.interrupt = 1;

    cpu_stack_push(pc_msb);
    cpu_stack_push(pc_lsb);
    cpu_stack_push(status.word);

    pc = read_irq_vector();
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

void CPU::CMP()
{
    uint8_t value {cpu_memory_read(arg_address)};

    status.flag.carry = acc >= value;

    value -= acc;

    status.flag.zero = check_for_zero_flag(value);
    status.flag.negative = check_for_negative_flag(value);
}

void CPU::CPX()
{
    uint8_t value {cpu_memory_read(arg_address)};

    status.flag.carry = x_reg >= value;

    value -= x_reg;

    status.flag.zero = check_for_zero_flag(value);
    status.flag.negative = check_for_negative_flag(value);
}

void CPU::CPY()
{
    uint8_t value {cpu_memory_read(arg_address)};

    status.flag.carry = y_reg >= value;

    value -= y_reg;

    status.flag.zero = check_for_zero_flag(value);
    status.flag.negative = check_for_negative_flag(value);
}

void CPU::DEC()
{
    uint8_t value {cpu_memory_read(arg_address)};

    value--;
    cpu_memory_write(arg_address, value);

    status.flag.zero = check_for_zero_flag(value);
    status.flag.negative = check_for_negative_flag(value);
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

void CPU::EOR()
{
    uint8_t value {cpu_memory_read(arg_address)};

    acc = acc ^ value;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::INC()
{
    uint8_t value {cpu_memory_read(arg_address)};

    value++;
    cpu_memory_write(arg_address, value);

    status.flag.zero = check_for_zero_flag(value);
    status.flag.negative = check_for_negative_flag(value);
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

void CPU::JMP()
{
    pc = arg_address;
}

void CPU::JSR()
{
    pc--;

    uint8_t pc_lsb = static_cast<uint8_t>(pc & Masks::zero_page_mask);
    uint8_t pc_msb = static_cast<uint8_t>(pc >> 8);

    cpu_stack_push(pc_msb);
    cpu_stack_push(pc_lsb);

    pc = arg_address;
}

void CPU::LDA()
{
    acc = cpu_memory_read(arg_address);

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::LDX()
{
    x_reg = cpu_memory_read(arg_address);

    status.flag.zero = check_for_zero_flag(x_reg);
    status.flag.negative = check_for_negative_flag(x_reg);
}

void CPU::LDY()
{
    y_reg = cpu_memory_read(arg_address);

    status.flag.zero = check_for_zero_flag(y_reg);
    status.flag.negative = check_for_negative_flag(y_reg);
}

void CPU::LSR()
{
    if (curr_instruction.address_mode == Instruction::AddressingMode::accumulator) {
        status.flag.carry = check_for_flag_with_mask(acc, Masks::carry_flag_mask);

        acc = acc >> 1;

        status.flag.zero = check_for_zero_flag(acc);
        status.flag.negative = check_for_negative_flag(acc);
    }
    else {
        uint8_t result {cpu_memory_read(arg_address)};
        status.flag.carry = check_for_flag_with_mask(result, Masks::carry_flag_mask);

        result = result >> 1;
        cpu_memory_write(arg_address, result);

        status.flag.zero = check_for_zero_flag(result);
        status.flag.negative = check_for_negative_flag(result);
    }
}

void CPU::NOP() {}

void CPU::ORA()
{
    uint8_t value {cpu_memory_read(arg_address)};

    acc = acc | value;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::PHA()
{
    cpu_stack_push(acc);
}

void CPU::PHP()
{
    status.flag.brk = 1;
    status.flag.unused = 1;

    cpu_stack_push(status.word);

    status.flag.brk = 0;
    status.flag.unused = 0;
}

void CPU::PLA()
{
    acc = cpu_stack_pop();

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::PLP()
{
    status.word = cpu_stack_pop();
}

void CPU::ROL()
{
    bool old_carry = status.flag.carry;

    if (curr_instruction.address_mode == Instruction::AddressingMode::accumulator) {
        status.flag.carry = check_for_flag_with_mask(acc, Masks::negative_flag_mask);

        acc = acc << 1;
        acc = acc | old_carry;

        status.flag.zero = check_for_zero_flag(acc);
        status.flag.negative = check_for_negative_flag(acc);
    }
    else {
        uint8_t result {cpu_memory_read(arg_address)};
        status.flag.carry = check_for_flag_with_mask(result, Masks::negative_flag_mask);

        result = result << 1;
        result = result | old_carry;
        cpu_memory_write(arg_address, result);

        status.flag.zero = check_for_zero_flag(result);
        status.flag.negative = check_for_negative_flag(result);
    }
}

void CPU::ROR()
{
    bool old_carry = status.flag.carry;

    if (curr_instruction.address_mode == Instruction::AddressingMode::accumulator) {
        status.flag.carry = check_for_flag_with_mask(acc, Masks::carry_flag_mask);

        acc = acc >> 1;
        acc = acc | (old_carry << 7);

        status.flag.zero = check_for_zero_flag(acc);
        status.flag.negative = check_for_negative_flag(acc);
    }
    else {
        uint8_t result {cpu_memory_read(arg_address)};
        status.flag.carry = check_for_flag_with_mask(result, Masks::carry_flag_mask);

        result = result >> 1;
        result = result | (old_carry << 7);
        cpu_memory_write(arg_address, result);

        status.flag.zero = check_for_zero_flag(result);
        status.flag.negative = check_for_negative_flag(result);
    }
}

void CPU::RTI()
{
    status.word = cpu_stack_pop();

    status.flag.brk = 0;
    status.flag.unused = 0;

    uint8_t pc_lsb {cpu_stack_pop()};
    uint8_t pc_msb {cpu_stack_pop()};

    pc = (pc_msb << 8) | pc_lsb;
}

void CPU::RTS()
{
    uint8_t pc_lsb {cpu_stack_pop()};
    uint8_t pc_msb {cpu_stack_pop()};

    pc = (pc_msb << 8) | pc_lsb;
    pc++;
}

void CPU::SBC()
{
    uint8_t value {cpu_memory_read(arg_address)};
    uint8_t value_neg = static_cast<uint8_t>(~value);
    uint16_t result = static_cast<uint16_t>(acc + value_neg + status.flag.carry);

    bool acc_sign {check_for_flag_with_mask(acc, Masks::negative_flag_mask)};
    bool value_sign {check_for_flag_with_mask(value, Masks::negative_flag_mask)};
    bool result_sign {check_for_flag_with_mask(result, Masks::negative_flag_mask)};

    acc = static_cast<uint8_t>(result);

    status.flag.carry = check_for_flag_with_mask(result, 0xFF00);
    status.flag.zero = check_for_zero_flag(acc);
    status.flag.overflow = check_for_sign_change(acc_sign, value_sign, result_sign);
    status.flag.negative = check_for_negative_flag(acc);
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

void CPU::STA()
{
    cpu_memory_write(arg_address, acc);
}

void CPU::STX()
{
    cpu_memory_write(arg_address, x_reg);
}

void CPU::STY()
{
    cpu_memory_write(arg_address, y_reg);
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
    x_reg = cpu_memory_read(MC::stack_offset + stack_ptr);

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
    cpu_memory_write(MC::stack_offset + stack_ptr, x_reg);
}

void CPU::TYA()
{
    acc = y_reg;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::ILL() {}
