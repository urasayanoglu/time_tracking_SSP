CC = gcc
CFLAGS = -Wall -Wextra -std=c18

default: Timetrackingnc

Timetrackingnc: Timetrackingnc.o
	$(CC) $(CFLAGS) -o Timetrackingnc Timetrackingnc.o -lncurses -lmenu

Timetrackingnc.o: Timetrackingnc.c
	$(CC) $(CFLAGS) -c Timetrackingnc.c

clean:
	$(RM) Timetrackingnc *.o *~