CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: s-talk

s-talk: hi.o list.o
	$(CC) $(CFLAGS) $^ -o $@

hi.o: hi.c list.h 
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f *.o s-talk