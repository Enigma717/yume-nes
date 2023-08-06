#include "./test_main.h"
#include "../include/bus.h"


void test_brk_behaviour()
{
    // TODO
}


void test_clc_behaviour()
{
    SystemBus bus;
    uint8_t target_word = ~(1 << 0);

    bus.cpu.status.word = 0xFF;
    bus.cpu.CLC();

    MY_ASSERT(bus.cpu.status.word == target_word);
}

void test_cld_behaviour()
{
    SystemBus bus;
    uint8_t target_word = ~(1 << 3);

    bus.cpu.status.word = 0xFF;
    bus.cpu.CLD();

    MY_ASSERT(bus.cpu.status.word == target_word);
}

void test_cli_behaviour()
{
    SystemBus bus;
    uint8_t target_word = ~(1 << 2);

    bus.cpu.status.word = 0xFF;
    bus.cpu.CLI();

    MY_ASSERT(bus.cpu.status.word == target_word);
}

void test_clv_behaviour()
{
    SystemBus bus;
    uint8_t target_word = ~(1 << 6);

    bus.cpu.status.word = 0xFF;
    bus.cpu.CLV();

    MY_ASSERT(bus.cpu.status.word == target_word);
}


void test_dex_behaviour()
{
    SystemBus bus;
    uint8_t target_x_reg = 0x86;

    bus.cpu.x_reg = 0x87;
    bus.cpu.DEX();

    MY_ASSERT(bus.cpu.x_reg == target_x_reg);
}

void test_dey_behaviour()
{
    SystemBus bus;
    uint8_t target_y_reg = 0x86;

    bus.cpu.y_reg = 0x87;
    bus.cpu.DEY();

    MY_ASSERT(bus.cpu.y_reg == target_y_reg);
}


void test_inx_behaviour()
{
    SystemBus bus;
    uint8_t target_x_reg = 0xB0;

    bus.cpu.x_reg = 0xAF;
    bus.cpu.INX();

    MY_ASSERT(bus.cpu.x_reg == target_x_reg);
}

void test_iny_behaviour()
{
    SystemBus bus;
    uint8_t target_y_reg = 0xB0;

    bus.cpu.y_reg = 0xAF;
    bus.cpu.INY();

    MY_ASSERT(bus.cpu.y_reg == target_y_reg);
}


void test_nop_behaviour()
{
    // TODO
}

void test_pha_behaviour()
{
    SystemBus bus;
    uint8_t stack_ptr_init = bus.cpu.stack_ptr;
    uint8_t acc_init_value = 0xAD;

    bus.cpu.acc = acc_init_value;
    bus.cpu.PHA();

    MY_ASSERT(bus.cpu.cpu_mem_read(stack_offset + stack_ptr_init) == acc_init_value);
}

void test_php_behaviour()
{
    SystemBus bus;
    uint8_t stack_ptr_init = bus.cpu.stack_ptr;
    uint8_t status_init_mask = 0xAD;
    uint8_t status_final_mask = status_init_mask | (1 << 4) | (1 << 5);

    bus.cpu.status.word = status_init_mask;
    bus.cpu.PHP();

    MY_ASSERT(bus.cpu.cpu_mem_read(stack_offset + stack_ptr_init) == status_final_mask);
}

void test_pla_behaviour()
{
    SystemBus bus;
    uint8_t stack_ptr_init = bus.cpu.stack_ptr;
    uint8_t acc_init_value = 0xAD;

    bus.cpu.acc = acc_init_value;
    bus.cpu.PHA();

    bus.cpu.acc = 0x00;
    bus.cpu.PLA();

    MY_ASSERT(bus.cpu.acc == acc_init_value);
}

void test_plp_behaviour()
{
    SystemBus bus;
    uint8_t stack_ptr_init = bus.cpu.stack_ptr;
    uint8_t status_init_mask = 0xAD;
    uint8_t status_final_mask = status_init_mask | (1 << 4) | (1 << 5);

    bus.cpu.status.word = status_init_mask;
    bus.cpu.PHP();

    bus.cpu.status.word = 0x00;
    bus.cpu.PLP();

    MY_ASSERT(bus.cpu.status.word == status_final_mask);
}


void ut_cpu_implied_opcodes_behaviour()
{
    TEST_SET;

    test_brk_behaviour();

    test_clc_behaviour();
    test_cld_behaviour();
    test_cli_behaviour();
    test_clv_behaviour();

    test_dex_behaviour();
    test_dey_behaviour();

    test_inx_behaviour();
    test_iny_behaviour();

    test_nop_behaviour();

    test_pha_behaviour();
    test_php_behaviour();
    test_pla_behaviour();
    test_plp_behaviour();
}
