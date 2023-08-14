#include "./cpu_tests.h"
#include "../test_main.h"
#include "../../include/cpu.h"


void test_set_status_word_directly()
{
    CPU cpu;
    uint8_t mask {0b0011'0100};

    cpu.status.word = mask;

    MY_ASSERT(cpu.status.word == mask);
}

void test_set_carry_flag_as_true()
{
    CPU cpu;
    uint8_t carry_flag_mask {0b0000'0001};

    cpu.status.word = 0x00;
    cpu.status.flag.carry = 1;

    MY_ASSERT(cpu.status.word == carry_flag_mask);
}

void test_set_zero_flag_as_true()
{
    CPU cpu;
    uint8_t zero_flag_mask {0b0000'0010};

    cpu.status.word = 0x00;
    cpu.status.flag.zero = 1;

    MY_ASSERT(cpu.status.word == zero_flag_mask);
}

void test_set_interrupt_flag_as_true()
{
    CPU cpu;
    uint8_t interrupt_flag_mask {0b0000'0100};

    cpu.status.word = 0x00;
    cpu.status.flag.interrupt = 1;

    MY_ASSERT(cpu.status.word == interrupt_flag_mask);
}

void test_set_decimal_flag_as_true()
{
    CPU cpu;
    uint8_t decimal_flag_mask {0b0000'1000};

    cpu.status.word = 0x00;
    cpu.status.flag.decimal = 1;

    MY_ASSERT(cpu.status.word == decimal_flag_mask);
}

void test_set_break_flag_as_true()
{
    CPU cpu;
    uint8_t break_flag_mask {0b0001'0000};

    cpu.status.word = 0x00;
    cpu.status.flag.brk = 1;

    MY_ASSERT(cpu.status.word == break_flag_mask);
}

void test_set_unused_flag_as_true()
{
    CPU cpu;
    uint8_t unused_flag_mask {0b0010'0000};

    cpu.status.word = 0x00;
    cpu.status.flag.unused = 1;

    MY_ASSERT(cpu.status.word == unused_flag_mask);
}

void test_set_overflow_flag_as_true()
{
    CPU cpu;
    uint8_t overflow_flag_mask {0b0100'0000};

    cpu.status.word = 0x00;
    cpu.status.flag.overflow = 1;

    MY_ASSERT(cpu.status.word == overflow_flag_mask);
}

void test_set_negative_flag_as_true()
{
    CPU cpu;
    uint8_t negative_flag_mask {0b1000'0000};

    cpu.status.word = 0x00;
    cpu.status.flag.negative = 1;

    MY_ASSERT(cpu.status.word == negative_flag_mask);
}


void ut_cpu_status_register()
{
    TEST_SET;

    test_set_status_word_directly();
    test_set_carry_flag_as_true();
    test_set_zero_flag_as_true();
    test_set_interrupt_flag_as_true();
    test_set_decimal_flag_as_true();
    test_set_break_flag_as_true();
    test_set_unused_flag_as_true();
    test_set_overflow_flag_as_true();
    test_set_negative_flag_as_true();
}
