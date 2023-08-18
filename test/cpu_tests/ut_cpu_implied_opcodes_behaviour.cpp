#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/bus.h"


void test_brk_behaviour()
{
    SystemBus bus;
    uint8_t target_word {0xBD};
    uint8_t target_stack_ptr {0xFA};
    uint16_t target_pc {0x2731};

    bus.cpu.cpu_memory_write(MemoryConsts::irq_vector_msb, 0x27);
    bus.cpu.cpu_memory_write(MemoryConsts::irq_vector_lsb, 0x31);

    bus.cpu.pc = 0x01FF;
    bus.cpu.status.word = 0x89;
    bus.cpu.BRK();

    bool status_check {bus.cpu.status.word == target_word};
    bool stack_ptr_check {bus.cpu.stack_ptr == target_stack_ptr};
    bool pc_check {bus.cpu.pc == target_pc};

    bool stack_msb_check {bus.cpu.cpu_memory_read(0x01FD) == 0x01};
    bool stack_lsb_check {bus.cpu.cpu_memory_read(0x01FC) == 0xFF};
    bool stack_word_check {bus.cpu.cpu_memory_read(0x01FB) == target_word};

    bool stack_check {stack_msb_check && stack_lsb_check && stack_word_check};
    bool all_check {status_check && stack_ptr_check && pc_check && stack_check};

    MY_ASSERT(all_check == true);
}

void test_clc_behaviour()
{
    CPU cpu;
    uint8_t target_word {0b1111'1110};

    cpu.status.word = 0xFF;
    cpu.CLC();

    MY_ASSERT(cpu.status.word == target_word);
}

void test_cld_behaviour()
{
    CPU cpu;
    uint8_t target_word {0b1111'0111};

    cpu.status.word = 0xFF;
    cpu.CLD();

    MY_ASSERT(cpu.status.word == target_word);
}

void test_cli_behaviour()
{
    CPU cpu;
    uint8_t target_word {0b1111'1011};

    cpu.status.word = 0xFF;
    cpu.CLI();

    MY_ASSERT(cpu.status.word == target_word);
}

void test_clv_behaviour()
{
    CPU cpu;
    uint8_t target_word {0b1011'1111};

    cpu.status.word = 0xFF;
    cpu.CLV();

    MY_ASSERT(cpu.status.word == target_word);
}

void test_dex_behaviour()
{
    CPU cpu;
    uint8_t target_x_reg {0x86};

    cpu.x_reg = 0x87;
    cpu.DEX();

    MY_ASSERT(cpu.x_reg == target_x_reg);
}

void test_dey_behaviour()
{
    CPU cpu;
    uint8_t target_y_reg {0x86};

    cpu.y_reg = 0x87;
    cpu.DEY();

    MY_ASSERT(cpu.y_reg == target_y_reg);
}

void test_inx_behaviour()
{
    CPU cpu;
    uint8_t target_x_reg {0xB0};

    cpu.x_reg = 0xAF;
    cpu.INX();

    MY_ASSERT(cpu.x_reg == target_x_reg);
}

void test_iny_behaviour()
{
    CPU cpu;
    uint8_t target_y_reg {0xB0};

    cpu.y_reg = 0xAF;
    cpu.INY();

    MY_ASSERT(cpu.y_reg == target_y_reg);
}

void test_irq_behaviour()
{
    SystemBus bus;
    uint8_t target_word {0xAD};
    uint8_t target_stack_ptr {0xFA};
    uint16_t target_pc {0x2731};

    bus.cpu.cpu_memory_write(MemoryConsts::irq_vector_msb, 0x27);
    bus.cpu.cpu_memory_write(MemoryConsts::irq_vector_lsb, 0x31);

    bus.cpu.pc = 0x01FF;
    bus.cpu.status.word = 0x89;
    bus.cpu.interrupt_irq();

    bool status_check {bus.cpu.status.word == target_word};
    bool stack_ptr_check {bus.cpu.stack_ptr == target_stack_ptr};
    bool pc_check {bus.cpu.pc == target_pc};

    bool stack_msb_check {bus.cpu.cpu_memory_read(0x01FD) == 0x01};
    bool stack_lsb_check {bus.cpu.cpu_memory_read(0x01FC) == 0xFF};
    bool stack_word_check {bus.cpu.cpu_memory_read(0x01FB) == target_word};

    bool stack_check {stack_msb_check && stack_lsb_check && stack_word_check};
    bool all_check {status_check && stack_ptr_check && pc_check && stack_check};

    MY_ASSERT(all_check == true);
}

void test_nmi_behaviour()
{
    SystemBus bus;
    uint8_t target_word {0xAD};
    uint8_t target_stack_ptr {0xFA};
    uint16_t target_pc {0x2731};

    bus.cpu.cpu_memory_write(MemoryConsts::nmi_vector_msb, 0x27);
    bus.cpu.cpu_memory_write(MemoryConsts::nmi_vector_lsb, 0x31);

    bus.cpu.pc = 0x01FF;
    bus.cpu.status.word = 0x89;
    bus.cpu.interrupt_nmi();

    bool status_check {bus.cpu.status.word == target_word};
    bool stack_ptr_check {bus.cpu.stack_ptr == target_stack_ptr};
    bool pc_check {bus.cpu.pc == target_pc};

    bool stack_msb_check {bus.cpu.cpu_memory_read(0x01FD) == 0x01};
    bool stack_lsb_check {bus.cpu.cpu_memory_read(0x01FC) == 0xFF};
    bool stack_word_check {bus.cpu.cpu_memory_read(0x01FB) == target_word};

    bool stack_check {stack_msb_check && stack_lsb_check && stack_word_check};
    bool all_check {status_check && stack_ptr_check && pc_check && stack_check};

    MY_ASSERT(all_check == true);
}

void test_pha_behaviour()
{
    SystemBus bus;
    uint8_t stack_ptr_init {bus.cpu.stack_ptr};
    uint8_t acc_init_value {0xAD};

    bus.cpu.acc = acc_init_value;
    bus.cpu.PHA();

    MY_ASSERT(bus.cpu.cpu_memory_read(MemoryConsts::stack_offset + stack_ptr_init) == acc_init_value);
}

void test_php_behaviour()
{
    SystemBus bus;
    uint8_t stack_ptr_init {bus.cpu.stack_ptr};
    uint8_t status_init_mask {0xAD};
    uint8_t status_final_mask = status_init_mask | 0b0001'0000 | 0b0010'0000;

    bus.cpu.status.word = status_init_mask;
    bus.cpu.PHP();

    MY_ASSERT(bus.cpu.cpu_memory_read(MemoryConsts::stack_offset + stack_ptr_init) == status_final_mask);
}

void test_pla_behaviour()
{
    SystemBus bus;
    uint8_t acc_init_value {0xAD};

    bus.cpu.acc = acc_init_value;
    bus.cpu.PHA();

    bus.cpu.acc = 0x00;
    bus.cpu.PLA();

    MY_ASSERT(bus.cpu.acc == acc_init_value);
}

void test_plp_behaviour()
{
    SystemBus bus;
    uint8_t status_init_mask {0xAD};
    uint8_t status_final_mask = status_init_mask | 0b0001'0000 | 0b0010'0000;

    bus.cpu.status.word = status_init_mask;
    bus.cpu.PHP();

    bus.cpu.status.word = 0x00;
    bus.cpu.PLP();

    MY_ASSERT(bus.cpu.status.word == status_final_mask);
}

void test_rti_behaviour()
{
    SystemBus bus;
    uint8_t target_word {0x8D};
    uint8_t target_stack_ptr {0xFD};
    uint16_t target_pc {0x01FF};

    bus.cpu.pc = target_pc;
    bus.cpu.status.word = 0x89;
    bus.cpu.interrupt_nmi();
    bus.cpu.RTI();

    bool status_check {bus.cpu.status.word == target_word};
    bool stack_ptr_check {bus.cpu.stack_ptr == target_stack_ptr};
    bool pc_check {bus.cpu.pc == target_pc};

    bool all_check {status_check && stack_ptr_check && pc_check};

    MY_ASSERT(all_check == true);
}

void test_rts_behaviour()
{
    SystemBus bus;
    uint16_t target_pc {0x01FF};

    bus.cpu.pc = 0x01FF;
    bus.cpu.JSR();
    bus.cpu.RTS();

    bool pc_check {bus.cpu.pc == target_pc};

    MY_ASSERT(pc_check == true);
}

void test_sec_behaviour()
{
    CPU cpu;
    uint8_t target_word {0b0000'0001};

    cpu.status.word = 0x00;
    cpu.SEC();

    MY_ASSERT(cpu.status.word == target_word);
}

void test_sed_behaviour()
{
    CPU cpu;
    uint8_t target_word {0b0000'1000};

    cpu.status.word = 0x00;
    cpu.SED();

    MY_ASSERT(cpu.status.word == target_word);
}

void test_sei_behaviour()
{
    CPU cpu;
    uint8_t target_word {0b0000'0100};

    cpu.status.word = 0x00;
    cpu.SEI();

    MY_ASSERT(cpu.status.word == target_word);
}

void test_tax_behaviour()
{
    CPU cpu;
    uint8_t target_value {0x77};

    cpu.acc = target_value;
    cpu.TAX();

    MY_ASSERT(cpu.x_reg == target_value);
}

void test_tay_behaviour()
{
    CPU cpu;
    uint8_t target_value {0x88};

    cpu.acc = target_value;
    cpu.TAY();

    MY_ASSERT(cpu.y_reg == target_value);
}

void test_tsx_behaviour()
{
    SystemBus bus;
    uint8_t target_value {0x99};

    bus.cpu.cpu_memory_write(MemoryConsts::stack_offset + bus.cpu.stack_ptr, target_value);
    bus.cpu.TSX();

    MY_ASSERT(bus.cpu.x_reg == target_value);
}

void test_txa_behaviour()
{
    CPU cpu;
    uint8_t target_value {0xAA};

    cpu.x_reg = target_value;
    cpu.TXA();

    MY_ASSERT(cpu.acc == target_value);
}

void test_txs_behaviour()
{
    SystemBus bus;
    uint8_t target_value {0xBB};

    bus.cpu.x_reg = target_value;
    bus.cpu.TXS();

    uint8_t value_from_stack {bus.cpu.cpu_memory_read(MemoryConsts::stack_offset + bus.cpu.stack_ptr)};

    MY_ASSERT(value_from_stack == target_value);
}

void test_tya_behaviour()
{
    CPU cpu;
    uint8_t target_value {0xCC};

    cpu.y_reg = target_value;
    cpu.TYA();

    MY_ASSERT(cpu.acc == target_value);
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

    test_irq_behaviour();
    test_nmi_behaviour();

    test_pha_behaviour();
    test_php_behaviour();
    test_pla_behaviour();
    test_plp_behaviour();

    test_rti_behaviour();
    test_rts_behaviour();

    test_sec_behaviour();
    test_sed_behaviour();
    test_sei_behaviour();

    test_tax_behaviour();
    test_tay_behaviour();
    test_tsx_behaviour();
    test_txa_behaviour();
    test_txs_behaviour();
    test_tya_behaviour();
}
