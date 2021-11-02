
CPP=g++

FLAGS=-g -O2

AUTOFLAGS=-std=c++11 -pthread -march=native

LDLIBS=-lntl -lgmp -lm

FILES= main.cpp encryption.cpp commitment.cpp helper.cpp linearityproof.cpp shortnessproof.cpp

run:
	clear
	$(CPP) $(FLAGS) $(AUTOFLAGS) $(FILES) -o main $(LDLIBS)
	./main
