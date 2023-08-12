#include <algorithm>
#include <cstdint>
#include <memory>

#include "../include/cpu.h"
#include "../include/memory.h"
#include "../include/instruction.h"


void CPU::connect_with_ram(std::shared_ptr<Memory> ram)
{
    ram_ptr = ram;
}

MemoryPtr CPU::get_ram_address() const
{
    return ram_ptr;
}

void CPU::cpu_mem_write(uint16_t address, uint8_t data)
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

Instruction CPU::deduce_instr_from_opcode(uint8_t opcode) const
{
    auto instruction_it = std::find_if(
        Lookup::instructions_table.begin(),
        Lookup::instructions_table.end(),
        [=] (const Instruction& instr) { return instr.opcode == opcode; }
        );

    return *instruction_it;
}

void CPU::exec_cycle()
{
    uint8_t instr_opcode = cpu_mem_read(pc);
    pc++;


    Instruction instr_deduced = deduce_instr_from_opcode(instr_opcode);

    using MN = Instruction::MnemonicName;
    switch (instr_deduced.mnemonic) {
        case MN::BRK: BRK(); break;
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

uint16_t CPU::read_reset_vector()
{
    uint8_t lsb = cpu_mem_read(MemoryConsts::reset_vector_lsb);
    uint8_t msb = cpu_mem_read(MemoryConsts::reset_vector_msb);

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


///////////////
//  Opcodes  //
///////////////

void CPU::BRK()
{
    // TODO
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

void CPU::NOP()
{
    // TODO
}

void CPU::PHA()
{
    cpu_mem_write(MemoryConsts::stack_offset + stack_ptr, acc);
    stack_ptr--;
}

void CPU::PHP()
{
    status.flag.brk = 1;
    status.flag.unused = 1;

    cpu_mem_write(MemoryConsts::stack_offset + stack_ptr, status.word);
    stack_ptr--;

    status.flag.brk = 0;
    status.flag.unused = 0;
}

void CPU::PLA()
{
    stack_ptr++;
    acc = cpu_mem_read(MemoryConsts::stack_offset + stack_ptr);

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::PLP()
{
    stack_ptr++;
    status.word = cpu_mem_read(MemoryConsts::stack_offset + stack_ptr);
}

void CPU::RTI()
{
    // TODO: this is probably wrong

    stack_ptr++;
    status.word = cpu_mem_read(MemoryConsts::stack_offset + stack_ptr);

    status.flag.brk = 0;
    status.flag.unused = 0;

    stack_ptr++;
    pc = cpu_mem_read(MemoryConsts::stack_offset + stack_ptr);
}

void CPU::RTS()
{
    // TODO: same as above

    stack_ptr++;
    pc = cpu_mem_read(MemoryConsts::stack_offset + stack_ptr) - 1;
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
    x_reg = cpu_mem_read(MemoryConsts::stack_offset + stack_ptr);

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
    cpu_mem_write(MemoryConsts::stack_offset + stack_ptr, x_reg);
}

void CPU::TYA()
{
    acc = y_reg;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}
