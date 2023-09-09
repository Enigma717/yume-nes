#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/system.h"


void test_adc_zpx_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x80, 0xA9, 0x28, 0x85, 0xA1, 0xA9, 0xFF, 0x75, 0x21, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_adc_zpx_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x80, 0xA9, 0x15, 0x85, 0xA1, 0xA9, 0x73, 0x75, 0x21, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_adc_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x80, 0xA9, 0x01, 0x85, 0xA1, 0xA9, 0xFF, 0x75, 0x21, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_adc_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x80, 0xA9, 0xAD, 0x85, 0xA1, 0xA9, 0x16, 0x75, 0x21, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_adc_zpx_overflow_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x80, 0xA9, 0x63, 0x85, 0xA1, 0xA9, 0x58, 0x75, 0x21, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 1);
}

void test_adc_zpx_overflow_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x80, 0xA9, 0x05, 0x85, 0xA1, 0xA9, 0xAD, 0x75, 0x21, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 0);
}

void test_adc_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x80, 0xA9, 0x71, 0x85, 0xA1, 0xA9, 0x44, 0x75, 0x21, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_adc_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x80, 0xA9, 0x09, 0x85, 0xA1, 0xA9, 0x08, 0x75, 0x21, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_and_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x82, 0xA9, 0x55, 0x85, 0xA5, 0xA9, 0xAA, 0x35, 0x23, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_and_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x82, 0xA9, 0xFF, 0x85, 0xA5, 0xA9, 0x25, 0x35, 0x23, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_and_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x82, 0xA9, 0xCD, 0x85, 0xA5, 0xA9, 0x99, 0x35, 0x23, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_and_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x82, 0xA9, 0x67, 0x85, 0xA5, 0xA9, 0x81, 0x35, 0x23, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_asl_zpx_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x83, 0xA9, 0xBA, 0x85, 0xA7, 0x16, 0x24, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_asl_zpx_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x83, 0xA9, 0x54, 0x85, 0xA7, 0x16, 0x24, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_asl_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x83, 0xA9, 0x80,  0x85, 0xA7, 0x16, 0x24, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_asl_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x83, 0xA9, 0x7C, 0x85, 0xA7, 0x16, 0x24, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_asl_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x83, 0xA9, 0x67, 0x85, 0xA7, 0x16, 0x24, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_asl_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x83, 0xA9, 0x21, 0x85, 0xA7, 0x16, 0x24, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_cmp_zpx_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA9, 0x51, 0x85, 0x26, 0xA9, 0x77, 0xC5, 0x26, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_cmp_zpx_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA9, 0xA0, 0x85, 0x26, 0xA9, 0x21, 0xC5, 0x26, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_cmp_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x84, 0xA9, 0x37, 0x85, 0xAA, 0xD5, 0x26, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_cmp_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x84, 0xA9, 0x10, 0x85, 0xAA, 0xA9, 0x62, 0xD5, 0x26, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_cmp_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x84, 0xA9, 0xEE, 0x85, 0xAA, 0xA9, 0x01, 0xD5, 0x26, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_cmp_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x84, 0xA9, 0x90, 0x85, 0xAA, 0xA9, 0x69, 0xD5, 0x26, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_dec_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x85, 0xA9, 0x01, 0x85, 0xAE, 0xD6, 0x29, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_dec_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x85, 0xA9, 0xAE, 0x85, 0xAE, 0xD6, 0x29, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_dec_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x85, 0xA9, 0xDC, 0x85, 0xAE, 0xD6, 0x29, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_dec_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x85, 0xA9, 0x62, 0x85, 0xAE, 0xD6, 0x29, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_eor_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x86, 0xA9, 0xDA, 0x85, 0xB0, 0xA9, 0xDA, 0x55, 0x2A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_eor_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x86, 0xA9, 0x95, 0x85, 0xB0, 0xA9, 0x5A, 0x55, 0x2A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_eor_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x86, 0xA9, 0x43, 0x85, 0xB0, 0xA9, 0xA2, 0x55, 0x2A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_eor_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x86, 0xA9, 0x22, 0x85, 0xB0, 0xA9, 0x39, 0x55, 0x2A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_inc_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x87, 0xA9, 0xFF, 0x85, 0xB2, 0xF6, 0x2B, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_inc_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x87, 0xA9, 0x09, 0x85, 0xB2, 0xF6, 0x2B, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_inc_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x87, 0xA9, 0xA2, 0x85, 0xB2, 0xF6, 0x2B, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_inc_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x87, 0xA9, 0x10, 0x85, 0xB2, 0xF6, 0x2B, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_lda_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x88, 0xA9, 0x00, 0x85, 0xB4, 0xA9, 0xAE, 0xB5, 0x2C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_lda_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x88, 0xA9, 0xAE, 0x85, 0xB4, 0xA9, 0x00, 0xB5, 0x2C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_lda_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x88, 0xA9, 0xAF, 0x85, 0xB4, 0xA9, 0x00, 0xB5, 0x2C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_lda_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x88, 0xA9, 0x01, 0x85, 0xB4, 0xA9, 0x00, 0xB5, 0x2C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_ldy_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x89, 0xA0, 0x00, 0x84, 0xB7, 0xA0, 0xAE, 0xB4, 0x2E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_ldy_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x89, 0xA0, 0xAE, 0x84, 0xB7, 0xA0, 0x00, 0xB4, 0x2E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_ldy_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x89, 0xA0, 0xAF, 0x84, 0xB7, 0xA0, 0x00, 0xB4, 0x2E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_ldy_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x89, 0xA0, 0x01, 0x84, 0xB7, 0xA0, 0x00, 0xB4, 0x2E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_lsr_zpx_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x8A, 0xA9, 0x89, 0x85, 0xB9, 0x56, 0x2F, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_lsr_zpx_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x8A, 0xA9, 0x2A, 0x85, 0xB9, 0x56, 0x2F, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_lsr_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x8A, 0xA9, 0x01, 0x85, 0xB9, 0x56, 0x2F, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_lsr_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x8A, 0xA9, 0xEE, 0x85, 0xB9, 0x56, 0x2F, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_lsr_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x8A, 0xA9, 0x37, 0x85, 0xB9, 0x56, 0x2F, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_ora_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x60, 0xA9, 0x00, 0x85, 0x5F, 0x05, 0xFF, 0x10};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_ora_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x60, 0xA9, 0x8A, 0x85, 0x5F, 0xA9, 0x56, 0x15, 0xFF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_ora_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x60, 0xA9, 0x28, 0x85, 0x5F, 0xA9, 0xEF, 0x15, 0xFF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_ora_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x60, 0xA9, 0x45, 0x85, 0x5F, 0xA9, 0x23, 0x15, 0xFF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_rol_zpx_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5F, 0xA9, 0x99, 0x85, 0x5D, 0x36, 0xFE, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_rol_zpx_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5F, 0xA9, 0x6C, 0x85, 0x5D, 0x36, 0xFE, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_rol_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5F, 0xA9, 0x80, 0x85, 0x5D, 0x36, 0xFE, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_rol_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5F, 0xA9, 0xEF, 0x85, 0x5D, 0x36, 0xFE, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_rol_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5F, 0xA9, 0xD7, 0x85, 0x5D, 0x36, 0xFE, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_rol_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5F, 0xA9, 0x86, 0x85, 0x5D, 0x36, 0xFE, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_ror_zpx_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5D, 0xA9, 0xCD, 0x85, 0x59, 0x76, 0xFC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_ror_zpx_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5D, 0xA9, 0x9E, 0x85, 0x59, 0x76, 0xFC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_ror_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5D, 0xA9, 0x01, 0x85, 0x59, 0x76, 0xFC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_ror_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5D, 0xA9, 0xC4, 0x85, 0x59, 0x76, 0xFC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_ror_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5D, 0xA9, 0xA1, 0x85, 0x59, 0x76, 0xFC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_ror_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5D, 0xA9, 0x02, 0x85, 0x59, 0x76, 0xFC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_sbc_zpx_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5B, 0xA9, 0xCF, 0x85, 0x55, 0xA9, 0xFF, 0xF5, 0xFA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_sbc_zpx_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5B, 0xA9, 0xFE, 0x85, 0x55, 0xA9, 0xAA, 0xF5, 0xFA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_sbc_zpx_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5B, 0xA9, 0x76, 0x85, 0x55, 0xA9, 0x77, 0xF5, 0xFA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_sbc_zpx_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5B, 0xA9, 0x11, 0x85, 0x55, 0xA9, 0xC2, 0xF5, 0xFA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_sbc_zpx_overflow_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5B, 0xA9, 0x7C, 0x85, 0x55, 0xA9, 0x01, 0xF5, 0xFA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 1);
}

void test_sbc_zpx_overflow_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5B, 0xA9, 0x65, 0x85, 0x55, 0xA9, 0x7E, 0xF5, 0xFA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 0);
}

void test_sbc_zpx_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5B, 0xA9, 0x09, 0x85, 0x55, 0xA9, 0xDA, 0xF5, 0xFA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_sbc_zpx_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA2, 0x5B, 0xA9, 0x0F, 0x85, 0x55, 0xA9, 0x40, 0xF5, 0xFA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}


void ut_cpu_zero_page_x_opcodes_flags()
{
    TEST_SET;

    test_adc_zpx_carry_flag_set_true();
    test_adc_zpx_carry_flag_set_false();
    test_adc_zpx_zero_flag_set_true();
    test_adc_zpx_zero_flag_set_false();
    test_adc_zpx_overflow_flag_set_true();
    test_adc_zpx_overflow_flag_set_false();
    test_adc_zpx_negative_flag_set_true();
    test_adc_zpx_negative_flag_set_false();

    test_and_zpx_zero_flag_set_true();
    test_and_zpx_zero_flag_set_false();
    test_and_zpx_negative_flag_set_true();
    test_and_zpx_negative_flag_set_false();

    test_asl_zpx_carry_flag_set_true();
    test_asl_zpx_carry_flag_set_false();
    test_asl_zpx_zero_flag_set_true();
    test_asl_zpx_zero_flag_set_false();
    test_asl_zpx_negative_flag_set_true();
    test_asl_zpx_negative_flag_set_false();

    test_cmp_zpx_carry_flag_set_true();
    test_cmp_zpx_carry_flag_set_false();
    test_cmp_zpx_zero_flag_set_true();
    test_cmp_zpx_zero_flag_set_false();
    test_cmp_zpx_negative_flag_set_true();
    test_cmp_zpx_negative_flag_set_false();

    test_dec_zpx_zero_flag_set_true();
    test_dec_zpx_zero_flag_set_false();
    test_dec_zpx_negative_flag_set_true();
    test_dec_zpx_negative_flag_set_false();

    test_eor_zpx_zero_flag_set_true();
    test_eor_zpx_zero_flag_set_false();
    test_eor_zpx_negative_flag_set_true();
    test_eor_zpx_negative_flag_set_false();

    test_inc_zpx_zero_flag_set_true();
    test_inc_zpx_zero_flag_set_false();
    test_inc_zpx_negative_flag_set_true();
    test_inc_zpx_negative_flag_set_false();

    test_lda_zpx_zero_flag_set_true();
    test_lda_zpx_zero_flag_set_false();
    test_lda_zpx_negative_flag_set_true();
    test_lda_zpx_negative_flag_set_false();

    test_ldy_zpx_zero_flag_set_true();
    test_ldy_zpx_zero_flag_set_false();
    test_ldy_zpx_negative_flag_set_true();
    test_ldy_zpx_negative_flag_set_false();

    test_lsr_zpx_carry_flag_set_true();
    test_lsr_zpx_carry_flag_set_false();
    test_lsr_zpx_zero_flag_set_true();
    test_lsr_zpx_zero_flag_set_false();
    test_lsr_zpx_negative_flag_set_false();

    test_ora_zpx_zero_flag_set_true();
    test_ora_zpx_zero_flag_set_false();
    test_ora_zpx_negative_flag_set_true();
    test_ora_zpx_negative_flag_set_false();

    test_rol_zpx_carry_flag_set_true();
    test_rol_zpx_carry_flag_set_false();
    test_rol_zpx_zero_flag_set_true();
    test_rol_zpx_zero_flag_set_false();
    test_rol_zpx_negative_flag_set_true();
    test_rol_zpx_negative_flag_set_false();

    test_ror_zpx_carry_flag_set_true();
    test_ror_zpx_carry_flag_set_false();
    test_ror_zpx_zero_flag_set_true();
    test_ror_zpx_zero_flag_set_false();
    test_ror_zpx_negative_flag_set_true();
    test_ror_zpx_negative_flag_set_false();

    test_sbc_zpx_carry_flag_set_true();
    test_sbc_zpx_carry_flag_set_false();
    test_sbc_zpx_zero_flag_set_true();
    test_sbc_zpx_zero_flag_set_false();
    test_sbc_zpx_overflow_flag_set_true();
    test_sbc_zpx_overflow_flag_set_false();
    test_sbc_zpx_negative_flag_set_true();
    test_sbc_zpx_negative_flag_set_false();
}
