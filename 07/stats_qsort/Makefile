CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -g
OBJS    = main.o stats.o

statstool: $(OBJS)
	$(CC) $(OBJS) -lm -o statstool

main.o: main.c stats.h
	$(CC) $(CFLAGS) -c main.c

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c

clean:
	rm -f $(OBJS) statstool

.PHONY: clean
