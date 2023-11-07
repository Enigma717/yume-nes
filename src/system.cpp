#include "../include/system.h"

#include "../include/cartridge.h"
#include "../include/memory.h"

#include <chrono>
#include <iostream>


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

    if (system_cycles_executed % 3 == 0)
        cpu.perform_cycle(debug_mode);

    system_cycles_executed++;
}

void System::run()
{
    ppu.app_screen.setSize({1024, 960});
    ppu.app_screen.setPosition({448, 60});

    auto begin = std::chrono::steady_clock::now();

    while (ppu.app_screen.isOpen()) {
        // sf::Event event;
        // while (ppu.app_screen.pollEvent(event)) {
        //     if (event.type == sf::Event::Closed
        //         || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
        //         ppu.app_screen.close();
        //         return;
        //     }
        // }

        perform_cycle(false);

        if (system_cycles_executed % PPUConsts::rendered_pixels_count == 0) {
            const auto& bg_color = PPUColors::available_colors[ppu.memory_read(0x3F00)];

            ppu.app_screen.clear(bg_color);

            for (const auto& pixel : ppu.pixels_to_render) {
                if (pixel.getFillColor() != bg_color)
                    ppu.app_screen.draw(pixel);
            }

            ppu.app_screen.display();

            auto end = std::chrono::steady_clock::now();
            std::cout << "ELAPSED: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000000000.0 << "s\n";
            begin = std::chrono::steady_clock::now();
        }
    }
}


void System::prepare_system_for_start()
{
    ppu.connect_with_cartridge(cartridge);
    ppu.prepare_sprites_tiles_memory();

    cpu.connect_with_memory(ram);
    cpu.connect_with_cartridge(cartridge);
    cpu.hard_reset();
}
