CC = gcc
CFLAGS = -Wall -Wextra -std=c18

default: TimeTrackingMenu

TimeTrackingMenu: TimeTrackingMenu.o
	$(CC) $(CFLAGS) -o TimeTrackingMenu TimeTrackingMenu.o -lncurses -lmenu

Testaction: Testaction.o
	$(CC) $(CFLAGS) -o Testaction Testaction.o

TestFileio: TestFileio.o
	$(CC) $(CFLAGS) -o TestFileio TestFileio.o

TimeTrackingMenu.o: src/TimeTrackingMenu.c src/Fileio.h src/action.h
	$(CC) $(CFLAGS) -c src/TimeTrackingMenu.c

Testaction.o: src/Testaction.c src/action.h
	$(CC) $(CFLAGS) -c src/Testaction.c

TestFileio.o: src/TestFileio.c src/Fileio.h src/action.h
	$(CC) $(CFLAGS) -c src/TestFileio.c

action.o: src/action.c src/action.h
	$(CC) $(CFLAGS) -c src/action.c

Fileio.o: src/Fileio.c src/Fileio.h
	$(CC) $(CFLAGS) -c src/Fileio.c

clean:

	$(RM) Timetrackingnc Testaction TestFileio *.o *~

	$(RM) Timetrackingnc Testaction TestFileio data.txt *.o *~

