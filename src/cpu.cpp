#include <algorithm>

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
    status.word = 0x34;
    ram_ptr.lock()->mem_clear();
}


bool CPU::check_for_carry_flag(uint8_t reg) const
{
    return true;
}

bool CPU::check_for_zero_flag(uint8_t reg) const
{
    return reg == 0x00;
}

bool CPU::check_for_overflow_flag(uint8_t reg) const
{
    return true;
}

bool CPU::check_for_negative_flag(uint8_t reg) const
{
    return (reg & (1 << 7)) > 0;
}


Instruction CPU::deduce_instr_from_opcode(uint8_t opcode) const
{
    auto instruction = std::find_if(
        Lookup::instructions_table.begin(),
        Lookup::instructions_table.end(),
        [=] (const Instruction& instr) { return instr.opcode == opcode; }
        );

    return *instruction;
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
    cpu_mem_write(stack_offset + stack_ptr, acc);
    stack_ptr--;
}

void CPU::PHP()
{
    status.flag.brk = 1;
    status.flag.unused = 1;

    cpu_mem_write(stack_offset + stack_ptr, status.word);
    stack_ptr--;

    status.flag.brk = 0;
    status.flag.unused = 0;
}

void CPU::PLA()
{
    stack_ptr++;
    acc = cpu_mem_read(stack_offset + stack_ptr);

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}

void CPU::PLP()
{
    stack_ptr++;
    status.word = cpu_mem_read(stack_offset + stack_ptr);
}

void CPU::RTI()
{
    // TODO: this is probably wrong

    stack_ptr++;
    status.word = cpu_mem_read(stack_offset + stack_ptr);

    status.flag.brk = 0;
    status.flag.unused = 0;

    stack_ptr++;
    pc = cpu_mem_read(stack_offset + stack_ptr);
}

void CPU::RTS()
{
    // TODO: same as above

    stack_ptr++;
    pc = cpu_mem_read(stack_offset + stack_ptr) - 1;
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
    x_reg = cpu_mem_read(stack_offset + stack_ptr);

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
    cpu_mem_write(stack_offset + stack_ptr, x_reg);
}

void CPU::TYA()
{
    acc = y_reg;

    status.flag.zero = check_for_zero_flag(acc);
    status.flag.negative = check_for_negative_flag(acc);
}
