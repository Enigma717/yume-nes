#include "./cpu_tests.h"

#include "../test_main.h"
#include "../../include/bus.h"


void test_perform_cycle_instr_implied()
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
    SystemMemory program_code {0xCA, 0x08, 0x68, 0xAA, 0x00};

    bus.ram->memory_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(DebugMode::cpu_debug_mode);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instruction));


    MY_ASSERT(bus.cpu.x_reg == 0xB4);
}


void ut_cpu_perform_cycle_correctness()
{
    TEST_SET;

    test_perform_cycle_instr_implied();
}
