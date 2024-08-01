#include "../../include/system/controller.h"

namespace
{
    constexpr std::uint8_t first_bit_mask {0b0000'0001u};
    constexpr std::uint8_t msb_mask {0b1000'0000u};
    constexpr std::uint8_t buttons_count {8u}
}

/////////
// API //
/////////

bool Controller::handle_state_write(std::uint8_t data)
{
    // Exit app
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        return false;

    strobe = data & first_bit_mask;

    if (!strobe) {
        for (auto i {0}; i < buttons_count; i++) {
            const auto current_button {static_cast<Button>(i)};
            const auto current_button_state {
                sf::Keyboard::isKeyPressed(
                    ControllerKeys::key_binds.at(current_button))};

            if (current_button_state)
                buttons_state |= ControllerKeys::buttons_bits.at(current_button);
        }
    }

    return true;
}

std::uint8_t Controller::handle_state_read()
{
    const bool read_state = (buttons_state & msb_mask) >> 7;

    if (!strobe)
        buttons_state <<= 1;

    return read_state;
}
