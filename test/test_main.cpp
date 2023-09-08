#include "./test_main.h"

#include "./cpu_tests/cpu_tests.h"
#include "./cartridge_tests/cartridge_tests.h"

#include <iostream>


void run_cpu_tests()
{
    ut_cpu_boot_and_reset();
    ut_cpu_connection_with_components();
    ut_cpu_status_register();
    // ut_cpu_lookup_table_correctness();
    ut_cpu_cycle_correctness();
}

void run_opcodes_tests()
{
    ut_cpu_implied_opcodes_behaviour();
    ut_cpu_implied_opcodes_flags();
    ut_cpu_accumulator_opcodes_behaviour();
    ut_cpu_accumulator_opcodes_flags();
    ut_cpu_immediate_opcodes_behaviour();
    ut_cpu_immediate_opcodes_flags();
    ut_cpu_zero_page_opcodes_behaviour();
    ut_cpu_zero_page_opcodes_flags();
    ut_cpu_zero_page_x_opcodes_behaviour();
    ut_cpu_zero_page_x_opcodes_flags();
    ut_cpu_zero_page_y_opcodes_behaviour();
    ut_cpu_zero_page_y_opcodes_flags();
    ut_cpu_relative_opcodes_behaviour();
    ut_cpu_absolute_opcodes_behaviour();
    ut_cpu_absolute_opcodes_flags();
    ut_cpu_absolute_x_opcodes_behaviour();
    ut_cpu_absolute_x_opcodes_flags();
    ut_cpu_absolute_y_opcodes_behaviour();
    ut_cpu_absolute_y_opcodes_flags();
    ut_cpu_indirect_opcodes_behaviour();
    ut_cpu_indirect_x_opcodes_behaviour();
    ut_cpu_indirect_x_opcodes_flags();
    ut_cpu_indirect_y_opcodes_behaviour();
    ut_cpu_indirect_y_opcodes_flags();
}

void run_cartridge_tests()
{
    ut_cartridge_header_decoding();
}

void run_all_tests()
{
    run_cpu_tests();
    // run_opcodes_tests();
    run_cartridge_tests();
}


int main()
{
    run_all_tests();

    std::cout << "\n" << c_blue << "\nSummary: " << passed << " out of " << (passed + failed) << " tests passed" << c_reset << "\n\n";

    return 0;
}
