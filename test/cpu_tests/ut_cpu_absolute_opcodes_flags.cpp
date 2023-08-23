#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/bus.h"


void test_adc_abs_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x28, 0x8D, 0x21, 0x61, 0xA9, 0xFF, 0x6D, 0x21, 0x61, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_adc_abs_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x15, 0x8D, 0x21, 0x61, 0xA9, 0x73, 0x6D, 0x21, 0x61, 0x61, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_adc_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x8D, 0x21, 0x61, 0xA9, 0xFF, 0x6D, 0x21, 0x61, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_adc_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xAD, 0x8D, 0x21, 0x61, 0xA9, 0x16, 0x6D, 0x21, 0x61, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_adc_abs_overflow_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x63, 0x8D, 0x21, 0x61, 0xA9, 0x58, 0x6D, 0x21, 0x61, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 1);
}

void test_adc_abs_overflow_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x05, 0x8D, 0x21, 0x61, 0xA9, 0xAD, 0x6D, 0x21, 0x61, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 0);
}

void test_adc_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x71, 0x8D, 0x21, 0x61, 0xA9, 0x44, 0x6D, 0x21, 0x61, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_adc_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x09, 0x8D, 0x21, 0x61, 0xA9, 0x08, 0x6D, 0x21, 0x61, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_and_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x55, 0x8D, 0x23, 0x63, 0xA9, 0xAA, 0x2D, 0x23, 0x63, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_and_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xFF, 0x8D, 0x23, 0x63, 0xA9, 0x25, 0x2D, 0x23, 0x63, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_and_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xCD, 0x8D, 0x23, 0x63, 0xA9, 0x99, 0x2D, 0x23, 0x63, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_and_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x67, 0x8D, 0x23, 0x63, 0xA9, 0x81, 0x2D, 0x23, 0x63, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_asl_abs_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xBA, 0x8D, 0x24, 0x64, 0x0E, 0x24, 0x64, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_asl_abs_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x54, 0x8D, 0x24, 0x64, 0x0E, 0x24, 0x64, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_asl_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x80,  0x8D, 0x24, 0x64, 0x0E, 0x24, 0x64, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_asl_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x7C, 0x8D, 0x24, 0x64, 0x0E, 0x24, 0x64, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_asl_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x67, 0x8D, 0x24, 0x64, 0x0E, 0x24, 0x64, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_asl_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x21, 0x8D, 0x24, 0x64, 0x0E, 0x24, 0x64, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_bit_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x69, 0x8D, 0x25, 0x65, 0xA9, 0x96, 0x2C, 0x25, 0x65, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_bit_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x55, 0x8D, 0x25, 0x65, 0xA9, 0xE2, 0x2C, 0x25, 0x65, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_bit_abs_overflow_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x48, 0x8D, 0x25, 0x65, 0xA9, 0x92, 0x2C, 0x25, 0x65, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 1);
}

void test_bit_abs_overflow_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x28, 0x8D, 0x25, 0x65, 0xA9, 0x16, 0x2C, 0x25, 0x65, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 0);
}

void test_bit_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xC9, 0x8D, 0x25, 0x65, 0xA9, 0xF0, 0x2C, 0x25, 0x65, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_bit_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x8D, 0x25, 0x65, 0xA9, 0x7D, 0x2C, 0x25, 0x65, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_cmp_abs_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x51, 0x8D, 0x26, 0x66, 0xA9, 0x77, 0xCD, 0x26, 0x66, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_cmp_abs_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xA0, 0x8D, 0x26, 0x66, 0xA9, 0x21, 0xCD, 0x26, 0x66, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_cmp_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x37, 0x8D, 0x26, 0x66, 0xCD, 0x26, 0x66, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_cmp_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x10, 0x8D, 0x26, 0x66, 0xA9, 0x62, 0xCD, 0x26, 0x66, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_cmp_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xEE, 0x8D, 0x26, 0x66, 0xA9, 0x01, 0xCD, 0x26, 0x66, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_cmp_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x90, 0x8D, 0x26, 0x66, 0xA9, 0x69, 0xCD, 0x26, 0x66, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_cpx_abs_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x51, 0x8E, 0x27, 0x67, 0xA2, 0x77, 0xEC, 0x27, 0x67, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_cpx_abs_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0xA0, 0x8E, 0x27, 0x67, 0xA2, 0x21, 0xEC, 0x27, 0x67, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_cpx_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x37, 0x8E, 0x27, 0x67, 0xEC, 0x27, 0x67, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_cpx_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x10, 0x8E, 0x27, 0x67, 0xA2, 0x62, 0xEC, 0x27, 0x67, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_cpx_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0xEE, 0x8E, 0x27, 0x67, 0xA2, 0x01, 0xEC, 0x27, 0x67, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_cpx_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x90, 0x8E, 0x27, 0x67, 0xA2, 0x69, 0xEC, 0x27, 0x67, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_cpy_abs_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x51, 0x8C, 0x28, 0x68, 0xCC, 0x28, 0x68, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_cpy_abs_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0xA0, 0x8C, 0x28, 0x68, 0xA0, 0x21, 0xCC, 0x28, 0x68, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_cpy_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x37, 0x8C, 0x28, 0x68, 0xA0, 0x37, 0xCC, 0x28, 0x68, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_cpy_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x10, 0x8C, 0x28, 0x68, 0xA0, 0x62, 0xCC, 0x28, 0x68, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_cpy_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0xEE, 0x8C, 0x28, 0x68, 0xA0, 0x01, 0xCC, 0x28, 0x68, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_cpy_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x90, 0x8C, 0x28, 0x68, 0xA0, 0x69, 0xCC, 0x28, 0x68, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_dec_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x8D, 0x29, 0x69, 0xCE, 0x29, 0x69, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_dec_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xAE, 0x8D, 0x29, 0x69, 0xCE, 0x29, 0x69, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_dec_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xDC, 0x8D, 0x29, 0x69, 0xCE, 0x29, 0x69, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_dec_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x62, 0x8D, 0x29, 0x69, 0xCE, 0x29, 0x69, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_eor_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xDA, 0x8D, 0x2A, 0x6A, 0xA9, 0xDA, 0x4D, 0x2A, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_eor_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x95, 0x8D, 0x2A, 0x6A, 0xA9, 0x5A, 0x4D, 0x2A, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_eor_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x43, 0x8D, 0x2A, 0x6A, 0xA9, 0xA2, 0x4D, 0x2A, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_eor_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x22, 0x8D, 0x2A, 0x6A, 0xA9, 0x39, 0x4D, 0x2A, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_inc_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xFF, 0x8D, 0x2B, 0x6B, 0xEE, 0x2B, 0x6B, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_inc_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x09, 0x8D, 0x2B, 0x6B, 0xEE, 0x2B, 0x6B, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_inc_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xA2, 0x8D, 0x2B, 0x6B, 0xEE, 0x2B, 0x6B, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_inc_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x10, 0x8D, 0x2B, 0x6B, 0xEE, 0x2B, 0x6B, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_lda_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x00, 0x8D, 0x2C, 0x6C, 0xA9, 0xAE, 0xAD, 0x2C, 0x6C, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_lda_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xAE, 0x8D, 0x2C, 0x6C, 0xA9, 0x00, 0xAD, 0x2C, 0x6C, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_lda_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xAF, 0x8D, 0x2C, 0x6C, 0xA9, 0x00, 0xAD, 0x2C, 0x6C, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_lda_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x8D, 0x2C, 0x6C, 0xA9, 0x00, 0xAD, 0x2C, 0x6C, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_ldx_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x00, 0x8E, 0x2D, 0x6D, 0xA2, 0xAE, 0xAE, 0x2D, 0x6D, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_ldx_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0xAE, 0x8E, 0x2D, 0x6D, 0xA2, 0x00, 0xAE, 0x2D, 0x6D, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_ldx_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0xAF, 0x8E, 0x2D, 0x6D, 0xA2, 0x00, 0xAE, 0x2D, 0x6D, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_ldx_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x01, 0x8E, 0x2D, 0x6D, 0xA2, 0x00, 0xAE, 0x2D, 0x6D, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_ldy_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x00, 0x8C, 0x2E, 0x6E, 0xA0, 0xAE, 0xAC, 0x2E, 0x6E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_ldy_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0xAE, 0x8C, 0x2E, 0x6E, 0xA0, 0x00, 0xAC, 0x2E, 0x6E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_ldy_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0xAF, 0x8C, 0x2E, 0x6E, 0xA0, 0x00, 0xAC, 0x2E, 0x6E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_ldy_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x01, 0x8C, 0x2E, 0x6E, 0xA0, 0x00, 0xAC, 0x2E, 0x6E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_lsr_abs_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x89, 0x8D, 0x2F, 0x6F, 0x4E, 0x2F, 0x6F, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_lsr_abs_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x2A, 0x8D, 0x2F, 0x6F, 0x4E, 0x2F, 0x6F, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_lsr_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x8D, 0x2F, 0x6F, 0x4E, 0x2F, 0x6F, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_lsr_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xEE, 0x8D, 0x2F, 0x6F, 0x4E, 0x2F, 0x6F, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_lsr_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x37, 0x8D, 0x2F, 0x6F, 0x4E, 0x2F, 0x6F, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_ora_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x00, 0x8D, 0xFF, 0xCF, 0x0D, 0xFF, 0xCF, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_ora_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x8A, 0x8D, 0xFF, 0xCF, 0xA9, 0x56, 0x0D, 0xFF, 0xCF, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_ora_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x28, 0x8D, 0xFF, 0xCF, 0xA9, 0xEF, 0x0D, 0xFF, 0xCF, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_ora_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x45, 0x8D, 0xFF, 0xCF, 0xA9, 0x23, 0x0D, 0xFF, 0xCF, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_rol_abs_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x99, 0x8D, 0xFE, 0xCE, 0x2E, 0xFE, 0xCE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_rol_abs_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x6C, 0x8D, 0xFE, 0xCE, 0x2E, 0xFE, 0xCE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_rol_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x80, 0x8D, 0xFE, 0xCE, 0x2E, 0xFE, 0xCE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_rol_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xEF, 0x8D, 0xFE, 0xCE, 0x2E, 0xFE, 0xCE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_rol_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xD7, 0x8D, 0xFE, 0xCE, 0x2E, 0xFE, 0xCE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_rol_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x8E, 0x8D, 0xFE, 0xCE, 0x2E, 0xFE, 0xCE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_ror_abs_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xCD, 0x8D, 0xFC, 0xCC, 0x6E, 0xFC, 0xCC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_ror_abs_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x9E, 0x8D, 0xFC, 0xCC, 0x6E, 0xFC, 0xCC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_ror_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x8D, 0xFC, 0xCC, 0x6E, 0xFC, 0xCC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_ror_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xC4, 0x8D, 0xFC, 0xCC, 0x6E, 0xFC, 0xCC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_ror_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xA1, 0x8D, 0xFC, 0xCC, 0x6E, 0xFC, 0xCC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 1;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_ror_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x02, 0x8D, 0xFC, 0xCC, 0x6E, 0xFC, 0xCC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_sbc_abs_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xCF, 0x8D, 0xFA, 0xA9, 0xFF, 0xED, 0xFA, 0xCA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_sbc_abs_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xFE, 0x8D, 0xFA, 0xCA, 0xA9, 0xAA, 0xED, 0xFA, 0xCA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_sbc_abs_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x76, 0x8D, 0xFA, 0xCA, 0xA9, 0x77, 0xED, 0xFA, 0xCA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_sbc_abs_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x11, 0x8D, 0xFA, 0xCA, 0xA9, 0xC2, 0xED, 0xFA, 0xCA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_sbc_abs_overflow_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x7C, 0x8D, 0xFA, 0xCA, 0xA9, 0x01, 0xED, 0xFA, 0xCA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 1);
}

void test_sbc_abs_overflow_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x65, 0x8D, 0xFA, 0xCA, 0xA9, 0x7E, 0xED, 0xFA, 0xCA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 0);
}

void test_sbc_abs_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x09, 0x8D, 0xFA, 0xCA, 0xA9, 0xDA, 0xED, 0xFA, 0xCA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_sbc_abs_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x0F, 0x8D, 0xFA, 0xCA, 0xA9, 0x40, 0xED, 0xFA, 0xCA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}


void ut_cpu_absolute_opcodes_flags()
{
    TEST_SET;

    test_adc_abs_carry_flag_set_true();
    test_adc_abs_carry_flag_set_false();
    test_adc_abs_zero_flag_set_true();
    test_adc_abs_zero_flag_set_false();
    test_adc_abs_overflow_flag_set_true();
    test_adc_abs_overflow_flag_set_false();
    test_adc_abs_negative_flag_set_true();
    test_adc_abs_negative_flag_set_false();

    test_and_abs_zero_flag_set_true();
    test_and_abs_zero_flag_set_false();
    test_and_abs_negative_flag_set_true();
    test_and_abs_negative_flag_set_false();

    test_asl_abs_carry_flag_set_true();
    test_asl_abs_carry_flag_set_false();
    test_asl_abs_zero_flag_set_true();
    test_asl_abs_zero_flag_set_false();
    test_asl_abs_negative_flag_set_true();
    test_asl_abs_negative_flag_set_false();

    test_bit_abs_zero_flag_set_true();
    test_bit_abs_zero_flag_set_false();
    test_bit_abs_overflow_flag_set_true();
    test_bit_abs_overflow_flag_set_false();
    test_bit_abs_negative_flag_set_true();
    test_bit_abs_negative_flag_set_false();

    test_cmp_abs_carry_flag_set_true();
    test_cmp_abs_carry_flag_set_false();
    test_cmp_abs_zero_flag_set_true();
    test_cmp_abs_zero_flag_set_false();
    test_cmp_abs_negative_flag_set_true();
    test_cmp_abs_negative_flag_set_false();

    test_cpx_abs_carry_flag_set_true();
    test_cpx_abs_carry_flag_set_false();
    test_cpx_abs_zero_flag_set_true();
    test_cpx_abs_zero_flag_set_false();
    test_cpx_abs_negative_flag_set_true();
    test_cpx_abs_negative_flag_set_false();

    test_cpy_abs_carry_flag_set_true();
    test_cpy_abs_carry_flag_set_false();
    test_cpy_abs_zero_flag_set_true();
    test_cpy_abs_zero_flag_set_false();
    test_cpy_abs_negative_flag_set_true();
    test_cpy_abs_negative_flag_set_false();

    test_dec_abs_zero_flag_set_true();
    test_dec_abs_zero_flag_set_false();
    test_dec_abs_negative_flag_set_true();
    test_dec_abs_negative_flag_set_false();

    test_eor_abs_zero_flag_set_true();
    test_eor_abs_zero_flag_set_false();
    test_eor_abs_negative_flag_set_true();
    test_eor_abs_negative_flag_set_false();

    test_inc_abs_zero_flag_set_true();
    test_inc_abs_zero_flag_set_false();
    test_inc_abs_negative_flag_set_true();
    test_inc_abs_negative_flag_set_false();

    test_lda_abs_zero_flag_set_true();
    test_lda_abs_zero_flag_set_false();
    test_lda_abs_negative_flag_set_true();
    test_lda_abs_negative_flag_set_false();

    test_ldx_abs_zero_flag_set_true();
    test_ldx_abs_zero_flag_set_false();
    test_ldx_abs_negative_flag_set_true();
    test_ldx_abs_negative_flag_set_false();

    test_ldy_abs_zero_flag_set_true();
    test_ldy_abs_zero_flag_set_false();
    test_ldy_abs_negative_flag_set_true();
    test_ldy_abs_negative_flag_set_false();

    test_lsr_abs_carry_flag_set_true();
    test_lsr_abs_carry_flag_set_false();
    test_lsr_abs_zero_flag_set_true();
    test_lsr_abs_zero_flag_set_false();
    test_lsr_abs_negative_flag_set_false();

    test_ora_abs_zero_flag_set_true();
    test_ora_abs_zero_flag_set_false();
    test_ora_abs_negative_flag_set_true();
    test_ora_abs_negative_flag_set_false();

    test_rol_abs_carry_flag_set_true();
    test_rol_abs_carry_flag_set_false();
    test_rol_abs_zero_flag_set_true();
    test_rol_abs_zero_flag_set_false();
    test_rol_abs_negative_flag_set_true();
    test_rol_abs_negative_flag_set_false();

    test_ror_abs_carry_flag_set_true();
    test_ror_abs_carry_flag_set_false();
    test_ror_abs_zero_flag_set_true();
    test_ror_abs_zero_flag_set_false();
    test_ror_abs_negative_flag_set_true();
    test_ror_abs_negative_flag_set_false();

    test_sbc_abs_carry_flag_set_true();
    test_sbc_abs_carry_flag_set_false();
    test_sbc_abs_zero_flag_set_true();
    test_sbc_abs_zero_flag_set_false();
    test_sbc_abs_overflow_flag_set_true();
    test_sbc_abs_overflow_flag_set_false();
    test_sbc_abs_negative_flag_set_true();
    test_sbc_abs_negative_flag_set_false();
}
