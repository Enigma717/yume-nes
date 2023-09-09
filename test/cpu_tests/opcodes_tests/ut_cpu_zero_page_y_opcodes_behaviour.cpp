#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/system.h"


void test_ldx_zpy_behaviour()
{
    System nes;
    uint8_t target_value {0xEA};
    SystemMemory program_code {0xA0, 0x89, 0xA2, 0xEA, 0x86, 0xB7, 0xA2, 0x00, 0xB6, 0x2E, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.x_reg == target_value);
}

void test_stx_zpy_behaviour()
{
    System nes;
    uint8_t target_result {0x31};
    SystemMemory program_code {0xA0, 0x58, 0xA2, 0x31, 0x96, 0xF7, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.ram->memory_read(0x4F) == target_result);
}


void ut_cpu_zero_page_y_opcodes_behaviour()
{
    TEST_SET;

    test_ldx_zpy_behaviour();
    test_stx_zpy_behaviour();
}
