CC = gcc
CFLAGS = -Wall -Wextra -pthread

p-talk: testSend.o list.o sendto.o 
	$(CC) $(CFLAGS) $^ -o $@

s-talk: testing.o list.o sendto.o 
	$(CC) $(CFLAGS) $^ -o $@

s-pow: s-talk.o list.o sendto.o

s-talk.o: s-talk.c list.h sendto.h
	$(CC) $(CFLAGS) -c $< -o $@

testSend.o: testSend.c list.h sendto.h
	$(CC) $(CFLAGS) -c $< -o $@

testing.o: testing.c list.h sendto.h 
	$(CC) $(CFLAGS) -c $< -o $@

sendto.o: sendto.c sendto.h list.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f sendto.o testing.o  p-talk s-talk testSend.o
