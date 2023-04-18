CC = gcc
CFLAGS = -Wall -Wextra -std=c18

default: Testaction

Timetrackingnc: Timetrackingnc.o
	$(CC) $(CFLAGS) -o Timetrackingnc Timetrackingnc.o -lncurses -lmenu

Testaction: Testaction.o
	$(CC) $(CFLAGS) -o Testaction Testaction.o

Timetrackingnc.o: Timetrackingnc.c Fileio.h
	$(CC) $(CFLAGS) -c Timetrackingnc.c

Testaction.o: Testaction.c action.h
	$(CC) $(CFLAGS) -c Testaction.c

action.o: action.c action.h
	$(CC) $(CFLAGS) -c action.c

fileio.o: Fileio.c Fileio.h
	$(CC) $(CFLAGS) -c Fileio.c

clean:
	$(RM) Timetrackingnc Testaction *.o *~