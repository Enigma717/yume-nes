CPPFLAGS = -Wall -Wextra -Wconversion -pedantic -std=c++20 -ggdb3

.PHONY = all clean

SRCDIR := ../src
SRCS   := $(wildcard $(SRCDIR)/*.cpp)

CPUTESTDIR   := ./cpu_tests
CPUTESTS     := $(wildcard $(CPUTESTDIR)/*.cpp)
OPCODESDIR   := $(CPUTESTDIR)/opcodes_tests
OPCODESTESTS := $(wildcard $(OPCODESDIR)/*.cpp)

CARTTESTDIR := ./cartridge_tests
CARTTESTS   := $(wildcard $(CARTTESTDIR)/*.cpp)

all:
	$(CXX) $(CPPFLAGS) -o run_tests test_main.cpp $(SRCS) $(CPUTESTS) $(OPCODESTESTS) $(CARTTESTS)

clean:
	rm -f run_tests
