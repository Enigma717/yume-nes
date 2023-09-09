#include "./include/bus.h"

#include <cstdint>
#include <iostream>

namespace
{
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;

    constexpr Instruction ill_instruction {MN::ILL, AM::illegal, 0x02, 1, 1};
}


int main()
{
    SystemBus bus;

    bus.cartridge->load_cartridge("./test/cartridge_tests/roms/nestest.nes");
    bus.ram->memory_load_program(bus.cartridge->mapper.prg_rom_memory, 0xC000);
    bus.cpu.pc = 0xC000;

    do {
        bus.cpu.perform_cycle(true);
    } while (!(bus.cpu.curr_instruction == ill_instruction));

    std::cout << "\nTest result: " << static_cast<int>(bus.ram->memory_read(0x0002)) << "\n";

    return 0;
}
