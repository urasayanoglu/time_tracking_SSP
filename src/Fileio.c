/**

* @file fileio.c
* @brief Disk operations for Time Tracking project
* @author Uras Ayanoglu
* @author Jan-Krister Helenius
* @author Sebastian Sopola
*/

#include <stdio.h>
#include <string.h>
#include "Fileio.h"
#include "action.h"
#include "action.c"


// Save both databases to a file
/**

* @brief Saves both databases to a file.
* @param numberOfUsers Number of users to save
* @param numberOfActions Number of actions to save
* @param userdataFilename Name of file to save user data to
* @param actionFilename Name of file to save action data to
* @param users Pointer to the array of user structs
* @param actions Pointer to the array of action structs
* @return 1 on success, 0 on failure
*/
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


/**

* @brief Reads the number of users from the file, reserves enough memory for the user table and reads it.
* @param filename Name of file to read user table from
* @return Pointer to the array of user structs. Returns NULL upon failure.
*/
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
/**

* @brief Reads the number of actions from the file, reserves enough memory for the action table and reads it.
* @param filename Name of file to read action table from
* @return Pointer to the array of action structs. Returns NULL upon failure.
*/
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

/**

* @brief Reads user input from the console with a prompt and stores it in a string
* @param prompt Pointer to the prompt string to display on the console
* @param target Pointer to the string where the user input will be stored
*/
void stringInput(char *prompt, char *target)
{
    echo();  				// Enable echoing of typed characters
    curs_set(1);  			// Show cursor on the screen
    mvprintw(8, 32, prompt);  		// Position prompt (line to write input on) at row 12, column 32
    getnstr(target, NAMELENGTH);  	// Read input and store in target buffer
    noecho();  				// Disable echoing of typed characters
    curs_set(0);  			// Hide cursor
}





