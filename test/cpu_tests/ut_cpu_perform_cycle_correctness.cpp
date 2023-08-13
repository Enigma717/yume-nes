#include "./cpu_tests.h"
#include "../test_main.h"
#include "../../include/bus.h"


namespace InstrLookup
{
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;

    constexpr Instruction brk_instr {MN::BRK, AM::implied, 0x00, 1, 7};
}

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
    MemoryVec program_code {0xCA, 0x08, 0x68, 0xAA, 0x00};

    bus.ram->mem_load_program(program_code, bus.cpu.pc);

    do {
        bus.cpu.perform_cycle(true);
    } while (!(bus.cpu.curr_instruction == InstrLookup::brk_instr));


    MY_ASSERT(bus.cpu.x_reg == 0xB4);
}


void ut_cpu_perform_cycle_correctness()
{
    TEST_SET;

    test_perform_cycle_instr_implied();
}
