#ifndef INSTRUCTION_H
#define INSTRUCTION_H


#include <cstdint>
#include <string>


class Instruction {
public:
    enum class AddressingMode {
        implicit,
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

    std::string    mnemonic {};
    AddressingMode address_mode {};
    uint8_t        opcode {0x00};
    int            bytes {0};
    int            cycles {0};
};


#endif
