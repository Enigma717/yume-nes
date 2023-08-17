#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/bus.h"


void test_same_memory_address()
{
    SystemBus bus;

    MY_ASSERT(bus.ram == bus.cpu.get_memory_address().lock());
}

void test_direct_memory_access()
{
    SystemBus bus;
    uint16_t address {0x00DD};
    uint8_t data {0xFF};

    bus.ram->memory_write(address, data);

    MY_ASSERT(bus.ram->memory_read(address) == data);
}

void test_cpu_memory_access()
{
    SystemBus bus;
    uint16_t address {0x00DD};
    uint8_t data {0xFF};

    bus.cpu.cpu_memory_write(address, data);

    MY_ASSERT(bus.cpu.cpu_memory_read(address) == data);
}

void test_shared_memory_access()
{
    SystemBus bus;
    uint16_t address {0x00DD};
    uint8_t data {0xFF};

    bus.ram->memory_write(address, data);

    MY_ASSERT(bus.cpu.cpu_memory_read(address) == data);
}


void ut_cpu_bus_memory_connection()
{
    TEST_SET;

    test_same_memory_address();
    test_direct_memory_access();
    test_cpu_memory_access();
    test_shared_memory_access();
}
