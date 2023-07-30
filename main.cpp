#include <iostream>

#include "./include/bus.h"


int main()
{
    SystemBus *bus = new SystemBus();

    std::cout << "\nTest mikrofonu: " << bus->ram.mem_read(0x0024) << " | " << bus->cpu.ram_ptr->mem_read(0x0024) << "\n";
    std::cout << "Test mikrofonu debug: " << bus->ram.mem_read_debug(0x0024) << " | " << bus->cpu.ram_ptr->mem_read_debug(0x0024) << "\n";

    bus->ram.mem_write(0x0024, 0x69);
    std::cout << "\nTest mikrofonu: " << bus->ram.mem_read(0x0024) << " | " << bus->cpu.ram_ptr->mem_read(0x0024) << "\n";
    std::cout << "Test mikrofonu debug: " << bus->ram.mem_read_debug(0x0024) << " | " << bus->cpu.ram_ptr->mem_read_debug(0x0024) << "\n";

    bus->cpu.ram_ptr->mem_write(0x0024, 0x6A);
    std::cout << "\nTest mikrofonu: " << bus->ram.mem_read(0x0024) << " | " << bus->cpu.ram_ptr->mem_read(0x0024) << "\n";
    std::cout << "Test mikrofonu debug: " << bus->ram.mem_read_debug(0x0024) << " | " << bus->cpu.ram_ptr->mem_read_debug(0x0024) << "\n";

    std::cout << "BUS RAM ADDRESS: " << &bus->ram << "\n";
    std::cout << "CPU RAM ADDRESS: " << bus->cpu.ram_ptr << "\n";

    delete bus;

    return 0;
}