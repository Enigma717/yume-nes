#pragma once

#include "./instruction.h"
#include "./cpu_bus.h"

class CPU {
public:
    CPU() = delete;
    CPU(PPU& ppu_ref);

    void connect_bus_with_cartridge(std::shared_ptr<Cartridge> cartridge);
    void connect_bus_with_controller(std::shared_ptr<Controller> controller);

    void perform_cycle(bool debug_mode = false);
    void hard_reset();
    void log_debug_info() const;

private:
    void write_to_bus(std::uint16_t address, std::uint8_t data);
    void stack_push(std::uint8_t data);
    std::uint8_t read_from_bus(std::uint16_t address) const;
    std::uint8_t stack_pop();

    const Instruction* decode_instruction_from_opcode(std::uint8_t opcode) const;
    void next_instruction();
    void execute_addressing_mode();
    void execute_instruction();

    std::uint16_t read_nmi_vector() const;
    std::uint16_t read_reset_vector() const;
    std::uint16_t read_irq_vector() const;
    void interrupt_nmi();
    void interrupt_irq();
    void interrupt_reset();
    void process_interrupt(bool brk_flag_state = false);
    void perform_branching();

    void addressing_mode_immediate();
    void addressing_mode_zero_page();
    void addressing_mode_zero_page_x();
    void addressing_mode_zero_page_y();
    void addressing_mode_relative();
    void addressing_mode_absolute();
    void addressing_mode_absolute_x();
    void addressing_mode_absolute_y();
    void addressing_mode_indirect();
    void addressing_mode_indirect_x();
    void addressing_mode_indirect_y();

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

    CPUBus memory_bus;

    union Status {
        struct {
            std::uint8_t carry     : 1;
            std::uint8_t zero      : 1;
            std::uint8_t interrupt : 1;
            std::uint8_t decimal   : 1;
            std::uint8_t brk       : 1;
            std::uint8_t unused    : 1;
            std::uint8_t overflow  : 1;
            std::uint8_t negative  : 1;
        } flag;

        std::uint8_t word {0x34u};
    };

    std::uint8_t acc {0x00u};
    std::uint8_t x_reg {0x00u};
    std::uint8_t y_reg {0x00u};
    std::uint8_t stack_ptr {0xFDu};
    std::uint16_t pc {0x8000u};
    Status status {};

    std::uint16_t branch_offset {0x0000u};
    std::uint16_t arg_address {0x0000u};
    int cycles_queued {0};
    int cycles_executed {0};

    const Instruction* current_instruction {&Lookup::instructions_table[113]};
};
