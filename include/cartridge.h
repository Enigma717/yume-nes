#ifndef CARTRIDGE_H
#define CARTRIDGE_H


#include <cstdint>
#include <string>
#include <vector>


namespace CartridgeConsts
{
    constexpr size_t header_size {16};
}

using CartridgeContents = std::vector<uint8_t>;


class Cartridge {
public:
    void dump_cartridge_into_vector(const std::string &cartridge_path);
    void load_header();

    CartridgeContents cartridge_dump {};
    CartridgeContents header {CartridgeContents(CartridgeConsts::header_size, 0x00)};
};


#endif
