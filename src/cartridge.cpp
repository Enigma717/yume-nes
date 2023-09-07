#include "../include/cartridge.h"

#include <cstdint>
#include <iostream>
#include <iterator>
#include <filesystem>
#include <fstream>


void Cartridge::dump_cartridge_into_vector(const std::string &cartridge_path)
{
    if(std::filesystem::exists(cartridge_path)) {
        std::cout << "Loaded cartridge: " << cartridge_path << "\n";
    }
    else {
        std::cout << "Cartridge has not been loaded\n";
        return;
    }

    std::ifstream game(cartridge_path, std::ios::in | std::ios::binary);
    game.unsetf(std::ios::skipws);

    game.seekg(0, std::ios::end);
    std::streampos cartridge_size = game.tellg();
    game.seekg(0, std::ios::beg);

    std::cout << "Cartridge size: " << cartridge_size << " bytes\n";

    cartridge_dump.reserve(cartridge_size);
    cartridge_dump.insert(cartridge_dump.begin(),
        std::istream_iterator<uint8_t>(game),
        std::istream_iterator<uint8_t>());
}

void Cartridge::load_header()
{
    std::copy(cartridge_dump.begin(), cartridge_dump.begin() + CartridgeConsts::header_size, header.begin());
}

void Cartridge::decode_header()
{
    if (check_for_nes_logo_in_header() == false) {
        std::cout << "Nes logo in cartridge is not correct\n";
        return;
    }

    mapper.prg_rom_banks_count = header[4];
    mapper.chr_rom_banks_count = header[5];

    uint8_t flags6 {header[6]};
    uint8_t flags7 {header[7]};

    current_mapper_id = calculate_mapper_id(flags6, flags7);
    mapper.trainer_presence = check_for_trainer_presence(flags6);

    if (check_for_ignoring_mirroring(flags6)) {
        mirroring_mode = MirroringType::four_screen;
    }
    else {
        mirroring_mode = check_for_mirroring_mode(flags6) ?
                         Cartridge::MirroringType::vertical :
                         Cartridge::MirroringType::horizontal;
    }
}


uint8_t Cartridge::calculate_mapper_id(uint8_t first_flag, uint8_t second_flag) const
{
    uint8_t mapper_lsb = (first_flag & CartridgeConsts::mapper_mask) >> 4;
    uint8_t mapper_msb = (second_flag & CartridgeConsts::mapper_mask) >> 4;

    return (mapper_msb << 4) | mapper_lsb;
}

bool Cartridge::check_for_nes_logo_in_header()
{
    CartridgeContents nes_logo_in_header {header.begin(), header.begin() + CartridgeConsts::nes_logo.size()};

    return nes_logo_in_header == CartridgeConsts::nes_logo;
}

bool Cartridge::check_for_mirroring_mode(uint8_t flag) const
{
    return flag & CartridgeConsts::mirroring_mask;
}

bool Cartridge::check_for_ignoring_mirroring(uint8_t flag) const
{
    return flag & CartridgeConsts::ignore_mirroring_mask;
}

bool Cartridge::check_for_trainer_presence(uint8_t flag) const
{
    return flag & CartridgeConsts::trainer_mask;
}
