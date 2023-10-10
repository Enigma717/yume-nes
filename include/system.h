#pragma once

#include "./cartridge.h"
#include "./cpu.h"
#include "./ppu.h"
#include "./memory.h"

#include <memory>


class System {
public:
    System();

    std::shared_ptr<Memory> ram;
    std::shared_ptr<Cartridge> cartridge;
    PPU ppu;
    CPU cpu;
};
