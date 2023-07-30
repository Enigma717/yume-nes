CPPFLAGS = -Wall -pedantic -std=c++17 -ggdb3

.PHONY = all clean

SRC_DIR = ./src

all:
	$(CXX) $(FLAGS) -o emu main.cpp $(SRC_DIR)/bus.cpp $(SRC_DIR)/cpu.cpp $(SRC_DIR)/memory.cpp

clean:
	rm -f emu