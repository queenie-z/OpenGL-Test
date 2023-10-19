# This Makefile is designed to compile and link the OpenGL-based 'spin-sq' program.

# Compiler to be used is g++
CC=g++
# Flags for the compiler: specify include directory, C++ version, and enable debugging.
CFLAGS=-Iinclude -std=c++11 -g
# Libraries needed for linking the OpenGL-based program.
LIBS=-lglut -lGLEW -lGL -lGLU

# Default target executed when no arguments are given to make.
default_target: spin-sq objTest
.PHONY: default_target

# Target for linking the spin-sq.o and InitShader.o files.
spin-sq: spin-sq.o InitShader.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Target for compiling the spin-sq.cpp file.
spin-sq.o: spin-sq.cpp
	$(CC) $(CFLAGS) -c $^

# Target for compiling the InitShader.cpp file.
InitShader.o: Common/InitShader.cpp
	$(CC) $(CFLAGS) -c $^

# Target for linking the spin-sq.o and InitShader.o files.
objTest: objTest.o InitShader.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Target for compiling the spin-sq.cpp file.
objTest.o: objTest.cpp
	$(CC) $(CFLAGS) -c $^

# Target for cleaning files generated during editing and compilation.
clean:
	rm -f spin-sq objTest *~ *.o
