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
    constexpr auto square_size {8 * scale};
    constexpr auto pixel_size {1 * scale};
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

    for (auto i {0}; i < (screen_height / scale); i++) {
        for (auto j {0}; j < (screen_width / scale); j++) {
            if (color_index > 0x3F)
                color_index = 0x00;

            const auto x_coord = static_cast<float>(j * pixel_size);
            const auto y_coord = static_cast<float>(i * pixel_size);
            const auto current_color {PPUColors::available_colors[color_index]};

            sf::RectangleShape square(sf::Vector2f(pixel_size, pixel_size));
            square.setFillColor(current_color);
            square.setPosition(x_coord, y_coord);

            squares.push_back(square);

            color_index++;
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
                return 0;
            }
        }

        window.clear();

        for (auto i {0}; i < squares.size(); i++) {
            const auto& square {squares[i]};
            window.draw(square);

            // sf::Font font;
            // font.loadFromFile("/usr/share/fonts/TTF/iosevka-medium.ttc");
            // auto text = sf::Text{std::to_string(i), font, 10};
            // text.setPosition((square.getPosition().x + square.getSize().x / 2) - (text.getLocalBounds().width / 2),
            // (square.getPosition().y + square.getSize().y / 2) - (text.getLocalBounds().height / 2));

            // window.draw(text);
        }

        window.display();
    }


    return 0;
}
