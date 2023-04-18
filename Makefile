CC = gcc
CFLAGS = -Wall -Wextra -std=c18

default: Timetrackingnc

Timetrackingnc: Timetrackingnc.o
	$(CC) $(CFLAGS) -o Timetrackingnc Timetrackingnc.o -lncurses -lmenu

Testaction: Testaction.o
	$(CC) $(CFLAGS) -o Testaction Testaction.o

Timetrackingnc.o: src/Timetrackingnc.c src/Fileio.h
	$(CC) $(CFLAGS) -c src/Timetrackingnc.c

Testaction.o: src/Testaction.c src/action.h
	$(CC) $(CFLAGS) -c src/Testaction.c

action.o: src/action.c src/action.h
	$(CC) $(CFLAGS) -c src/action.c

fileio.o: src/Fileio.c src/Fileio.h
	$(CC) $(CFLAGS) -c src/Fileio.c

clean:
	$(RM) Timetrackingnc Testaction *.o *~