#include <cstdint>
#include <iostream>
#include <bitset>

#include "./include/bus.h"


int main()
{
    uint8_t status = 0b10010001;
    uint8_t result = status & (1 << 7);
    std::bitset<8> x(result);

    std::cout << "Checkujemy flage: " << x << "\n";

    return 0;
}
