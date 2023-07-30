#include "../include/bus.h"


SystemBus::SystemBus()
{
    cpu.connect_with_ram(ram);
}