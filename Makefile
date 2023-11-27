CPPFLAGS = -Wall -Wextra -Wconversion -pedantic -O3 -std=c++20 -ggdb3 -lsfml-graphics -lsfml-window -lsfml-system

.PHONY = all clean

SRC  := ./src
SRCS := $(wildcard $(SRC)/*.cpp)

all:
	$(CXX) $(CPPFLAGS) -o yume main.cpp $(SRCS)

clean:
	rm -f yume
