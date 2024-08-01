#pragma once

#include <cstdint>
#include <map>

#include <SFML/Window/Keyboard.hpp>

class Controller {
public:
    enum class Button {
        A,
        B,
        Select,
        Start,
        Up,
        Down,
        Left,
        Right,
    };

    bool    handle_state_write(std::uint8_t data);
    std::uint8_t handle_state_read();

private:
    bool strobe {false};
    std::uint8_t buttons_state {0x00u};
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

    static const std::map<Button, std::uint8_t> buttons_bits {
        {Button::A, 0b1000'0000u},
        {Button::B, 0b0100'0000u},
        {Button::Select, 0b0010'0000u},
        {Button::Start, 0b0001'0000u},
        {Button::Up, 0b0000'1000u},
        {Button::Down, 0b0000'0100u},
        {Button::Left, 0b0000'0010u},
        {Button::Right, 0b0000'0001u},
    };
}
