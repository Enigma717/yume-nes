#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/bus.h"


void test_asl_acc_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xBA, 0x0A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_asl_acc_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x54, 0x0A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_asl_acc_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x80, 0x0A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_asl_acc_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x7C, 0x0A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_asl_acc_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x67, 0x0A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_asl_acc_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x21, 0x0A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_lsr_acc_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x89, 0x4A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_lsr_acc_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x2A, 0x4A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_lsr_acc_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x4A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_lsr_acc_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xEE, 0x4A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_lsr_acc_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x37, 0x4A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_rol_acc_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x99, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_rol_acc_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x6C, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_rol_acc_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x80, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_rol_acc_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xEF, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_rol_acc_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xD7, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_rol_acc_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x86, 0x2A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_ror_acc_carry_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xCD, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 1);
}

void test_ror_acc_carry_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x9E, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.carry == 0);
}

void test_ror_acc_zero_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x01, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_ror_acc_zero_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xC4, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_ror_acc_negative_flag_set_true()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0xA1, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);
    bus.cpu.status.flag.carry = 1;

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_ror_acc_negative_flag_set_false()
{
    SystemBus bus;
    SystemMemory program_code {0xA9, 0x02, 0x6A, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}


void ut_cpu_accumulator_opcodes_flags()
{
    TEST_SET;

    test_asl_acc_carry_flag_set_true();
    test_asl_acc_carry_flag_set_false();
    test_asl_acc_zero_flag_set_true();
    test_asl_acc_zero_flag_set_false();
    test_asl_acc_negative_flag_set_true();
    test_asl_acc_negative_flag_set_false();

    test_lsr_acc_carry_flag_set_true();
    test_lsr_acc_carry_flag_set_false();
    test_lsr_acc_zero_flag_set_true();
    test_lsr_acc_zero_flag_set_false();
    test_lsr_acc_negative_flag_set_false();

    test_rol_acc_carry_flag_set_true();
    test_rol_acc_carry_flag_set_false();
    test_rol_acc_zero_flag_set_true();
    test_rol_acc_zero_flag_set_false();
    test_rol_acc_negative_flag_set_true();
    test_rol_acc_negative_flag_set_false();

    test_ror_acc_carry_flag_set_true();
    test_ror_acc_carry_flag_set_false();
    test_ror_acc_zero_flag_set_true();
    test_ror_acc_zero_flag_set_false();
    test_ror_acc_negative_flag_set_true();
    test_ror_acc_negative_flag_set_false();
}
