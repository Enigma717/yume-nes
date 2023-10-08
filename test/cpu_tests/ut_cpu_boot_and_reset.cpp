#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/system.h"


void test_check_registers_after_boot()
{
    System nes;

    bool check_regs = nes.cpu.x_reg | nes.cpu.y_reg | nes.cpu.acc;

    MY_ASSERT(check_regs == 0);
}

void test_check_stack_ptr_after_boot()
{
    System nes;
    uint8_t target_stack_ptr {0xFD};

    MY_ASSERT(nes.cpu.stack_ptr == target_stack_ptr);
}

void test_check_pc_address_after_boot()
{
    System nes;
    uint16_t target_pc {0x0000};

    MY_ASSERT(nes.cpu.pc == target_pc);
}

void test_check_status_after_boot()
{
    System nes;
    uint8_t target_status {0x34};

    MY_ASSERT(nes.cpu.status.word == target_status);
}

void test_check_memory_after_boot()
{
    System nes;
    SystemMemory empty_memory(MemoryConsts::memory_size, 0x00);

    MY_ASSERT(nes.ram->get_memory_copy() == empty_memory);
}

void test_check_offset_after_boot()
{
    System nes;
    uint8_t target_branch_offest {0x00};

    MY_ASSERT(nes.cpu.branch_offset == target_branch_offest);
}

void test_check_arg_address_after_boot()
{
    System nes;
    uint8_t target_arg_address {0x0000};

    MY_ASSERT(nes.cpu.arg_address == target_arg_address);
}

void test_check_curr_instr_after_boot()
{
    System nes;
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;
    Instruction target_instr {MN::KIL, AM::implied, 0x02, 1, 1};

    MY_ASSERT(nes.cpu.curr_instruction == target_instr);
}

void test_check_registers_after_reset()
{
    System nes;

    nes.cpu.acc = 0x21;
    nes.cpu.x_reg = 0x37;
    nes.cpu.y_reg = 0xAC;
    nes.cpu.hard_reset();

    bool check_regs = nes.cpu.acc | nes.cpu.x_reg | nes.cpu.y_reg;

    MY_ASSERT(check_regs == 0);
}

void test_check_stack_ptr_after_reset()
{
    System nes;
    uint8_t target_stack_ptr {0xFD};

    nes.cpu.stack_ptr = 0x77;
    nes.cpu.hard_reset();

    MY_ASSERT(nes.cpu.stack_ptr == target_stack_ptr);
}

void test_check_pc_address_after_reset()
{
    System nes;
    uint16_t target_pc {0xABCD};

    nes.cpu.memory_write(MemoryConsts::reset_vector_lsb, 0xCD);
    nes.cpu.memory_write(MemoryConsts::reset_vector_msb, 0xAB);
    nes.cpu.hard_reset();

    MY_ASSERT(nes.cpu.pc == target_pc);
}

void test_check_status_after_reset()
{
    System nes;
    uint8_t target_status {0x34};

    nes.cpu.status.word = 0xFF;
    nes.cpu.hard_reset();

    MY_ASSERT(nes.cpu.status.word == target_status);
}

void test_check_memory_after_reset()
{
    System nes;
    SystemMemory empty_memory(MemoryConsts::memory_size, 0x00);

    for (uint8_t i {0}; i < 10; i++) {
        nes.ram->memory_write(0xC0 * i, i);
    }

    nes.cpu.hard_reset();

    MY_ASSERT(nes.ram->get_memory_copy() == empty_memory);
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
