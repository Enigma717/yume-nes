CPPFLAGS = -Wall -pedantic -std=c++20 -ggdb3

.PHONY = all clean

SRC   := ../src
SRCS  := $(wildcard $(SRC)/*.cpp)
TESTS := $(wildcard ./*.cpp)

all:
	$(CXX) $(FLAGS) -o run_tests $(SRCS) $(TESTS)

clean:
	rm -f tests