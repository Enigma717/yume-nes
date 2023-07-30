#ifndef BUS_H
#define BUS_H


#include <memory>

#include "./cpu.h"
#include "./memory.h"


class SystemBus {
public:
    SystemBus();

    CPU cpu;
    Memory ram;
private:
};


#endif