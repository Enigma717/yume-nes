#ifndef INSTRUCTION_H
#define INSTRUCTION_H


#include <cstdint>
#include <string>
#include <vector>


class Instruction {
public:
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
        indirect_y
    };

    Instruction(std::string, AddressingMode, uint8_t, int, int) noexcept {};

    const std::string    mnemonic {};
    const AddressingMode address_mode {};
    const uint8_t        opcode {0x00};
    const int            bytes {0};
    const int            cycles {0};

    using AM = AddressingMode;
    const std::vector<Instruction> instructions_table {
        {"ADC", AM::immediate, 0x69, 2, 2}, {"ADC", AM::zero_page, 0x65, 2, 3},
        {"ADC", AM::zero_page_x, 0x75, 2, 4}, {"ADC", AM::absolute, 0x6D, 3, 4},
        {"ADC", AM::absolute_x, 0x7D, 3, 4}, {"ADC", AM::absolute_x, 0x79, 3, 4},
        {"ADC", AM::indirect_x, 0x61, 2, 6}, {"ADC", AM::indirect_y, 0x71, 2, 5},
        {"AND", AM::immediate, 0x29, 2, 2}, {"AND", AM::zero_page, 0x25, 2, 3},
        {"AND", AM::zero_page_x, 0x35, 2, 4}, {"AND", AM::absolute, 0x2D, 3, 4},
        {"AND", AM::absolute_x, 0x3D, 3, 4}, {"AND", AM::absolute_y, 0x39, 3, 4},
        {"AND", AM::indirect_x, 0x21, 2, 6}, {"AND", AM::indirect_y, 0x31, 2, 5},
        {"ASL", AM::accumulator, 0x0A, 1, 2}, {"ASL", AM::zero_page, 0x06, 2, 5},
        {"ASL", AM::zero_page_x, 0x16, 2, 6}, {"ASL", AM::absolute, 0x0E, 3, 6},
        {"ASL", AM::absolute_x, 0x1E, 3, 7}, {"BCC", AM::relative, 0x90, 2, 2},
        {"BCS", AM::relative, 0xB0, 2, 2}, {"BEQ", AM::relative, 0xF0, 2, 2},
        {"BIT", AM::zero_page, 0x24, 2, 3}, {"BIT", AM::absolute, 0x2C, 3, 4},
        {"BMI", AM::relative, 0x30, 2, 2}, {"BNE", AM::relative, 0xD0, 2, 2},
        {"BPL", AM::relative, 0x10, 2, 2}, {"BRK", AM::implied, 0x00, 1, 7},
        {"BVC", AM::relative, 0x50, 2, 2}, {"BVS", AM::relative, 0x70, 2, 2},
        {"CLC", AM::implied, 0x18, 1, 2}, {"CLD", AM::implied, 0xD8, 1, 2},
        {"CLI", AM::implied, 0x58, 1, 2}, {"CLV", AM::implied, 0xB8, 1, 2},
        {"CMP", AM::immediate, 0xC9, 2, 2}, {"CMP", AM::zero_page, 0xC5, 2, 3},
        {"CMP", AM::zero_page_x, 0xD5, 2, 4}, {"CMP", AM::absolute, 0xCD, 3, 4},
        {"CMP", AM::absolute_x, 0xDD, 3, 4}, {"CMP", AM::absolute_y, 0xD9, 3, 4},
        {"CMP", AM::indirect_x, 0xC1, 2, 6}, {"CMP", AM::indirect_y, 0xD1, 2, 5},
        {"CPX", AM::immediate, 0xE0, 2, 2}, {"CPX", AM::zero_page, 0xE4, 2, 3},
        {"CPX", AM::absolute, 0xEC, 3, 4}, {"CPY", AM::immediate, 0xC0, 2, 2},
        {"CPY", AM::zero_page, 0xC4, 2, 3}, {"CPY", AM::absolute, 0xCC, 3, 4},
        {"DEC", AM::zero_page, 0xC6, 2, 5}, {"DEC", AM::zero_page_x, 0xD6, 2, 6},
        {"DEC", AM::absolute, 0xCE, 3, 6}, {"DEC", AM::absolute_x, 0xDE, 3, 7},
        {"DEX", AM::implied, 0xCA, 1, 2}, {"DEY", AM::implied, 0x88, 1, 2},
        {"EOR", AM::immediate, 0x49, 2, 2}, {"EOR", AM::zero_page, 0x45, 2, 3},
        {"EOR", AM::zero_page_x, 0x55, 2, 4}, {"EOR", AM::absolute, 0x4D, 3, 4},
        {"EOR", AM::absolute_x, 0x5D, 3, 4}, {"EOR", AM::absolute_y, 0x59, 3, 4},
        {"EOR", AM::indirect_x, 0x41, 2, 6}, {"EOR", AM::indirect_y, 0x51, 2, 5},
        {"INC", AM::zero_page, 0xE6, 2, 5}, {"INC", AM::zero_page_x, 0xF6, 2, 6},
        {"INC", AM::absolute, 0xEE, 3, 6}, {"INC", AM::absolute_x, 0xFE, 3, 7},
        {"INX", AM::implied, 0xE8, 1, 2}, {"INY", AM::implied, 0xC8, 1, 2},
        {"JMP", AM::absolute, 0x4C, 3, 3}, {"JMP", AM::indirect, 0x6C, 3, 5},
        {"JSR", AM::absolute, 0x20, 3, 6}, {"LDA", AM::immediate, 0xA9, 2, 2},
        {"LDA", AM::zero_page, 0xA5, 2, 3}, {"LDA", AM::zero_page_x, 0xB5, 2, 4},
        {"LDA", AM::absolute, 0xAD, 3, 4}, {"LDA", AM::absolute_x, 0xBD, 3, 4},
        {"LDA", AM::absolute_y, 0xB9, 3, 4}, {"LDA", AM::indirect_x, 0xA1, 2, 6},
        {"LDA", AM::indirect_y, 0xB1, 2, 5}, {"LDX", AM::immediate, 0xA2, 2, 2},
        {"LDX", AM::zero_page, 0xA6, 2, 3}, {"LDX", AM::zero_page_y, 0xB6, 2, 4},
        {"LDX", AM::absolute, 0xAE, 3, 4}, {"LDX", AM::absolute_y, 0xBE, 3, 4},
        {"LDY", AM::immediate, 0xA0, 2, 2}, {"LDY", AM::zero_page, 0xA4, 2, 3},
        {"LDY", AM::zero_page_x, 0xB4, 2, 4}, {"LDY", AM::absolute, 0xAC, 3, 4},
        {"LDY", AM::absolute_x, 0xBC, 3, 4}, {"LSR", AM::accumulator, 0x4A, 1, 2},
        {"LSR", AM::zero_page, 0x46, 2, 5}, {"LSR", AM::zero_page_x, 0x56, 2, 6},
        {"LSR", AM::absolute, 0x4E, 3, 6}, {"LSR", AM::absolute_x, 0x5E, 3, 7},
        {"NOP", AM::implied, 0xEA, 1, 2}, {"ORA", AM::immediate, 0x09, 2, 2},
        {"ORA", AM::zero_page, 0x05, 2, 3}, {"ORA", AM::zero_page_x, 0x15, 2, 4},
        {"ORA", AM::absolute, 0x0D, 3, 4}, {"ORA", AM::absolute_x, 0x1D, 3, 4},
        {"ORA", AM::absolute_y, 0x19, 3, 4}, {"ORA", AM::indirect_x, 0x01, 2, 6},
        {"ORA", AM::indirect_y, 0x11, 2, 5}, {"PHA", AM::implied, 0x48, 1, 3},
        {"PHP", AM::implied, 0x08, 1, 3}, {"PLA", AM::implied, 0x68, 1, 4},
        {"PLP", AM::implied, 0x28, 1, 4}, {"ROL", AM::accumulator, 0x2A, 1, 2},
        {"ROL", AM::zero_page, 0x26, 2, 5}, {"ROL", AM::zero_page_x, 0x36, 2, 6},
        {"ROL", AM::absolute, 0x2E, 3, 6}, {"ROL", AM::absolute_x, 0x3E, 3, 7},
        {"ROR", AM::accumulator, 0x6A, 1, 2}, {"ROR", AM::zero_page, 0x66, 2, 5},
        {"ROR", AM::zero_page_x, 0x76, 2, 6}, {"ROR", AM::absolute, 0x6E, 3, 6},
        {"ROR", AM::absolute_x, 0x7E, 3, 7}, {"RTI", AM::implied, 0x40, 1, 6},
        {"RTS", AM::implied, 0x60, 1, 6}, {"SBC", AM::immediate, 0xE9, 2, 2},
        {"SBC", AM::zero_page, 0xE5, 2, 3}, {"SBC", AM::zero_page_x, 0xF5, 2, 4},
        {"SBC", AM::absolute, 0xED, 3, 4}, {"SBC", AM::absolute_x, 0xFD, 3, 4},
        {"SBC", AM::absolute_y, 0xF9, 3, 4}, {"SBC", AM::indirect_x, 0xE1, 2, 6},
        {"SBC", AM::indirect_y, 0xF1, 2, 5}, {"SEC", AM::implied, 0x38, 1, 2},
        {"SED", AM::implied, 0xF8, 1, 2}, {"SEI", AM::implied, 0x78, 1, 2},
        {"STA", AM::zero_page, 0x85, 2, 3}, {"STA", AM::zero_page_x, 0x95, 2, 4},
        {"STA", AM::absolute, 0x8D, 3, 4}, {"STA", AM::absolute_x, 0x9D, 3, 5},
        {"STA", AM::absolute, 0x99, 3, 5}, {"STA", AM::indirect_x, 0x81, 2, 6},
        {"STA", AM::indirect_y, 0x91, 2, 6}, {"STX", AM::zero_page, 0x86, 2, 3},
        {"STX", AM::zero_page_y, 0x96, 2, 4}, {"STX", AM::absolute, 0x8E, 3, 4},
        {"STY", AM::zero_page, 0x84, 2, 3}, {"STY", AM::zero_page_x, 0x94, 2, 4},
        {"STY", AM::zero_page_y, 0x8C, 3, 4}, {"TAX", AM::implied, 0xAA, 1, 2},
        {"TAY", AM::implied, 0xA8, 1, 2}, {"TSX", AM::implied, 0xBA, 1, 2},
        {"TXA", AM::implied, 0x8A, 1, 2}, {"TXS", AM::implied, 0x9A, 1, 2},
        {"TYA", AM::implied, 0x98, 1, 2}
    };
};


#endif
