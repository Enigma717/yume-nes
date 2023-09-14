#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/system.h"


void test_adc_iny_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x9C};
    SystemMemory program_code {0xA0, 0x71, 0xA9, 0x21, 0x85, 0xB2, 0xA9, 0x61, 0x85, 0xB3,
        0xA9, 0x28, 0x8D, 0x92, 0x61, 0xA9, 0x73, 0x71, 0xB2, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_adc_iny_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x9B};
    SystemMemory program_code {0xA0, 0x72, 0xA9, 0x22, 0x85, 0xB4, 0xA9, 0x62, 0x85, 0xB5,
        0xA9, 0x28, 0x8D, 0x94, 0x62, 0xA9, 0x73, 0x71, 0xB4, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_and_iny_behaviour()
{
    System nes;
    uint8_t target_result {0x22};
    SystemMemory program_code {0xA0, 0x73, 0xA9, 0x23, 0x85, 0xB6, 0xA9, 0x63, 0x85, 0xB7,
        0xA9, 0xAA, 0x8D, 0x96, 0x63, 0xA9, 0x33, 0x31, 0xB6, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_cmp_iny_behaviour()
{
    System nes;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA0, 0x76, 0xA9, 0x26, 0x85, 0xBC, 0xA9, 0x66, 0x85,
        0xBD, 0xA9, 0x77, 0x8D, 0x9C, 0x66, 0xD1, 0xBC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.status.word == target_word);
}

void test_eor_iny_behaviour()
{
    System nes;
    uint8_t target_result {0x99};
    SystemMemory program_code {0xA0, 0x7A, 0xA9, 0x2A, 0x85, 0xC4, 0xA9, 0x6A, 0x85, 0xC5,
        0xA9, 0xAA, 0x8D, 0xA4, 0x6A, 0xA9, 0x33, 0x51, 0xC4, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_lda_iny_behaviour()
{
    System nes;
    uint8_t target_value {0xAE};
    SystemMemory program_code {0xA0, 0x7C, 0xA9, 0x2C, 0x85, 0xC8, 0xA9, 0x6C, 0x85, 0xC9,
        0xA9, 0xAE, 0x8D, 0xA8, 0x6C, 0xA9, 0x00, 0xB1, 0xC8, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_value);
}

void test_ora_iny_behaviour()
{
    System nes;
    uint8_t target_result {0xBB};
    SystemMemory program_code {0xA0, 0x7D, 0xA9, 0x2D, 0x85, 0xCA, 0xA9, 0x6D, 0x85, 0xCB,
        0xA9, 0xAA, 0x8D, 0xAA, 0x6D, 0xA9, 0x33, 0x11, 0xCA, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sbc_iny_behaviour_with_carry()
{
    System nes;
    uint8_t target_result {0x4B};
    SystemMemory program_code {0xA0, 0x7E, 0xA9, 0x2E, 0x85, 0xCC, 0xA9, 0x6E, 0x85, 0xCD,
        0xA9, 0x28, 0x8D, 0xAC, 0x6E, 0xA9, 0x73, 0xF1, 0xCC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 1;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sbc_iny_behaviour_without_carry()
{
    System nes;
    uint8_t target_result {0x4A};
    SystemMemory program_code {0xA0, 0x7E, 0xA9, 0x2E, 0x85, 0xCC, 0xA9, 0x6E, 0x85, 0xCD,
        0xA9, 0x28, 0x8D, 0xAC, 0x6E, 0xA9, 0x73, 0xF1, 0xCC, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_result);
}

void test_sta_iny_behaviour()
{
    System nes;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA0, 0x7F, 0xA9, 0x2F, 0x85, 0xCE, 0xA9, 0x6F,
        0x85, 0xCF, 0xA9, 0x31, 0x91, 0xCE, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cpu_memory_read(0x6FAE) == target_result);
}


void ut_cpu_indirect_y_opcodes_behaviour()
{
    TEST_SET;

    test_adc_iny_behaviour_with_carry();
    test_adc_iny_behaviour_without_carry();
    test_and_iny_behaviour();
    test_cmp_iny_behaviour();
    test_eor_iny_behaviour();
    test_lda_iny_behaviour();
    test_ora_iny_behaviour();
    test_sbc_iny_behaviour_with_carry();
    test_sbc_iny_behaviour_without_carry();
    test_sta_iny_behaviour();
}
