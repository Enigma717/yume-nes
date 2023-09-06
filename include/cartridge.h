#ifndef CARTRIDGE_H
#define CARTRIDGE_H


#include <cstdint>
#include <string>
#include <vector>

using CartridgeContents = std::vector<uint8_t>;

namespace CartridgeConsts
{
    constexpr size_t header_size  {16};
    constexpr size_t prg_rom_size {16384};
    constexpr size_t chr_rom_size {8192};

    const CartridgeContents nes_logo {0x4E, 0x45, 0x53, 0x1A};
}


class Cartridge {
public:
    CartridgeContents cartridge_dump {};
    CartridgeContents header {CartridgeContents(CartridgeConsts::header_size, 0x00)};

    int    prg_rom_banks_count {0};
    int    chr_rom_banks_count {0};
    int    current_mapper      {0};
    bool   trainer_presence    {false};


    void dump_cartridge_into_vector(const std::string &cartridge_path);
    void load_header();

    bool check_nes_logo_in_header();
    bool decode_header();
};


#endif
