#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/bus.h"


void test_perform_cycle_instr_implied()
{
    SystemBus bus;
    uint8_t target_x_reg {0xB4};
    SystemMemory program_code {0xCA, 0x08, 0x68, 0xAA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.x_reg == target_x_reg);
}

void test_correct_cycle_count()
{
    SystemBus bus;
    int target_cycles_executed {36};
    SystemMemory program_code {0xA9, 0x40, 0x8D, 0x00, 0x30, 0xA9, 0x80, 0x8D, 0xFF, 0x30,
        0xA9, 0x50, 0x8D, 0x00, 0x31, 0xA9, 0x00, 0x8D, 0x80,
        0x40, 0xA9, 0x37, 0x8D, 0x80, 0x50, 0x6C, 0xFF, 0x30};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 0;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.cycles_executed == target_cycles_executed);
}

void test_correct_cycle_count_after_branch()
{
    SystemBus bus;
    int target_cycles_executed {8};
    SystemMemory program_code {0xA9, 0x37, 0xC9, 0xAD, 0xD0, 0x02, 0xA9, 0x00, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.cycles_executed == target_cycles_executed);
}

void test_correct_cycle_count_after_branch_to_new_page()
{
    SystemBus bus;
    int target_cycles_executed {9};
    SystemMemory program_code {0xA9, 0x37, 0xC9, 0xAD, 0xD0, 0xFF, 0xA9, 0x00, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.cycles_executed == target_cycles_executed);
}

void test_correct_cycle_count_after_page_crossing()
{
    SystemBus bus;
    int target_cycles_executed {14};
    SystemMemory program_code {0xA2, 0x96, 0xA9, 0x77, 0x8D, 0x3C, 0x67, 0xDD, 0xA6, 0x66, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.cycles_executed == target_cycles_executed);
}


void ut_cpu_perform_cycle_correctness()
{
    TEST_SET;

    test_perform_cycle_instr_implied();
    test_correct_cycle_count();
    test_correct_cycle_count_after_branch();
    test_correct_cycle_count_after_branch_to_new_page();
    test_correct_cycle_count_after_page_crossing();
}
