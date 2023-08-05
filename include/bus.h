#ifndef BUS_H
#define BUS_H


#include <memory>

#include "./cpu.h"
#include "./memory.h"


class SystemBus {
public:
    SystemBus();

    CPU cpu;
    std::shared_ptr<Memory> ram;
private:
};


#endif