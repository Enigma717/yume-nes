#ifndef TEST_MAIN_H
#define TEST_MAIN_H


#include <iostream>
#include <iomanip>
#include <string>


inline const std::string c_reset = "\033[0m";
inline const std::string c_red   = "\033[31m";
inline const std::string c_green = "\033[32m";
inline const std::string c_blue  = "\033[34m";

inline int passed = 0;
inline int failed = 0;


#define TEST_PASS \
    (std::cout << c_blue << "Test: " << c_reset << __FUNCTION__ << c_green << "\t\t  [PASSED]" << c_reset << "\n", \
    passed++)

#define TEST_FAIL \
    (std::cout << c_blue << "Test: " << c_reset << __FUNCTION__ << c_red << "\t\t  [FAILED]" << c_reset << "\n", \
    failed++)

#define TEST_SET \
    std::cout << c_blue << "\n===== Tests set: " << __FUNCTION__ << " ===== " << c_reset << "\n"

#define MY_ASSERT(expr) (expr ? TEST_PASS : TEST_FAIL)


void ut_bus_cpu_memory_connection();
void ut_cpu_status_register();
void ut_cpu_hard_reset();
void ut_cpu_implied_opcodes_behaviour();


#endif
