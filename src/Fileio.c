/*
 * File:        fileio.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Disk operations for Time Tracking project
 */

#include <stdio.h>
#include <string.h>
#include "Fileio.h"
#include "action.h"
#include "action.c"


// Save both databases to a file
int writeDB(int numberOfUsers, int numberOfActions, char *userdataFilename, char *actionFilename, struct User *users,
        struct Action *actions) {
    FILE *fileptr;
    fileptr = fopen(userdataFilename, "w");
    if (fileptr != NULL)
    {
        fwrite(&numberOfUsers, sizeof(int), 1, fileptr);     // First write the length of the array
        fwrite(users, sizeof(struct User), numberOfUsers, fileptr);
        fclose(fileptr);
    }
    else
    {
        return 0;
    }

    fileptr = fopen(actionFilename, "w");
    if (fileptr != NULL)
    {
        fwrite(&numberOfActions, sizeof(int), 1, fileptr);     // First write the length of the array
        fwrite(actions, sizeof(struct Action), numberOfActions, fileptr);
        fclose(fileptr);
        return 1;
    }
    else
    {
        return 0;
    }
}

// Reads the number of users from the file, then reserves enough memory for
// the user table and reads it. Finally returns the pointer to the array of
// user structs
// Returns NULL upon failure
struct User *readUserTable(char *filename) {
    FILE *fileptr;
    struct User *userArray = NULL;
    int numberOfUsers = 0;
    fileptr = fopen(filename, "r");     // Open in read mode
    if (fileptr == NULL)
    {
        return NULL;
    }
    else
    {
        fseek(fileptr, 0, SEEK_SET);
        fread(&numberOfUsers, sizeof(int), 1, fileptr);      // Read the integer that tells the length of the array
        userArray = (struct User *) malloc(numberOfUsers * sizeof(struct User));
        if (userArray == NULL)
        {
            return NULL;
        }
        else
        {
            fread(userArray, sizeof(struct User), numberOfUsers, fileptr);     // Read the struct array
        }
        fclose(fileptr);
        }
    return userArray;
}

struct Action *readActionTable(char *filename) {
    FILE *fileptr;
    struct Action *actionArray = NULL;
    int numberOfActions = 0;
    fileptr = fopen(filename, "r");     // Open in read mode
    if (fileptr == NULL) {
        return NULL;
    } else {
        fseek(fileptr, 0, SEEK_SET);
        fread(&numberOfActions, sizeof(int), 1, fileptr);      // Read the integer that tells the length of the array
        actionArray = (struct Action *) malloc(numberOfActions * sizeof(struct Action));
        if (actionArray == NULL) {
            return NULL;
        } else {
            fread(actionArray, sizeof(struct Action), numberOfActions, fileptr);     // Read the struct array
        }
        fclose(fileptr);
    }
    return actionArray;
}


void stringInput(char *prompt, char *target)
{
    echo();  				// Enable echoing of typed characters
    curs_set(1);  			// Show cursor on the screen
    mvprintw(8, 32, prompt);  		// Position prompt (line to write input on) at row 12, column 32
    getnstr(target, NAMELENGTH);  	// Read input and store in target buffer
    noecho();  				// Disable echoing of typed characters
    curs_set(0);  			// Hide cursor
}





