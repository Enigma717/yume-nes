#include "../include/system.h"


System::System() : cpu{ppu}
{
    ram = std::make_shared<Memory>();
    cartridge = std::make_shared<Cartridge>();

    ppu.connect_with_cartridge(cartridge);

    cpu.connect_with_memory(ram);
    cpu.connect_with_cartridge(cartridge);
    cpu.hard_reset();
}
