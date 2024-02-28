
CC = gcc
CFLAGS = -Wall -Wextra -pthread 

s-talk: s-talk.o list.o sendto.o 
	$(CC) $(CFLAGS) $^ -o $@

s-talk.o: s-talk.c list.h sendto.h
	$(CC) $(CFLAGS) -c $< -o $@

sendto.o: sendto.c sendto.h list.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f sendto.o testing.o  p-talk s-talk testSend.o s-talk.o