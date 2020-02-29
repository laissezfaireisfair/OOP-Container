CC = g++
CFLAGS = -Wall -pedantic -std=c++11


test: test1 test2 test3 test4 test5

clean:
	rm -rf build/*

test1: build/test1.out

test2: build/test2.out

test3: build/test3.out

test4: build/test4.out

test5: build/test5.out

build/test1.out: test/test1*.cpp include/Container.hpp
	$(CC) $(CFLAGS) -g $< -o $@ -I include/

build/test2.out: test/test2*.cpp include/Container.hpp
	$(CC) $(CFLAGS) -g $< -o $@ -I include/

build/test3.out: test/test3*.cpp include/Container.hpp
	$(CC) $(CFLAGS) -g $< -o $@ -I include/

build/test4.out: test/test4*.cpp include/Container.hpp
	$(CC) $(CFLAGS) -g $< -o $@ -I include/

build/test5.out: test/test5*.cpp include/Container.hpp
	$(CC) $(CFLAGS) -g $< -o $@ -I include/
