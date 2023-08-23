#ifndef CPU_TESTS_H
#define CPU_TESTS_H


#include "../../include/instruction.h"


namespace InstrLookup
{
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;

    constexpr Instruction brk_instruction {MN::BRK, AM::implied, 0x00, 1, 7};
}


void ut_cpu_boot_and_reset();
void ut_cpu_bus_memory_connection();
void ut_cpu_status_register();
void ut_cpu_lookup_table_correctness();
void ut_cpu_implied_opcodes_behaviour();
void ut_cpu_implied_opcodes_flags();
void ut_cpu_accumulator_opcodes_behaviour();
void ut_cpu_accumulator_opcodes_flags();
void ut_cpu_immediate_opcodes_behaviour();
void ut_cpu_immediate_opcodes_flags();
void ut_cpu_zero_page_opcodes_behaviour();
void ut_cpu_zero_page_opcodes_flags();
void ut_cpu_zero_page_x_opcodes_behaviour();
void ut_cpu_zero_page_x_opcodes_flags();
void ut_cpu_zero_page_y_opcodes_behaviour();
void ut_cpu_zero_page_y_opcodes_flags();
void ut_cpu_relative_opcodes_behaviour();
void ut_cpu_absolute_opcodes_behaviour();
void ut_cpu_absolute_opcodes_flags();
void ut_cpu_absolute_x_opcodes_behaviour();
void ut_cpu_absolute_x_opcodes_flags();
void ut_cpu_absolute_y_opcodes_behaviour();
void ut_cpu_absolute_y_opcodes_flags();
void ut_cpu_perform_cycle_correctness();


#endif
