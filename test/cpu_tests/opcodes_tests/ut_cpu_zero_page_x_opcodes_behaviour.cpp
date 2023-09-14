#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/system.h"


void test_zpx_page_wrapping()
{
    System nes;
    uint8_t target_address {0x7F};
    SystemMemory program_code {0xA2, 0x80, 0xA9, 0x21, 0x95, 0xFF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(target_address) == 0x21);
}

void test_adc_zpx_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x9C};
    SystemMemory program_code {0xA2, 0x80, 0xA9, 0x28, 0x85, 0xA1, 0xA9, 0x73, 0x75, 0x21, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_adc_zpx_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x9B};
    SystemMemory program_code {0xA2, 0x81, 0xA9, 0x28, 0x85, 0xA3, 0xA9, 0x73, 0x75, 0x22, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_and_zpx_behaviour()
{
    System nes;
    uint8_t target_result {0x22};
    SystemMemory program_code {0xA2, 0x82, 0xA9, 0xAA, 0x85, 0xA5, 0xA9, 0x33, 0x35, 0x23, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_asl_zpx_behaviour()
{
    System nes;
    uint8_t target_result {0x94};
    SystemMemory program_code {0xA2, 0x83, 0xA9, 0xCA, 0x85, 0xA7, 0x16, 0x24, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0xA7) == target_result);
}

void test_cmp_zpx_behaviour()
{
    System nes;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA2, 0x84, 0xA9, 0x77, 0x85, 0xAA, 0xD5, 0x26, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.word == target_word);
}

void test_dec_zpx_behaviour()
{
    System nes;
    uint8_t target_result {0x32};
    SystemMemory program_code {0xA2, 0x85, 0xA9, 0x33, 0x85, 0xAE, 0xD6, 0x29, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0xAE) == target_result);
}

void test_eor_zpx_behaviour()
{
    System nes;
    uint8_t target_result {0x99};
    SystemMemory program_code {0xA2, 0x86, 0xA9, 0xAA, 0x85, 0xB0, 0xA9, 0x33, 0x55, 0x2A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_inc_zpx_behaviour()
{
    System nes;
    uint8_t target_result {0x34};
    SystemMemory program_code {0xA2, 0x87, 0xA9, 0x33, 0x85, 0xB2, 0xF6, 0x2B, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0xB2) == target_result);
}

void test_lda_zpx_behaviour()
{
    System nes;
    uint8_t target_value {0xAE};
    SystemMemory program_code {0xA2, 0x88, 0xA9, 0xAE, 0x85, 0xB4, 0xA9, 0x00, 0xB5, 0x2C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_value);
}

void test_ldy_zpx_behaviour()
{
    System nes;
    uint8_t target_value {0xEA};
    SystemMemory program_code {0xA2, 0x89, 0xA0, 0xEA, 0x84, 0xB7, 0xA0, 0x00, 0xB4, 0x2E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.y_reg == target_value);
}

void test_lsr_zpx_behaviour()
{
    System nes;
    uint8_t target_result {0x4B};
    SystemMemory program_code {0xA2, 0x8A, 0xA9, 0x97, 0x85, 0xB9, 0x56, 0x2F, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0xB9) == target_result);
}

void test_ora_zpx_behaviour()
{
    System nes;
    uint8_t target_result {0xBB};
    SystemMemory program_code {0xA2, 0x60, 0xA9, 0xAA, 0x85, 0x5F, 0xA9, 0x33, 0x15, 0xFF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_rol_zpx_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x3D};
    SystemMemory program_code {0xA2, 0x5F, 0xA9, 0x9E, 0x85, 0x5D, 0x36, 0xFE, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0x5D) == target_result);
}

void test_rol_zpx_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x3C};
    SystemMemory program_code {0xA2, 0x5E, 0xA9, 0x9E, 0x85, 0x5C, 0x36, 0xFE, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0x5C) == target_result);
}

void test_ror_zpx_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0xA6};
    SystemMemory program_code {0xA2, 0x5D, 0xA9, 0x4D, 0x85, 0x59, 0x76, 0xFC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0x59) == target_result);
}

void test_ror_zpx_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x26};
    SystemMemory program_code {0xA2, 0x5C, 0xA9, 0x4D, 0x85, 0x57, 0x76, 0xFB, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0x57) == target_result);
}

void test_sbc_zpx_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x4B};
    SystemMemory program_code {0xA2, 0x5B, 0xA9, 0x28, 0x85, 0x55, 0xA9, 0x73, 0xF5, 0xFA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sbc_zpx_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x4A};
    SystemMemory program_code {0xA2, 0x5A, 0xA9, 0x28, 0x85, 0x53, 0xA9, 0x73, 0xF5, 0xF9, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sta_zpx_behaviour()
{
    System nes;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA2, 0x59, 0xA9, 0x31, 0x95, 0xF8, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0x51) == target_result);
}

void test_sty_zpx_behaviour()
{
    System nes;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA2, 0x57, 0xA0, 0x31, 0x94, 0xF6, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0x4D) == target_result);
}


void ut_cpu_zero_page_x_opcodes_behaviour()
{
    TEST_SET;

    test_zpx_page_wrapping();
    test_adc_zpx_behaviour_with_carry();
    test_adc_zpx_behaviour_without_carry();
    test_and_zpx_behaviour();
    test_asl_zpx_behaviour();
    test_cmp_zpx_behaviour();
    test_dec_zpx_behaviour();
    test_eor_zpx_behaviour();
    test_inc_zpx_behaviour();
    test_lda_zpx_behaviour();
    test_ldy_zpx_behaviour();
    test_lsr_zpx_behaviour();
    test_ora_zpx_behaviour();
    test_rol_zpx_behaviour_with_carry();
    test_rol_zpx_behaviour_without_carry();
    test_ror_zpx_behaviour_with_carry();
    test_ror_zpx_behaviour_without_carry();
    test_sbc_zpx_behaviour_with_carry();
    test_sbc_zpx_behaviour_without_carry();
    test_sta_zpx_behaviour();
    test_sty_zpx_behaviour();
}
