////////////////////////////////////////////////////////////////////////////
//  Main reference: https://www.nesdev.org/obelisk-6502-guide/index.html  //
////////////////////////////////////////////////////////////////////////////

#ifndef CPU_H
#define CPU_H


#include <cstdint>
#include <memory>
#include <vector>

#include "../include/instruction.h"


class Memory;

using MemoryPtr = std::weak_ptr<Memory>;


class CPU {
public:
    union Status {
        struct {
            uint8_t carry     : 1;
            uint8_t zero      : 1;
            uint8_t interrupt : 1;
            uint8_t decimal   : 1;
            uint8_t brk       : 1;
            uint8_t unused    : 1;
            uint8_t overflow  : 1;
            uint8_t negative  : 1;
        } flag;

        uint8_t word {0x34};
    };

    uint8_t  acc       {0x00};
    uint8_t  x_reg     {0x00};
    uint8_t  y_reg     {0x00};
    uint8_t  stack_ptr {0xFD};
    uint16_t pc        {0x8000};
    Status   status    {};


    void connect_with_ram(std::shared_ptr<Memory> ram);
    MemoryPtr get_ram_address() const;

    void    cpu_mem_write(uint16_t address, uint8_t data);
    uint8_t cpu_mem_read(uint16_t address) const;
    int     cpu_mem_read_debug(uint16_t address) const;


    Instruction deduce_instr_from_opcode(uint8_t opcode) const;
    void hard_reset();
    void exec_cycle();


    /////  Instructions  /////
    void BRK();

    void CLC();
    void CLD();
    void CLI();
    void CLV();

    void DEX();
    void DEY();

    void INX();
    void INY();

    void NOP();

    void PHA();
    void PHP();
    void PLA();
    void PLP();

    void RTI();
    void RTS();

    void SEC();
    void SED();
    void SEI();

    void TAX();
    void TAY();
    void TSX();
    void TXA();
    void TXS();
    void TYA();

private:
    MemoryPtr ram_ptr {};


    uint16_t initialize_pc();

    bool check_for_zero_flag(uint8_t reg) const;
    bool check_for_negative_flag(uint8_t reg) const;
};


namespace Lookup
{
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;
    static const std::vector<Instruction> instructions_table {
        {MN::ADC, AM::immediate, 0x69, 2, 2}, {MN::ADC, AM::zero_page, 0x65, 2, 3},
        {MN::ADC, AM::zero_page_x, 0x75, 2, 4}, {MN::ADC, AM::absolute, 0x6D, 3, 4},
        {MN::ADC, AM::absolute_x, 0x7D, 3, 4}, {MN::ADC, AM::absolute_y, 0x79, 3, 4},
        {MN::ADC, AM::indirect_x, 0x61, 2, 6}, {MN::ADC, AM::indirect_y, 0x71, 2, 5},
        {MN::AND, AM::immediate, 0x29, 2, 2}, {MN::AND, AM::zero_page, 0x25, 2, 3},
        {MN::AND, AM::zero_page_x, 0x35, 2, 4}, {MN::AND, AM::absolute, 0x2D, 3, 4},
        {MN::AND, AM::absolute_x, 0x3D, 3, 4}, {MN::AND, AM::absolute_y, 0x39, 3, 4},
        {MN::AND, AM::indirect_x, 0x21, 2, 6}, {MN::AND, AM::indirect_y, 0x31, 2, 5},
        {MN::ASL, AM::accumulator, 0x0A, 1, 2}, {MN::ASL, AM::zero_page, 0x06, 2, 5},
        {MN::ASL, AM::zero_page_x, 0x16, 2, 6}, {MN::ASL, AM::absolute, 0x0E, 3, 6},
        {MN::ASL, AM::absolute_x, 0x1E, 3, 7}, {MN::BCC, AM::relative, 0x90, 2, 2},
        {MN::BCS, AM::relative, 0xB0, 2, 2}, {MN::BEQ, AM::relative, 0xF0, 2, 2},
        {MN::BIT, AM::zero_page, 0x24, 2, 3}, {MN::BIT, AM::absolute, 0x2C, 3, 4},
        {MN::BMI, AM::relative, 0x30, 2, 2}, {MN::BNE, AM::relative, 0xD0, 2, 2},
        {MN::BPL, AM::relative, 0x10, 2, 2}, {MN::BRK, AM::implied, 0x00, 1, 7},
        {MN::BVC, AM::relative, 0x50, 2, 2}, {MN::BVS, AM::relative, 0x70, 2, 2},
        {MN::CLC, AM::implied, 0x18, 1, 2}, {MN::CLD, AM::implied, 0xD8, 1, 2},
        {MN::CLI, AM::implied, 0x58, 1, 2}, {MN::CLV, AM::implied, 0xB8, 1, 2},
        {MN::CMP, AM::immediate, 0xC9, 2, 2}, {MN::CMP, AM::zero_page, 0xC5, 2, 3},
        {MN::CMP, AM::zero_page_x, 0xD5, 2, 4}, {MN::CMP, AM::absolute, 0xCD, 3, 4},
        {MN::CMP, AM::absolute_x, 0xDD, 3, 4}, {MN::CMP, AM::absolute_y, 0xD9, 3, 4},
        {MN::CMP, AM::indirect_x, 0xC1, 2, 6}, {MN::CMP, AM::indirect_y, 0xD1, 2, 5},
        {MN::CPX, AM::immediate, 0xE0, 2, 2}, {MN::CPX, AM::zero_page, 0xE4, 2, 3},
        {MN::CPX, AM::absolute, 0xEC, 3, 4}, {MN::CPY, AM::immediate, 0xC0, 2, 2},
        {MN::CPY, AM::zero_page, 0xC4, 2, 3}, {MN::CPY, AM::absolute, 0xCC, 3, 4},
        {MN::DEC, AM::zero_page, 0xC6, 2, 5}, {MN::DEC, AM::zero_page_x, 0xD6, 2, 6},
        {MN::DEC, AM::absolute, 0xCE, 3, 6}, {MN::DEC, AM::absolute_x, 0xDE, 3, 7},
        {MN::DEX, AM::implied, 0xCA, 1, 2}, {MN::DEY, AM::implied, 0x88, 1, 2},
        {MN::EOR, AM::immediate, 0x49, 2, 2}, {MN::EOR, AM::zero_page, 0x45, 2, 3},
        {MN::EOR, AM::zero_page_x, 0x55, 2, 4}, {MN::EOR, AM::absolute, 0x4D, 3, 4},
        {MN::EOR, AM::absolute_x, 0x5D, 3, 4}, {MN::EOR, AM::absolute_y, 0x59, 3, 4},
        {MN::EOR, AM::indirect_x, 0x41, 2, 6}, {MN::EOR, AM::indirect_y, 0x51, 2, 5},
        {MN::INC, AM::zero_page, 0xE6, 2, 5}, {MN::INC, AM::zero_page_x, 0xF6, 2, 6},
        {MN::INC, AM::absolute, 0xEE, 3, 6}, {MN::INC, AM::absolute_x, 0xFE, 3, 7},
        {MN::INX, AM::implied, 0xE8, 1, 2}, {MN::INY, AM::implied, 0xC8, 1, 2},
        {MN::JMP, AM::absolute, 0x4C, 3, 3}, {MN::JMP, AM::indirect, 0x6C, 3, 5},
        {MN::JSR, AM::absolute, 0x20, 3, 6}, {MN::LDA, AM::immediate, 0xA9, 2, 2},
        {MN::LDA, AM::zero_page, 0xA5, 2, 3}, {MN::LDA, AM::zero_page_x, 0xB5, 2, 4},
        {MN::LDA, AM::absolute, 0xAD, 3, 4}, {MN::LDA, AM::absolute_x, 0xBD, 3, 4},
        {MN::LDA, AM::absolute_y, 0xB9, 3, 4}, {MN::LDA, AM::indirect_x, 0xA1, 2, 6},
        {MN::LDA, AM::indirect_y, 0xB1, 2, 5}, {MN::LDX, AM::immediate, 0xA2, 2, 2},
        {MN::LDX, AM::zero_page, 0xA6, 2, 3}, {MN::LDX, AM::zero_page_y, 0xB6, 2, 4},
        {MN::LDX, AM::absolute, 0xAE, 3, 4}, {MN::LDX, AM::absolute_y, 0xBE, 3, 4},
        {MN::LDY, AM::immediate, 0xA0, 2, 2}, {MN::LDY, AM::zero_page, 0xA4, 2, 3},
        {MN::LDY, AM::zero_page_x, 0xB4, 2, 4}, {MN::LDY, AM::absolute, 0xAC, 3, 4},
        {MN::LDY, AM::absolute_x, 0xBC, 3, 4}, {MN::LSR, AM::accumulator, 0x4A, 1, 2},
        {MN::LSR, AM::zero_page, 0x46, 2, 5}, {MN::LSR, AM::zero_page_x, 0x56, 2, 6},
        {MN::LSR, AM::absolute, 0x4E, 3, 6}, {MN::LSR, AM::absolute_x, 0x5E, 3, 7},
        {MN::NOP, AM::implied, 0xEA, 1, 2}, {MN::ORA, AM::immediate, 0x09, 2, 2},
        {MN::ORA, AM::zero_page, 0x05, 2, 3}, {MN::ORA, AM::zero_page_x, 0x15, 2, 4},
        {MN::ORA, AM::absolute, 0x0D, 3, 4}, {MN::ORA, AM::absolute_x, 0x1D, 3, 4},
        {MN::ORA, AM::absolute_y, 0x19, 3, 4}, {MN::ORA, AM::indirect_x, 0x01, 2, 6},
        {MN::ORA, AM::indirect_y, 0x11, 2, 5}, {MN::PHA, AM::implied, 0x48, 1, 3},
        {MN::PHP, AM::implied, 0x08, 1, 3}, {MN::PLA, AM::implied, 0x68, 1, 4},
        {MN::PLP, AM::implied, 0x28, 1, 4}, {MN::ROL, AM::accumulator, 0x2A, 1, 2},
        {MN::ROL, AM::zero_page, 0x26, 2, 5}, {MN::ROL, AM::zero_page_x, 0x36, 2, 6},
        {MN::ROL, AM::absolute, 0x2E, 3, 6}, {MN::ROL, AM::absolute_x, 0x3E, 3, 7},
        {MN::ROR, AM::accumulator, 0x6A, 1, 2}, {MN::ROR, AM::zero_page, 0x66, 2, 5},
        {MN::ROR, AM::zero_page_x, 0x76, 2, 6}, {MN::ROR, AM::absolute, 0x6E, 3, 6},
        {MN::ROR, AM::absolute_x, 0x7E, 3, 7}, {MN::RTI, AM::implied, 0x40, 1, 6},
        {MN::RTS, AM::implied, 0x60, 1, 6}, {MN::SBC, AM::immediate, 0xE9, 2, 2},
        {MN::SBC, AM::zero_page, 0xE5, 2, 3}, {MN::SBC, AM::zero_page_x, 0xF5, 2, 4},
        {MN::SBC, AM::absolute, 0xED, 3, 4}, {MN::SBC, AM::absolute_x, 0xFD, 3, 4},
        {MN::SBC, AM::absolute_y, 0xF9, 3, 4}, {MN::SBC, AM::indirect_x, 0xE1, 2, 6},
        {MN::SBC, AM::indirect_y, 0xF1, 2, 5}, {MN::SEC, AM::implied, 0x38, 1, 2},
        {MN::SED, AM::implied, 0xF8, 1, 2}, {MN::SEI, AM::implied, 0x78, 1, 2},
        {MN::STA, AM::zero_page, 0x85, 2, 3}, {MN::STA, AM::zero_page_x, 0x95, 2, 4},
        {MN::STA, AM::absolute, 0x8D, 3, 4}, {MN::STA, AM::absolute_x, 0x9D, 3, 5},
        {MN::STA, AM::absolute_y, 0x99, 3, 5}, {MN::STA, AM::indirect_x, 0x81, 2, 6},
        {MN::STA, AM::indirect_y, 0x91, 2, 6}, {MN::STX, AM::zero_page, 0x86, 2, 3},
        {MN::STX, AM::zero_page_y, 0x96, 2, 4}, {MN::STX, AM::absolute, 0x8E, 3, 4},
        {MN::STY, AM::zero_page, 0x84, 2, 3}, {MN::STY, AM::zero_page_x, 0x94, 2, 4},
        {MN::STY, AM::absolute, 0x8C, 3, 4}, {MN::TAX, AM::implied, 0xAA, 1, 2},
        {MN::TAY, AM::implied, 0xA8, 1, 2}, {MN::TSX, AM::implied, 0xBA, 1, 2},
        {MN::TXA, AM::implied, 0x8A, 1, 2}, {MN::TXS, AM::implied, 0x9A, 1, 2},
        {MN::TYA, AM::implied, 0x98, 1, 2}
    };
}


#endif
