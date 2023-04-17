CC = gcc
CFLAGS = -Wall -Wextra -std=c18

default: Timetrackingnc

Timetrackingnc: Timetrackingnc.o
	$(CC) $(CFLAGS) -o Timetrackingnc Timetrackingnc.o -lncurses -lmenu

Testaction: Testaction.o
	$(CC) $(CFLAGS) -o Testaction Testaction.o

Testaction.o: src/Testaction.c src/Action.h
	$(CC) $(CFLAGS) -c src/Testaction.c

Timetrackingnc.o: Timetrackingnc.c src/Fileio.h
	$(CC) $(CFLAGS) -c Timetrackingnc.c

fileio.o: src/Fileio.c src/Fileio.h
	$(CC) $(CFLAGS) -c src/Fileio.c

clean:
	$(RM) Timetrackingnc *.o *~