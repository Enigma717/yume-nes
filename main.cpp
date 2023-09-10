#include "./include/system.h"

#include <cstdint>
#include <iostream>

namespace
{
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;

    constexpr Instruction rts_instruction {MN::RTS, AM::implied, 0x60, 1, 6};
}


int main()
{
    System nes;

    nes.cartridge->load_cartridge("./test/cartridge_tests/roms/nestest.nes");
    nes.ram->memory_load_program(nes.cartridge->mapper.prg_rom_memory, 0xC000);
    nes.cpu.pc = 0xC000;

    do {
        nes.cpu.perform_cycle(true);
    } while (!(nes.cpu.curr_instruction == rts_instruction && nes.cpu.arg_address == 0xC66E));

    std::cout << "\nTest result: " << static_cast<int>(nes.ram->memory_read(0x0002)) << "\n";

    return 0;
}
