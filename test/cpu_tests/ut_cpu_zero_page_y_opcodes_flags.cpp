#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/bus.h"



void test_ldx_zpy_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x89, 0xA2, 0x00, 0x86, 0xB7, 0xA2, 0xAE, 0xB6, 0x2E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_ldx_zpy_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x89, 0xA2, 0xAE, 0x86, 0xB7, 0xA2, 0x00, 0xB6, 0x2E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_ldx_zpy_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x89, 0xA2, 0xAF, 0x86, 0xB7, 0xA2, 0x00, 0xB6, 0x2E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_ldx_zpy_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA0, 0x89, 0xA2, 0x01, 0x86, 0xB7, 0xA2, 0x00, 0xB6, 0x2E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}


void ut_cpu_zero_page_y_opcodes_flags()
{
    TEST_SET;


    test_ldx_zpy_zero_flag_set_true();
    test_ldx_zpy_zero_flag_set_false();
    test_ldx_zpy_negative_flag_set_true();
    test_ldx_zpy_negative_flag_set_false();
}
