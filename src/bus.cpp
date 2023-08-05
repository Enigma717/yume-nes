#include "../include/bus.h"


SystemBus::SystemBus()
{
    ram = std::make_shared<Memory>();
    cpu.connect_with_ram(ram);
}
