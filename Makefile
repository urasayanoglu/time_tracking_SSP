CC = gcc
CFLAGS = -Wall -Wextra -std=c18

default: Timetrackingnc

Timetrackingnc: Timetrackingnc.o
	$(CC) $(CFLAGS) -o Timetrackingnc Timetrackingnc.o -lncurses -lmenu

Testaction: Testaction.o
	$(CC) $(CFLAGS) -o Testaction Testaction.o

TestFileio: TestFileio.o
	$(CC) $(CFLAGS) -o TestFileio TestFileio.o

Timetrackingnc.o: src/Timetrackingnc.c src/Fileio.h
	$(CC) $(CFLAGS) -c src/Timetrackingnc.c

Testaction.o: src/Testaction.c src/action.h
	$(CC) $(CFLAGS) -c src/Testaction.c

TestFileio.o: src/TestFileio.c src/Fileio.h src/action.h
	$(CC) $(CFLAGS) -c src/TestFileio.c

action.o: src/action.c src/action.h
	$(CC) $(CFLAGS) -c src/action.c

Fileio.o: src/Fileio.c src/Fileio.h
	$(CC) $(CFLAGS) -c src/Fileio.c

clean:
	$(RM) Timetrackingnc Testaction TestFileio data.txt *.o *~