#include "../include/instruction.h"


bool Instruction::operator==(const Instruction& rhs) const
{
    return mnemonic == rhs.mnemonic &&
        address_mode == rhs.address_mode &&
        opcode == rhs.opcode &&
        bytes == rhs.bytes &&
        cycles == rhs.cycles;
}
