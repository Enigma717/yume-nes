#ifndef CPU_TESTS_H
#define CPU_TESTS_H


void ut_cpu_bus_memory_connection();
void ut_cpu_status_register();
void ut_cpu_boot_and_reset();
void ut_cpu_implied_opcodes_behaviour();
void ut_cpu_implied_opcodes_flags();
void ut_cpu_lookup_table_correctness();
void ut_cpu_perform_cycle_correctness();


#endif
