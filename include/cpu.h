////////////////////////////////////////////////////////////////////////////
//  Main reference: https://www.nesdev.org/obelisk-6502-guide/index.html  //
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "./instruction.h"

#include <memory>
#include <vector>


class Memory;
class Cartridge;
class PPU;

using MemoryPtr = std::weak_ptr<Memory>;
using CartridgePtr = std::weak_ptr<Cartridge>;


class CPU {
public:
    CPU() = delete;
    CPU(PPU& ppu_ref);


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

    uint8_t  acc {0x00};
    uint8_t  x_reg {0x00};
    uint8_t  y_reg {0x00};
    uint8_t  stack_ptr {0xFD};
    uint16_t pc {0x8000};
    Status   status {};

    uint16_t    branch_offset {0x0000};
    uint16_t    arg_address {0x0000};
    int         cycles_queued {0};
    int         cycles_executed {0};
    Instruction curr_instruction {};


    void         connect_with_memory(std::shared_ptr<Memory> ram);
    void         connect_with_cartridge(std::shared_ptr<Cartridge> cartridge);
    MemoryPtr    get_memory_pointer() const;
    CartridgePtr get_cartridge_pointer() const;

    void    memory_write(uint16_t address, uint8_t value) const;
    uint8_t memory_read(uint16_t address) const;
    void    stack_push(uint8_t value);
    uint8_t stack_pop();

    void        perform_cycle(bool debug_mode = false);
    void        next_instruction();
    void        exec_address_mode();
    void        exec_instruction();
    Instruction deduce_instruction_from_opcode(uint8_t opcode) const;

    void interrupt_nmi();
    void interrupt_irq();
    void interrupt_reset();
    void hard_reset();
    void log_debug_info();

    /////  Addressing modes  /////
    void address_mode_immediate();
    void address_mode_zero_page();
    void address_mode_zero_page_x();
    void address_mode_zero_page_y();
    void address_mode_relative();
    void address_mode_absolute();
    void address_mode_absolute_x();
    void address_mode_absolute_y();
    void address_mode_indirect();
    void address_mode_indirect_x();
    void address_mode_indirect_y();

    /////  Instructions  /////
    void ADC(); void AND(); void ASL();
    void BCC(); void BCS(); void BEQ();
    void BIT(); void BMI(); void BNE();
    void BPL(); void BRK(); void BVC();
    void BVS(); void CLC(); void CLD();
    void CLI(); void CLV(); void CMP();
    void CPX(); void CPY(); void DEC();
    void DEX(); void DEY(); void EOR();
    void INC(); void INX(); void INY();
    void JMP(); void JSR(); void LDA();
    void LDX(); void LDY(); void LSR();
    void NOP(); void ORA(); void PHA();
    void PHP(); void PLA(); void PLP();
    void ROL(); void ROR(); void RTI();
    void RTS(); void SBC(); void SEC();
    void SED(); void SEI(); void STA();
    void STX(); void STY(); void TAX();
    void TAY(); void TSX(); void TXA();
    void TXS(); void TYA(); void ILL();

private:
    MemoryPtr ram_ptr {};
    CartridgePtr cartridge_ptr {};
    PPU& ppu_ref;


    uint16_t read_nmi_vector() const;
    uint16_t read_reset_vector() const;
    uint16_t read_irq_vector() const;

    bool check_for_zero_flag(uint8_t reg) const;
    bool check_for_negative_flag(uint8_t reg) const;
    bool check_for_flag_with_mask(uint16_t reg, uint16_t mask) const;
    bool check_for_page_crossing(uint16_t old_address, uint16_t new_address) const;
    bool check_for_sign_change(bool a, bool b, bool c) const;

    void process_interrupt(bool brk_flag_state = 0);
    void perform_branching();
};


namespace Lookup
{
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;

    static const std::vector<Instruction> instructions_table {
        {MN::AAC, AM::immediate, 0x0B, 2, 2}, {MN::AAC, AM::immediate, 0x2B, 2, 3},
        {MN::AAX, AM::zero_page, 0x87, 2, 3}, {MN::AAX, AM::zero_page_y, 0x97, 2, 4},
        {MN::AAX, AM::absolute, 0x8F, 3, 4}, {MN::AAX, AM::indirect_x, 0x83, 2, 6},
        {MN::ADC, AM::immediate, 0x69, 2, 2}, {MN::ADC, AM::zero_page, 0x65, 2, 3},
        {MN::ADC, AM::zero_page_x, 0x75, 2, 4}, {MN::ADC, AM::absolute, 0x6D, 3, 4},
        {MN::ADC, AM::absolute_x, 0x7D, 3, 4}, {MN::ADC, AM::absolute_y, 0x79, 3, 4},
        {MN::ADC, AM::indirect_x, 0x61, 2, 6}, {MN::ADC, AM::indirect_y, 0x71, 2, 5},
        {MN::AND, AM::immediate, 0x29, 2, 2}, {MN::AND, AM::zero_page, 0x25, 2, 3},
        {MN::AND, AM::zero_page_x, 0x35, 2, 4}, {MN::AND, AM::absolute, 0x2D, 3, 4},
        {MN::AND, AM::absolute_x, 0x3D, 3, 4}, {MN::AND, AM::absolute_y, 0x39, 3, 4},
        {MN::AND, AM::indirect_x, 0x21, 2, 6}, {MN::AND, AM::indirect_y, 0x31, 2, 5},
        {MN::ARR, AM::immediate, 0x6B, 2, 2}, {MN::ASL, AM::accumulator, 0x0A, 1, 2},
        {MN::ASL, AM::zero_page, 0x06, 2, 5}, {MN::ASL, AM::zero_page_x, 0x16, 2, 6},
        {MN::ASL, AM::absolute, 0x0E, 3, 6}, {MN::ASL, AM::absolute_x, 0x1E, 3, 7},
        {MN::ASR, AM::immediate, 0x4B, 2, 2}, {MN::ATX, AM::immediate, 0xAB, 2, 2},
        {MN::AXA, AM::absolute_y, 0x9F, 3, 5}, {MN::AXA, AM::indirect_y, 0x93, 2, 6},
        {MN::AXS, AM::immediate, 0xCB, 2, 2}, {MN::BCC, AM::relative, 0x90, 2, 2},
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
        {MN::DCP, AM::zero_page, 0xC7, 2, 5}, {MN::DCP, AM::zero_page_x, 0xD7, 2, 6},
        {MN::DCP, AM::absolute, 0xCF, 3, 6}, {MN::DCP, AM::absolute_x, 0xDF, 3, 7},
        {MN::DCP, AM::absolute_y, 0xDB, 3, 7}, {MN::DCP, AM::indirect_x, 0xC3, 2, 8},
        {MN::DCP, AM::indirect_y, 0xD3, 2, 8}, {MN::DEC, AM::zero_page, 0xC6, 2, 5},
        {MN::DEC, AM::zero_page_x, 0xD6, 2, 6}, {MN::DEC, AM::absolute, 0xCE, 3, 6},
        {MN::DEC, AM::absolute_x, 0xDE, 3, 7}, {MN::DEX, AM::implied, 0xCA, 1, 2},
        {MN::DEY, AM::implied, 0x88, 1, 2}, {MN::DOP, AM::immediate, 0x80, 2, 2},
        {MN::DOP, AM::immediate, 0x82, 2, 2}, {MN::DOP, AM::immediate, 0x89, 2, 2},
        {MN::DOP, AM::immediate, 0xC2, 2, 2}, {MN::DOP, AM::immediate, 0xE2, 2, 2},
        {MN::DOP, AM::zero_page, 0x04, 2, 3}, {MN::DOP, AM::zero_page, 0x44, 2, 3},
        {MN::DOP, AM::zero_page, 0x64, 2, 3}, {MN::DOP, AM::zero_page_x, 0x14, 2, 4},
        {MN::DOP, AM::zero_page_x, 0x34, 2, 4}, {MN::DOP, AM::zero_page_x, 0x54, 2, 4},
        {MN::DOP, AM::zero_page_x, 0x74, 2, 4}, {MN::DOP, AM::zero_page_x, 0xD4, 2, 4},
        {MN::DOP, AM::zero_page_x, 0xF4, 2, 4}, {MN::EOR, AM::immediate, 0x49, 2, 2},
        {MN::EOR, AM::zero_page, 0x45, 2, 3}, {MN::EOR, AM::zero_page_x, 0x55, 2, 4},
        {MN::EOR, AM::absolute, 0x4D, 3, 4}, {MN::EOR, AM::absolute_x, 0x5D, 3, 4},
        {MN::EOR, AM::absolute_y, 0x59, 3, 4}, {MN::EOR, AM::indirect_x, 0x41, 2, 6},
        {MN::EOR, AM::indirect_y, 0x51, 2, 5}, {MN::INC, AM::zero_page, 0xE6, 2, 5},
        {MN::INC, AM::zero_page_x, 0xF6, 2, 6}, {MN::INC, AM::absolute, 0xEE, 3, 6},
        {MN::INC, AM::absolute_x, 0xFE, 3, 7}, {MN::INX, AM::implied, 0xE8, 1, 2},
        {MN::INY, AM::implied, 0xC8, 1, 2}, {MN::ISC, AM::zero_page, 0xE7, 2, 5},
        {MN::ISC, AM::zero_page_x, 0xF7, 2, 6}, {MN::ISC, AM::absolute, 0xEF, 3, 6},
        {MN::ISC, AM::absolute_x, 0xFF, 3, 7}, {MN::ISC, AM::absolute_y, 0xFB, 3, 7},
        {MN::ISC, AM::indirect_x, 0xE3, 2, 8}, {MN::ISC, AM::indirect_y, 0xF3, 2, 8},
        {MN::JMP, AM::absolute, 0x4C, 3, 3}, {MN::JMP, AM::indirect, 0x6C, 3, 5},
        {MN::JSR, AM::absolute, 0x20, 3, 6}, {MN::KIL, AM::implied, 0x02, 1, 1},
        {MN::KIL, AM::implied, 0x12, 1, 1}, {MN::KIL, AM::implied, 0x22, 1, 1},
        {MN::KIL, AM::implied, 0x32, 1, 1}, {MN::KIL, AM::implied, 0x42, 1, 1},
        {MN::KIL, AM::implied, 0x52, 1, 1}, {MN::KIL, AM::implied, 0x62, 1, 1},
        {MN::KIL, AM::implied, 0x72, 1, 1}, {MN::KIL, AM::implied, 0x92, 1, 1},
        {MN::KIL, AM::implied, 0xB2, 1, 1}, {MN::KIL, AM::implied, 0xD2, 1, 1},
        {MN::KIL, AM::implied, 0xF2, 1, 1}, {MN::LAR, AM::absolute_y, 0xBB, 3, 4},
        {MN::LAX, AM::zero_page, 0xA7, 2, 3}, {MN::LAX, AM::zero_page_y, 0xB7, 2, 4},
        {MN::LAX, AM::absolute, 0xAF, 3, 4}, {MN::LAX, AM::absolute_y, 0xBF, 3, 4},
        {MN::LAX, AM::indirect_x, 0xA3, 2, 6}, {MN::LAX, AM::indirect_y, 0xB3, 2, 5},
        {MN::LDA, AM::immediate, 0xA9, 2, 2}, {MN::LDA, AM::zero_page, 0xA5, 2, 3},
        {MN::LDA, AM::zero_page_x, 0xB5, 2, 4}, {MN::LDA, AM::absolute, 0xAD, 3, 4},
        {MN::LDA, AM::absolute_x, 0xBD, 3, 4}, {MN::LDA, AM::absolute_y, 0xB9, 3, 4},
        {MN::LDA, AM::indirect_x, 0xA1, 2, 6}, {MN::LDA, AM::indirect_y, 0xB1, 2, 5},
        {MN::LDX, AM::immediate, 0xA2, 2, 2}, {MN::LDX, AM::zero_page, 0xA6, 2, 3},
        {MN::LDX, AM::zero_page_y, 0xB6, 2, 4}, {MN::LDX, AM::absolute, 0xAE, 3, 4},
        {MN::LDX, AM::absolute_y, 0xBE, 3, 4}, {MN::LDY, AM::immediate, 0xA0, 2, 2},
        {MN::LDY, AM::zero_page, 0xA4, 2, 3}, {MN::LDY, AM::zero_page_x, 0xB4, 2, 4},
        {MN::LDY, AM::absolute, 0xAC, 3, 4}, {MN::LDY, AM::absolute_x, 0xBC, 3, 4},
        {MN::LSR, AM::accumulator, 0x4A, 1, 2}, {MN::LSR, AM::zero_page, 0x46, 2, 5},
        {MN::LSR, AM::zero_page_x, 0x56, 2, 6}, {MN::LSR, AM::absolute, 0x4E, 3, 6},
        {MN::LSR, AM::absolute_x, 0x5E, 3, 7}, {MN::NOP, AM::implied, 0x1A, 1, 2},
        {MN::NOP, AM::implied, 0x3A, 1, 2}, {MN::NOP, AM::implied, 0x5A, 1, 2},
        {MN::NOP, AM::implied, 0x7A, 1, 2}, {MN::NOP, AM::implied, 0xDA, 1, 2},
        {MN::NOP, AM::implied, 0xEA, 1, 2}, {MN::NOP, AM::implied, 0xFA, 1, 2},
        {MN::ORA, AM::immediate, 0x09, 2, 2}, {MN::ORA, AM::zero_page, 0x05, 2, 3},
        {MN::ORA, AM::zero_page_x, 0x15, 2, 4}, {MN::ORA, AM::absolute, 0x0D, 3, 4},
        {MN::ORA, AM::absolute_x, 0x1D, 3, 4}, {MN::ORA, AM::absolute_y, 0x19, 3, 4},
        {MN::ORA, AM::indirect_x, 0x01, 2, 6}, {MN::ORA, AM::indirect_y, 0x11, 2, 5},
        {MN::PHA, AM::implied, 0x48, 1, 3}, {MN::PHP, AM::implied, 0x08, 1, 3},
        {MN::PLA, AM::implied, 0x68, 1, 4}, {MN::PLP, AM::implied, 0x28, 1, 4},
        {MN::RLA, AM::zero_page, 0x27, 2, 5}, {MN::RLA, AM::zero_page_x, 0x37, 2, 6},
        {MN::RLA, AM::absolute, 0x2F, 3, 6}, {MN::RLA, AM::absolute_x, 0x3F, 3, 7},
        {MN::RLA, AM::absolute_y, 0x3B, 3, 7}, {MN::RLA, AM::indirect_x, 0x23, 2, 8},
        {MN::RLA, AM::indirect_y, 0x33, 2, 8}, {MN::ROL, AM::accumulator, 0x2A, 1, 2},
        {MN::ROL, AM::zero_page, 0x26, 2, 5}, {MN::ROL, AM::zero_page_x, 0x36, 2, 6},
        {MN::ROL, AM::absolute, 0x2E, 3, 6}, {MN::ROL, AM::absolute_x, 0x3E, 3, 7},
        {MN::ROR, AM::accumulator, 0x6A, 1, 2}, {MN::ROR, AM::zero_page, 0x66, 2, 5},
        {MN::ROR, AM::zero_page_x, 0x76, 2, 6}, {MN::ROR, AM::absolute, 0x6E, 3, 6},
        {MN::ROR, AM::absolute_x, 0x7E, 3, 7}, {MN::RRA, AM::zero_page, 0x67, 2, 5},
        {MN::RRA, AM::zero_page_x, 0x77, 2, 6}, {MN::RRA, AM::absolute, 0x6F, 3, 6},
        {MN::RRA, AM::absolute_x, 0x7F, 3, 7}, {MN::RRA, AM::absolute_y, 0x7B, 3, 7},
        {MN::RRA, AM::indirect_x, 0x63, 2, 8}, {MN::RRA, AM::indirect_y, 0x73, 2, 8},
        {MN::RTI, AM::implied, 0x40, 1, 6}, {MN::RTS, AM::implied, 0x60, 1, 6},
        {MN::SBC, AM::immediate, 0xE9, 2, 2}, {MN::SBC, AM::immediate, 0xEB, 2, 2},
        {MN::SBC, AM::zero_page, 0xE5, 2, 3}, {MN::SBC, AM::zero_page_x, 0xF5, 2, 4},
        {MN::SBC, AM::absolute, 0xED, 3, 4}, {MN::SBC, AM::absolute_x, 0xFD, 3, 4},
        {MN::SBC, AM::absolute_y, 0xF9, 3, 4}, {MN::SBC, AM::indirect_x, 0xE1, 2, 6},
        {MN::SBC, AM::indirect_y, 0xF1, 2, 5}, {MN::SEC, AM::implied, 0x38, 1, 2},
        {MN::SED, AM::implied, 0xF8, 1, 2}, {MN::SEI, AM::implied, 0x78, 1, 2},
        {MN::SLO, AM::zero_page, 0x07, 2, 5}, {MN::SLO, AM::zero_page_x, 0x17, 2, 6},
        {MN::SLO, AM::absolute, 0x0F, 3, 6}, {MN::SLO, AM::absolute_x, 0x1F, 3, 7},
        {MN::SLO, AM::absolute_y, 0x1B, 3, 7}, {MN::SLO, AM::indirect_x, 0x03, 2, 8},
        {MN::SLO, AM::indirect_y, 0x13, 2, 8}, {MN::SRE, AM::zero_page, 0x47, 2, 5},
        {MN::SRE, AM::zero_page_x, 0x57, 2, 6}, {MN::SRE, AM::absolute, 0x4F, 3, 6},
        {MN::SRE, AM::absolute_x, 0x5F, 3, 7}, {MN::SRE, AM::absolute_y, 0x5B, 3, 7},
        {MN::SRE, AM::indirect_x, 0x43, 2, 8}, {MN::SRE, AM::indirect_y, 0x53, 2, 8},
        {MN::STA, AM::zero_page, 0x85, 2, 3}, {MN::STA, AM::zero_page_x, 0x95, 2, 4},
        {MN::STA, AM::absolute, 0x8D, 3, 4}, {MN::STA, AM::absolute_x, 0x9D, 3, 5},
        {MN::STA, AM::absolute_y, 0x99, 3, 5}, {MN::STA, AM::indirect_x, 0x81, 2, 6},
        {MN::STA, AM::indirect_y, 0x91, 2, 6}, {MN::STX, AM::zero_page, 0x86, 2, 3},
        {MN::STX, AM::zero_page_y, 0x96, 2, 4}, {MN::STX, AM::absolute, 0x8E, 3, 4},
        {MN::STY, AM::zero_page, 0x84, 2, 3}, {MN::STY, AM::zero_page_x, 0x94, 2, 4},
        {MN::STY, AM::absolute, 0x8C, 3, 4}, {MN::SXA, AM::absolute_y, 0x9E, 3, 5},
        {MN::SYA, AM::absolute_x, 0x9C, 3, 5}, {MN::TAX, AM::implied, 0xAA, 1, 2},
        {MN::TAY, AM::implied, 0xA8, 1, 2}, {MN::TOP, AM::absolute, 0x0C, 3, 4},
        {MN::TOP, AM::absolute_x, 0x1C, 3, 4}, {MN::TOP, AM::absolute_x, 0x3C, 3, 4},
        {MN::TOP, AM::absolute_x, 0x5C, 3, 4}, {MN::TOP, AM::absolute_x, 0x7C, 3, 4},
        {MN::TOP, AM::absolute_x, 0xDC, 3, 4}, {MN::TOP, AM::absolute_x, 0xFC, 3, 4},
        {MN::TSX, AM::implied, 0xBA, 1, 2}, {MN::TXA, AM::implied, 0x8A, 1, 2},
        {MN::TXS, AM::implied, 0x9A, 1, 2}, {MN::TYA, AM::implied, 0x98, 1, 2},
        {MN::XAA, AM::immediate, 0x8B, 2, 2}, {MN::XAS, AM::absolute_y, 0x9B, 3, 5}
    };
}
