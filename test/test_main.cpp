#include <iostream>

#include "./test_main.h"
#include "./cpu_tests/cpu_tests.h"


void run_all_tests()
{
    ut_cpu_bus_memory_connection();
    ut_cpu_status_register();
    ut_cpu_hard_reset();
    ut_cpu_implied_opcodes_behaviour();
    ut_cpu_implied_opcodes_flags();
    ut_cpu_lookup_table_correctness();
}


int main()
{
    run_all_tests();

    std::cout << "\n" << c_blue << "\nSummary: " << passed << " out of " << (passed + failed) << " tests passed" << c_reset << "\n\n";

    return 0;
}
