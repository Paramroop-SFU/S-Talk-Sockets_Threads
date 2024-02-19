CC = gcc
CFLAGS = -Wall -Wextra -pthread

p-talk: testSend.o list.o sendto.o receive.o
	$(CC) $(CFLAGS) $^ -o $@

s-talk: testing.o list.o sendto.o receive.o
	$(CC) $(CFLAGS) $^ -o $@

testSend.o: testSend.c list.h sendto.h receive.h
	$(CC) $(CFLAGS) -c $< -o $@

testing.o: testing.c list.h sendto.h receive.h
	$(CC) $(CFLAGS) -c $< -o $@

sendto.o: sendto.c sendto.h list.h
	$(CC) $(CFLAGS) -c $< -o $@

receive.o: receive.c receive.h list.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f sendto.o testing.o receive.o p-talk s-talk testSend.o
