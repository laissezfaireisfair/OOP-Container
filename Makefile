CC=g++
CFLAGS=-Wall -pedantic -std=c++11
INCLUDEDIR=include

build/test*.out: test/test*.cpp
	$(CC) $(CFLAGS) -g $< -o $@ -I $(INCLUDEDIR)
