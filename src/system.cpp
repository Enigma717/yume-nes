#include "../include/system.h"


System::System() : cpu{ppu}
{
    ram = std::make_shared<Memory>();
    cartridge = std::make_shared<Cartridge>();
}

void System::prepare_system_for_start()
{
    ppu.connect_with_cartridge(cartridge);
    ppu.prepare_sprites_tiles_memory();

    cpu.connect_with_memory(ram);
    cpu.connect_with_cartridge(cartridge);
    cpu.hard_reset();
}
