#ifndef BUS_H
#define BUS_H


#include <memory>

#include "./cpu.h"
#include "./memory.h"


class SystemBus {
public:
    SystemBus();

    std::shared_ptr<Memory> ram;
    CPU cpu;
private:
};


#endif
