#include "./test_main.h"
#include "../include/bus.h"


void test_check_registers_after_boot()
{
    SystemBus bus;

    bool check_regs = bus.cpu.x_reg | bus.cpu.y_reg | bus.cpu.acc;

    MY_ASSERT(check_regs == 0);
}

void test_check_stack_ptr_after_boot()
{
    SystemBus bus;
    uint8_t target_stack_ptr = 0xFD;

    MY_ASSERT(bus.cpu.stack_ptr == target_stack_ptr);
}

void test_check_status_after_boot()
{
    SystemBus bus;
    uint8_t target_status = 0x34;

    MY_ASSERT(bus.cpu.status.word == target_status);
}

void test_check_memory_after_boot()
{
    SystemBus bus;
    std::vector<uint8_t> empty_memory = std::vector<uint8_t>(0x800, 0x00);

    MY_ASSERT(bus.ram->get_memory_copy() == empty_memory);
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
    uint8_t target_stack_ptr = 0xFD;

    bus.cpu.stack_ptr = 0x77;
    bus.cpu.hard_reset();

    MY_ASSERT(bus.cpu.stack_ptr == target_stack_ptr);
}

void test_check_status_after_reset()
{
    SystemBus bus;
    uint8_t target_status = 0x34;

    bus.cpu.status.word = 0xFF;
    bus.cpu.hard_reset();

    MY_ASSERT(bus.cpu.status.word == target_status);
}

void test_check_memory_after_reset()
{
    SystemBus bus;
    std::vector<uint8_t> empty_memory = std::vector<uint8_t>(0x800, 0x00);

    for (auto i = 0; i < 10; i++) {
        bus.cpu.cpu_mem_write(0xC0 * i, i);
    }

    bus.cpu.hard_reset();

    MY_ASSERT(bus.ram->get_memory_copy() == empty_memory);
}


void ut_cpu_hard_reset()
{
    TEST_SET;

    test_check_registers_after_boot();
    test_check_stack_ptr_after_boot();
    test_check_status_after_boot();
    test_check_memory_after_boot();

    test_check_registers_after_reset();
    test_check_stack_ptr_after_reset();
    test_check_status_after_reset();
    test_check_memory_after_reset();
}
