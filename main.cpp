#include "./include/system.h"

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
    System nes;

    nes.cartridge->load_cartridge("./test/cartridge_tests/roms/nestest.nes");
    nes.ram->memory_load_program(nes.cartridge->mapper.prg_rom_memory, 0xC000);
    nes.cpu.pc = 0xC000;

    do {
        nes.cpu.perform_cycle(true);
    } while (!(nes.cpu.cycles_executed == 30000));

    std::cout << "\nTest result: " << static_cast<int>(nes.ram->memory_read(0x0002)) << "\n";

    return 0;
}
