CC = gcc
CFLAGS = -Wall -Wextra -std=c18

default: Hello

Hello: Hello.o
	$(CC) $(CFLAGS) -o Hello Hello.o -lncurses

Hello.o: Hello.c
	$(CC) $(CFLAGS) -c Hello.c

clean:
	$(RM) Hello *.o *~