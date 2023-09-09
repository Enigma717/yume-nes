#include "../cpu_tests.h"

#include "../../test_main.h"
#include "../../../include/system.h"


void test_dex_zero_flag_set_true()
{
    CPU cpu;

    cpu.x_reg = 0x01;
    cpu.DEX();

    MY_ASSERT(cpu.status.flag.zero == 1);
}

void test_dex_zero_flag_set_false()
{
    CPU cpu;

    cpu.x_reg = 0xDA;
    cpu.DEX();

    MY_ASSERT(cpu.status.flag.zero == 0);
}

void test_dex_negative_flag_set_true()
{
    CPU cpu;

    cpu.x_reg = 0xAA;
    cpu.DEX();

    MY_ASSERT(cpu.status.flag.negative == 1);
}

void test_dex_negative_flag_set_false()
{
    CPU cpu;

    cpu.x_reg = 0x77;
    cpu.DEX();

    MY_ASSERT(cpu.status.flag.negative == 0);
}

void test_dey_zero_flag_set_true()
{
    CPU cpu;

    cpu.y_reg = 0x01;
    cpu.DEY();

    MY_ASSERT(cpu.status.flag.zero == 1);
}

void test_dey_zero_flag_set_false()
{
    CPU cpu;

    cpu.y_reg = 0xAA;
    cpu.DEY();

    MY_ASSERT(cpu.status.flag.zero == 0);
}

void test_dey_negative_flag_set_true()
{
    CPU cpu;

    cpu.y_reg = 0xAA;
    cpu.DEY();

    MY_ASSERT(cpu.status.flag.negative == 1);
}

void test_dey_negative_flag_set_false()
{
    CPU cpu;

    cpu.y_reg = 0x77;
    cpu.DEY();

    MY_ASSERT(cpu.status.flag.negative == 0);
}

void test_inx_zero_flag_set_true()
{
    CPU cpu;

    cpu.x_reg = 0xFF;
    cpu.INX();

    MY_ASSERT(cpu.status.flag.zero == 1);
}

void test_inx_zero_flag_set_false()
{
    CPU cpu;

    cpu.x_reg = 0xAA;
    cpu.INX();

    MY_ASSERT(cpu.status.flag.zero == 0);
}

void test_inx_negative_flag_set_true()
{
    CPU cpu;

    cpu.x_reg = 0xAA;
    cpu.INX();

    MY_ASSERT(cpu.status.flag.negative == 1);
}

void test_inx_negative_flag_set_false()
{
    CPU cpu;

    cpu.x_reg = 0x77;
    cpu.INX();

    MY_ASSERT(cpu.status.flag.negative == 0);
}

void test_iny_zero_flag_set_true()
{
    CPU cpu;

    cpu.y_reg = 0xFF;
    cpu.INY();

    MY_ASSERT(cpu.status.flag.zero == 1);
}

void test_iny_zero_flag_set_false()
{
    CPU cpu;

    cpu.y_reg = 0xAA;
    cpu.INY();

    MY_ASSERT(cpu.status.flag.zero == 0);
}

void test_iny_negative_flag_set_true()
{
    CPU cpu;

    cpu.y_reg = 0xAA;
    cpu.INY();

    MY_ASSERT(cpu.status.flag.negative == 1);
}

void test_iny_negative_flag_set_false()
{
    CPU cpu;

    cpu.y_reg = 0x77;
    cpu.INY();

    MY_ASSERT(cpu.status.flag.negative == 0);
}

void test_pla_zero_flag_set_true()
{
    System nes;

    nes.cpu.acc = 0x00;
    nes.cpu.PHA();

    nes.cpu.PLA();

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_pla_zero_flag_set_false()
{
    System nes;

    nes.cpu.acc = 0x77;
    nes.cpu.PHA();

    nes.cpu.PLA();

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_pla_negative_flag_set_true()
{
    System nes;

    nes.cpu.acc = 0xAA;
    nes.cpu.PHA();

    nes.cpu.PLA();

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_pla_negative_flag_set_false()
{
    System nes;

    nes.cpu.acc = 0x77;
    nes.cpu.PHA();

    nes.cpu.PLA();

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_tax_zero_flag_set_true()
{
    CPU cpu;

    cpu.acc = 0x00;
    cpu.TAX();

    MY_ASSERT(cpu.status.flag.zero == 1);
}

void test_tax_zero_flag_set_false()
{
    CPU cpu;

    cpu.acc = 0x77;
    cpu.TAX();

    MY_ASSERT(cpu.status.flag.zero == 0);
}

void test_tax_negative_flag_set_true()
{
    CPU cpu;

    cpu.acc = 0xAA;
    cpu.TAX();

    MY_ASSERT(cpu.status.flag.negative == 1);
}

void test_tax_negative_flag_set_false()
{
    CPU cpu;

    cpu.acc = 0x77;
    cpu.TAX();

    MY_ASSERT(cpu.status.flag.negative == 0);
}

void test_tay_zero_flag_set_true()
{
    CPU cpu;

    cpu.acc = 0x00;
    cpu.TAY();

    MY_ASSERT(cpu.status.flag.zero == 1);
}

void test_tay_zero_flag_set_false()
{
    CPU cpu;

    cpu.acc = 0x77;
    cpu.TAY();

    MY_ASSERT(cpu.status.flag.zero == 0);
}

void test_tay_negative_flag_set_true()
{
    CPU cpu;

    cpu.acc = 0xAA;
    cpu.TAY();

    MY_ASSERT(cpu.status.flag.negative == 1);
}

void test_tay_negative_flag_set_false()
{
    CPU cpu;

    cpu.acc = 0x77;
    cpu.TAY();

    MY_ASSERT(cpu.status.flag.negative == 0);
}

void test_tsx_zero_flag_set_true()
{
    System nes;

    nes.ram->memory_write(MemoryConsts::stack_offset + nes.cpu.stack_ptr, 0x00);
    nes.cpu.TSX();

    MY_ASSERT(nes.cpu.status.flag.zero == 1);
}

void test_tsx_zero_flag_set_false()
{
    System nes;

    nes.ram->memory_write(MemoryConsts::stack_offset + nes.cpu.stack_ptr, 0x77);
    nes.cpu.TSX();

    MY_ASSERT(nes.cpu.status.flag.zero == 0);
}

void test_tsx_negative_flag_set_true()
{
    System nes;

    nes.ram->memory_write(MemoryConsts::stack_offset + nes.cpu.stack_ptr, 0xAA);
    nes.cpu.TSX();

    MY_ASSERT(nes.cpu.status.flag.negative == 1);
}

void test_tsx_negative_flag_set_false()
{
    System nes;

    nes.ram->memory_write(MemoryConsts::stack_offset + nes.cpu.stack_ptr, 0x77);
    nes.cpu.TSX();

    MY_ASSERT(nes.cpu.status.flag.negative == 0);
}

void test_txa_zero_flag_set_true()
{
    CPU cpu;

    cpu.x_reg = 0x00;
    cpu.TXA();

    MY_ASSERT(cpu.status.flag.zero == 1);
}

void test_txa_zero_flag_set_false()
{
    CPU cpu;

    cpu.x_reg = 0x77;
    cpu.TXA();

    MY_ASSERT(cpu.status.flag.zero == 0);
}

void test_txa_negative_flag_set_true()
{
    CPU cpu;

    cpu.x_reg = 0xAA;
    cpu.TXA();

    MY_ASSERT(cpu.status.flag.negative == 1);
}

void test_txa_negative_flag_set_false()
{
    CPU cpu;

    cpu.x_reg = 0x77;
    cpu.TXA();

    MY_ASSERT(cpu.status.flag.negative == 0);
}

void test_tya_zero_flag_set_true()
{
    CPU cpu;

    cpu.y_reg = 0x00;
    cpu.TYA();

    MY_ASSERT(cpu.status.flag.zero == 1);
}

void test_tya_zero_flag_set_false()
{
    CPU cpu;

    cpu.y_reg = 0x77;
    cpu.TYA();

    MY_ASSERT(cpu.status.flag.zero == 0);
}

void test_tya_negative_flag_set_true()
{
    CPU cpu;

    cpu.y_reg = 0xAA;
    cpu.TYA();

    MY_ASSERT(cpu.status.flag.negative == 1);
}

void test_tya_negative_flag_set_false()
{
    CPU cpu;

    cpu.y_reg = 0x77;
    cpu.TYA();

    MY_ASSERT(cpu.status.flag.negative == 0);
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

    test_tax_zero_flag_set_true();
    test_tax_zero_flag_set_false();
    test_tax_negative_flag_set_true();
    test_tax_negative_flag_set_false();
    test_tay_zero_flag_set_true();
    test_tay_zero_flag_set_false();
    test_tay_negative_flag_set_true();
    test_tay_negative_flag_set_false();
    test_tsx_zero_flag_set_true();
    test_tsx_zero_flag_set_false();
    test_tsx_negative_flag_set_true();
    test_tsx_negative_flag_set_false();
    test_txa_zero_flag_set_true();
    test_txa_zero_flag_set_false();
    test_txa_negative_flag_set_true();
    test_txa_negative_flag_set_false();
    test_tya_zero_flag_set_true();
    test_tya_zero_flag_set_false();
    test_tya_negative_flag_set_true();
    test_tya_negative_flag_set_false();
}
