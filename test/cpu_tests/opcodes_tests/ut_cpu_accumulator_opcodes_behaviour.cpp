#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/bus.h"


void test_asl_acc_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x94};
    SystemMemory program_code {0xA9, 0xCA, 0x0A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_lsr_acc_behaviour()
{
    SystemBus bus;
    uint8_t target_result {0x4B};
    SystemMemory program_code {0xA9, 0x97, 0x4A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_rol_acc_behaviour_with_carry()
{
    SystemBus bus;
    uint8_t target_result {0x3D};
    SystemMemory program_code {0xA9, 0x9E, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 1;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_rol_acc_behaviour_without_carry()
{
    SystemBus bus;
    uint8_t target_result {0x3C};
    SystemMemory program_code {0xA9, 0x9E, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 0;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_ror_acc_behaviour_with_carry()
{
    SystemBus bus;
    uint8_t target_result {0xA6};
    SystemMemory program_code {0xA9, 0x4D, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 1;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}

void test_ror_acc_behaviour_without_carry()
{
    SystemBus bus;
    uint8_t target_result {0x26};
    SystemMemory program_code {0xA9, 0x4D, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 0;

    do {
        bus.cpu.perform_cycle();
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.acc == target_result);
}


void ut_cpu_accumulator_opcodes_behaviour()
{
    TEST_SET;

    test_asl_acc_behaviour();
    test_lsr_acc_behaviour();
    test_rol_acc_behaviour_with_carry();
    test_rol_acc_behaviour_without_carry();
    test_ror_acc_behaviour_with_carry();
    test_ror_acc_behaviour_without_carry();
}
