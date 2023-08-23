CPPFLAGS = -Wall -Wextra -Wconversion -pedantic -std=c++20 -ggdb3

.PHONY = all clean

SRCDIR := ../src
SRCS   := $(wildcard $(SRCDIR)/*.cpp)

CPUTESTDIR := ./cpu_tests
CPUTESTS   := $(wildcard $(CPUTESTDIR)/*.cpp)

all:
	$(CXX) $(CPPFLAGS) -o run_tests test_main.cpp $(SRCS) $(CPUTESTS)

clean:
	rm -f run_tests
