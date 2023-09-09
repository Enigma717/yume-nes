#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/system.h"


void test_adc_iny_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x71, 0xA9, 0x21, 0x85, 0xB2, 0xA9, 0x61, 0x85, 0xB3,
        0xA9, 0x28, 0x8D, 0x92, 0x61, 0xA9, 0xFF, 0x71, 0xB2, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_adc_iny_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x71, 0xA9, 0x21, 0x85, 0xB2, 0xA9, 0x61, 0x85, 0xB3,
        0xA9, 0x15, 0x8D, 0x92, 0x61, 0xA9, 0x73, 0x71, 0xB2, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_adc_iny_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x71, 0xA9, 0x21, 0x85, 0xB2, 0xA9, 0x61, 0x85, 0xB3,
        0xA9, 0x01, 0x8D, 0x92, 0x61, 0xA9, 0xFF, 0x71, 0xB2, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_adc_iny_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x71, 0xA9, 0x21, 0x85, 0xB2, 0xA9, 0x61, 0x85, 0xB3,
        0xA9, 0xAD, 0x8D, 0x92, 0x61, 0xA9, 0x16, 0x71, 0xB2, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_adc_iny_overflow_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x71, 0xA9, 0x21, 0x85, 0xB2, 0xA9, 0x61, 0x85, 0xB3,
        0xA9, 0x63, 0x8D, 0x92, 0x61, 0xA9, 0x58, 0x71, 0xB2, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 1);
}

void test_adc_iny_overflow_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x71, 0xA9, 0x21, 0x85, 0xB2, 0xA9, 0x61, 0x85, 0xB3,
        0xA9, 0x05, 0x8D, 0x92, 0x61, 0xA9, 0xAD, 0x71, 0xB2, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 0);
}

void test_adc_iny_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x71, 0xA9, 0x21, 0x85, 0xB2, 0xA9, 0x61, 0x85, 0xB3,
        0xA9, 0x71, 0x8D, 0x92, 0x61, 0xA9, 0x44, 0x71, 0xB2, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_adc_iny_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x71, 0xA9, 0x21, 0x85, 0xB2, 0xA9, 0x61, 0x85, 0xB3,
        0xA9, 0x09, 0x8D, 0x92, 0x61, 0xA9, 0x08, 0x71, 0xB2, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_and_iny_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x73, 0xA9, 0x23, 0x85, 0xB6, 0xA9, 0x63, 0x85, 0xB7,
        0xA9, 0x5, 0x8D, 0x96, 0x63, 0xA9, 0xAA, 0x31, 0xB6, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_and_iny_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x73, 0xA9, 0x23, 0x85, 0xB6, 0xA9, 0x63, 0x85, 0xB7,
        0xA9, 0xFF, 0x8D, 0x96, 0x63, 0xA9, 0x25, 0x31, 0xB6, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_and_iny_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x73, 0xA9, 0x23, 0x85, 0xB6, 0xA9, 0x63, 0x85, 0xB7,
        0xA9, 0xCD, 0x8D, 0x96, 0x63, 0xA9, 0x99, 0x31, 0xB6, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_and_iny_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x73, 0xA9, 0x23, 0x85, 0xB6, 0xA9, 0x63, 0x85, 0xB7,
        0xA9, 0x67, 0x8D, 0x96, 0x63, 0xA9, 0x81, 0x31, 0xB6, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_cmp_iny_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x76, 0xA9, 0x26, 0x85, 0xBC, 0xA9, 0x66, 0x85, 0xBD,
        0xA9, 0x51, 0x8D, 0x9C, 0x66, 0xA9, 0x77, 0xD1, 0xBC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_cmp_iny_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x76, 0xA9, 0x26, 0x85, 0xBC, 0xA9, 0x66, 0x85, 0xBD,
        0xA9, 0x40, 0x8D, 0x9C, 0x66, 0xA9, 0x21, 0xD1, 0xBC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_cmp_iny_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x76, 0xA9, 0x26, 0x85, 0xBC, 0xA9, 0x66, 0x85,
        0xBD, 0xA9, 0x37, 0x8D, 0x9C, 0x66, 0xD1, 0xBC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_cmp_iny_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x76, 0xA9, 0x26, 0x85, 0xBC, 0xA9, 0x66, 0x85, 0xBD,
        0xA9, 0x10, 0x8D, 0x9C, 0x66, 0xA9, 0x62, 0xD1, 0xBC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_cmp_iny_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x76, 0xA9, 0x26, 0x85, 0xBC, 0xA9, 0x66, 0x85, 0xBD,
        0xA9, 0xEE, 0x8D, 0x9C, 0x66, 0xA9, 0x01, 0xD1, 0xBC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_cmp_iny_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x76, 0xA9, 0x26, 0x85, 0xBC, 0xA9, 0x66, 0x85, 0xBD,
        0xA9, 0x90, 0x8D, 0x9C, 0x66, 0xA9, 0x69, 0xD1, 0xBC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_eor_iny_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7A, 0xA9, 0x2A, 0x85, 0xC4, 0xA9, 0x6A, 0x85, 0xC5,
        0xA9, 0xDA, 0x8D, 0xA4, 0x6A, 0xA9, 0xDA, 0x51, 0xC4, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_eor_iny_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7A, 0xA9, 0x2A, 0x85, 0xC4, 0xA9, 0x6A, 0x85, 0xC5,
        0xA9, 0x95, 0x8D, 0xA4, 0x6A, 0xA9, 0x5A, 0x51, 0xC4, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_eor_iny_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7A, 0xA9, 0x2A, 0x85, 0xC4, 0xA9, 0x6A, 0x85, 0xC5,
        0xA9, 0x43, 0x8D, 0xA4, 0x6A, 0xA9, 0xA2, 0x51, 0xC4, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_eor_iny_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7A, 0xA9, 0x2A, 0x85, 0xC4, 0xA9, 0x6A, 0x85, 0xC5,
        0xA9, 0x22, 0x8D, 0xA4, 0x6A, 0xA9, 0x39, 0x51, 0xC4, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_lda_iny_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7C, 0xA9, 0x2C, 0x85, 0xC8, 0xA9, 0x6C, 0x85, 0xC9,
        0xA9, 0x00, 0x8D, 0xA8, 0x6C, 0xA9, 0xAE, 0xB1, 0xC8, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_lda_iny_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7C, 0xA9, 0x2C, 0x85, 0xC8, 0xA9, 0x6C, 0x85, 0xC9,
        0xA9, 0xAE, 0x8D, 0xA8, 0x6C, 0xA9, 0x00, 0xB1, 0xC8, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_lda_iny_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7C, 0xA9, 0x2C, 0x85, 0xC8, 0xA9, 0x6C, 0x85, 0xC9,
        0xA9, 0xAF, 0x8D, 0xA8, 0x6C, 0xA9, 0x00, 0xB1, 0xC8, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_lda_iny_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7C, 0xA9, 0x2C, 0x85, 0xC8, 0xA9, 0x6C, 0x85, 0xC9,
        0xA9, 0x01, 0x8D, 0xA8, 0x6C, 0xA9, 0x00, 0xB1, 0xC8, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_ora_iny_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7D, 0xA9, 0x2D, 0x85, 0xCA, 0xA9, 0x6D, 0x85, 0xCB,
        0xA9, 0x00, 0x8D, 0xAA, 0x6D, 0x11, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_ora_iny_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7D, 0xA9, 0x2D, 0x85, 0xCA, 0xA9, 0x6D, 0x85, 0xCB,
        0xA9, 0x8A, 0x8D, 0xAA, 0x6D, 0xA9, 0x56, 0x11, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_ora_iny_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7D, 0xA9, 0x2D, 0x85, 0xCA, 0xA9, 0x6D, 0x85, 0xCB,
        0xA9, 0x28, 0x8D, 0xAA, 0x6D, 0xA9, 0xEF, 0x11, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_ora_iny_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7D, 0xA9, 0x2D, 0x85, 0xCA, 0xA9, 0x6D, 0x85, 0xCB,
        0xA9, 0x45, 0x8D, 0xAA, 0x6D, 0xA9, 0x23, 0x11, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_sbc_iny_carry_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7E, 0xA9, 0x2E, 0x85, 0xCC, 0xA9, 0x6E, 0x85, 0xCD,
        0xA9, 0xCF, 0x8D, 0xAC, 0x6E, 0xA9, 0xFF, 0xF1, 0xCC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 1);
}

void test_sbc_iny_carry_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7E, 0xA9, 0x2E, 0x85, 0xCC, 0xA9, 0x6E, 0x85, 0xCD,
        0xA9, 0xFE, 0x8D, 0xAC, 0x6E, 0xA9, 0xAA, 0xF1, 0xCC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.carry == 0);
}

void test_sbc_iny_zero_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7E, 0xA9, 0x2E, 0x85, 0xCC, 0xA9, 0x6E, 0x85, 0xCD,
        0xA9, 0x76, 0x8D, 0xAC, 0x6E, 0xA9, 0x77, 0xF1, 0xCC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_sbc_iny_zero_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7E, 0xA9, 0x2E, 0x85, 0xCC, 0xA9, 0x6E, 0x85, 0xCD,
        0xA9, 0x11, 0x8D, 0xAC, 0x6E, 0xA9, 0xC2, 0xF1, 0xCC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_sbc_iny_overflow_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7E, 0xA9, 0x2E, 0x85, 0xCC, 0xA9, 0x6E, 0x85, 0xCD,
        0xA9, 0x7C, 0x8D, 0xAC, 0x6E, 0xA9, 0x01, 0xF1, 0xCC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 1);
}

void test_sbc_iny_overflow_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7E, 0xA9, 0x2E, 0x85, 0xCC, 0xA9, 0x6E, 0x85, 0xCD,
        0xA9, 0x65, 0x8D, 0xAC, 0x6E, 0xA9, 0x7E, 0xF1, 0xCC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.overflow == 0);
}

void test_sbc_iny_negative_flag_set_true()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7E, 0xA9, 0x2E, 0x85, 0xCC, 0xA9, 0x6E, 0x85, 0xCD,
        0xA9, 0x09, 0x8D, 0xAC, 0x6E, 0xA9, 0xDA, 0xF1, 0xCC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_sbc_iny_negative_flag_set_false()
{
    System nes;
    SystemMemory program_code {0xA0, 0x7E, 0xA9, 0x2E, 0x85, 0xCC, 0xA9, 0x6E, 0x85, 0xCD,
        0xA9, 0x0A, 0x8D, 0xAC, 0x6E, 0xA9, 0x40, 0xF1, 0xCC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}


void ut_cpu_indirect_y_opcodes_flags()
{
    TEST_SET;

    test_adc_iny_carry_flag_set_true();
    test_adc_iny_carry_flag_set_false();
    test_adc_iny_zero_flag_set_true();
    test_adc_iny_zero_flag_set_false();
    test_adc_iny_overflow_flag_set_true();
    test_adc_iny_overflow_flag_set_false();
    test_adc_iny_negative_flag_set_true();
    test_adc_iny_negative_flag_set_false();

    test_and_iny_zero_flag_set_true();
    test_and_iny_zero_flag_set_false();
    test_and_iny_negative_flag_set_true();
    test_and_iny_negative_flag_set_false();

    test_cmp_iny_carry_flag_set_true();
    test_cmp_iny_carry_flag_set_false();
    test_cmp_iny_zero_flag_set_true();
    test_cmp_iny_zero_flag_set_false();
    test_cmp_iny_negative_flag_set_true();
    test_cmp_iny_negative_flag_set_false();

    test_eor_iny_zero_flag_set_true();
    test_eor_iny_zero_flag_set_false();
    test_eor_iny_negative_flag_set_true();
    test_eor_iny_negative_flag_set_false();

    test_lda_iny_zero_flag_set_true();
    test_lda_iny_zero_flag_set_false();
    test_lda_iny_negative_flag_set_true();
    test_lda_iny_negative_flag_set_false();

    test_ora_iny_zero_flag_set_true();
    test_ora_iny_zero_flag_set_false();
    test_ora_iny_negative_flag_set_true();
    test_ora_iny_negative_flag_set_false();

    test_sbc_iny_carry_flag_set_true();
    test_sbc_iny_carry_flag_set_false();
    test_sbc_iny_zero_flag_set_true();
    test_sbc_iny_zero_flag_set_false();
    test_sbc_iny_overflow_flag_set_true();
    test_sbc_iny_overflow_flag_set_false();
    test_sbc_iny_negative_flag_set_true();
    test_sbc_iny_negative_flag_set_false();
}
