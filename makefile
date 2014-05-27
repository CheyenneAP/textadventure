LINK.o=$(LINK.cc)
CC=gcc
CXX=g++
CPPFLAGS=
CXXFLAGS=-g -Wall
LDLIBS=
SRCS=$(wildcard *.cc)

adventure: adventure.cc

clean:
	rm -f *.d *.o adventure
