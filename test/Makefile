CPPFLAGS = -Wall -pedantic -std=c++20 -ggdb3

.PHONY = all clean

SRC      := ../src
SRCS     := $(wildcard $(SRC)/*.cpp)
CPUTESTS := $(wildcard ./cpu_tests/*.cpp)

all:
	$(CXX) $(FLAGS) -o run_tests test_main.cpp $(SRCS) $(CPUTESTS)

clean:
	rm -f tests
