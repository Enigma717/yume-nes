////////////////////////////////////////////////////////////////////////////
//  Main reference: https://www.nesdev.org/obelisk-6502-guide/index.html  //
////////////////////////////////////////////////////////////////////////////

#ifndef CPU_H
#define CPU_H


#include <cstdint>
#include <memory>


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
    uint16_t pc        {0x0000};
    Status status      {};

    /////////////////////////////////////

    void connect_with_ram(std::shared_ptr<Memory> ram);
    MemoryPtr get_ram_address() const;

    void    cpu_mem_write(uint16_t address, uint8_t data);
    uint8_t cpu_mem_read(uint16_t address) const;
    int     cpu_mem_read_debug(uint16_t address) const;

    void hard_reset();


    /////  Opcodes  /////
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

    /////////////////////////////////////

    bool check_for_carry_flag(uint8_t reg) const;
    bool check_for_zero_flag(uint8_t reg) const;
    bool check_for_overflow_flag(uint8_t reg) const;
    bool check_for_negative_flag(uint8_t reg) const;
};


#endif
