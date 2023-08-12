CPPFLAGS = -Wall -Wextra -Wconversion -pedantic -std=c++20 -ggdb3

.PHONY = all clean

SRC      := ../src
SRCS     := $(wildcard $(SRC)/*.cpp)
CPUTESTS := $(wildcard ./cpu_tests/*.cpp)

all:
	$(CXX) $(CPPFLAGS) -o run_tests test_main.cpp $(SRCS) $(CPUTESTS)

clean:
	rm -f run_tests
