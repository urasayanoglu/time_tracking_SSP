/*
 * File:        fileio.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Disk operations for Time Tracking project
 */

#include "Fileio.h"
#include "action.h"

// To do read or write operations sequentially, open the file
// and catch the pointer in a variable (fileptr = fopen(stuffhere))
// Now you can just do consecutive write/read operations, here:
// 1. fwrite(stuff to write int, fileptr)
// 2. fwrite(stuff to write int, fileptr)
// 3. fwrite(stuff to write a struct, fileptr)
// 4. fwrite(stuff to write a struct, fileptr)
// .. and the pointer at fileptr updates automatically between
// writes. this is called a stream operation
// (at least I think&hope it happens this way)
int writeDB(int numberOfUsers, int numberOfActions, char *filename, struct User *users, struct Action *actions)
{

}

// for reading, the implementer needs to loo look up hoq fseek works and use it
// to set the pointer to the correct place after reading the ints at
// the beginning of the file
struct User *readUserTable(char *filename)
{
    return NULL;
}

struct Action *readActionTable(char *filename)
{
    return NULL;
}