#include "../../include/cartridge/cartridge.h"

#include <iostream>
#include <iterator>
#include <filesystem>
#include <fstream>

namespace
{
    constexpr std::size_t trainer_size {512uz};

    constexpr std::uint8_t header_chr_rom_size_byte_flag {0x05u};
    constexpr std::uint8_t header_mapper_lsb_and_mirroring_byte_flag {0x06u};
    constexpr std::uint8_t header_mapper_msb_byte_flag {0x07u};
    constexpr std::uint8_t header_prg_ram_size_byte_flag {0x08u};
    constexpr std::uint8_t header_prg_rom_size_byte_flag {0x04u};

    constexpr std::uint8_t ignore_mirroring_mask {0b0000'1000u};
    constexpr std::uint8_t mapper_mask {0b1111'0000u};
    constexpr std::uint8_t mirroring_mask {0b0000'0001u};
    constexpr std::uint8_t prg_ram_mask {0b0000'0010u};
    constexpr std::uint8_t trainer_mask {0b0000'0100u};

    const CartridgeContents nes_logo {0x4Eu, 0x45u, 0x53u, 0x1Au};
}

/////////
// API //
/////////

bool Cartridge::load_cartridge(const std::string& cartridge_path)
{
    if (!dump_cartridge_into_vector(cartridge_path))
        return false;

    if (!decode_header())
        return false;

    const auto final_prg_ram_size {
        MapperConsts::prg_ram_bank_size * mapper.prg_ram_banks_count};
    const auto final_prg_rom_size {
        MapperConsts::prg_rom_bank_size * mapper.prg_rom_banks_count};
    const auto final_chr_rom_size {
        MapperConsts::chr_rom_bank_size * mapper.chr_rom_banks_count};

    mapper.prg_rom_memory.resize(final_prg_ram_size);
    mapper.prg_rom_memory.resize(final_prg_rom_size);
    mapper.chr_rom_memory.resize(final_chr_rom_size);

    const auto actual_trainer_size {mapper.trainer_presence ? trainer_size : 0};
    const auto default_offset {CartridgeConsts::header_size + actual_trainer_size};
    const auto roms_crossing_point {default_offset + final_prg_rom_size};

    std::copy(cartridge_dump.begin() + default_offset,
        cartridge_dump.begin() + roms_crossing_point,
        mapper.prg_rom_memory.begin());
    std::copy(cartridge_dump.begin() + roms_crossing_point,
        cartridge_dump.begin() + roms_crossing_point + final_chr_rom_size,
        mapper.chr_rom_memory.begin());

    return true;
}

///////////////////
// File decoding //
///////////////////

bool Cartridge::dump_cartridge_into_vector(const std::string& cartridge_path)
{
    if (!std::filesystem::exists(cartridge_path)) {
        std::cerr << "\nCartridge file not found in given path!\nSearched path: "
            << cartridge_path << "\n";

        return false;
    }

    std::ifstream game(cartridge_path, std::ios::in | std::ios::binary);
    game.unsetf(std::ios::skipws);

    game.seekg(0, std::ios::end);
    std::streampos cartridge_size = game.tellg();
    game.seekg(0, std::ios::beg);

    cartridge_dump.reserve(cartridge_size);
    cartridge_dump.insert(
        cartridge_dump.begin(),
        std::istream_iterator<std::uint8_t>(game),
        std::istream_iterator<std::uint8_t>());

    return true;
}

bool Cartridge::decode_header()
{
    std::copy(
        cartridge_dump.begin(),
        cartridge_dump.begin() + CartridgeConsts::header_size,
        header.begin());

    if (!check_for_nes_logo_in_header()) {
        std::cerr << "\nNes logo in header is not correct!\n\n";

        return false;
    }

    mapper.prg_rom_banks_count = header[header_prg_rom_size_byte_flag];
    mapper.chr_rom_banks_count = header[header_chr_rom_size_byte_flag];
    mapper.trainer_presence = check_for_trainer_presence();

    if (check_for_prg_ram_presence()) {
        mapper.prg_ram_presence = true;
        mapper.prg_ram_banks_count = header[header_prg_ram_size_byte_flag];
    }

    if (check_for_ignoring_mirroring())
        mirroring_mode = MirroringType::four_screen;
    else
        mirroring_mode = check_for_mirroring_mode() ?
            MirroringType::vertical : MirroringType::horizontal;

    current_mapper_id = calculate_mapper_id();

    return true;
}

////////////////////
// Helper methods //
////////////////////

bool Cartridge::check_for_nes_logo_in_header() const
{
    CartridgeContents nes_logo_in_header {
        header.begin(), header.begin() + nes_logo.size()};

    return nes_logo_in_header == nes_logo;
}

bool Cartridge::check_for_mirroring_mode() const
{
    return header[header_mapper_lsb_and_mirroring_byte_flag] & mirroring_mask;
}

bool Cartridge::check_for_prg_ram_presence() const
{
    return header[header_mapper_lsb_and_mirroring_byte_flag] & prg_ram_mask;
}

bool Cartridge::check_for_trainer_presence() const
{
    return header[header_mapper_lsb_and_mirroring_byte_flag] & trainer_mask;
}

bool Cartridge::check_for_ignoring_mirroring() const
{
    return header[header_mapper_lsb_and_mirroring_byte_flag] & ignore_mirroring_mask;
}

std::uint8_t Cartridge::calculate_mapper_id() const
{
    const auto mapper_lsb {
        static_cast<std::uint8_t>(
            (header[header_mapper_lsb_and_mirroring_byte_flag] & mapper_mask) >> 4)};
    const auto mapper_msb {
        static_cast<std::uint8_t>(
            (header[header_mapper_msb_byte_flag] & mapper_mask) >> 4)};

    return (mapper_msb << 4) | mapper_lsb;
}
