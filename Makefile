# make         -> build the simulator (./rfsim) and the tests
# make run     -> build and run the simulator
# make test    -> build and run the tests
# make clean   -> delete built programs
CXX      ?= g++
CXXFLAGS  = -std=c++17 -O2 -Wall -Wextra -Iinclude

LIB_SRC  = $(wildcard src/*/*.cpp)
HEADERS  = $(wildcard include/*/*.hpp) $(wildcard tests/*.hpp)

all: rfsim test_coloring

rfsim: $(LIB_SRC) app/main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@

test_coloring: $(LIB_SRC) tests/test_coloring.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -Itests $(filter %.cpp,$^) -o $@

run: rfsim
	./rfsim

test: test_coloring
	./test_coloring

clean:
	rm -f rfsim test_coloring

.PHONY: all run test clean
