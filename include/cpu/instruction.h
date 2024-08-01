#pragma once

#include <array>
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

    MnemonicName mnemonic {MnemonicName::KIL};
    AddressingMode addressing_mode {AddressingMode::implied};
    std::uint8_t opcode {0x02u};
    int bytes {1};
    int cycles {1};

    bool operator==(const Instruction& rhs) const
    {
        return mnemonic == rhs.mnemonic &&
            addressing_mode == rhs.addressing_mode &&
            opcode == rhs.opcode &&
            bytes == rhs.bytes &&
            cycles == rhs.cycles;
    }
};

namespace Lookup
{
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;

    constexpr std::array<Instruction, 256uz> instructions_table {{
        {MN::AAC, AM::immediate, 0x0Bu, 2, 2}, {MN::AAC, AM::immediate, 0x2Bu, 2, 3},
        {MN::AAX, AM::zero_page, 0x87u, 2, 3}, {MN::AAX, AM::zero_page_y, 0x97u, 2, 4},
        {MN::AAX, AM::absolute, 0x8Fu, 3, 4}, {MN::AAX, AM::indirect_x, 0x83u, 2, 6},
        {MN::ADC, AM::immediate, 0x69u, 2, 2}, {MN::ADC, AM::zero_page, 0x65u, 2, 3},
        {MN::ADC, AM::zero_page_x, 0x75u, 2, 4}, {MN::ADC, AM::absolute, 0x6Du, 3, 4},
        {MN::ADC, AM::absolute_x, 0x7Du, 3, 4}, {MN::ADC, AM::absolute_y, 0x79u, 3, 4},
        {MN::ADC, AM::indirect_x, 0x61u, 2, 6}, {MN::ADC, AM::indirect_y, 0x71u, 2, 5},
        {MN::AND, AM::immediate, 0x29u, 2, 2}, {MN::AND, AM::zero_page, 0x25u, 2, 3},
        {MN::AND, AM::zero_page_x, 0x35u, 2, 4}, {MN::AND, AM::absolute, 0x2Du, 3, 4},
        {MN::AND, AM::absolute_x, 0x3Du, 3, 4}, {MN::AND, AM::absolute_y, 0x39u, 3, 4},
        {MN::AND, AM::indirect_x, 0x21u, 2, 6}, {MN::AND, AM::indirect_y, 0x31u, 2, 5},
        {MN::ARR, AM::immediate, 0x6Bu, 2, 2}, {MN::ASL, AM::accumulator, 0x0Au, 1, 2},
        {MN::ASL, AM::zero_page, 0x06u, 2, 5}, {MN::ASL, AM::zero_page_x, 0x16u, 2, 6},
        {MN::ASL, AM::absolute, 0x0Eu, 3, 6}, {MN::ASL, AM::absolute_x, 0x1Eu, 3, 7},
        {MN::ASR, AM::immediate, 0x4Bu, 2, 2}, {MN::ATX, AM::immediate, 0xABu, 2, 2},
        {MN::AXA, AM::absolute_y, 0x9Fu, 3, 5}, {MN::AXA, AM::indirect_y, 0x93u, 2, 6},
        {MN::AXS, AM::immediate, 0xCBu, 2, 2}, {MN::BCC, AM::relative, 0x90u, 2, 2},
        {MN::BCS, AM::relative, 0xB0u, 2, 2}, {MN::BEQ, AM::relative, 0xF0u, 2, 2},
        {MN::BIT, AM::zero_page, 0x24u, 2, 3}, {MN::BIT, AM::absolute, 0x2Cu, 3, 4},
        {MN::BMI, AM::relative, 0x30u, 2, 2}, {MN::BNE, AM::relative, 0xD0u, 2, 2},
        {MN::BPL, AM::relative, 0x10u, 2, 2}, {MN::BRK, AM::implied, 0x00u, 1, 7},
        {MN::BVC, AM::relative, 0x50u, 2, 2}, {MN::BVS, AM::relative, 0x70u, 2, 2},
        {MN::CLC, AM::implied, 0x18u, 1, 2}, {MN::CLD, AM::implied, 0xD8u, 1, 2},
        {MN::CLI, AM::implied, 0x58u, 1, 2}, {MN::CLV, AM::implied, 0xB8u, 1, 2},
        {MN::CMP, AM::immediate, 0xC9u, 2, 2}, {MN::CMP, AM::zero_page, 0xC5u, 2, 3},
        {MN::CMP, AM::zero_page_x, 0xD5u, 2, 4}, {MN::CMP, AM::absolute, 0xCDu, 3, 4},
        {MN::CMP, AM::absolute_x, 0xDDu, 3, 4}, {MN::CMP, AM::absolute_y, 0xD9u, 3, 4},
        {MN::CMP, AM::indirect_x, 0xC1u, 2, 6}, {MN::CMP, AM::indirect_y, 0xD1u, 2, 5},
        {MN::CPX, AM::immediate, 0xE0u, 2, 2}, {MN::CPX, AM::zero_page, 0xE4u, 2, 3},
        {MN::CPX, AM::absolute, 0xECu, 3, 4}, {MN::CPY, AM::immediate, 0xC0u, 2, 2},
        {MN::CPY, AM::zero_page, 0xC4u, 2, 3}, {MN::CPY, AM::absolute, 0xCCu, 3, 4},
        {MN::DCP, AM::zero_page, 0xC7u, 2, 5}, {MN::DCP, AM::zero_page_x, 0xD7u, 2, 6},
        {MN::DCP, AM::absolute, 0xCFu, 3, 6}, {MN::DCP, AM::absolute_x, 0xDFu, 3, 7},
        {MN::DCP, AM::absolute_y, 0xDBu, 3, 7}, {MN::DCP, AM::indirect_x, 0xC3u, 2, 8},
        {MN::DCP, AM::indirect_y, 0xD3u, 2, 8}, {MN::DEC, AM::zero_page, 0xC6u, 2, 5},
        {MN::DEC, AM::zero_page_x, 0xD6u, 2, 6}, {MN::DEC, AM::absolute, 0xCEu, 3, 6},
        {MN::DEC, AM::absolute_x, 0xDEu, 3, 7}, {MN::DEX, AM::implied, 0xCAu, 1, 2},
        {MN::DEY, AM::implied, 0x88u, 1, 2}, {MN::DOP, AM::immediate, 0x80u, 2, 2},
        {MN::DOP, AM::immediate, 0x82u, 2, 2}, {MN::DOP, AM::immediate, 0x89u, 2, 2},
        {MN::DOP, AM::immediate, 0xC2u, 2, 2}, {MN::DOP, AM::immediate, 0xE2u, 2, 2},
        {MN::DOP, AM::zero_page, 0x04u, 2, 3}, {MN::DOP, AM::zero_page, 0x44u, 2, 3},
        {MN::DOP, AM::zero_page, 0x64u, 2, 3}, {MN::DOP, AM::zero_page_x, 0x14u, 2, 4},
        {MN::DOP, AM::zero_page_x, 0x34u, 2, 4}, {MN::DOP, AM::zero_page_x, 0x54u, 2, 4},
        {MN::DOP, AM::zero_page_x, 0x74u, 2, 4}, {MN::DOP, AM::zero_page_x, 0xD4u, 2, 4},
        {MN::DOP, AM::zero_page_x, 0xF4u, 2, 4}, {MN::EOR, AM::immediate, 0x49u, 2, 2},
        {MN::EOR, AM::zero_page, 0x45u, 2, 3}, {MN::EOR, AM::zero_page_x, 0x55u, 2, 4},
        {MN::EOR, AM::absolute, 0x4Du, 3, 4}, {MN::EOR, AM::absolute_x, 0x5Du, 3, 4},
        {MN::EOR, AM::absolute_y, 0x59u, 3, 4}, {MN::EOR, AM::indirect_x, 0x41u, 2, 6},
        {MN::EOR, AM::indirect_y, 0x51u, 2, 5}, {MN::INC, AM::zero_page, 0xE6u, 2, 5},
        {MN::INC, AM::zero_page_x, 0xF6u, 2, 6}, {MN::INC, AM::absolute, 0xEEu, 3, 6},
        {MN::INC, AM::absolute_x, 0xFEu, 3, 7}, {MN::INX, AM::implied, 0xE8u, 1, 2},
        {MN::INY, AM::implied, 0xC8u, 1, 2}, {MN::ISC, AM::zero_page, 0xE7u, 2, 5},
        {MN::ISC, AM::zero_page_x, 0xF7u, 2, 6}, {MN::ISC, AM::absolute, 0xEFu, 3, 6},
        {MN::ISC, AM::absolute_x, 0xFFu, 3, 7}, {MN::ISC, AM::absolute_y, 0xFBu, 3, 7},
        {MN::ISC, AM::indirect_x, 0xE3u, 2, 8}, {MN::ISC, AM::indirect_y, 0xF3u, 2, 8},
        {MN::JMP, AM::absolute, 0x4Cu, 3, 3}, {MN::JMP, AM::indirect, 0x6Cu, 3, 5},
        {MN::JSR, AM::absolute, 0x20u, 3, 6}, {MN::KIL, AM::implied, 0x02u, 1, 1},
        {MN::KIL, AM::implied, 0x12u, 1, 1}, {MN::KIL, AM::implied, 0x22u, 1, 1},
        {MN::KIL, AM::implied, 0x32u, 1, 1}, {MN::KIL, AM::implied, 0x42u, 1, 1},
        {MN::KIL, AM::implied, 0x52u, 1, 1}, {MN::KIL, AM::implied, 0x62u, 1, 1},
        {MN::KIL, AM::implied, 0x72u, 1, 1}, {MN::KIL, AM::implied, 0x92u, 1, 1},
        {MN::KIL, AM::implied, 0xB2u, 1, 1}, {MN::KIL, AM::implied, 0xD2u, 1, 1},
        {MN::KIL, AM::implied, 0xF2u, 1, 1}, {MN::LAR, AM::absolute_y, 0xBBu, 3, 4},
        {MN::LAX, AM::zero_page, 0xA7u, 2, 3}, {MN::LAX, AM::zero_page_y, 0xB7u, 2, 4},
        {MN::LAX, AM::absolute, 0xAFu, 3, 4}, {MN::LAX, AM::absolute_y, 0xBFu, 3, 4},
        {MN::LAX, AM::indirect_x, 0xA3u, 2, 6}, {MN::LAX, AM::indirect_y, 0xB3u, 2, 5},
        {MN::LDA, AM::immediate, 0xA9u, 2, 2}, {MN::LDA, AM::zero_page, 0xA5u, 2, 3},
        {MN::LDA, AM::zero_page_x, 0xB5u, 2, 4}, {MN::LDA, AM::absolute, 0xADu, 3, 4},
        {MN::LDA, AM::absolute_x, 0xBDu, 3, 4}, {MN::LDA, AM::absolute_y, 0xB9u, 3, 4},
        {MN::LDA, AM::indirect_x, 0xA1u, 2, 6}, {MN::LDA, AM::indirect_y, 0xB1u, 2, 5},
        {MN::LDX, AM::immediate, 0xA2u, 2, 2}, {MN::LDX, AM::zero_page, 0xA6u, 2, 3},
        {MN::LDX, AM::zero_page_y, 0xB6u, 2, 4}, {MN::LDX, AM::absolute, 0xAEu, 3, 4},
        {MN::LDX, AM::absolute_y, 0xBEu, 3, 4}, {MN::LDY, AM::immediate, 0xA0u, 2, 2},
        {MN::LDY, AM::zero_page, 0xA4u, 2, 3}, {MN::LDY, AM::zero_page_x, 0xB4u, 2, 4},
        {MN::LDY, AM::absolute, 0xACu, 3, 4}, {MN::LDY, AM::absolute_x, 0xBCu, 3, 4},
        {MN::LSR, AM::accumulator, 0x4Au, 1, 2}, {MN::LSR, AM::zero_page, 0x46u, 2, 5},
        {MN::LSR, AM::zero_page_x, 0x56u, 2, 6}, {MN::LSR, AM::absolute, 0x4Eu, 3, 6},
        {MN::LSR, AM::absolute_x, 0x5Eu, 3, 7}, {MN::NOP, AM::implied, 0x1Au, 1, 2},
        {MN::NOP, AM::implied, 0x3Au, 1, 2}, {MN::NOP, AM::implied, 0x5Au, 1, 2},
        {MN::NOP, AM::implied, 0x7Au, 1, 2}, {MN::NOP, AM::implied, 0xDAu, 1, 2},
        {MN::NOP, AM::implied, 0xEAu, 1, 2}, {MN::NOP, AM::implied, 0xFAu, 1, 2},
        {MN::ORA, AM::immediate, 0x09u, 2, 2}, {MN::ORA, AM::zero_page, 0x05u, 2, 3},
        {MN::ORA, AM::zero_page_x, 0x15u, 2, 4}, {MN::ORA, AM::absolute, 0x0Du, 3, 4},
        {MN::ORA, AM::absolute_x, 0x1Du, 3, 4}, {MN::ORA, AM::absolute_y, 0x19u, 3, 4},
        {MN::ORA, AM::indirect_x, 0x01u, 2, 6}, {MN::ORA, AM::indirect_y, 0x11u, 2, 5},
        {MN::PHA, AM::implied, 0x48u, 1, 3}, {MN::PHP, AM::implied, 0x08u, 1, 3},
        {MN::PLA, AM::implied, 0x68u, 1, 4}, {MN::PLP, AM::implied, 0x28u, 1, 4},
        {MN::RLA, AM::zero_page, 0x27u, 2, 5}, {MN::RLA, AM::zero_page_x, 0x37u, 2, 6},
        {MN::RLA, AM::absolute, 0x2Fu, 3, 6}, {MN::RLA, AM::absolute_x, 0x3Fu, 3, 7},
        {MN::RLA, AM::absolute_y, 0x3Bu, 3, 7}, {MN::RLA, AM::indirect_x, 0x23u, 2, 8},
        {MN::RLA, AM::indirect_y, 0x33u, 2, 8}, {MN::ROL, AM::accumulator, 0x2Au, 1, 2},
        {MN::ROL, AM::zero_page, 0x26u, 2, 5}, {MN::ROL, AM::zero_page_x, 0x36u, 2, 6},
        {MN::ROL, AM::absolute, 0x2Eu, 3, 6}, {MN::ROL, AM::absolute_x, 0x3Eu, 3, 7},
        {MN::ROR, AM::accumulator, 0x6Au, 1, 2}, {MN::ROR, AM::zero_page, 0x66u, 2, 5},
        {MN::ROR, AM::zero_page_x, 0x76u, 2, 6}, {MN::ROR, AM::absolute, 0x6Eu, 3, 6},
        {MN::ROR, AM::absolute_x, 0x7Eu, 3, 7}, {MN::RRA, AM::zero_page, 0x67u, 2, 5},
        {MN::RRA, AM::zero_page_x, 0x77u, 2, 6}, {MN::RRA, AM::absolute, 0x6Fu, 3, 6},
        {MN::RRA, AM::absolute_x, 0x7Fu, 3, 7}, {MN::RRA, AM::absolute_y, 0x7Bu, 3, 7},
        {MN::RRA, AM::indirect_x, 0x63u, 2, 8}, {MN::RRA, AM::indirect_y, 0x73u, 2, 8},
        {MN::RTI, AM::implied, 0x40u, 1, 6}, {MN::RTS, AM::implied, 0x60u, 1, 6},
        {MN::SBC, AM::immediate, 0xE9u, 2, 2}, {MN::SBC, AM::immediate, 0xEBu, 2, 2},
        {MN::SBC, AM::zero_page, 0xE5u, 2, 3}, {MN::SBC, AM::zero_page_x, 0xF5u, 2, 4},
        {MN::SBC, AM::absolute, 0xEDu, 3, 4}, {MN::SBC, AM::absolute_x, 0xFDu, 3, 4},
        {MN::SBC, AM::absolute_y, 0xF9u, 3, 4}, {MN::SBC, AM::indirect_x, 0xE1u, 2, 6},
        {MN::SBC, AM::indirect_y, 0xF1u, 2, 5}, {MN::SEC, AM::implied, 0x38u, 1, 2},
        {MN::SED, AM::implied, 0xF8u, 1, 2}, {MN::SEI, AM::implied, 0x78u, 1, 2},
        {MN::SLO, AM::zero_page, 0x07u, 2, 5}, {MN::SLO, AM::zero_page_x, 0x17u, 2, 6},
        {MN::SLO, AM::absolute, 0x0Fu, 3, 6}, {MN::SLO, AM::absolute_x, 0x1Fu, 3, 7},
        {MN::SLO, AM::absolute_y, 0x1Bu, 3, 7}, {MN::SLO, AM::indirect_x, 0x03u, 2, 8},
        {MN::SLO, AM::indirect_y, 0x13u, 2, 8}, {MN::SRE, AM::zero_page, 0x47u, 2, 5},
        {MN::SRE, AM::zero_page_x, 0x57u, 2, 6}, {MN::SRE, AM::absolute, 0x4Fu, 3, 6},
        {MN::SRE, AM::absolute_x, 0x5Fu, 3, 7}, {MN::SRE, AM::absolute_y, 0x5Bu, 3, 7},
        {MN::SRE, AM::indirect_x, 0x43u, 2, 8}, {MN::SRE, AM::indirect_y, 0x53u, 2, 8},
        {MN::STA, AM::zero_page, 0x85u, 2, 3}, {MN::STA, AM::zero_page_x, 0x95u, 2, 4},
        {MN::STA, AM::absolute, 0x8Du, 3, 4}, {MN::STA, AM::absolute_x, 0x9Du, 3, 5},
        {MN::STA, AM::absolute_y, 0x99u, 3, 5}, {MN::STA, AM::indirect_x, 0x81u, 2, 6},
        {MN::STA, AM::indirect_y, 0x91u, 2, 6}, {MN::STX, AM::zero_page, 0x86u, 2, 3},
        {MN::STX, AM::zero_page_y, 0x96u, 2, 4}, {MN::STX, AM::absolute, 0x8Eu, 3, 4},
        {MN::STY, AM::zero_page, 0x84u, 2, 3}, {MN::STY, AM::zero_page_x, 0x94u, 2, 4},
        {MN::STY, AM::absolute, 0x8Cu, 3, 4}, {MN::SXA, AM::absolute_y, 0x9Eu, 3, 5},
        {MN::SYA, AM::absolute_x, 0x9Cu, 3, 5}, {MN::TAX, AM::implied, 0xAAu, 1, 2},
        {MN::TAY, AM::implied, 0xA8u, 1, 2}, {MN::TOP, AM::absolute, 0x0Cu, 3, 4},
        {MN::TOP, AM::absolute_x, 0x1Cu, 3, 4}, {MN::TOP, AM::absolute_x, 0x3Cu, 3, 4},
        {MN::TOP, AM::absolute_x, 0x5Cu, 3, 4}, {MN::TOP, AM::absolute_x, 0x7Cu, 3, 4},
        {MN::TOP, AM::absolute_x, 0xDCu, 3, 4}, {MN::TOP, AM::absolute_x, 0xFCu, 3, 4},
        {MN::TSX, AM::implied, 0xBAu, 1, 2}, {MN::TXA, AM::implied, 0x8Au, 1, 2},
        {MN::TXS, AM::implied, 0x9Au, 1, 2}, {MN::TYA, AM::implied, 0x98u, 1, 2},
        {MN::XAA, AM::immediate, 0x8Bu, 2, 2}, {MN::XAS, AM::absolute_y, 0x9Bu, 3, 5}
    }};
}
