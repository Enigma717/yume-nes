#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/system.h"


void test_correct_cycle_count()
{
    System nes;
    int target_cycles_executed {35};
    SystemMemory program_code {0xA9, 0x40, 0x8D, 0x00, 0x30, 0xA9, 0x80, 0x8D, 0xFF, 0x30,
        0xA9, 0x50, 0x8D, 0x00, 0x31, 0xA9, 0x00, 0x8D, 0x80,
        0x40, 0xA9, 0x37, 0x8D, 0x80, 0x50, 0x6C, 0xFF, 0x30};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cycles_executed == target_cycles_executed);
}

void test_correct_cycle_count_after_branch()
{
    System nes;
    int target_cycles_executed {7};
    SystemMemory program_code {0xA9, 0x37, 0xC9, 0xAD, 0xD0, 0x02, 0xA9, 0x00, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cycles_executed == target_cycles_executed);
}

void test_correct_cycle_count_after_branch_to_new_page()
{
    System nes;
    int target_cycles_executed {15};
    SystemMemory program_code {0xA9, 0x37, 0xC9, 0xAD, 0xD0, 0x7F};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.ram->memory_load_program(program_code, nes.cpu.pc + 0x85);
    nes.cpu.memory_write(0x010A, 0x00);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cycles_executed == target_cycles_executed);
}

void test_correct_cycle_count_after_page_crossing()
{
    System nes;
    int target_cycles_executed {13};
    SystemMemory program_code {0xA2, 0x96, 0xA9, 0x77, 0x8D, 0x3C, 0x67, 0xDD, 0xA6, 0x66, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.cycles_executed == target_cycles_executed);
}


void ut_cpu_cycle_correctness()
{
    TEST_SET;

    test_correct_cycle_count();
    test_correct_cycle_count_after_branch();
    test_correct_cycle_count_after_branch_to_new_page();
    test_correct_cycle_count_after_page_crossing();
}
