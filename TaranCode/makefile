CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: s-talk

s-talk: main.o sender.o receiver.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c sender.h receiver.h
	$(CC) $(CFLAGS) -c $< -o $@

sender.o: sender.c sender.h
	$(CC) $(CFLAGS) -c $< -o $@

receiver.o: receiver.c receiver.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o s-talk
