#include "./test_main.h"
#include "../include/cpu.h"


void test_set_status_word_direct() 
{
    CPU cpu;
    uint8_t mask {0b00110100};

    cpu.set_status_word(mask);

    MY_ASSERT(cpu.read_status_word() == mask);
}

void test_set_carry_flag_true() 
{
    CPU cpu;
    uint8_t carry_mask = (1 << 0);

    cpu.set_carry_flag(true);

    MY_ASSERT(cpu.read_status_word() == carry_mask);
}

void test_set_zero_flag_true() 
{
    CPU cpu;
    uint8_t zero_mask = (1 << 1);

    cpu.set_zero_flag(true);

    MY_ASSERT(cpu.read_status_word() == zero_mask);
}

void test_set_interrupt_flag_true()
{
    CPU cpu;
    uint8_t interrupt_mask = (1 << 2);

    cpu.set_interrupt_flag(true);

    MY_ASSERT(cpu.read_status_word() == interrupt_mask);
}

void test_set_decimal_flag_true()
{
    CPU cpu;
    uint8_t decimal_mask = (1 << 3);

    cpu.set_decimal_flag(true);

    MY_ASSERT(cpu.read_status_word() == decimal_mask);
}

void test_set_brk_flag_true()
{
    CPU cpu;
    uint8_t brk_mask = (1 << 4);

    cpu.set_brk_flag(true);

    MY_ASSERT(cpu.read_status_word() == brk_mask);
}

void test_set_unused_flag_true()
{
    CPU cpu;
    uint8_t unused_mask = (1 << 5);

    cpu.set_unused_flag(true);

    MY_ASSERT(cpu.read_status_word() == unused_mask);
}

void test_set_overflow_flag_true()
{
    CPU cpu;
    uint8_t overflow_mask = (1 << 6);

    cpu.set_overflow_flag(true);

    MY_ASSERT(cpu.read_status_word() == overflow_mask);
}

void test_set_negative_flag_true()
{
    CPU cpu;
    uint8_t negative_mask = (1 << 7);

    cpu.set_negative_flag(true);

    MY_ASSERT(cpu.read_status_word() == negative_mask);
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