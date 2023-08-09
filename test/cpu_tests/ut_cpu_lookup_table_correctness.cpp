#include "./cpu_tests.h"
#include "../test_main.h"
#include "../../include/bus.h"


using AM = Instruction::AddressingMode;

void test_adc_mode_immediate()
{
    SystemBus bus;
    Instruction target_instr {"ADC", AM::immediate, 0x69, 2, 2};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_zero_page()
{
    SystemBus bus;
    Instruction target_instr {"ADC", AM::zero_page, 0x65, 2, 3};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_zero_page_x()
{
    SystemBus bus;
    Instruction target_instr {"ADC", AM::zero_page_x, 0x75, 2, 4};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_absolute()
{
    SystemBus bus;
    Instruction target_instr {"ADC", AM::absolute, 0x6D, 3, 4};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_absolute_x()
{
    SystemBus bus;
    Instruction target_instr {"ADC", AM::absolute_x, 0x7D, 3, 4};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_absolute_y()
{
    SystemBus bus;
    Instruction target_instr {"ADC", AM::absolute_y, 0x79, 3, 4};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_indirect_x()
{
    SystemBus bus;
    Instruction target_instr {"ADC", AM::indirect_x, 0x61, 2, 6};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_adc_mode_indirect_y()
{
    SystemBus bus;
    Instruction target_instr {"ADC", AM::indirect_y, 0x71, 2, 5};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_immediate()
{
    SystemBus bus;
    Instruction target_instr {"AND", AM::immediate, 0x29, 2, 2};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_zero_page()
{
    SystemBus bus;
    Instruction target_instr {"AND", AM::zero_page, 0x25, 2, 3};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_zero_page_x()
{
    SystemBus bus;
    Instruction target_instr {"AND", AM::zero_page_x, 0x35, 2, 4};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_absolute()
{
    SystemBus bus;
    Instruction target_instr {"AND", AM::absolute, 0x2D, 3, 4};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_absolute_x()
{
    SystemBus bus;
    Instruction target_instr {"AND", AM::absolute_x, 0x3D, 3, 4};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_absolute_y()
{
    SystemBus bus;
    Instruction target_instr {"AND", AM::absolute_y, 0x39, 3, 4};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_indirect_x()
{
    SystemBus bus;
    Instruction target_instr {"AND", AM::indirect_x, 0x21, 2, 6};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

    MY_ASSERT(deduced == target_instr);
}

void test_and_mode_indirect_y()
{
    SystemBus bus;
    Instruction target_instr {"AND", AM::indirect_y, 0x31, 2, 5};

    Instruction deduced = bus.cpu.deduce_instr_from_opcode(target_instr.opcode);

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
}
