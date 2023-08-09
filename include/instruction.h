#ifndef INSTRUCTION_H
#define INSTRUCTION_H


#include <cstdint>
#include <string>


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
        indirect_y,
        illegal
    };

    const std::string    mnemonic {"ILL"};
    const AddressingMode address_mode {AddressingMode::illegal};
    const uint8_t        opcode {0x00};
    const int            bytes {0};
    const int            cycles {0};


    bool operator==(const Instruction& rhs) const;
};


#endif
