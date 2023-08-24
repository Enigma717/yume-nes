#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/bus.h"


void test_bcc_rel_behaviour()
{
    SystemBus bus;
    uint8_t target_accumulator {0x4D};
    SystemMemory program_code {0xA9, 0x4D, 0x85, 0xA0, 0x06, 0xA0, 0x90, 0x02, 0xA9, 0x00, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_accumulator);
}

void test_bcs_rel_behaviour()
{
    SystemBus bus;
    uint8_t target_accumulator {0xAD};
    SystemMemory program_code {0xA9, 0xAD, 0x85, 0x80, 0x06, 0x80, 0xB0, 0x02, 0xA9, 0x00, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_accumulator);
}

void test_beq_rel_behaviour()
{
    SystemBus bus;
    uint8_t target_accumulator {0x21};
    SystemMemory program_code {0xA9, 0x21, 0xC9, 0x21, 0xF0, 0x02, 0xA9, 0x00, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_accumulator);
}

void test_bmi_rel_behaviour()
{
    SystemBus bus;
    uint8_t target_accumulator {0x99};
    SystemMemory program_code {0xA9, 0x99, 0x85, 0x90, 0xC6, 0x90, 0x30, 0x02, 0xA9, 0x00, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_accumulator);
}

void test_bne_rel_behaviour()
{
    SystemBus bus;
    uint8_t target_accumulator {0x37};
    SystemMemory program_code {0xA9, 0x37, 0xC9, 0xAD, 0xD0, 0x02, 0xA9, 0x00, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_accumulator);
}

void test_bpl_rel_behaviour()
{
    SystemBus bus;
    uint8_t target_accumulator {0x14};
    SystemMemory program_code {0xA9, 0x14, 0x48, 0xA9, 0x00, 0x68, 0x10, 0x02, 0xA9, 0x00, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_accumulator);
}

void test_bvc_rel_behaviour()
{
    SystemBus bus;
    uint8_t target_accumulator {0x50};
    SystemMemory program_code {0xA9, 0x62, 0xE9, 0x11, 0x50, 0x02, 0xA9, 0x00, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_accumulator);
}

void test_bvs_rel_behaviour()
{
    SystemBus bus;
    uint8_t target_accumulator {0xB8};
    SystemMemory program_code {0xA9, 0x42, 0x69, 0x76, 0x70, 0x02, 0xA9, 0x00, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_accumulator);
}


void ut_cpu_relative_opcodes_behaviour()
{
    TEST_SET;

    test_bcc_rel_behaviour();
    test_bcs_rel_behaviour();
    test_beq_rel_behaviour();
    test_bmi_rel_behaviour();
    test_bne_rel_behaviour();
    test_bpl_rel_behaviour();
    test_bvc_rel_behaviour();
    test_bvs_rel_behaviour();
}
