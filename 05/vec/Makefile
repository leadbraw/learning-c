CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -g
OBJS    = main.o vec.o

vectest: $(OBJS)
	$(CC) $(OBJS) -o vectest

main.o: main.c vec.h
	$(CC) $(CFLAGS) -c main.c

vec.o: vec.c vec.h
	$(CC) $(CFLAGS) -c vec.c

clean:
	rm -f $(OBJS) vectest

.PHONY: clean
