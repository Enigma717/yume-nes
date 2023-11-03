#include "../include/system.h"

#include "../include/cartridge.h"
#include "../include/memory.h"


System::System() : cpu{ppu}
{
    ram = std::make_shared<Memory>();
    cartridge = std::make_shared<Cartridge>();
}

void System::boot_up(const std::string& cartridge_path)
{
    cartridge->load_cartridge(cartridge_path);
    prepare_system_for_start();
}

void System::perform_cycle(bool debug_mode)
{
    ppu.perform_cycle(false);
    ppu.perform_cycle(false);
    ppu.perform_cycle(false);

    cpu.perform_cycle(debug_mode);

    system_cycles_executed += 4;
}


void System::prepare_system_for_start()
{
    ppu.connect_with_cartridge(cartridge);
    ppu.prepare_sprites_tiles_memory();

    cpu.connect_with_memory(ram);
    cpu.connect_with_cartridge(cartridge);
    cpu.hard_reset();
}
