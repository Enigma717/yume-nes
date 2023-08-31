#include "../include/cartridge.h"

#include <iostream>
#include <iterator>
#include <filesystem>
#include <fstream>


void Cartridge::dump_cartridge_into_vector(const std::string &cartridge_path)
{
    if(std::filesystem::exists(cartridge_path))
        std::cout << "LOADED FILE: " << cartridge_path << "\n";

    std::ifstream game(cartridge_path, std::ios::in | std::ios::binary);

    game.unsetf(std::ios::skipws);

    game.seekg(0, std::ios::end);
    std::streampos cartridge_size = game.tellg();
    game.seekg(0, std::ios::beg);

    std::cout << "SIZE: " << cartridge_size << "\n";

    cartridge_dump.reserve(cartridge_size);

    cartridge_dump.insert(cartridge_dump.begin(),
        std::istream_iterator<uint8_t>(game),
        std::istream_iterator<uint8_t>());
}


void Cartridge::load_header()
{
    std::copy(cartridge_dump.begin(), cartridge_dump.begin() + CartridgeConsts::header_size, header.begin());
}
