#pragma once

#include "../cpu/cpu.h"
#include "../ppu/ppu.h"

#include <memory>


class System {
public:
    System();

    std::shared_ptr<Cartridge> cartridge;
    PPU ppu;
    CPU cpu;


    bool boot_up(const std::string& cartridge_path);
    void run_console();

private:
    int system_cycles_executed {0};

    void prepare_system_for_start();
    void perform_master_clock_cycle(bool debug_mode = false);
};
