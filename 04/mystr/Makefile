CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -g
OBJS    = main.o mystr.o

mystr: $(OBJS)
	$(CC) $(OBJS) -o mystr

main.o: main.c mystr.h
	$(CC) $(CFLAGS) -c main.c

mystr.o: mystr.c mystr.h
	$(CC) $(CFLAGS) -c stats.c

clean:
	rm -f $(OBJS) mystr

.PHONY: clean
