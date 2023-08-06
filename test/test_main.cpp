#include <iostream>

#include "./test_main.h"


void run_all_tests()
{
    ut_bus_cpu_memory_connection();
    ut_cpu_status_register();
    ut_cpu_hard_reset();
    ut_cpu_implied_opcodes_behaviour();
}


int main()
{
    run_all_tests();

    std::cout << "\n" << c_blue << "\nSummary: " << passed << " out of " << (passed + failed) << " tests passed" << c_reset << "\n\n";

    return 0;
}
