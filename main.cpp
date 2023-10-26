#include "./include/system.h"

#include <iostream>
#include <bitset>
#include <iomanip>

#include <SFML/Graphics.hpp>


namespace
{
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;

    constexpr Instruction rts_instruction {MN::RTS, AM::implied, 0x60, 1, 6};

    constexpr auto screen_width {256};
    constexpr auto screen_height {240};
    constexpr auto pattern_table_screen_size {128};
}


int main()
{
    System nes;

    nes.boot_up("./test/cartridge_tests/roms/nestest.nes");

    do {
        nes.cpu.perform_cycle(true);
    } while (!(nes.cpu.cycles_executed == 100000));

    // do {
    //     nes.cpu.perform_cycle(true);
    // } while (!(nes.cpu.curr_instruction == rts_instruction && nes.cpu.arg_address == 0xC66E));

    // std::cout << "\nTest result: " << static_cast<int>(nes.ram->memory_read(0x0002)) << "\n";

    // for (auto i {0}; i < (PPUConsts::nametables_size / 2); i++) {
    //     const auto& read_byte {nes.ppu.nametables[i]};

    //     if (i % 8 == 0)
    //         std::cout << std::dec << "\nTiles: " << i << "-" << i + 8 << ": " << std::hex;

    //     std::cout << std::setfill('0') << "0x" << std::setw(2) << std::right << (int) read_byte << "\t";
    // }


    // sf::RenderWindow window(sf::VideoMode(pattern_table_screen_size * 2, pattern_table_screen_size), "Yume NES");

    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed ||
    //             (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
    //             window.close();
    //             return 0;
    //         }
    //     }

    //     window.setSize({pattern_table_screen_size * 8, pattern_table_screen_size * 4});
    //     window.clear(PPUColors::available_colors[0x1D]);

    //     for (auto& tile : nes.ppu.sprites_tiles) {
    //         for (auto& pixel : tile.pixels) {
    //             const auto pixel_color_index {pixel.color_index};
    //             if (pixel_color_index != 0) {
    //                 sf::Color new_color;

    //                 switch (pixel_color_index) {
    //                     case 0b01: new_color = PPUColors::available_colors[0x12]; break;
    //                     case 0b10: new_color = PPUColors::available_colors[0x37]; break;
    //                     case 0b11: new_color = PPUColors::available_colors[0x07]; break;
    //                     default: break;
    //                 }

    //                 pixel.sfml_pixel.setFillColor(new_color);
    //                 window.draw(pixel.sfml_pixel);
    //             }
    //         }
    //     }

    //     window.display();
    // }


    return 0;
}
