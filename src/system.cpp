#include "../include/system.h"

#include "../include/cartridge.h"
#include "../include/memory.h"

#include <chrono>
#include <iostream>


namespace
{
    constexpr size_t final_screen_width {1024};
    constexpr size_t final_screen_height {960};
    constexpr size_t center_screen_in_x_axis {448};
    constexpr size_t center_screen_in_y_axis {60};
    constexpr size_t framerate_cap {60};
    constexpr size_t cycles_needed_to_render_frame {89342};
    constexpr size_t ppu_cycles_needed_for_cpu_tick {3};

    constexpr uint16_t palette_bg_color_address {0x3F00};
}


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

void System::run()
{
    ppu.app_screen.setSize({final_screen_width, final_screen_height});
    ppu.app_screen.setPosition({center_screen_in_x_axis, center_screen_in_y_axis});
    ppu.app_screen.setFramerateLimit(framerate_cap);
    ppu.app_screen.setVerticalSyncEnabled(false);

    sf::Event event;
    sf::Clock clock;
    while (ppu.app_screen.isOpen()) {
        // while (ppu.app_screen.pollEvent(event)) {
        //     if (event.type == sf::Event::Closed
        //         || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
        //         ppu.app_screen.close();
        //         return;
        //     }
        //     if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        //         std::cout << "\n\n\nSPACE PRESSED\n\n\n";
        //     }
        // }

        perform_cycle(false);

        if (system_cycles_executed % cycles_needed_to_render_frame == 0) {
            const auto& bg_color = PPUColors::available_colors.at(ppu.memory_read(palette_bg_color_address));

            ppu.app_screen.clear(bg_color);

            for (const auto& pixel : ppu.pixels_to_render) {
                if (pixel.getFillColor() != bg_color)
                    ppu.app_screen.draw(pixel);
            }

            ppu.app_screen.display();
            std::cout << "FPS:" << 1.0 / clock.getElapsedTime().asSeconds() << "\n";
            clock.restart();
        }
    }
}

void System::perform_cycle(bool debug_mode)
{
    ppu.perform_cycle(false);

    if (system_cycles_executed % ppu_cycles_needed_for_cpu_tick == 0)
        cpu.perform_cycle(debug_mode);

    system_cycles_executed++;
}

void System::prepare_system_for_start()
{
    ppu.connect_with_cartridge(cartridge);

    cpu.connect_with_memory(ram);
    cpu.connect_with_cartridge(cartridge);
    cpu.hard_reset();
}
