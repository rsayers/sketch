CXX=g++
LDFLAGS=-lsdl2 -I/opt/homebrew/include
LDLIBS=-L/opt/homebrew/lib

all: example

example:
	$(CXX) $(LDFLAGS) -o example example.cpp $(LDLIBS)