#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/system.h"


void test_same_memory_object()
{
    System nes;

    MY_ASSERT(nes.ram == nes.cpu.get_memory_pointer().lock());
}

void test_same_cartridge_object()
{
    System nes;

    MY_ASSERT(nes.cartridge == nes.cpu.get_cartridge_pointer().lock());
}

void test_direct_memory_access()
{
    System nes;
    uint16_t address {0x00DD};
    uint8_t data {0xFF};

    nes.ram->memory_write(address, data);

    MY_ASSERT(nes.ram->memory_read(address) == data);
}

void test_cpu_memory_access()
{
    System nes;
    uint16_t address {0x00DD};
    uint8_t data {0xFF};

    nes.cpu.cpu_memory_write(address, data);

    MY_ASSERT(nes.cpu.cpu_memory_read(address) == data);
}

void test_shared_memory_access()
{
    System nes;
    uint16_t address {0x00DD};
    uint8_t data {0xFF};

    nes.ram->memory_write(address, data);

    MY_ASSERT(nes.cpu.cpu_memory_read(address) == data);
}

void test_cpu_ram_memory_mirroring()
{
    System nes;
    uint16_t target_address {0x02FA};
    uint16_t actual_address {0x0AFA};
    uint8_t data {0xFF};

    nes.ram->memory_write(actual_address, data);

    MY_ASSERT(nes.cpu.cpu_memory_read(target_address) == data);
}


void ut_cpu_connection_with_components()
{
    TEST_SET;

    test_same_memory_object();
    test_same_cartridge_object();
    test_direct_memory_access();
    test_cpu_memory_access();
    test_shared_memory_access();
    test_cpu_ram_memory_mirroring();
}
