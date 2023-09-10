#ifndef INSTRUCTION_H
#define INSTRUCTION_H


#include <cstdint>


class Instruction {
public:
    enum class MnemonicName {
        ADC, AND, ASL,
        BCC, BCS, BEQ,
        BIT, BMI, BNE,
        BPL, BRK, BVC,
        BVS, CLC, CLD,
        CLI, CLV, CMP,
        CPX, CPY, DEC,
        DEX, DEY, DOP,
        EOR, INC, INX,
        INY, JMP, JSR,
        LDA, LDX, LDY,
        LSR, NOP, ORA,
        PHA, PHP, PLA,
        PLP, ROL, ROR,
        RTI, RTS, SBC,
        SEC, SED, SEI,
        STA, STX, STY,
        TAX, TAY, TOP,
        TSX, TXA, TXS,
        TYA, ILL
    };

    enum class AddressingMode {
        implied,
        accumulator,
        immediate,
        zero_page,
        zero_page_x,
        zero_page_y,
        relative,
        absolute,
        absolute_x,
        absolute_y,
        indirect,
        indirect_x,
        indirect_y,
        illegal
    };

    MnemonicName   mnemonic {MnemonicName::ILL};
    AddressingMode address_mode {AddressingMode::illegal};
    uint8_t        opcode {0x02};
    int            bytes {1};
    int            cycles {1};

    bool operator==(const Instruction& rhs) const;
};


#endif
