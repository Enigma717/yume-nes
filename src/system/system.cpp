#include "../../include/system/system.h"

#include "../../include/system/controller.h"

#include <chrono>
#include <iostream>


namespace
{
    constexpr int ppu_cycles_needed_to_render_frame {89342};
    constexpr int ppu_cycles_needed_for_cpu_tick {3};
}


/////////
// API //
/////////

System::System() : cpu{ppu}
{
    cartridge = std::make_shared<Cartridge>();
    controller = std::make_shared<Controller>();
}

bool System::boot_up(const std::string& cartridge_path)
{
    if (!cartridge->load_cartridge(cartridge_path)) {
        std::cerr << "\nError occurred while trying to load cartridge.\n\n";

        return false;
    }

    prepare_system_for_start();
    cartridge_loaded = true;

    return true;
}

void System::run_console()
{
    if (!cartridge_loaded) {
        std::cerr << "\nPlease load a cartridge first.\n\n";

        return;
    }

    while (ppu.app_screen.isOpen()) {
        perform_master_clock_cycle(false);

        if (system_cycles_executed % ppu_cycles_needed_to_render_frame == 0) {
            ppu.render_whole_frame();
        }
    }
}


//////////////////////////
// System functionality //
//////////////////////////

void System::prepare_system_for_start()
{
    ppu.connect_bus_with_cartridge(cartridge);

    cpu.connect_bus_with_cartridge(cartridge);
    cpu.connect_bus_with_controller(controller);
    cpu.hard_reset();
}

void System::perform_master_clock_cycle(bool debug_mode)
{
    ppu.perform_cycle(false);

    if (system_cycles_executed % ppu_cycles_needed_for_cpu_tick == 0)
        cpu.perform_cycle(debug_mode);

    system_cycles_executed++;
}
