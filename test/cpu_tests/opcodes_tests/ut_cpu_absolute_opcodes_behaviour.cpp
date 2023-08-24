#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/bus.h"


void test_adc_abs_behaviour_with_carry()
{
    SystemBus bus;
    uint8_t target_result {0x9C};
    SystemMemory program_code {0xA9, 0x28, 0x8D, 0x21, 0x61, 0xA9, 0x73, 0x6D, 0x21, 0x61, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 1;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_adc_abs_behaviour_without_carry()
{
    SystemBus bus;
    uint8_t target_result {0x9B};
    SystemMemory program_code {0xA9, 0x28, 0x8D, 0x22, 0x62, 0xA9, 0x73, 0x6D, 0x22, 0x62, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 0;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_and_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x22};
    SystemMemory program_code {0xA9, 0xAA, 0x8D, 0x23, 0x63, 0xA9, 0x33, 0x2D, 0x23, 0x63, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_asl_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x94};
    SystemMemory program_code {0xA9, 0xCA, 0x8D, 0x24, 0x64, 0x0E, 0x24, 0x64, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0x6424) == target_result);
}

void test_bit_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_word {0x76};
    SystemMemory program_code {0xA9, 0x69, 0x8D, 0x25, 0x65, 0xA9, 0x96, 0x2C, 0x25, 0x65, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.word == target_word);
}

void test_cmp_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA9, 0x77, 0x8D, 0x26, 0x66, 0xCD, 0x26, 0x66, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.word == target_word);
}

void test_cpx_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA2, 0x77, 0x8E, 0x27, 0x67, 0xEC, 0x27, 0x67, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.word == target_word);
}

void test_cpy_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_word {0x37};
    SystemMemory program_code {0xA0, 0x77, 0x8C, 0x28, 0x68, 0xCC, 0x28, 0x68, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.word == target_word);
}

void test_dec_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x32};
    SystemMemory program_code {0xA9, 0x33, 0x8D, 0x29, 0x69, 0xCE, 0x29, 0x69, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0x6929) == target_result);
}

void test_eor_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x99};
    SystemMemory program_code {0xA9, 0xAA, 0x8D, 0x2A, 0x6A, 0xA9, 0x33, 0x4D, 0x2A, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_inc_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x34};
    SystemMemory program_code {0xA9, 0x33, 0x8D, 0x2B, 0x6B, 0xEE, 0x2B, 0x6B, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0x6B2B) == target_result);
}

void test_jmp_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_accumulator {0x62};
    SystemMemory program_code {0xA9, 0x62, 0x4C, 0x09, 0x00, 0xA9, 0xAA, 0x69, 0x12, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_accumulator);
}

void test_jsr_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_accumulator {0x90};
    SystemMemory program_code {0x20, 0x06, 0x00, 0x20, 0x09, 0x00, 0xA9, 0x90, 0x60, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_accumulator);
}

void test_lda_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_value {0xAE};
    SystemMemory program_code {0xA9, 0xAE, 0x8D, 0x2C, 0x6C, 0xA9, 0x00, 0xAD, 0x2C, 0x6C, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_value);
}

void test_ldx_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_value {0xCB};
    SystemMemory program_code {0xA2, 0xCB, 0x8E, 0x2D, 0x6D, 0xA2, 0x00, 0xAE, 0x2D, 0x6D, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.x_reg == target_value);
}

void test_ldy_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_value {0xEA};
    SystemMemory program_code {0xA0, 0xEA, 0x8C, 0x2E, 0x6E, 0xA0, 0x00, 0xAC, 0x2E, 0x6E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.y_reg == target_value);
}

void test_lsr_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x4B};
    SystemMemory program_code {0xA9, 0x97, 0x8D, 0x2F, 0x6F, 0x4E, 0x2F, 0x6F, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0x6F2F) == target_result);
}

void test_ora_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0xBB};
    SystemMemory program_code {0xA9, 0xAA, 0x8D, 0xFF, 0xCF, 0xA9, 0x33, 0x0D, 0xFF, 0xCF, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_rol_abs_behaviour_with_carry()
{
    SystemBus bus;
    uint8_t target_result {0x3D};
    SystemMemory program_code {0xA9, 0x9E, 0x8D, 0xFE, 0xCE, 0x2E, 0xFE, 0xCE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 1;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0xCEFE) == target_result);
}

void test_rol_abs_behaviour_without_carry()
{
    SystemBus bus;
    uint8_t target_result {0x3C};
    SystemMemory program_code {0xA9, 0x9E, 0x8D, 0xFD, 0xCD, 0x2E, 0xFD, 0xCD, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 0;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0xCDFD) == target_result);
}

void test_ror_abs_behaviour_with_carry()
{
    SystemBus bus;
    uint8_t target_result {0xA6};
    SystemMemory program_code {0xA9, 0x4D, 0x8D, 0xFC, 0xCC, 0x6E, 0xFC, 0xCC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 1;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0xCCFC) == target_result);
}

void test_ror_abs_behaviour_without_carry()
{
    SystemBus bus;
    uint8_t target_result {0x26};
    SystemMemory program_code {0xA9, 0x4D, 0x8D, 0xFB, 0xCB, 0x6E, 0xFB, 0xCB, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 0;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0xCBFB) == target_result);
}

void test_sbc_abs_behaviour_with_carry()
{
    SystemBus bus;
    uint8_t target_result {0x4B};
    SystemMemory program_code {0xA9, 0x28, 0x8D, 0xFA, 0xCA, 0xA9, 0x73, 0xED, 0xFA, 0xCA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 1;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_sbc_abs_behaviour_without_carry()
{
    SystemBus bus;
    uint8_t target_result {0x4A};
    SystemMemory program_code {0xA9, 0x28, 0x8D, 0xF9, 0xC9, 0xA9, 0x73, 0xED, 0xF9, 0xC9, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 0;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_sta_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA9, 0x31, 0x8D, 0xF8, 0xC8, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0xC8F8) == target_result);
}

void test_stx_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA2, 0x31, 0x8E, 0xF7, 0xC7, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0xC7F7) == target_result);
}

void test_sty_abs_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA0, 0x31, 0x8C, 0xF6, 0xC6, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0xC6F6) == target_result);
}


void ut_cpu_absolute_opcodes_behaviour()
{
    TEST_SET;

    test_adc_abs_behaviour_with_carry();
    test_adc_abs_behaviour_without_carry();
    test_and_abs_behaviour();
    test_asl_abs_behaviour();
    test_bit_abs_behaviour();
    test_cmp_abs_behaviour();
    test_cpx_abs_behaviour();
    test_cpy_abs_behaviour();
    test_dec_abs_behaviour();
    test_eor_abs_behaviour();
    test_inc_abs_behaviour();
    test_jmp_abs_behaviour();
    test_jsr_abs_behaviour();
    test_lda_abs_behaviour();
    test_ldx_abs_behaviour();
    test_ldy_abs_behaviour();
    test_lsr_abs_behaviour();
    test_ora_abs_behaviour();
    test_rol_abs_behaviour_with_carry();
    test_rol_abs_behaviour_without_carry();
    test_ror_abs_behaviour_with_carry();
    test_ror_abs_behaviour_without_carry();
    test_sbc_abs_behaviour_with_carry();
    test_sbc_abs_behaviour_without_carry();
    test_sta_abs_behaviour();
    test_stx_abs_behaviour();
    test_sty_abs_behaviour();
}
