CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -g
OBJS    = main.o contacts.o

contactprog: $(OBJS)
	$(CC) $(OBJS) -o contactprog

main.o: main.c contacts.h
	$(CC) $(CFLAGS) -c main.c

contacts.o: contacts.c contacts.h
	$(CC) $(CFLAGS) -c contacts.c

clean:
	rm -f $(OBJS) contactprog

.PHONY: clean
