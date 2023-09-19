#include "../include/ppu.h"

#include "../include/cartridge.h"


void PPU::connect_with_cartridge(std::shared_ptr<Cartridge> cartridge)
{
    cartridge_ptr = cartridge;
}
