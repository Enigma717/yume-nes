#ifndef BUS_H
#define BUS_H


#include "./cpu.h"
#include "./memory.h"

#include <memory>


class SystemBus {
public:
    SystemBus();

    std::shared_ptr<Memory> ram;
    CPU cpu;
};


#endif
