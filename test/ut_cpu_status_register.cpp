#include "./test_main.h"
#include "../include/cpu.h"


void test_set_status_word_direct() 
{
    CPU cpu;
    uint8_t mask {0b00110100};

    cpu.status.word = mask;

    MY_ASSERT(cpu.status.word == mask);
}

void test_set_carry_flag_true() 
{
    CPU cpu;
    uint8_t carry_mask = (1 << 0);

    cpu.status.flag.carry = 1;

    MY_ASSERT(cpu.status.word == carry_mask);
}

void test_set_zero_flag_true() 
{
    CPU cpu;
    uint8_t zero_mask = (1 << 1);

    cpu.status.flag.zero = 1;

    MY_ASSERT(cpu.status.word == zero_mask);
}

void test_set_interrupt_flag_true()
{
    CPU cpu;
    uint8_t interrupt_mask = (1 << 2);

    cpu.status.flag.interrupt = 1;

    MY_ASSERT(cpu.status.word == interrupt_mask);
}

void test_set_decimal_flag_true()
{
    CPU cpu;
    uint8_t decimal_mask = (1 << 3);

    cpu.status.flag.decimal = 1;

    MY_ASSERT(cpu.status.word == decimal_mask);
}

void test_set_brk_flag_true()
{
    CPU cpu;
    uint8_t brk_mask = (1 << 4);

    cpu.status.flag.brk = 1;

    MY_ASSERT(cpu.status.word == brk_mask);
}

void test_set_unused_flag_true()
{
    CPU cpu;
    uint8_t unused_mask = (1 << 5);

    cpu.status.flag.unused = 1;

    MY_ASSERT(cpu.status.word == unused_mask);
}

void test_set_overflow_flag_true()
{
    CPU cpu;
    uint8_t overflow_mask = (1 << 6);

    cpu.status.flag.overflow = 1;

    MY_ASSERT(cpu.status.word == overflow_mask);
}

void test_set_negative_flag_true()
{
    CPU cpu;
    uint8_t negative_mask = (1 << 7);

    cpu.status.flag.negative = 1;

    MY_ASSERT(cpu.status.word == negative_mask);
}



void ut_cpu_status_register()
{
    TEST_SET;

    test_set_status_word_direct(); 
    test_set_carry_flag_true(); 
    test_set_zero_flag_true(); 
    test_set_interrupt_flag_true();
    test_set_decimal_flag_true();
    test_set_brk_flag_true();
    test_set_unused_flag_true();
    test_set_overflow_flag_true();
    test_set_negative_flag_true();
}