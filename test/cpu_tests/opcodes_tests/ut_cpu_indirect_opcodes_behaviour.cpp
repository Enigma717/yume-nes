#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/system.h"


void test_jmp_ind_behaviour()
{
    System nes;
    uint8_t target_accumulator {0x26};
    SystemMemory program_code {0xA9, 0x0F, 0x8D, 0xFE, 0xAA, 0xA9, 0x00, 0x8D, 0xFF,
        0xAA, 0x6C, 0xFE, 0xAA, 0xA9, 0xFF, 0xA9, 0x26, 0x00};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.acc == target_accumulator);
}

void test_jmp_ind_page_crossing_bug_behaviour()
{
    System nes;
    uint16_t target_address {0x4080};
    SystemMemory program_code {0xA9, 0x40, 0x8D, 0x00, 0x30, 0xA9, 0x80, 0x8D, 0xFF, 0x30,
        0xA9, 0x50, 0x8D, 0x00, 0x31, 0xA9, 0x00, 0x8D, 0x80,
        0x40, 0xA9, 0x37, 0x8D, 0x80, 0x50, 0x6C, 0xFF, 0x30};

    nes.ram->memory_load_program(program_code, nes.cpu.pc);
    nes.cpu.status.flag.carry = 0;

    do {
        nes.cpu.perform_cycle();
    } while (!(nes.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(nes.cpu.arg_address == target_address);
}


void ut_cpu_indirect_opcodes_behaviour()
{
    TEST_SET;

    test_jmp_ind_behaviour();
    test_jmp_ind_page_crossing_bug_behaviour();
}
