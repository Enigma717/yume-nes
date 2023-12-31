#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/system.h"


void test_adc_aby_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x91, 0xA9, 0x28, 0x8D, 0xB2, 0x61, 0xA9, 0xFF, 0x79, 0x21, 0x61, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_adc_aby_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x91, 0xA9, 0x15, 0x8D, 0xB2, 0x61, 0xA9, 0x73, 0x79, 0x21, 0x61, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_adc_aby_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x91, 0xA9, 0x01, 0x8D, 0xB2, 0x61, 0xA9, 0xFF, 0x79, 0x21, 0x61, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_adc_aby_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x91, 0xA9, 0xAD, 0x8D, 0xB2, 0x61, 0xA9, 0x16, 0x79, 0x21, 0x61, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_adc_aby_overflow_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x91, 0xA9, 0x63, 0x8D, 0xB2, 0x61, 0xA9, 0x58, 0x79, 0x21, 0x61, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 1);
}

void test_adc_aby_overflow_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x91, 0xA9, 0x05, 0x8D, 0xB2, 0x61, 0xA9, 0xAD, 0x79, 0x21, 0x61, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 0);
}

void test_adc_aby_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x91, 0xA9, 0x71, 0x8D, 0xB2, 0x61, 0xA9, 0x44, 0x79, 0x21, 0x61, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_adc_aby_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x91, 0xA9, 0x09, 0x8D, 0xB2, 0x61, 0xA9, 0x08, 0x79, 0x21, 0x61, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_and_aby_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x93, 0xA9, 0x55, 0x8D, 0xB6, 0x63, 0xA9, 0xAA, 0x39, 0x23, 0x63, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_and_aby_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x93, 0xA9, 0xFF, 0x8D, 0xB6, 0x63, 0xA9, 0x25, 0x39, 0x23, 0x63, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_and_aby_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x93, 0xA9, 0xCD, 0x8D, 0xB6, 0x63, 0xA9, 0x99, 0x39, 0x23, 0x63, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_and_aby_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x93, 0xA9, 0x67, 0x8D, 0xB6, 0x63, 0xA9, 0x81, 0x39, 0x23, 0x63, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_cmp_aby_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x96, 0xA9, 0x51, 0x8D, 0xBC, 0x66, 0xA9, 0x77, 0xD9, 0x26, 0x66, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_cmp_aby_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x96, 0xA9, 0xA0, 0x8D, 0xBC, 0x66, 0xA9, 0x21, 0xD9, 0x26, 0x66, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_cmp_aby_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x96, 0xA9, 0x37, 0x8D, 0xBC, 0x66, 0xD9, 0x26, 0x66, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_cmp_aby_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x96, 0xA9, 0x10, 0x8D, 0xBC, 0x66, 0xA9, 0x62, 0xD9, 0x26, 0x66, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_cmp_aby_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x96, 0xA9, 0xEE, 0x8D, 0xBC, 0x66, 0xA9, 0x01, 0xD9, 0x26, 0x66, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_cmp_aby_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x96, 0xA9, 0x90, 0x8D, 0xBC, 0x66, 0xA9, 0x69, 0xD9, 0x26, 0x66, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_eor_aby_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9A, 0xA9, 0xDA, 0x8D, 0xC4, 0x6A, 0xA9, 0xDA, 0x59, 0x2A, 0x6A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_eor_aby_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9A, 0xA9, 0x95, 0x8D, 0xC4, 0x6A, 0xA9, 0x5A, 0x59, 0x2A, 0x6A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_eor_aby_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9A, 0xA9, 0x43, 0x8D, 0xC4, 0x6A, 0xA9, 0xA2, 0x59, 0x2A, 0x6A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_eor_aby_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9A, 0xA9, 0x22, 0x8D, 0xC4, 0x6A, 0xA9, 0x39, 0x59, 0x2A, 0x6A, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_lda_aby_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9C, 0xA9, 0x00, 0x8D, 0xC8, 0x6C, 0xA9, 0xAE, 0xB9, 0x2C, 0x6C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_lda_aby_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9C, 0xA9, 0xAE, 0x8D, 0xC8, 0x6C, 0xA9, 0x00, 0xB9, 0x2C, 0x6C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_lda_aby_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9C, 0xA9, 0xAF, 0x8D, 0xC8, 0x6C, 0xA9, 0x00, 0xB9, 0x2C, 0x6C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_lda_aby_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9C, 0xA9, 0x01, 0x8D, 0xC8, 0x6C, 0xA9, 0x00, 0xB9, 0x2C, 0x6C, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_ldx_aby_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9E, 0xA2, 0x00, 0x8E, 0xCC, 0x6E, 0xA2, 0xAE, 0xBE, 0x2E, 0x6E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_ldx_aby_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9E, 0xA2, 0xAE, 0x8E, 0xCC, 0x6E, 0xA2, 0x00, 0xBE, 0x2E, 0x6E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_ldx_aby_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9E, 0xA2, 0xAF, 0x8E, 0xCC, 0x6E, 0xA2, 0x00, 0xBE, 0x2E, 0x6E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_ldx_aby_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x9E, 0xA2, 0x01, 0x8E, 0xCC, 0x6E, 0xA2, 0x00, 0xBE, 0x2E, 0x6E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_ora_aby_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAF, 0xA9, 0x00, 0x8D, 0xAE, 0xD0, 0x19, 0xFF, 0xCF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_ora_aby_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAF, 0xA9, 0x8A, 0x8D, 0xAE, 0xD0, 0xA9, 0x56, 0x19, 0xFF, 0xCF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_ora_aby_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAF, 0xA9, 0x28, 0x8D, 0xAE, 0xD0, 0xA9, 0xEF, 0x19, 0xFF, 0xCF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_ora_aby_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAF, 0xA9, 0x45, 0x8D, 0xAE, 0xD0, 0xA9, 0x23, 0x19, 0xFF, 0xCF, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_sbc_aby_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAA, 0xA9, 0xCF, 0x8D, 0xA4, 0xCB, 0xA9, 0xFF, 0xF9, 0xFA, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_sbc_aby_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAA, 0xA9, 0xFE, 0x8D, 0xA4, 0xCB, 0xA9, 0xAA, 0xF9, 0xFA, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_sbc_aby_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAA, 0xA9, 0x76, 0x8D, 0xA4, 0xCB, 0xA9, 0x77, 0xF9, 0xFA, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_sbc_aby_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAA, 0xA9, 0x11, 0x8D, 0xA4, 0xCB, 0xA9, 0xC2, 0xF9, 0xFA, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_sbc_aby_overflow_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAA, 0xA9, 0x7C, 0x8D, 0xA4, 0xCB, 0xA9, 0x01, 0xF9, 0xFA, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 1);
}

void test_sbc_aby_overflow_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAA, 0xA9, 0x65, 0x8D, 0xA4, 0xCB, 0xA9, 0x7E, 0xF9, 0xFA, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 0);
}

void test_sbc_aby_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAA, 0xA9, 0x09, 0x8D, 0xA4, 0xCB, 0xA9, 0xDA, 0xF9, 0xFA, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_sbc_aby_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0xAA, 0xA9, 0x0F, 0x8D, 0xA4, 0xCB, 0xA9, 0x40, 0xF9, 0xFA, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}


void ut_cpu_absolute_y_opcodes_flags()
{
    TEST_SET;

    test_adc_aby_carry_flag_set_true();
    test_adc_aby_carry_flag_set_false();
    test_adc_aby_zero_flag_set_true();
    test_adc_aby_zero_flag_set_false();
    test_adc_aby_overflow_flag_set_true();
    test_adc_aby_overflow_flag_set_false();
    test_adc_aby_negative_flag_set_true();
    test_adc_aby_negative_flag_set_false();

    test_and_aby_zero_flag_set_true();
    test_and_aby_zero_flag_set_false();
    test_and_aby_negative_flag_set_true();
    test_and_aby_negative_flag_set_false();

    test_cmp_aby_carry_flag_set_true();
    test_cmp_aby_carry_flag_set_false();
    test_cmp_aby_zero_flag_set_true();
    test_cmp_aby_zero_flag_set_false();
    test_cmp_aby_negative_flag_set_true();
    test_cmp_aby_negative_flag_set_false();

    test_eor_aby_zero_flag_set_true();
    test_eor_aby_zero_flag_set_false();
    test_eor_aby_negative_flag_set_true();
    test_eor_aby_negative_flag_set_false();

    test_lda_aby_zero_flag_set_true();
    test_lda_aby_zero_flag_set_false();
    test_lda_aby_negative_flag_set_true();
    test_lda_aby_negative_flag_set_false();

    test_ldx_aby_zero_flag_set_true();
    test_ldx_aby_zero_flag_set_false();
    test_ldx_aby_negative_flag_set_true();
    test_ldx_aby_negative_flag_set_false();

    test_ora_aby_zero_flag_set_true();
    test_ora_aby_zero_flag_set_false();
    test_ora_aby_negative_flag_set_true();
    test_ora_aby_negative_flag_set_false();

    test_sbc_aby_carry_flag_set_true();
    test_sbc_aby_carry_flag_set_false();
    test_sbc_aby_zero_flag_set_true();
    test_sbc_aby_zero_flag_set_false();
    test_sbc_aby_overflow_flag_set_true();
    test_sbc_aby_overflow_flag_set_false();
    test_sbc_aby_negative_flag_set_true();
    test_sbc_aby_negative_flag_set_false();
}
