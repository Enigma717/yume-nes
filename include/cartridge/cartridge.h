#pragma once

#include "./mapper_nrom.h"

#include <string>


namespace CartridgeConsts
{
    constexpr std::size_t header_size {16uz};
}


class Cartridge {
public:
    enum class MirroringType {
        horizontal,
        vertical,
        single_screen,
        four_screen
    };

    bool load_cartridge(const std::string& cartridge_path);

    MapperNROM mapper {};
    MirroringType mirroring_mode {Cartridge::MirroringType::horizontal};

private:
    bool dump_cartridge_into_vector(const std::string& cartridge_path);
    bool decode_header();

    bool check_for_nes_logo_in_header() const;
    bool check_for_mirroring_mode() const;
    bool check_for_prg_ram_presence() const;
    bool check_for_trainer_presence() const;
    bool check_for_ignoring_mirroring() const;
    std::uint8_t calculate_mapper_id() const;

    CartridgeContents cartridge_dump {};
    CartridgeContents header {CartridgeContents(CartridgeConsts::header_size, 0x00)};
    int current_mapper_id {-1};
};
