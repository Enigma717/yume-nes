#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/system.h"


void test_adc_aby_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x9C};
    SystemMemory program_code {0xA0, 0x91, 0xA9, 0x28, 0x8D, 0xB2, 0x61, 0xA9, 0x73, 0x79, 0x21, 0x61, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_adc_aby_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x9B};
    SystemMemory program_code {0xA0, 0x92, 0xA9, 0x28, 0x8D, 0xB4, 0x62, 0xA9, 0x73, 0x79, 0x22, 0x62, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_and_aby_behaviour()
{
    System nes;
    uint8_t target_result {0x22};
    SystemMemory program_code {0xA0, 0x93, 0xA9, 0xAA, 0x8D, 0xB6, 0x63, 0xA9, 0x33, 0x39, 0x23, 0x63, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_cmp_aby_behaviour()
{
    System nes;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA0, 0x96, 0xA9, 0x77, 0x8D, 0xBC, 0x66, 0xD9, 0x26, 0x66, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.word == target_word);
}

void test_eor_aby_behaviour()
{
    System nes;
    uint8_t target_result {0x99};
    SystemMemory program_code {0xA0, 0x9A, 0xA9, 0xAA, 0x8D, 0xC4, 0x6A, 0xA9, 0x33, 0x59, 0x2A, 0x6A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_lda_aby_behaviour()
{
    System nes;
    uint8_t target_value {0xAE};
    SystemMemory program_code {0xA0, 0x9C, 0xA9, 0xAE, 0x8D, 0xC8, 0x6C, 0xA9, 0x00, 0xB9, 0x2C, 0x6C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_value);
}

void test_ldx_aby_behaviour()
{
    System nes;
    uint8_t target_value {0xEA};
    SystemMemory program_code {0xA0, 0x9E, 0xA2, 0xEA, 0x8E, 0xCC, 0x6E, 0xA2, 0x00, 0xBE, 0x2E, 0x6E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.x_reg == target_value);
}

void test_ora_aby_behaviour()
{
    System nes;
    uint8_t target_result {0xBB};
    SystemMemory program_code {0xA0, 0xAF, 0xA9, 0xAA, 0x8D, 0xAE, 0xD0, 0xA9, 0x33, 0x19, 0xFF, 0xCF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sbc_aby_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x4B};
    SystemMemory program_code {0xA0, 0xAA, 0xA9, 0x28, 0x8D, 0xA4, 0xCB, 0xA9, 0x73, 0xF9, 0xFA, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sbc_aby_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x4A};
    SystemMemory program_code {0xA0, 0xA9, 0xA9, 0x28, 0x8D, 0xA2, 0xCA, 0xA9, 0x73, 0xF9, 0xF9, 0xC9, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sta_aby_behaviour()
{
    System nes;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA0, 0xA8, 0xA9, 0x31, 0x99, 0xF8, 0xC8, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0xC9A0) == target_result);
}


void ut_cpu_absolute_y_opcodes_behaviour()
{
    TEST_SET;

    test_adc_aby_behaviour_with_carry();
    test_adc_aby_behaviour_without_carry();
    test_and_aby_behaviour();
    test_cmp_aby_behaviour();
    test_eor_aby_behaviour();
    test_lda_aby_behaviour();
    test_ldx_aby_behaviour();
    test_ora_aby_behaviour();
    test_sbc_aby_behaviour_with_carry();
    test_sbc_aby_behaviour_without_carry();
    test_sta_aby_behaviour();
}
