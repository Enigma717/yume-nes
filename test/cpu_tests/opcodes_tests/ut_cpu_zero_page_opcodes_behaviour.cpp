#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/system.h"


void test_adc_zpg_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x9C};
    SystemMemory program_code {0xA9, 0x28, 0x85, 0x21, 0xA9, 0x73, 0x65, 0x21, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_adc_zpg_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x9B};
    SystemMemory program_code {0xA9, 0x28, 0x85, 0x22, 0xA9, 0x73, 0x65, 0x22, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_and_zpg_behaviour()
{
    System nes;
    uint8_t target_result {0x22};
    SystemMemory program_code {0xA9, 0xAA, 0x85, 0x23, 0xA9, 0x33, 0x25, 0x23, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_asl_zpg_behaviour()
{
    System nes;
    uint8_t target_result {0x94};
    SystemMemory program_code {0xA9, 0xCA, 0x85, 0x24, 0x06, 0x24, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.memory_read(0x24) == target_result);
}

void test_bit_zpg_behaviour()
{
    System nes;
    uint8_t target_word {0x76};
    SystemMemory program_code {0xA9, 0x69, 0x85, 0x25, 0xA9, 0x96, 0x24, 0x25, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.word == target_word);
}

void test_cmp_zpg_behaviour()
{
    System nes;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA9, 0x77, 0x85, 0x26, 0xC5, 0x26, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.word == target_word);
}

void test_cpx_zpg_behaviour()
{
    System nes;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA2, 0x77, 0x86, 0x27, 0xE4, 0x27, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.word == target_word);
}

void test_cpy_zpg_behaviour()
{
    System nes;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA0, 0x77, 0x84, 0x28, 0xC4, 0x28, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.word == target_word);
}

void test_dec_zpg_behaviour()
{
    System nes;
    uint8_t target_result {0x32};
    SystemMemory program_code {0xA9, 0x33, 0x85, 0x29, 0xC6, 0x29, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.memory_read(0x29) == target_result);
}

void test_eor_zpg_behaviour()
{
    System nes;
    uint8_t target_result {0x99};
    SystemMemory program_code {0xA9, 0xAA, 0x85, 0x2A, 0xA9, 0x33, 0x45, 0x2A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_inc_zpg_behaviour()
{
    System nes;
    uint8_t target_result {0x34};
    SystemMemory program_code {0xA9, 0x33, 0x85, 0x2B, 0xE6, 0x2B, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.memory_read(0x2B) == target_result);
}

void test_lda_zpg_behaviour()
{
    System nes;
    uint8_t target_value {0xAE};
    SystemMemory program_code {0xA9, 0xAE, 0x85, 0x2C, 0xA9, 0x00, 0xA5, 0x2C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_value);
}

void test_ldx_zpg_behaviour()
{
    System nes;
    uint8_t target_value {0xCB};
    SystemMemory program_code {0xA2, 0xCB, 0x86, 0x2D, 0xA2, 0x00, 0xA6, 0x2D, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.x_reg == target_value);
}

void test_ldy_zpg_behaviour()
{
    System nes;
    uint8_t target_value {0xEA};
    SystemMemory program_code {0xA0, 0xEA, 0x84, 0x2E, 0xA0, 0x00, 0xA4, 0x2E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.y_reg == target_value);
}

void test_lsr_zpg_behaviour()
{
    System nes;
    uint8_t target_result {0x4B};
    SystemMemory program_code {0xA9, 0x97, 0x85, 0x2F, 0x46, 0x2F, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.memory_read(0x2F) == target_result);
}

void test_ora_zpg_behaviour()
{
    System nes;
    uint8_t target_result {0xBB};
    SystemMemory program_code {0xA9, 0xAA, 0x85, 0xFF, 0xA9, 0x33, 0x05, 0xFF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_rol_zpg_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x3D};
    SystemMemory program_code {0xA9, 0x9E, 0x85, 0xFE, 0x26, 0xFE, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.memory_read(0xFE) == target_result);
}

void test_rol_zpg_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x3C};
    SystemMemory program_code {0xA9, 0x9E, 0x85, 0xFD, 0x26, 0xFD, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.memory_read(0xFD) == target_result);
}

void test_ror_zpg_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0xA6};
    SystemMemory program_code {0xA9, 0x4D, 0x85, 0xFC, 0x66, 0xFC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.memory_read(0xFC) == target_result);
}

void test_ror_zpg_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x26};
    SystemMemory program_code {0xA9, 0x4D, 0x85, 0xFB, 0x66, 0xFB, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.memory_read(0xFB) == target_result);
}

void test_sbc_zpg_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x4B};
    SystemMemory program_code {0xA9, 0x28, 0x85, 0xFA, 0xA9, 0x73, 0xE5, 0xFA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sbc_zpg_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x4A};
    SystemMemory program_code {0xA9, 0x28, 0x85, 0xF9, 0xA9, 0x73, 0xE5, 0xF9, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sta_zpg_behaviour()
{
    System nes;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA9, 0x31, 0x85, 0xF8, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.memory_read(0xF8) == target_result);
}

void test_stx_zpg_behaviour()
{
    System nes;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA2, 0x31, 0x86, 0xF7, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.memory_read(0xF7) == target_result);
}

void test_sty_zpg_behaviour()
{
    System nes;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA0, 0x31, 0x84, 0xF6, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.memory_read(0xF6) == target_result);
}


void ut_cpu_zero_page_opcodes_behaviour()
{
    TEST_SET;

    test_adc_zpg_behaviour_with_carry();
    test_adc_zpg_behaviour_without_carry();
    test_and_zpg_behaviour();
    test_asl_zpg_behaviour();
    test_bit_zpg_behaviour();
    test_cmp_zpg_behaviour();
    test_cpx_zpg_behaviour();
    test_cpy_zpg_behaviour();
    test_dec_zpg_behaviour();
    test_eor_zpg_behaviour();
    test_inc_zpg_behaviour();
    test_lda_zpg_behaviour();
    test_ldx_zpg_behaviour();
    test_ldy_zpg_behaviour();
    test_lsr_zpg_behaviour();
    test_ora_zpg_behaviour();
    test_rol_zpg_behaviour_with_carry();
    test_rol_zpg_behaviour_without_carry();
    test_ror_zpg_behaviour_with_carry();
    test_ror_zpg_behaviour_without_carry();
    test_sbc_zpg_behaviour_with_carry();
    test_sbc_zpg_behaviour_without_carry();
    test_sta_zpg_behaviour();
    test_stx_zpg_behaviour();
    test_sty_zpg_behaviour();
}
