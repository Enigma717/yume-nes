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


void test_adc_imm_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xFF, 0x69, 0x28, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_adc_imm_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x73, 0x69, 0x15, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_adc_imm_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xFF, 0x69, 0x01, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_adc_imm_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x16, 0x69, 0xAD, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_adc_imm_overflow_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x58, 0x69, 0x63, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.overflow == 1);
}

void test_adc_imm_overflow_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xAD, 0x69, 0x05, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.overflow == 0);
}

void test_adc_imm_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x44, 0x69, 0x71, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_adc_imm_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x08, 0x69, 0x09, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_and_imm_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xAA, 0x29, 0x55, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_and_imm_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x25, 0x29, 0xFF, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_and_imm_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x99, 0x29, 0xCD, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_and_imm_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x81, 0x29, 0x67, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_cmp_imm_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x77, 0xC9, 0x51, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_cmp_imm_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x21, 0xC9, 0xA0, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_cmp_imm_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x37, 0xC9, 0x37, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_cmp_imm_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x62, 0xC9, 0x10, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_cmp_imm_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0xC9, 0xEE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_cmp_imm_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x69, 0xC9, 0x90, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_cpx_imm_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x77, 0xE0, 0x51, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_cpx_imm_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x21, 0xE0, 0xA0, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_cpx_imm_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x37, 0xE0, 0x37, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_cpx_imm_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x62, 0xE0, 0x10, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_cpx_imm_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x01, 0xE0, 0xEE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_cpx_imm_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x69, 0xE0, 0x90, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_cpy_imm_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x77, 0xC0, 0x51, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_cpy_imm_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x21, 0xC0, 0xA0, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_cpy_imm_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x37, 0xC0, 0x37, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_cpy_imm_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x62, 0xC0, 0x10, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_cpy_imm_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x01, 0xC0, 0xEE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_cpy_imm_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x69, 0xC0, 0x90, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}


void ut_cpu_immediate_opcodes_flags()
{
    TEST_SET;

    test_adc_imm_carry_flag_set_true();
    test_adc_imm_carry_flag_set_false();
    test_adc_imm_zero_flag_set_true();
    test_adc_imm_zero_flag_set_false();
    test_adc_imm_overflow_flag_set_true();
    test_adc_imm_overflow_flag_set_false();
    test_adc_imm_negative_flag_set_true();
    test_adc_imm_negative_flag_set_false();

    test_and_imm_zero_flag_set_true();
    test_and_imm_zero_flag_set_false();
    test_and_imm_negative_flag_set_true();
    test_and_imm_negative_flag_set_false();

    test_cmp_imm_carry_flag_set_true();
    test_cmp_imm_carry_flag_set_false();
    test_cmp_imm_zero_flag_set_true();
    test_cmp_imm_zero_flag_set_false();
    test_cmp_imm_negative_flag_set_true();
    test_cmp_imm_negative_flag_set_false();

    test_cpx_imm_carry_flag_set_true();
    test_cpx_imm_carry_flag_set_false();
    test_cpx_imm_zero_flag_set_true();
    test_cpx_imm_zero_flag_set_false();
    test_cpx_imm_negative_flag_set_true();
    test_cpx_imm_negative_flag_set_false();

    test_cpy_imm_carry_flag_set_true();
    test_cpy_imm_carry_flag_set_false();
    test_cpy_imm_zero_flag_set_true();
    test_cpy_imm_zero_flag_set_false();
    test_cpy_imm_negative_flag_set_true();
    test_cpy_imm_negative_flag_set_false();
}
