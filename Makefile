CXX=g++
CXXWARNINGS=-Wall -Wextra -Werror -Wpedantic -Wshadow -Wsign-conversion -Wconversion 
CXXFLAGS=-g -std=c++20 ${CXXWARNINGS}

.PHONY: clean all Makefile

all: build/syntrix

build:
	mkdir -p build/

build/syntrix: src/syntrix.cc src/symbol.o src/symbol.h | build
	${CXX} ${CXXFLAGS} $^ -o $@

clean:
	rm -rf build/
