#include "../include/cartridge.h"

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

bool Cartridge::check_nes_logo_in_header()
{
    CartridgeContents nes_logo_in_header {header.begin(), header.begin() + CartridgeConsts::nes_logo.size()};

    return nes_logo_in_header == CartridgeConsts::nes_logo;
}

bool Cartridge::decode_header()
{
    if (check_nes_logo_in_header() == false) {
        std::cout << "Nes logo in cartridge is not correct\n";
        return false;
    }

    return true;
}
