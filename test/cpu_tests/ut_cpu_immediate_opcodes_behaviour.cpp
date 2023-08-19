#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/bus.h"


namespace DebugMode
{
    constexpr bool debug_mode = false;
}

namespace InstrLookup
{
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;

    constexpr Instruction brk_instr {MN::BRK, AM::implied, 0x00, 1, 7};
}


void test_adc_imm_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x9B};
    SystemMemory program_code {0xA9, 0x73, 0x69, 0x28, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_and_imm_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x22};
    SystemMemory program_code {0xA9, 0x33, 0x29, 0xAA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_cmp_imm_behaviour()
{
    SystemBus bus;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA9, 0x77, 0xC9, 0x77, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.word == target_word);
}

void test_cpx_imm_behaviour()
{
    SystemBus bus;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA2, 0x77, 0xE0, 0x77, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.word == target_word);
}

void test_cpy_imm_behaviour()
{
    SystemBus bus;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA0, 0x77, 0xC0, 0x77, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.word == target_word);
}

void test_eor_imm_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x99};
    SystemMemory program_code {0xA9, 0x33, 0x49, 0xAA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_lda_imm_behaviour()
{
    SystemBus bus;
    uint8_t target_value {0xAE};
    SystemMemory program_code {0xA9, 0xAE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.acc == target_value);
}

void test_ldx_imm_behaviour()
{
    SystemBus bus;
    uint8_t target_value {0xCB};
    SystemMemory program_code {0xA2, 0xCB, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.x_reg == target_value);
}

void test_ldy_imm_behaviour()
{
    SystemBus bus;
    uint8_t target_value {0xEA};
    SystemMemory program_code {0xA0, 0xEA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.y_reg == target_value);
}

void test_ora_imm_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0xBB};
    SystemMemory program_code {0xA9, 0x33, 0x09, 0xAA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_sbc_imm_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x4A};
    SystemMemory program_code {0xA9, 0x73, 0xE9, 0x28, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.acc == target_result);
}



void ut_cpu_immediate_opcodes_behaviour()
{
    TEST_SET;

    test_adc_imm_behaviour();
    test_and_imm_behaviour();
    test_cmp_imm_behaviour();
    test_cpx_imm_behaviour();
    test_cpy_imm_behaviour();
    test_eor_imm_behaviour();
    test_lda_imm_behaviour();
    test_ldx_imm_behaviour();
    test_ldy_imm_behaviour();
    test_ora_imm_behaviour();
    test_sbc_imm_behaviour();
}
