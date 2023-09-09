#include "./include/bus.h"

#include <cstdint>
#include <iostream>


int main()
{
    SystemBus bus;

    bus.cartridge->load_cartridge("./test/cartridge_tests/roms/nestest.nes");
    bus.ram->memory_load_program(bus.cartridge->mapper.prg_rom_memory, 0xC000);
    bus.cpu.pc = 0xC000;

    do {
        bus.cpu.perform_cycle(true);
    } while (!(bus.cpu.cycles_executed == 3000));

    return 0;
}
