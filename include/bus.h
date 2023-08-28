#ifndef BUS_H
#define BUS_H


#include "./cartridge.h"
#include "./cpu.h"
#include "./memory.h"

#include <memory>


class SystemBus {
public:
    SystemBus();

    std::shared_ptr<Memory> ram;
    std::shared_ptr<Cartridge> cartridge;
    CPU cpu;
};


#endif
