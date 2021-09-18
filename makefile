CFLAGS = g++ -Wall -Wextra -pedantic -g -ldl
.PHONY: all gdb valgrind clean

all:
	$(CFLAGS) test.cpp Deque.hpp

gdb:
	gdb a.out

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all -v ./a.out

clean:
	rm a.out *.gch
