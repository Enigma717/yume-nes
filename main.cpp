#include "./include/system.h"

int main()
{
    System nes;

    nes.boot_up("./test/cartridge_tests/roms/coredump.nes");
    nes.run_console();

    return 0;
}
