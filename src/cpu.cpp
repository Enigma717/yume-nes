#include "../include/cpu.h"
#include "../include/memory.h"


void CPU::connect_with_ram(std::shared_ptr<Memory> ram)
{
    CPU::ram_ptr = ram;
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
    acc = 0;
    x_reg = 0;
    y_reg = 0;
    stk_ptr = 0xFD;
    status.word = 0x34;
    ram_ptr.lock()->mem_clear();
}


bool CPU::check_for_carry_flag(uint8_t reg) const
{
    return
}

bool CPU::check_for_zero_flag(uint8_t reg) const
{
    return
}

bool CPU::check_for_overflow_flag(uint8_t reg) const
{
    return
}

bool CPU::check_for_negative_flag(uint8_t reg) const
{
    return
}



//////////////
// Opcodes  //
//////////////

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

}

void CPU::DEY()
{

}

void CPU::INX()
{

}

void CPU::INY()
{

}

void CPU::NOP()
{

}

void CPU::PHA()
{

}

void CPU::PHP()
{

}

void CPU::PLA()
{

}

void CPU::PLP()
{

}

void CPU::RTI()
{

}

void CPU::RTS()
{

}

void CPU::SEC()
{

}

void CPU::SED()
{

}

void CPU::SEI()
{

}

void CPU::TAX()
{

}

void CPU::TAY()
{

}

void CPU::TSX()
{

}

void CPU::TXA()
{

}

void CPU::TXS()
{

}

void CPU::TYA()
{

}
