#pragma once

#include <cstdint>
#include <map>

#include <SFML/Window/Keyboard.hpp>


class Controller {
public:
    enum Button {
        A,
        B,
        Select,
        Start,
        Up,
        Down,
        Left,
        Right,
    };

    bool strobe;
    uint8_t buttons_state {0x00};


    void handle_state_write(uint8_t data);
    uint8_t handle_state_read();
};

namespace ControllerKeys
{
    using SFMLKey = sf::Keyboard::Key;
    using Button = Controller::Button;

    static const std::map<Button, SFMLKey> key_binds {
        {Button::A, SFMLKey::L},
        {Button::B, SFMLKey::K},
        {Button::Select, SFMLKey::H},
        {Button::Start, SFMLKey::J},
        {Button::Up, SFMLKey::W},
        {Button::Down, SFMLKey::S},
        {Button::Left, SFMLKey::A},
        {Button::Right, SFMLKey::D},
    };

    static const std::map<Button, uint8_t> buttons_bits {
        {Button::A, 0b1000'0000},
        {Button::B, 0b0100'0000},
        {Button::Select, 0b0010'0000},
        {Button::Start, 0b0001'0000},
        {Button::Up, 0b0000'1000},
        {Button::Down, 0b0000'0100},
        {Button::Left, 0b0000'0010},
        {Button::Right, 0b0000'0001},
    };
}
