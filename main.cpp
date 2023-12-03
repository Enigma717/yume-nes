#include "./include/system/system.h"

#include <iostream>


int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "\nMissing cartridge file!\n";
        std::cerr << "\nProper usage: ./yume <path_to_cartridge_file>\n\n";

        return 1;
    }

    std::string cartridge_path(argv[1]);

    System nes;

    if (!nes.boot_up(cartridge_path))
        return 1;

    nes.run_console();

    return 0;
}
