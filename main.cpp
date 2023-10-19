#include "./include/system.h"

#include <iostream>

#include <SFML/Graphics.hpp>


namespace
{
    using MN = Instruction::MnemonicName;
    using AM = Instruction::AddressingMode;

    constexpr Instruction rts_instruction {MN::RTS, AM::implied, 0x60, 1, 6};

    constexpr auto scale {1};
    constexpr auto screen_width {256 * scale};
    constexpr auto screen_height {240 * scale};
    constexpr auto square_size {16 * scale};
}


int main()
{
    // System nes;

    // nes.cartridge->load_cartridge("./test/cartridge_tests/roms/nestest.nes");
    // nes.cpu.pc = 0xC000;

    // do {
    //     nes.cpu.perform_cycle(true);
    // } while (!(nes.cpu.curr_instruction == rts_instruction && nes.cpu.arg_address == 0xC66E));

    // std::cout << "\nTest result: " << static_cast<int>(nes.ram->memory_read(0x0002)) << "\n";


    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Yume NES");
    std::vector<sf::RectangleShape> squares;

    auto color_index {0x00};

    for (auto i {0}; i < 16; i++)
    {
        for (auto j {0}; j < 16; j++)
        {
            if (color_index > 0x3F)
                color_index = 0x00;

            const auto x_coord = static_cast<float>(j * square_size);
            const auto y_coord = static_cast<float>(i * square_size);
            const auto current_color {PPUColors::available_colors[color_index]};

            sf::RectangleShape square(sf::Vector2f(square_size, square_size));
            square.setFillColor(current_color);
            square.setPosition(x_coord, y_coord);

            squares.push_back(square);

            color_index++;
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
                return 0;
            }
        }

        window.clear();

        for (const auto& square : squares) {
            window.draw(square);
        }

        window.display();
    }


    return 0;
}
