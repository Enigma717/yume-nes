#pragma once

#include "./cpu.h"
#include "./ppu.h"
#include "./memory.h" // TO REMOVE

#include <memory>


class System {
public:
    System();

    std::shared_ptr<Memory> ram;
    std::shared_ptr<Cartridge> cartridge;
    PPU ppu;
    CPU cpu;


    void boot_up(const std::string& cartridge_path);
    void perform_cycle(bool debug_mode = false);
    void run();

private:
    int system_cycles_executed {0};

    void prepare_system_for_start();
};
