#pragma once

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
        DEX, DEY, EOR,
        INC, INX, INY,
        JMP, JSR, LDA,
        LDX, LDY, LSR,
        NOP, ORA, PHA,
        PHP, PLA, PLP,
        ROL, ROR, RTI,
        RTS, SBC, SEC,
        SED, SEI, STA,
        STX, STY, TAX,
        TAY, TSX, TXA,
        TXS, TYA,
        // Illegal opcodes (subject to future implementation)
        AAC, AAX, ARR,
        ASR, ATX, AXA,
        AXS, DCP, DOP,
        ISC, KIL, LAR,
        LAX, RLA, RRA,
        SLO, SRE, SXA,
        SYA, TOP, XAA,
        XAS
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
    };

    MnemonicName   mnemonic {MnemonicName::KIL};
    AddressingMode address_mode {AddressingMode::implied};
    uint8_t        opcode {0x02};
    int            bytes {1};
    int            cycles {1};

    bool operator==(const Instruction& rhs) const;
};
