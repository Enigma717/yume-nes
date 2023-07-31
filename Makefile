CPPFLAGS = -Wall -pedantic -std=c++17 -ggdb3

.PHONY = all clean

SRC  := ./src
SRCS := $(wildcard $(SRC)/*.cpp)

all:
	$(CXX) $(FLAGS) -o emu main.cpp $(SRCS)

clean:
	rm -f emu