CC = gcc
CFLAGS = -Wall -Wextra

all: Even Odd

Even: even.c
	$(CC) $(CFLAGS) -o Even even.c

Odd: odd.c
	$(CC) $(CFLAGS) -o Odd odd.c

clean:
	rm -f Even Odd /tmp/turn.txt

run: all
	./Odd &
	./Even &

.PHONY: all clean run
