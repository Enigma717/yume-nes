#ifndef CARTRIDGE_H
#define CARTRIDGE_H


#include "./mapper_nrom.h"

#include <string>


namespace CartridgeConsts
{
    constexpr size_t header_size {16};

    constexpr uint8_t mapper_mask           {0b1111'0000};
    constexpr uint8_t mirroring_mask        {0b0000'0001};
    constexpr uint8_t trainer_mask          {0b0000'0100};
    constexpr uint8_t ignore_mirroring_mask {0b0000'1000};

    const CartridgeContents nes_logo {0x4E, 0x45, 0x53, 0x1A};
}


class Cartridge {
public:
    enum class MirroringType {
        horizontal,
        vertical,
        single_screen,
        four_screen
    };

    MapperNROM mapper {};

    CartridgeContents cartridge_dump {};
    CartridgeContents header {CartridgeContents(CartridgeConsts::header_size, 0x00)};

    int current_mapper_id {0};
    MirroringType mirroring_mode {Cartridge::MirroringType::horizontal};


    void load_cartridge(const std::string &cartridge_path);
    void dump_cartridge_into_vector(const std::string &cartridge_path);
    void decode_header();

private:
    uint8_t calculate_mapper_id(uint8_t first_flag, uint8_t second_flag) const;

    bool check_for_nes_logo_in_header() const;
    bool check_for_mirroring_mode(uint8_t flag) const;
    bool check_for_ignoring_mirroring(uint8_t flag) const;
    bool check_for_trainer_presence(uint8_t flag) const;
};


#endif
