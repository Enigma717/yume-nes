#include "../include/bus.h"


SystemBus::SystemBus()
{
    ram = std::make_shared<Memory>();
    cpu.connect_with_memory(ram);
    cpu.hard_reset();
}
