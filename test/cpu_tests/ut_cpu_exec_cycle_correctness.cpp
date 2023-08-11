#include "./cpu_tests.h"
#include "../test_main.h"
#include "../../include/bus.h"


void test_exec_cycle_instr_implied()
{
    ///////////////////////////////
    // Executed program:         //
    //                           //
    // DEX      # x = 0xFF       //
    // PHP      # status = 0xB4  //
    // PLA      # acc = status   //
    // TAX      # x = acc        //
    //                           //
    // Result: x == 0xB4         //
    ///////////////////////////////

    SystemBus bus;
    uint8_t dex_opcode = 0xCA;
    uint8_t php_opcode = 0x08;
    uint8_t pla_opcode = 0x68;
    uint8_t tax_opcode = 0xAA;

    bus.ram->mem_write(bus.cpu.pc + 0, dex_opcode);
    bus.ram->mem_write(bus.cpu.pc + 1, php_opcode);
    bus.ram->mem_write(bus.cpu.pc + 2, pla_opcode);
    bus.ram->mem_write(bus.cpu.pc + 3, tax_opcode);
    bus.cpu.exec_cycle();
    bus.cpu.exec_cycle();
    bus.cpu.exec_cycle();
    bus.cpu.exec_cycle();


    MY_ASSERT(bus.cpu.x_reg == 0xB4);
}


void ut_cpu_exec_cycle_correctness()
{
    TEST_SET;

    test_exec_cycle_instr_implied();
}
