#include "./test_main.h"
#include "../include/bus.h"


void test_check_registers_after_reset()
{
    SystemBus bus;

    bus.cpu.hard_reset();

    bool check_regs = bus.cpu.x_reg | bus.cpu.y_reg | bus.cpu.acc;

    MY_ASSERT(check_regs == 0);
}

void test_check_stk_ptr_after_reset()
{
    SystemBus bus;
    uint8_t target_stk_ptr = 0xFD;

    bus.cpu.hard_reset();

    MY_ASSERT(bus.cpu.stk_ptr == target_stk_ptr);
}

void test_check_status_after_reset()
{
    SystemBus bus;
    uint8_t target_status = 0x34;

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

    test_check_registers_after_reset();
    test_check_stk_ptr_after_reset();
    test_check_status_after_reset();
    test_check_memory_after_reset();
}
