#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/bus.h"


void test_jmp_ind_behaviour()
{
    SystemBus bus;
    uint8_t target_accumulator {0x26};
    SystemMemory program_code {0xA9, 0x0E, 0x8D, 0xFE, 0xAA, 0xA9, 0x00, 0x8D, 0xFF, 0xAA, 0x6C, 0xFE, 0xAA, 0xA9, 0xFF, 0xA9, 0x26, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 0;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_accumulator);
}


void ut_cpu_indirect_opcodes_behaviour()
{
    TEST_SET;

    test_jmp_ind_behaviour();
}
