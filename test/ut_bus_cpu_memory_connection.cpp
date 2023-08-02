#include "./test_main.h"
#include "../include/bus.h"



void test_same_memory_address() 
{
    SystemBus bus;

    MY_ASSERT(&bus.ram == bus.cpu.get_ram_address());
}

void test_direct_memory_access() 
{
    SystemBus bus;
    uint16_t address {0x00DD};
    uint8_t value {0xFF};

    bus.ram.mem_write(address, value);

    MY_ASSERT(bus.ram.mem_read(address) == value);
}

void test_cpu_memory_access() 
{
    SystemBus bus;
    uint16_t address {0x00DD};
    uint8_t value {0xFF};

    bus.cpu.cpu_mem_write(address, value);

    MY_ASSERT(bus.cpu.cpu_mem_read(address) == value);
}

void test_shared_memory_access()
{
    SystemBus bus;
    uint16_t address {0x00DD};
    uint8_t value {0xFF};

    bus.ram.mem_write(address, value);

    MY_ASSERT(bus.cpu.cpu_mem_read(address) == value);
}

void test_outside_memory_read()
{
    SystemBus bus;
    uint16_t address {0xFFFF};

    MY_ASSERT(bus.ram.mem_read(address) == 0x00);
}


void ut_bus_cpu_memory_connection()
{
    TEST_SET;

    test_same_memory_address();
    test_direct_memory_access();
    test_cpu_memory_access();
    test_shared_memory_access();
    test_outside_memory_read();
}