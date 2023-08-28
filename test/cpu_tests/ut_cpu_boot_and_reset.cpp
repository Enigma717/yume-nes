#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/bus.h"
#include <memory.h>


void test_check_registers_after_boot()
{
    SystemBus bus;

    bool check_regs = bus.cpu.x_reg | bus.cpu.y_reg | bus.cpu.acc;

    MY_ASSERT(check_regs == 0);
}

void test_check_stack_ptr_after_boot()
{
    SystemBus bus;
    uint8_t target_stack_ptr {0xFD};

    MY_ASSERT(bus.cpu.stack_ptr == target_stack_ptr);
}

void test_check_pc_address_after_boot()
{
    SystemBus bus;
    uint16_t target_pc {0x0000};

    MY_ASSERT(bus.cpu.pc == target_pc);
}

void test_check_status_after_boot()
{
    SystemBus bus;
    uint8_t target_status {0x34};

    MY_ASSERT(bus.cpu.status.word == target_status);
}

void test_check_memory_after_boot()
{
    SystemBus bus;
    SystemMemory empty_memory(MemoryConsts::memory_size, 0x00);

    MY_ASSERT(bus.ram->get_memory_copy() == empty_memory);
}

void test_check_offset_after_boot()
{
    SystemBus bus;
    uint8_t target_branch_offest {0x00};

    MY_ASSERT(bus.cpu.branch_offset == target_branch_offest);
}

void test_check_arg_address_after_boot()
{
    SystemBus bus;
    uint8_t target_arg_address {0x0000};

    MY_ASSERT(bus.cpu.arg_address == target_arg_address);
}

void test_check_curr_instr_after_boot()
{
    SystemBus bus;
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;
    Instruction target_instr {MN::ILL, AM::illegal, 0x02, 1, 1};

    MY_ASSERT(bus.cpu.curr_instruction == target_instr);
}

void test_check_registers_after_reset()
{
    SystemBus bus;

    bus.cpu.acc = 0x21;
    bus.cpu.x_reg = 0x37;
    bus.cpu.y_reg = 0xAC;
    bus.cpu.hard_reset();

    bool check_regs = bus.cpu.acc | bus.cpu.x_reg | bus.cpu.y_reg;

    MY_ASSERT(check_regs == 0);
}

void test_check_stack_ptr_after_reset()
{
    SystemBus bus;
    uint8_t target_stack_ptr {0xFD};

    bus.cpu.stack_ptr = 0x77;
    bus.cpu.hard_reset();

    MY_ASSERT(bus.cpu.stack_ptr == target_stack_ptr);
}

void test_check_pc_address_after_reset()
{
    SystemBus bus;
    uint16_t target_pc {0xABCD};

    bus.ram->memory_write(MemoryConsts::reset_vector_lsb, 0xCD);
    bus.ram->memory_write(MemoryConsts::reset_vector_msb, 0xAB);
    bus.cpu.hard_reset();

    MY_ASSERT(bus.cpu.pc == target_pc);
}

void test_check_status_after_reset()
{
    SystemBus bus;
    uint8_t target_status {0x34};

    bus.cpu.status.word = 0xFF;
    bus.cpu.hard_reset();

    MY_ASSERT(bus.cpu.status.word == target_status);
}

void test_check_memory_after_reset()
{
    SystemBus bus;
    SystemMemory empty_memory(MemoryConsts::memory_size, 0x00);

    for (uint8_t i {0}; i < 10; i++) {
        bus.ram->memory_write(0xC0 * i, i);
    }

    bus.cpu.hard_reset();

    MY_ASSERT(bus.ram->get_memory_copy() == empty_memory);
}


void ut_cpu_boot_and_reset()
{
    TEST_SET;

    test_check_registers_after_boot();
    test_check_stack_ptr_after_boot();
    test_check_pc_address_after_boot();
    test_check_status_after_boot();
    test_check_memory_after_boot();
    test_check_offset_after_boot();
    test_check_arg_address_after_boot();
    test_check_curr_instr_after_boot();


    test_check_registers_after_reset();
    test_check_stack_ptr_after_reset();
    test_check_pc_address_after_reset();
    test_check_status_after_reset();
    test_check_memory_after_reset();
}
