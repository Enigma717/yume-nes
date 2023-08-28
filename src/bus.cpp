#include "../include/bus.h"


SystemBus::SystemBus()
{
    ram = std::make_shared<Memory>();
    cartridge = std::make_shared<Cartridge>();

    cpu.connect_with_memory(ram);
    cpu.connect_with_cartridge(cartridge);
    cpu.hard_reset();
}
