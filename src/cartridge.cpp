#include "../include/cartridge.h"

#include <iostream>
#include <iterator>
#include <filesystem>
#include <fstream>


namespace
{
    constexpr size_t trainer_size {512};

    constexpr uint8_t header_chr_rom_size_byte_flag {0x05};
    constexpr uint8_t header_mapper_lsb_and_mirroring_byte_flag {0x06};
    constexpr uint8_t header_mapper_msb_byte_flag {0x07};
    constexpr uint8_t header_prg_ram_size_byte_flag {0x08};
    constexpr uint8_t header_prg_rom_size_byte_flag {0x04};

    constexpr uint8_t ignore_mirroring_mask {0b0000'1000};
    constexpr uint8_t mapper_mask {0b1111'0000};
    constexpr uint8_t mirroring_mask {0b0000'0001};
    constexpr uint8_t prg_ram_mask {0b0000'0010};
    constexpr uint8_t trainer_mask {0b0000'0100};

    const CartridgeContents nes_logo {0x4E, 0x45, 0x53, 0x1A};
}


void Cartridge::load_cartridge(const std::string& cartridge_path)
{
    dump_cartridge_into_vector(cartridge_path);
    decode_header();


    auto final_prg_ram_size {MapperConsts::prg_ram_bank_size * mapper.prg_ram_banks_count};
    auto final_prg_rom_size {MapperConsts::prg_rom_bank_size * mapper.prg_rom_banks_count};
    auto final_chr_rom_size {MapperConsts::chr_rom_bank_size * mapper.chr_rom_banks_count};

    mapper.prg_rom_memory.reserve(final_prg_ram_size);
    mapper.prg_rom_memory.reserve(final_prg_rom_size);
    mapper.chr_rom_memory.reserve(final_chr_rom_size);


    auto actual_trainer_size {mapper.trainer_presence ? trainer_size : 0};
    auto default_offset {CartridgeConsts::header_size + actual_trainer_size};
    auto roms_crossing_point {default_offset + final_prg_rom_size};

    std::copy(cartridge_dump.begin() + default_offset,
        cartridge_dump.begin() + roms_crossing_point,
        mapper.prg_rom_memory.begin());
    std::copy(cartridge_dump.begin() + roms_crossing_point,
        cartridge_dump.begin() + roms_crossing_point + final_chr_rom_size,
        mapper.chr_rom_memory.begin());
}

void Cartridge::dump_cartridge_into_vector(const std::string& cartridge_path)
{
    if(!(std::filesystem::exists(cartridge_path))) {
        std::cout << "Cartridge hasn't been loaded\nSearched path: " << cartridge_path << "\n";

        return;
    }

    std::ifstream game(cartridge_path, std::ios::in | std::ios::binary);
    game.unsetf(std::ios::skipws);

    game.seekg(0, std::ios::end);
    std::streampos cartridge_size = game.tellg();
    game.seekg(0, std::ios::beg);

    cartridge_dump.reserve(cartridge_size);
    cartridge_dump.insert(cartridge_dump.begin(),
        std::istream_iterator<uint8_t>(game),
        std::istream_iterator<uint8_t>());
}

void Cartridge::decode_header()
{
    std::copy(cartridge_dump.begin(),
        cartridge_dump.begin() + CartridgeConsts::header_size,
        header.begin());

    if (!check_for_nes_logo_in_header()) {
        std::cout << "Nes logo in header is not correct\n";

        return;
    }

    mapper.prg_rom_banks_count = header.at(header_prg_rom_size_byte_flag);
    mapper.chr_rom_banks_count = header.at(header_chr_rom_size_byte_flag);
    mapper.trainer_presence = check_for_trainer_presence();

    if (check_for_prg_ram_presence()) {
        mapper.prg_ram_presence = true;
        mapper.prg_ram_banks_count = header.at(header_prg_ram_size_byte_flag);
    }

    if (check_for_ignoring_mirroring())
        mirroring_mode = MirroringType::four_screen;
    else
        mirroring_mode = check_for_mirroring_mode() ? MirroringType::vertical : MirroringType::horizontal;

    current_mapper_id = calculate_mapper_id();
}

bool Cartridge::check_for_nes_logo_in_header() const
{
    CartridgeContents nes_logo_in_header {header.begin(), header.begin() + nes_logo.size()};

    return nes_logo_in_header == nes_logo;
}

bool Cartridge::check_for_mirroring_mode() const
{
    return header.at(header_mapper_lsb_and_mirroring_byte_flag) & mirroring_mask;
}

bool Cartridge::check_for_prg_ram_presence() const
{
    return header.at(header_mapper_lsb_and_mirroring_byte_flag) & prg_ram_mask;
}

bool Cartridge::check_for_trainer_presence() const
{
    return header.at(header_mapper_lsb_and_mirroring_byte_flag) & trainer_mask;
}

bool Cartridge::check_for_ignoring_mirroring() const
{
    return header.at(header_mapper_lsb_and_mirroring_byte_flag) & ignore_mirroring_mask;
}

uint8_t Cartridge::calculate_mapper_id() const
{
    const uint8_t mapper_lsb = (header.at(header_mapper_lsb_and_mirroring_byte_flag) & mapper_mask) >> 4;
    const uint8_t mapper_msb = (header.at(header_mapper_msb_byte_flag) & mapper_mask) >> 4;

    return (mapper_msb << 4) | mapper_lsb;
}
