#pragma once

#include "./mapper_nrom.h"

#include <string>


namespace CartridgeConsts
{
    constexpr size_t header_size {16};
}

using CartridgeContents = std::vector<uint8_t>;

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

    MirroringType mirroring_mode {Cartridge::MirroringType::horizontal};
    int current_mapper_id {0};


    bool load_cartridge(const std::string& cartridge_path);
    bool dump_cartridge_into_vector(const std::string& cartridge_path);
    bool decode_header();

private:
    bool    check_for_nes_logo_in_header() const;
    bool    check_for_mirroring_mode() const;
    bool    check_for_prg_ram_presence() const;
    bool    check_for_trainer_presence() const;
    bool    check_for_ignoring_mirroring() const;
    uint8_t calculate_mapper_id() const;
};
