#include "./cpu_tests.h"
#include "../test_main.h"
#include "../../include/cpu.h"


using MN = Instruction::MnemonicName;
using AM = Instruction::AddressingMode;

void test_adc_mode_immediate()
{
    CPU cpu;
    Instruction target_instr {MN::ADC, AM::immediate, 0x69, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::ADC, AM::zero_page, 0x65, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::ADC, AM::zero_page_x, 0x75, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::ADC, AM::absolute, 0x6D, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::ADC, AM::absolute_x, 0x7D, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_absolute_y()
{
    CPU cpu;
    Instruction target_instr {MN::ADC, AM::absolute_y, 0x79, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_indirect_x()
{
    CPU cpu;
    Instruction target_instr {MN::ADC, AM::indirect_x, 0x61, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_indirect_y()
{
    CPU cpu;
    Instruction target_instr {MN::ADC, AM::indirect_y, 0x71, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_immediate()
{
    CPU cpu;
    Instruction target_instr {MN::AND, AM::immediate, 0x29, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::AND, AM::zero_page, 0x25, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::AND, AM::zero_page_x, 0x35, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::AND, AM::absolute, 0x2D, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::AND, AM::absolute_x, 0x3D, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_absolute_y()
{
    CPU cpu;
    Instruction target_instr {MN::AND, AM::absolute_y, 0x39, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_indirect_x()
{
    CPU cpu;
    Instruction target_instr {MN::AND, AM::indirect_x, 0x21, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_indirect_y()
{
    CPU cpu;
    Instruction target_instr {MN::AND, AM::indirect_y, 0x31, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_asl_mode_accumulator()
{
    CPU cpu;
    Instruction target_instr {MN::ASL, AM::accumulator, 0x0A, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_asl_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::ASL, AM::zero_page, 0x06, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_asl_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::ASL, AM::zero_page_x, 0x16, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_asl_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::ASL, AM::absolute, 0x0E, 3, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_asl_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::ASL, AM::absolute_x, 0x1E, 3, 7};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_bcc_mode_relative()
{
    CPU cpu;
    Instruction target_instr {MN::BCC, AM::relative, 0x90, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_bcs_mode_relative()
{
    CPU cpu;
    Instruction target_instr {MN::BCS, AM::relative, 0xB0, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_beq_mode_relative()
{
    CPU cpu;
    Instruction target_instr {MN::BEQ, AM::relative, 0xF0, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_bit_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::BIT, AM::zero_page, 0x24, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_bit_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::BIT, AM::absolute, 0x2C, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_bmi_mode_relative()
{
    CPU cpu;
    Instruction target_instr {MN::BMI, AM::relative, 0x30, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_bne_mode_relative()
{
    CPU cpu;
    Instruction target_instr {MN::BNE, AM::relative, 0xD0, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_bpl_mode_relative()
{
    CPU cpu;
    Instruction target_instr {MN::BPL, AM::relative, 0x10, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_brk_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::BRK, AM::implied, 0x00, 1, 7};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_bvc_mode_relative()
{
    CPU cpu;
    Instruction target_instr {MN::BVC, AM::relative, 0x50, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_bvs_mode_relative()
{
    CPU cpu;
    Instruction target_instr {MN::BVS, AM::relative, 0x70, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_clc_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::CLC, AM::implied, 0x18, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cld_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::CLD, AM::implied, 0xD8, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cli_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::CLI, AM::implied, 0x58, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_clv_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::CLV, AM::implied, 0xB8, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cmp_mode_immediate()
{
    CPU cpu;
    Instruction target_instr {MN::CMP, AM::immediate, 0xC9, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cmp_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::CMP, AM::zero_page, 0xC5, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cmp_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::CMP, AM::zero_page_x, 0xD5, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cmp_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::CMP, AM::absolute, 0xCD, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cmp_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::CMP, AM::absolute_x, 0xDD, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cmp_mode_absolute_y()
{
    CPU cpu;
    Instruction target_instr {MN::CMP, AM::absolute_y, 0xD9, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cmp_mode_indirect_x()
{
    CPU cpu;
    Instruction target_instr {MN::CMP, AM::indirect_x, 0xC1, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cmp_mode_indirect_y()
{
    CPU cpu;
    Instruction target_instr {MN::CMP, AM::indirect_y, 0xD1, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cpx_mode_immediate()
{
    CPU cpu;
    Instruction target_instr {MN::CPX, AM::immediate, 0xE0, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cpx_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::CPX, AM::zero_page, 0xE4, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cpx_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::CPX, AM::absolute, 0xEC, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cpy_mode_immediate()
{
    CPU cpu;
    Instruction target_instr {MN::CPY, AM::immediate, 0xC0, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cpy_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::CPY, AM::zero_page, 0xC4, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_cpy_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::CPY, AM::absolute, 0xCC, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_dec_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::DEC, AM::zero_page, 0xC6, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_dec_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::DEC, AM::zero_page_x, 0xD6, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_dec_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::DEC, AM::absolute, 0xCE, 3, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_dec_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::DEC, AM::absolute_x, 0xDE, 3, 7};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_dex_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::DEX, AM::implied, 0xCA, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_dey_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::DEY, AM::implied, 0x88, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_eor_mode_immediate()
{
    CPU cpu;
    Instruction target_instr {MN::EOR, AM::immediate, 0x49, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_eor_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::EOR, AM::zero_page, 0x45, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_eor_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::EOR, AM::zero_page_x, 0x55, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_eor_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::EOR, AM::absolute, 0x4D, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_eor_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::EOR, AM::absolute_x, 0x5D, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_eor_mode_absolute_y()
{
    CPU cpu;
    Instruction target_instr {MN::EOR, AM::absolute_y, 0x59, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_eor_mode_indirect_x()
{
    CPU cpu;
    Instruction target_instr {MN::EOR, AM::indirect_x, 0x41, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_eor_mode_indirect_y()
{
    CPU cpu;
    Instruction target_instr {MN::EOR, AM::indirect_y, 0x51, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_inc_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::INC, AM::zero_page, 0xE6, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_inc_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::INC, AM::zero_page_x, 0xF6, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_inc_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::INC, AM::absolute, 0xEE, 3, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_inc_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::INC, AM::absolute_x, 0xFE, 3, 7};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_inx_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::INX, AM::implied, 0xE8, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_iny_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::INY, AM::implied, 0xC8, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_jmp_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::JMP, AM::absolute, 0x4C, 3, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_jmp_mode_indirect()
{
    CPU cpu;
    Instruction target_instr {MN::JMP, AM::indirect, 0x6C, 3, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_jsr_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::JSR, AM::absolute, 0x20, 3, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lda_mode_immediate()
{
    CPU cpu;
    Instruction target_instr {MN::LDA, AM::immediate, 0xA9, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lda_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::LDA, AM::zero_page, 0xA5, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lda_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::LDA, AM::zero_page_x, 0xB5, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lda_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::LDA, AM::absolute, 0xAD, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lda_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::LDA, AM::absolute_x, 0xBD, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lda_mode_absolute_y()
{
    CPU cpu;
    Instruction target_instr {MN::LDA, AM::absolute_y, 0xB9, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lda_mode_indirect_x()
{
    CPU cpu;
    Instruction target_instr {MN::LDA, AM::indirect_x, 0xA1, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lda_mode_indirect_y()
{
    CPU cpu;
    Instruction target_instr {MN::LDA, AM::indirect_y, 0xB1, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ldx_mode_immediate()
{
    CPU cpu;
    Instruction target_instr {MN::LDX, AM::immediate, 0xA2, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ldx_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::LDX, AM::zero_page, 0xA6, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ldx_mode_zero_page_y()
{
    CPU cpu;
    Instruction target_instr {MN::LDX, AM::zero_page_y, 0xB6, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ldx_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::LDX, AM::absolute, 0xAE, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ldx_mode_absolute_y()
{
    CPU cpu;
    Instruction target_instr {MN::LDX, AM::absolute_y, 0xBE, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ldy_mode_immediate()
{
    CPU cpu;
    Instruction target_instr {MN::LDY, AM::immediate, 0xA0, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ldy_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::LDY, AM::zero_page, 0xA4, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ldy_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::LDY, AM::zero_page_x, 0xB4, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ldy_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::LDY, AM::absolute, 0xAC, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ldy_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::LDY, AM::absolute_x, 0xBC, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lsr_mode_accumulator()
{
    CPU cpu;
    Instruction target_instr {MN::LSR, AM::accumulator, 0x4A, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lsr_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::LSR, AM::zero_page, 0x46, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lsr_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::LSR, AM::zero_page_x, 0x56, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lsr_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::LSR, AM::absolute, 0x4E, 3, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_lsr_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::LSR, AM::absolute_x, 0x5E, 3, 7};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_nop_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::NOP, AM::implied, 0xEA, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ora_mode_immediate()
{
    CPU cpu;
    Instruction target_instr {MN::ORA, AM::immediate, 0x09, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ora_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::ORA, AM::zero_page, 0x05, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ora_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::ORA, AM::zero_page_x, 0x15, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ora_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::ORA, AM::absolute, 0x0D, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ora_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::ORA, AM::absolute_x, 0x1D, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ora_mode_absolute_y()
{
    CPU cpu;
    Instruction target_instr {MN::ORA, AM::absolute_y, 0x19, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ora_mode_indirect_x()
{
    CPU cpu;
    Instruction target_instr {MN::ORA, AM::indirect_x, 0x01, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ora_mode_indirect_y()
{
    CPU cpu;
    Instruction target_instr {MN::ORA, AM::indirect_y, 0x11, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_pha_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::PHA, AM::implied, 0x48, 1, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_php_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::PHP, AM::implied, 0x08, 1, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_pla_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::PLA, AM::implied, 0x68, 1, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_plp_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::PLP, AM::implied, 0x28, 1, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_rol_mode_accumulator()
{
    CPU cpu;
    Instruction target_instr {MN::ROL, AM::accumulator, 0x2A, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_rol_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::ROL, AM::zero_page, 0x26, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_rol_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::ROL, AM::zero_page_x, 0x36, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_rol_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::ROL, AM::absolute, 0x2E, 3, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_rol_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::ROL, AM::absolute_x, 0x3E, 3, 7};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ror_mode_accumulator()
{
    CPU cpu;
    Instruction target_instr {MN::ROR, AM::accumulator, 0x6A, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ror_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::ROR, AM::zero_page, 0x66, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ror_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::ROR, AM::zero_page_x, 0x76, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ror_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::ROR, AM::absolute, 0x6E, 3, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_ror_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::ROR, AM::absolute_x, 0x7E, 3, 7};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_rti_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::RTI, AM::implied, 0x40, 1, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_rts_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::RTS, AM::implied, 0x60, 1, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sbc_mode_immediate()
{
    CPU cpu;
    Instruction target_instr {MN::SBC, AM::immediate, 0xE9, 2, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sbc_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::SBC, AM::zero_page, 0xE5, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sbc_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::SBC, AM::zero_page_x, 0xF5, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sbc_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::SBC, AM::absolute, 0xED, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sbc_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::SBC, AM::absolute_x, 0xFD, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sbc_mode_absolute_y()
{
    CPU cpu;
    Instruction target_instr {MN::SBC, AM::absolute_y, 0xF9, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sbc_mode_indirect_x()
{
    CPU cpu;
    Instruction target_instr {MN::SBC, AM::indirect_x, 0xE1, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sbc_mode_indirect_y()
{
    CPU cpu;
    Instruction target_instr {MN::SBC, AM::indirect_y, 0xF1, 2, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sec_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::SEC, AM::implied, 0x38, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sed_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::SED, AM::implied, 0xF8, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sei_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::SEI, AM::implied, 0x78, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sta_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::STA, AM::zero_page, 0x85, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sta_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::STA, AM::zero_page_x, 0x95, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sta_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::STA, AM::absolute, 0x8D, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sta_mode_absolute_x()
{
    CPU cpu;
    Instruction target_instr {MN::STA, AM::absolute_x, 0x9D, 3, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sta_mode_absolute_y()
{
    CPU cpu;
    Instruction target_instr {MN::STA, AM::absolute_y, 0x99, 3, 5};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sta_mode_indirect_x()
{
    CPU cpu;
    Instruction target_instr {MN::STA, AM::indirect_x, 0x81, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sta_mode_indirect_y()
{
    CPU cpu;
    Instruction target_instr {MN::STA, AM::indirect_y, 0x91, 2, 6};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_stx_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::STX, AM::zero_page, 0x86, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_stx_mode_zero_page_y()
{
    CPU cpu;
    Instruction target_instr {MN::STX, AM::zero_page_y, 0x96, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_stx_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::STX, AM::absolute, 0x8E, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sty_mode_zero_page()
{
    CPU cpu;
    Instruction target_instr {MN::STY, AM::zero_page, 0x84, 2, 3};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sty_mode_zero_page_x()
{
    CPU cpu;
    Instruction target_instr {MN::STY, AM::zero_page_x, 0x94, 2, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_sty_mode_absolute()
{
    CPU cpu;
    Instruction target_instr {MN::STY, AM::absolute, 0x8C, 3, 4};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_tax_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::TAX, AM::implied, 0xAA, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_tay_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::TAY, AM::implied, 0xA8, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_tsx_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::TSX, AM::implied, 0xBA, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_txa_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::TXA, AM::implied, 0x8A, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_txs_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::TXS, AM::implied, 0x9A, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_tya_mode_implied()
{
    CPU cpu;
    Instruction target_instr {MN::TYA, AM::implied, 0x98, 1, 2};

    Instruction deduced = cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}


void ut_cpu_lookup_table_correctness()
{
    TEST_SET;

    test_adc_mode_immediate();
    test_adc_mode_zero_page();
    test_adc_mode_zero_page_x();
    test_adc_mode_absolute();
    test_adc_mode_absolute_x();
    test_adc_mode_absolute_y();
    test_adc_mode_indirect_x();
    test_adc_mode_indirect_y();

    test_and_mode_immediate();
    test_and_mode_zero_page();
    test_and_mode_zero_page_x();
    test_and_mode_absolute();
    test_and_mode_absolute_x();
    test_and_mode_absolute_y();
    test_and_mode_indirect_x();
    test_and_mode_indirect_y();

    test_asl_mode_accumulator();
    test_asl_mode_zero_page();
    test_asl_mode_zero_page_x();
    test_asl_mode_absolute();
    test_asl_mode_absolute_x();

    test_bcc_mode_relative();
    test_bcs_mode_relative();
    test_beq_mode_relative();
    test_bit_mode_zero_page();
    test_bit_mode_absolute();
    test_bmi_mode_relative();
    test_bne_mode_relative();
    test_bpl_mode_relative();
    test_brk_mode_implied();
    test_bvc_mode_relative();
    test_bvs_mode_relative();

    test_clc_mode_implied();
    test_cld_mode_implied();
    test_cli_mode_implied();
    test_clv_mode_implied();

    test_cmp_mode_immediate();
    test_cmp_mode_zero_page();
    test_cmp_mode_zero_page_x();
    test_cmp_mode_absolute();
    test_cmp_mode_absolute_x();
    test_cmp_mode_absolute_y();
    test_cmp_mode_indirect_x();
    test_cmp_mode_indirect_y();

    test_cpx_mode_immediate();
    test_cpx_mode_zero_page();
    test_cpx_mode_absolute();
    test_cpy_mode_immediate();
    test_cpy_mode_zero_page();
    test_cpy_mode_absolute();

    test_dec_mode_zero_page();
    test_dec_mode_zero_page_x();
    test_dec_mode_absolute();
    test_dec_mode_absolute_x();
    test_dex_mode_implied();
    test_dey_mode_implied();

    test_eor_mode_immediate();
    test_eor_mode_zero_page();
    test_eor_mode_zero_page_x();
    test_eor_mode_absolute();
    test_eor_mode_absolute_x();
    test_eor_mode_absolute_y();
    test_eor_mode_indirect_x();
    test_eor_mode_indirect_y();

    test_inc_mode_zero_page();
    test_inc_mode_zero_page_x();
    test_inc_mode_absolute();
    test_inc_mode_absolute_x();
    test_inx_mode_implied();
    test_iny_mode_implied();

    test_jmp_mode_absolute();
    test_jmp_mode_indirect();
    test_jsr_mode_absolute();

    test_lda_mode_immediate();
    test_lda_mode_zero_page();
    test_lda_mode_zero_page_x();
    test_lda_mode_absolute();
    test_lda_mode_absolute_x();
    test_lda_mode_absolute_y();
    test_lda_mode_indirect_x();
    test_lda_mode_indirect_y();

    test_ldx_mode_immediate();
    test_ldx_mode_zero_page();
    test_ldx_mode_zero_page_y();
    test_ldx_mode_absolute();
    test_ldx_mode_absolute_y();

    test_ldy_mode_immediate();
    test_ldy_mode_zero_page();
    test_ldy_mode_zero_page_x();
    test_ldy_mode_absolute();
    test_ldy_mode_absolute_x();

    test_lsr_mode_accumulator();
    test_lsr_mode_zero_page();
    test_lsr_mode_zero_page_x();
    test_lsr_mode_absolute();
    test_lsr_mode_absolute_x();

    test_nop_mode_implied();

    test_lda_mode_immediate();
    test_lda_mode_zero_page();
    test_lda_mode_zero_page_x();
    test_lda_mode_absolute();
    test_lda_mode_absolute_x();
    test_lda_mode_absolute_y();
    test_lda_mode_indirect_x();
    test_lda_mode_indirect_y();

    test_pha_mode_implied();
    test_php_mode_implied();
    test_pla_mode_implied();
    test_plp_mode_implied();

    test_rol_mode_accumulator();
    test_rol_mode_zero_page();
    test_rol_mode_zero_page_x();
    test_rol_mode_absolute();
    test_rol_mode_absolute_x();

    test_ror_mode_accumulator();
    test_ror_mode_zero_page();
    test_ror_mode_zero_page_x();
    test_ror_mode_absolute();
    test_ror_mode_absolute_x();

    test_rti_mode_implied();
    test_rts_mode_implied();

    test_sbc_mode_immediate();
    test_sbc_mode_zero_page();
    test_sbc_mode_zero_page_x();
    test_sbc_mode_absolute();
    test_sbc_mode_absolute_x();
    test_sbc_mode_absolute_y();
    test_sbc_mode_indirect_x();
    test_sbc_mode_indirect_y();

    test_sec_mode_implied();
    test_sed_mode_implied();
    test_sei_mode_implied();

    test_sta_mode_zero_page();
    test_sta_mode_zero_page_x();
    test_sta_mode_absolute();
    test_sta_mode_absolute_x();
    test_sta_mode_absolute_y();
    test_sta_mode_indirect_x();
    test_sta_mode_indirect_y();

    test_stx_mode_zero_page();
    test_stx_mode_zero_page_y();
    test_stx_mode_absolute();

    test_sty_mode_zero_page();
    test_sty_mode_zero_page_x();
    test_sty_mode_absolute();

    test_tax_mode_implied();
    test_tay_mode_implied();
    test_tsx_mode_implied();
    test_txa_mode_implied();
    test_txs_mode_implied();
    test_tya_mode_implied();
}
