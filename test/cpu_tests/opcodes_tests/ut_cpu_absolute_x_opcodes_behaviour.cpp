#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/system.h"


void test_adc_abx_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x9C};
    SystemMemory program_code {0xA2, 0x91, 0xA9, 0x28, 0x8D, 0xB2, 0x61, 0xA9, 0x73, 0x7D, 0x21, 0x61, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_adc_abx_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x9B};
    SystemMemory program_code {0xA2, 0x92, 0xA9, 0x28, 0x8D, 0xB4, 0x62, 0xA9, 0x73, 0x7D, 0x22, 0x62, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_and_abx_behaviour()
{
    System nes;
    uint8_t target_result {0x22};
    SystemMemory program_code {0xA2, 0x93, 0xA9, 0xAA, 0x8D, 0xB6, 0x63, 0xA9, 0x33, 0x3D, 0x23, 0x63, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_asl_abx_behaviour()
{
    System nes;
    uint8_t target_result {0x94};
    SystemMemory program_code {0xA2, 0x94, 0xA9, 0xCA, 0x8D, 0xB8, 0x64, 0x1E, 0x24, 0x64, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.ram->memory_read(0x64B8) == target_result);
}

void test_cmp_abx_behaviour()
{
    System nes;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA2, 0x96, 0xA9, 0x77, 0x8D, 0xBC, 0x66, 0xDD, 0x26, 0x66, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.word == target_word);
}

void test_dec_abx_behaviour()
{
    System nes;
    uint8_t target_result {0x32};
    SystemMemory program_code {0xA2, 0x99, 0xA9, 0x33, 0x8D, 0xC2, 0x69, 0xDE, 0x29, 0x69, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.ram->memory_read(0x69C2) == target_result);
}

void test_eor_abx_behaviour()
{
    System nes;
    uint8_t target_result {0x99};
    SystemMemory program_code {0xA2, 0x9A, 0xA9, 0xAA, 0x8D, 0xC4, 0x6A, 0xA9, 0x33, 0x5D, 0x2A, 0x6A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_inc_abx_behaviour()
{
    System nes;
    uint8_t target_result {0x34};
    SystemMemory program_code {0xA2, 0x9B, 0xA9, 0x33, 0x8D, 0xC6, 0x6B, 0xFE, 0x2B, 0x6B, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.ram->memory_read(0x6BC6) == target_result);
}

void test_lda_abx_behaviour()
{
    System nes;
    uint8_t target_value {0xAE};
    SystemMemory program_code {0xA2, 0x9C, 0xA9, 0xAE, 0x8D, 0xC8, 0x6C, 0xA9, 0x00, 0xBD, 0x2C, 0x6C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_value);
}

void test_ldy_abx_behaviour()
{
    System nes;
    uint8_t target_value {0xEA};
    SystemMemory program_code {0xA2, 0x9E, 0xA0, 0xEA, 0x8C, 0xCC, 0x6E, 0xA0, 0x00, 0xBC, 0x2E, 0x6E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.y_reg == target_value);
}

void test_lsr_abx_behaviour()
{
    System nes;
    uint8_t target_result {0x4B};
    SystemMemory program_code {0xA2, 0x9F, 0xA9, 0x97, 0x8D, 0xCE, 0x6F, 0x5E, 0x2F, 0x6F, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.ram->memory_read(0x6FCE) == target_result);
}

void test_ora_abx_behaviour()
{
    System nes;
    uint8_t target_result {0xBB};
    SystemMemory program_code {0xA2, 0xAF, 0xA9, 0xAA, 0x8D, 0xAE, 0xD0, 0xA9, 0x33, 0x1D, 0xFF, 0xCF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_rol_abx_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x3D};
    SystemMemory program_code {0xA2, 0xAE, 0xA9, 0x9E, 0x8D, 0xAC, 0xCF, 0x3E, 0xFE, 0xCE, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.ram->memory_read(0xCFAC) == target_result);
}

void test_rol_abx_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x3C};
    SystemMemory program_code {0xA2, 0xAD, 0xA9, 0x9E, 0x8D, 0xAA, 0xCE, 0x3E, 0xFD, 0xCD, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.ram->memory_read(0xCEAA) == target_result);
}

void test_ror_abx_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0xA6};
    SystemMemory program_code {0xA2, 0xAC, 0xA9, 0x4D, 0x8D, 0xA8, 0xCD, 0x7E, 0xFC, 0xCC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.ram->memory_read(0xCDA8) == target_result);
}

void test_ror_abx_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x26};
    SystemMemory program_code {0xA2, 0xAB, 0xA9, 0x4D, 0x8D, 0xA6, 0xCC, 0x7E, 0xFB, 0xCB, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.ram->memory_read(0xCCA6) == target_result);
}

void test_sbc_abx_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x4B};
    SystemMemory program_code {0xA2, 0xAA, 0xA9, 0x28, 0x8D, 0xA4, 0xCB, 0xA9, 0x73, 0xFD, 0xFA, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sbc_abx_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x4A};
    SystemMemory program_code {0xA2, 0xA9, 0xA9, 0x28, 0x8D, 0xA2, 0xCA, 0xA9, 0x73, 0xFD, 0xF9, 0xC9, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sta_abx_behaviour()
{
    System nes;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA2, 0xA8, 0xA9, 0x31, 0x9D, 0xF8, 0xC8, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.ram->memory_read(0xC9A0) == target_result);
}


void ut_cpu_absolute_x_opcodes_behaviour()
{
    TEST_SET;

    test_adc_abx_behaviour_with_carry();
    test_adc_abx_behaviour_without_carry();
    test_and_abx_behaviour();
    test_asl_abx_behaviour();
    test_cmp_abx_behaviour();
    test_dec_abx_behaviour();
    test_eor_abx_behaviour();
    test_inc_abx_behaviour();
    test_lda_abx_behaviour();
    test_ldy_abx_behaviour();
    test_lsr_abx_behaviour();
    test_ora_abx_behaviour();
    test_rol_abx_behaviour_with_carry();
    test_rol_abx_behaviour_without_carry();
    test_ror_abx_behaviour_with_carry();
    test_ror_abx_behaviour_without_carry();
    test_sbc_abx_behaviour_with_carry();
    test_sbc_abx_behaviour_without_carry();
    test_sta_abx_behaviour();
}
