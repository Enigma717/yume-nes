CPPFLAGS = -Wall -pedantic -std=c++17 -ggdb3

.PHONY = all clean

SRC   := ../src
SRCS  := $(wildcard $(SRC)/*.cpp)
TESTS := $(wildcard ./*.cpp)

all:
	$(CXX) $(FLAGS) -o tests $(SRCS) $(TESTS)

clean:
	rm -f tests