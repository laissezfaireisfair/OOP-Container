CC = g++
CFLAGS = -Wall -pedantic -std=c++11



build: build/test1.out build/test2.out build/test3.out build/test4.out build/test5.out build/test6.out

run: build
	echo "Running test 1...\n"
	./build/test1.out
	echo "\nTest 1 input end. Running test 2...\n"
	./build/test2.out
	echo "\nTest 2 input end. Running test 3...\n"
	./build/test3.out
	echo "\nTest 3 input end. Running test 4...\n"
	./build/test4.out
	echo "\nTest 4 input end. Running test 5...\n"
	./build/test5.out
	echo "\nTest 5 input end. Running test 6...\n"
	./build/test6.out
	echo "\nTest 6 input end.\n"

clean:
	rm -rf build/*

test1: build/test1.out
	./build/test1.out

test2: build/test2.out
	./build/test2.out

test3: build/test3.out
	./build/test3.out

test4: build/test4.out
	./build/test4.out

test5: build/test5.out
	./build/test5.out

test6: build/test6.out
	./build/test6.out

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

build/test6.out: test/test6*.cpp include/Container.hpp
	$(CC) $(CFLAGS) -g $< -o $@ -I include/
