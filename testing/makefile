
test: list.o test.o
	g++ -Wall -Wextra -g -o test list.o test.o

list.o: list.c list.h
	g++ -Wall -Wextra -g -c list.

test.o: test.c  list.h
	g++ -Wall -Wextra -g -c test.c

clean:
	rm -f test list.o test.o