#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/bus.h"


void test_adc_zpg_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x28, 0x85, 0x21, 0xA9, 0xFF, 0x65, 0x21, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_adc_zpg_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x15, 0x85, 0x21, 0xA9, 0x73, 0x65, 0x21, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_adc_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x85, 0x21, 0xA9, 0xFF, 0x65, 0x21, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_adc_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xAD, 0x85, 0x21, 0xA9, 0x16, 0x65, 0x21, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_adc_zpg_overflow_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x63, 0x85, 0x21, 0xA9, 0x58, 0x65, 0x21, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 1);
}

void test_adc_zpg_overflow_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x05, 0x85, 0x21, 0xA9, 0xAD, 0x65, 0x21, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 0);
}

void test_adc_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x71, 0x85, 0x21, 0xA9, 0x44, 0x65, 0x21, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_adc_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x09, 0x85, 0x21, 0xA9, 0x08, 0x65, 0x21, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_and_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x55, 0x85, 0x23, 0xA9, 0xAA, 0x25, 0x23, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_and_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xFF, 0x85, 0x23, 0xA9, 0x25, 0x25, 0x23, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_and_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xCD, 0x85, 0x23, 0xA9, 0x99, 0x25, 0x23, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_and_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x67, 0x85, 0x23, 0xA9, 0x81, 0x25, 0x23, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_asl_zpg_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xBA, 0x85, 0x24, 0x06, 0x24, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_asl_zpg_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x54, 0x85, 0x24, 0x06, 0x24, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_asl_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x80,  0x85, 0x24, 0x06, 0x24, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_asl_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x7C, 0x85, 0x24, 0x06, 0x24, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_asl_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x67, 0x85, 0x24, 0x06, 0x24, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_asl_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x21, 0x85, 0x24, 0x06, 0x24, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_bit_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x69, 0x85, 0x25, 0xA9, 0x96, 0x24, 0x25, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_bit_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x55, 0x85, 0x25, 0xA9, 0xE2, 0x24, 0x25, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_bit_zpg_overflow_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x48, 0x85, 0x25, 0xA9, 0x92, 0x24, 0x25, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 1);
}

void test_bit_zpg_overflow_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x28, 0x85, 0x25, 0xA9, 0x16, 0x24, 0x25, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 0);
}

void test_bit_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xC9, 0x85, 0x25, 0xA9, 0xF0, 0x24, 0x25, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_bit_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x85, 0x25, 0xA9, 0x7D, 0x24, 0x25, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_cmp_zpg_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x51, 0x85, 0x26, 0xA9, 0x77, 0xC5, 0x26, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_cmp_zpg_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xA0, 0x85, 0x26, 0xA9, 0x21, 0xC5, 0x26, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_cmp_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x37, 0x85, 0x26, 0xC5, 0x26, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_cmp_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x10, 0x85, 0x26, 0xA9, 0x62, 0xC5, 0x26, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_cmp_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xEE, 0x85, 0x26, 0xA9, 0x01, 0xC5, 0x26, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_cmp_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x90, 0x85, 0x26, 0xA9, 0x69, 0xC5, 0x26, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_cpx_zpg_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x51, 0x86, 0x27, 0xA2, 0x77, 0xE4, 0x27, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_cpx_zpg_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0xA0, 0x86, 0x27, 0xA2, 0x21, 0xE4, 0x27, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_cpx_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x37, 0x86, 0x27, 0xE4, 0x27, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_cpx_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x10, 0x86, 0x27, 0xA2, 0x62, 0xE4, 0x27, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_cpx_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0xEE, 0x86, 0x27, 0xA2, 0x01, 0xE4, 0x27, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_cpx_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x90, 0x86, 0x27, 0xA2, 0x69, 0xE4, 0x27, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_cpy_zpg_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x51, 0x84, 0x28, 0xC4, 0x28, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_cpy_zpg_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0xA0, 0x84, 0x28, 0xA0, 0x21, 0xC4, 0x28, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_cpy_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x37, 0x84, 0x28, 0xA0, 0x37, 0xC4, 0x28, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_cpy_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x10, 0x84, 0x28, 0xA0, 0x62, 0xC4, 0x28, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_cpy_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0xEE, 0x84, 0x28, 0xA0, 0x01, 0xC4, 0x28, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_cpy_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x90, 0x84, 0x28, 0xA0, 0x69, 0xC4, 0x28, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_dec_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x85, 0x29, 0xC6, 0x29, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_dec_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xAE, 0x85, 0x29, 0xC6, 0x29, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_dec_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xDC, 0x85, 0x29, 0xC6, 0x29, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_dec_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x62, 0x85, 0x29, 0xC6, 0x29, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_eor_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xDA, 0x85, 0x2A, 0xA9, 0xDA, 0x45, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_eor_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x95, 0x85, 0x2A, 0xA9, 0x5A, 0x45, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_eor_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x43, 0x85, 0x2A, 0xA9, 0xA2, 0x45, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_eor_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x22, 0x85, 0x2A, 0xA9, 0x39, 0x45, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_inc_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xFF, 0x85, 0x2B, 0xE6, 0x2B, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_inc_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x09, 0x85, 0x2B, 0xE6, 0x2B, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_inc_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xA2, 0x85, 0x2B, 0xE6, 0x2B, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_inc_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x10, 0x85, 0x2B, 0xE6, 0x2B, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_lda_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x00, 0x85, 0x2C, 0xA9, 0xAE, 0xA5, 0x2C, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_lda_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xAE, 0x85, 0x2C, 0xA9, 0x00, 0xA5, 0x2C, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_lda_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xAF, 0x85, 0x2C, 0xA9, 0x00, 0xA5, 0x2C, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_lda_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x85, 0x2C, 0xA9, 0x00, 0xA5, 0x2C, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_ldx_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x00, 0x86, 0x2D, 0xA2, 0xAE, 0xA6, 0x2D, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_ldx_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0xAE, 0x86, 0x2D, 0xA2, 0x00, 0xA6, 0x2D, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_ldx_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0xAF, 0x86, 0x2D, 0xA2, 0x00, 0xA6, 0x2D, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_ldx_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA2, 0x01, 0x86, 0x2D, 0xA2, 0x00, 0xA6, 0x2D, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_ldy_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x00, 0x84, 0x2E, 0xA0, 0xAE, 0xA4, 0x2E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_ldy_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0xAE, 0x84, 0x2E, 0xA0, 0x00, 0xA4, 0x2E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_ldy_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0xAF, 0x84, 0x2E, 0xA0, 0x00, 0xA4, 0x2E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_ldy_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x01, 0x84, 0x2E, 0xA0, 0x00, 0xA4, 0x2E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_lsr_zpg_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x89, 0x85, 0x2F, 0x46, 0x2F, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_lsr_zpg_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x2A, 0x85, 0x2F, 0x46, 0x2F, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_lsr_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x85, 0x2F, 0x46, 0x2F, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_lsr_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xEE, 0x85, 0x2F, 0x46, 0x2F, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_lsr_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x37, 0x85, 0x2F, 0x46, 0x2F, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_ora_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x00, 0x85, 0xFF, 0x05, 0xFF, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_ora_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x8A, 0x85, 0xFF, 0xA9, 0x56, 0x05, 0xFF, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_ora_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x28, 0x85, 0xFF, 0xA9, 0xEF, 0x05, 0xFF, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_ora_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x45, 0x85, 0xFF, 0xA9, 0x23, 0x05, 0xFF, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_rol_zpg_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x99, 0x85, 0xFE, 0x26, 0xFE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_rol_zpg_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x6C, 0x85, 0xFE, 0x26, 0xFE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_rol_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x80, 0x85, 0xFE, 0x26, 0xFE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_rol_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xEF, 0x85, 0xFE, 0x26, 0xFE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_rol_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xD7, 0x85, 0xFE, 0x26, 0xFE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_rol_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x86, 0x85, 0xFE, 0x26, 0xFE, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_ror_zpg_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xCD, 0x85, 0xFC, 0x66, 0xFC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_ror_zpg_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x9E, 0x85, 0xFC, 0x66, 0xFC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_ror_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x85, 0xFC, 0x66, 0xFC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_ror_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xC4, 0x85, 0xFC, 0x66, 0xFC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_ror_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xA1, 0x85, 0xFC, 0x66, 0xFC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 1;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_ror_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x02, 0x85, 0xFC, 0x66, 0xFC, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_sbc_zpg_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xCF, 0x85, 0xFA, 0xA9, 0xFF, 0xE5, 0xFA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_sbc_zpg_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xFE, 0x85, 0xFA, 0xA9, 0xAA, 0xE5, 0xFA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_sbc_zpg_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x76, 0x85, 0xFA, 0xA9, 0x77, 0xE5, 0xFA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_sbc_zpg_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x11, 0x85, 0xFA, 0xA9, 0xC2, 0xE5, 0xFA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_sbc_zpg_overflow_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x7C, 0x85, 0xFA, 0xA9, 0x01, 0xE5, 0xFA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 1);
}

void test_sbc_zpg_overflow_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x65, 0x85, 0xFA, 0xA9, 0x7E, 0xE5, 0xFA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.overflow == 0);
}

void test_sbc_zpg_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x09, 0x85, 0xFA, 0xA9, 0xDA, 0xE5, 0xFA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_sbc_zpg_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x0F, 0x85, 0xFA, 0xA9, 0x40, 0xE5, 0xFA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}


void ut_cpu_zero_page_opcodes_flags()
{
    TEST_SET;

    test_adc_zpg_carry_flag_set_true();
    test_adc_zpg_carry_flag_set_false();
    test_adc_zpg_zero_flag_set_true();
    test_adc_zpg_zero_flag_set_false();
    test_adc_zpg_overflow_flag_set_true();
    test_adc_zpg_overflow_flag_set_false();
    test_adc_zpg_negative_flag_set_true();
    test_adc_zpg_negative_flag_set_false();

    test_and_zpg_zero_flag_set_true();
    test_and_zpg_zero_flag_set_false();
    test_and_zpg_negative_flag_set_true();
    test_and_zpg_negative_flag_set_false();

    test_asl_zpg_carry_flag_set_true();
    test_asl_zpg_carry_flag_set_false();
    test_asl_zpg_zero_flag_set_true();
    test_asl_zpg_zero_flag_set_false();
    test_asl_zpg_negative_flag_set_true();
    test_asl_zpg_negative_flag_set_false();

    test_bit_zpg_zero_flag_set_true();
    test_bit_zpg_zero_flag_set_false();
    test_bit_zpg_overflow_flag_set_true();
    test_bit_zpg_overflow_flag_set_false();
    test_bit_zpg_negative_flag_set_true();
    test_bit_zpg_negative_flag_set_false();

    test_cmp_zpg_carry_flag_set_true();
    test_cmp_zpg_carry_flag_set_false();
    test_cmp_zpg_zero_flag_set_true();
    test_cmp_zpg_zero_flag_set_false();
    test_cmp_zpg_negative_flag_set_true();
    test_cmp_zpg_negative_flag_set_false();

    test_cpx_zpg_carry_flag_set_true();
    test_cpx_zpg_carry_flag_set_false();
    test_cpx_zpg_zero_flag_set_true();
    test_cpx_zpg_zero_flag_set_false();
    test_cpx_zpg_negative_flag_set_true();
    test_cpx_zpg_negative_flag_set_false();

    test_cpy_zpg_carry_flag_set_true();
    test_cpy_zpg_carry_flag_set_false();
    test_cpy_zpg_zero_flag_set_true();
    test_cpy_zpg_zero_flag_set_false();
    test_cpy_zpg_negative_flag_set_true();
    test_cpy_zpg_negative_flag_set_false();

    test_dec_zpg_zero_flag_set_true();
    test_dec_zpg_zero_flag_set_false();
    test_dec_zpg_negative_flag_set_true();
    test_dec_zpg_negative_flag_set_false();

    test_eor_zpg_zero_flag_set_true();
    test_eor_zpg_zero_flag_set_false();
    test_eor_zpg_negative_flag_set_true();
    test_eor_zpg_negative_flag_set_false();

    test_inc_zpg_zero_flag_set_true();
    test_inc_zpg_zero_flag_set_false();
    test_inc_zpg_negative_flag_set_true();
    test_inc_zpg_negative_flag_set_false();

    test_lda_zpg_zero_flag_set_true();
    test_lda_zpg_zero_flag_set_false();
    test_lda_zpg_negative_flag_set_true();
    test_lda_zpg_negative_flag_set_false();

    test_ldx_zpg_zero_flag_set_true();
    test_ldx_zpg_zero_flag_set_false();
    test_ldx_zpg_negative_flag_set_true();
    test_ldx_zpg_negative_flag_set_false();

    test_ldy_zpg_zero_flag_set_true();
    test_ldy_zpg_zero_flag_set_false();
    test_ldy_zpg_negative_flag_set_true();
    test_ldy_zpg_negative_flag_set_false();

    test_lsr_zpg_carry_flag_set_true();
    test_lsr_zpg_carry_flag_set_false();
    test_lsr_zpg_zero_flag_set_true();
    test_lsr_zpg_zero_flag_set_false();
    test_lsr_zpg_negative_flag_set_false();

    test_ora_zpg_zero_flag_set_true();
    test_ora_zpg_zero_flag_set_false();
    test_ora_zpg_negative_flag_set_true();
    test_ora_zpg_negative_flag_set_false();

    test_rol_zpg_carry_flag_set_true();
    test_rol_zpg_carry_flag_set_false();
    test_rol_zpg_zero_flag_set_true();
    test_rol_zpg_zero_flag_set_false();
    test_rol_zpg_negative_flag_set_true();
    test_rol_zpg_negative_flag_set_false();

    test_ror_zpg_carry_flag_set_true();
    test_ror_zpg_carry_flag_set_false();
    test_ror_zpg_zero_flag_set_true();
    test_ror_zpg_zero_flag_set_false();
    test_ror_zpg_negative_flag_set_true();
    test_ror_zpg_negative_flag_set_false();

    test_sbc_zpg_carry_flag_set_true();
    test_sbc_zpg_carry_flag_set_false();
    test_sbc_zpg_zero_flag_set_true();
    test_sbc_zpg_zero_flag_set_false();
    test_sbc_zpg_overflow_flag_set_true();
    test_sbc_zpg_overflow_flag_set_false();
    test_sbc_zpg_negative_flag_set_true();
    test_sbc_zpg_negative_flag_set_false();
}
