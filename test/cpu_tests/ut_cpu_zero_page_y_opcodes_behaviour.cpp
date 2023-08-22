#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/bus.h"


void test_ldx_zpy_behaviour()
{
    SystemBus bus;
    uint8_t target_value {0xEA};
    SystemMemory program_code {0xA0, 0x89, 0xA2, 0xEA, 0x86, 0xB7, 0xA2, 0x00, 0xB6, 0x2E, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.x_reg == target_value);
}

void test_stx_zpy_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA0, 0x58, 0xA2, 0x31, 0x96, 0xF7, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.ram->memory_read(0x4F) == target_result);
}


void ut_cpu_zero_page_y_opcodes_behaviour()
{
    TEST_SET;

    test_ldx_zpy_behaviour();
    test_stx_zpy_behaviour();
}
