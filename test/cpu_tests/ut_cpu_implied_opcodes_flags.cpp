#include "./cpu_tests.h"
#include "../test_main.h"
#include "../../include/bus.h"


void test_dex_zero_flag_set_true()
{
    SystemBus bus;

    bus.cpu.x_reg = 0x01;
    bus.cpu.DEX();

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_dex_zero_flag_set_false()
{
    SystemBus bus;

    bus.cpu.x_reg = 0xDA;
    bus.cpu.DEX();

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_dex_negative_flag_set_true()
{
    SystemBus bus;

    bus.cpu.x_reg = 0xAA;
    bus.cpu.DEX();

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_dex_negative_flag_set_false()
{
    SystemBus bus;

    bus.cpu.x_reg = 0x77;
    bus.cpu.DEX();

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_dey_zero_flag_set_true()
{
    SystemBus bus;

    bus.cpu.y_reg = 0x01;
    bus.cpu.DEY();

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_dey_zero_flag_set_false()
{
    SystemBus bus;

    bus.cpu.y_reg = 0xAA;
    bus.cpu.DEY();

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_dey_negative_flag_set_true()
{
    SystemBus bus;

    bus.cpu.y_reg = 0xAA;
    bus.cpu.DEY();

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_dey_negative_flag_set_false()
{
    SystemBus bus;

    bus.cpu.y_reg = 0x77;
    bus.cpu.DEY();

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_inx_zero_flag_set_true()
{
    SystemBus bus;

    bus.cpu.x_reg = 0xFF;
    bus.cpu.INX();

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_inx_zero_flag_set_false()
{
    SystemBus bus;

    bus.cpu.x_reg = 0xAA;
    bus.cpu.INX();

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_inx_negative_flag_set_true()
{
    SystemBus bus;

    bus.cpu.x_reg = 0xAA;
    bus.cpu.INX();

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_inx_negative_flag_set_false()
{
    SystemBus bus;

    bus.cpu.x_reg = 0x77;
    bus.cpu.INX();

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_iny_zero_flag_set_true()
{
    SystemBus bus;

    bus.cpu.y_reg = 0xFF;
    bus.cpu.INY();

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_iny_zero_flag_set_false()
{
    SystemBus bus;

    bus.cpu.y_reg = 0xAA;
    bus.cpu.INY();

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_iny_negative_flag_set_true()
{
    SystemBus bus;

    bus.cpu.y_reg = 0xAA;
    bus.cpu.INY();

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_iny_negative_flag_set_false()
{
    SystemBus bus;

    bus.cpu.y_reg = 0x77;
    bus.cpu.INY();

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}

void test_pla_zero_flag_set_true()
{
    SystemBus bus;

    bus.cpu.acc = 0x00;
    bus.cpu.PHA();

    bus.cpu.PLA();

    MY_ASSERT(bus.cpu.status.flag.zero == 1);
}

void test_pla_zero_flag_set_false()
{
    SystemBus bus;

    bus.cpu.acc = 0x77;
    bus.cpu.PHA();

    bus.cpu.PLA();

    MY_ASSERT(bus.cpu.status.flag.zero == 0);
}

void test_pla_negative_flag_set_true()
{
    SystemBus bus;

    bus.cpu.acc = 0xAA;
    bus.cpu.PHA();

    bus.cpu.PLA();

    MY_ASSERT(bus.cpu.status.flag.negative == 1);
}

void test_pla_negative_flag_set_false()
{
    SystemBus bus;

    bus.cpu.acc = 0x77;
    bus.cpu.PHA();

    bus.cpu.PLA();

    MY_ASSERT(bus.cpu.status.flag.negative == 0);
}



void ut_cpu_implied_opcodes_flags()
{
    TEST_SET;

    test_dex_zero_flag_set_true();
    test_dex_zero_flag_set_false();
    test_dex_negative_flag_set_true();
    test_dex_negative_flag_set_false();
    test_dey_zero_flag_set_true();
    test_dey_zero_flag_set_false();
    test_dey_negative_flag_set_true();
    test_dey_negative_flag_set_false();

    test_inx_zero_flag_set_true();
    test_inx_zero_flag_set_false();
    test_inx_negative_flag_set_true();
    test_inx_negative_flag_set_false();
    test_iny_zero_flag_set_true();
    test_iny_zero_flag_set_false();
    test_iny_negative_flag_set_true();
    test_iny_negative_flag_set_false();

    test_pla_zero_flag_set_true();
    test_pla_zero_flag_set_false();
    test_pla_negative_flag_set_true();
    test_pla_negative_flag_set_false();
}
