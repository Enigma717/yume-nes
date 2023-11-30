CPPFLAGS = -Wall -Wextra -pedantic -O3 -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system

.PHONY = all clean

CPUDIR  := ./src/cpu
CARTDIR := ./src/cartridge
PPUDIR  := ./src/ppu
SYSDIR  := ./src/system


CPUSRC  := $(wildcard $(CPUDIR)/*.cpp)
CARTSRC := $(wildcard $(CARTDIR)/*.cpp)
PPUSRC  := $(wildcard $(PPUDIR)/*.cpp)
SYSSRC  := $(wildcard $(SYSDIR)/*.cpp)

all:
	$(CXX) $(CPPFLAGS) -o yume main.cpp $(CPUSRC) $(CARTSRC) $(PPUSRC) $(SYSSRC)

clean:
	rm -f yume
