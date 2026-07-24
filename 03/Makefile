CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g
OBJS = main.o greet.o

greetings: $(OBJS)
	$(CC) $(OBJS) -o greetings

main.o: main.c greet.h
	$(CC) $(CFLAGS) -c main.c

greet.o: greet.c greet.h
	$(CC) $(CFLAGS) -c greet.c

clean:
	rm -f $(OBJS) greetings

.PHONY: clean
