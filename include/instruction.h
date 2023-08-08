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
        // TODO
    };
};


#endif
