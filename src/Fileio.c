/*
 * File:        fileio.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Disk operations for Time Tracking project
 */

#include "Fileio.h"
#include "action.h"
#include "action.c"


// add user information and actions to database, to 'data.txt' file
int writeDB(int numberOfUsers, int numberOfActions, char *userdataFilename, , char *actionFilename struct User *users,
        struct Action *actions) {
    FILE *fileptr;
    fileptr = fopen(userdataFilename, "w");
    if (fileptr != NULL)
    {
        fwrite(&numberOfUsers, sizeof(int), 1, fileptr);     // First write the length of the array
        fwrite(numberOfUsers, sizeof(struct Student), numberOfUsers, fileptr);
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
        fwrite(numberOfActions, sizeof(struct Action), numberOfActions, fileptr);
        fclose(fileptr);
        return 1;
    }
    else
    {
        return 0;
    }

    /*

    FILE *filePointer = NULL;

    // open the file
    filePointer = fopen(filename, "a");

    // check was file opened correctly
    if (filePointer == NULL) {
        return 0;
    }

    // loop through all users to add them to file
    for (int index = 0; index < numberOfUsers; index++) {
        fprintf(filePointer, "ID: %d, Type: %d, Status: %d, First name: %s Last name: %s\n",
                (users + index)->ID,
                (users + index)->type,
                (users + index)->status,
                (users + index)->firstName,
                (users + index)->lastName
        );

    }

    // loop through all actions to add them to file
    for (int index = 0; index < numberOfActions; index++) {
        fprintf(filePointer,
                "usedID: %d, actionType: %d, Day: %d, Hour: %d, Minutes: %d, Month: %d, Second: %d, Year: %d,\n",
                (actions + index)->usedID,
                (actions + index)->actionType,
                (actions + index)->day,
                (actions + index)->hour,
                (actions + index)->minute,
                (actions + index)->month,
                (actions + index)->second,
                (actions + index)->year
        );

    }

    // close connection to file after information has been saved into it
    fclose(filePointer);

    return 1;
    */
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
    if (fileptr == NULL)
    {
        return NULL;
    }
    else
    {
        fseek(fileptr, 0, SEEK_SET);
        fread(&numberOfActions, sizeof(int), 1, fileptr);      // Read the integer that tells the length of the array
        actionArray = (struct Action *) malloc(numberOfActions * sizeof(struct Action));
        if (actionArray == NULL)
        {
            return NULL;
        }
        else
        {
            fread(actionArray, sizeof(struct Action), numberOfActions, fileptr);     // Read the struct array
        }
        fclose(fileptr);
    }
    return actionArray;

    /*
    struct User *memoryPointer = NULL;

    memoryPointer = (struct User *) malloc(numberOfUsers * sizeof(struct User));

    // check successfulity of memory allocation
    if (memoryPointer == NULL) {
        return NULL;
    }

    FILE *readFilePointer = NULL;

    readFilePointer = fopen(filename, "r");

    // check was file opened correctly
    if (readFilePointer == NULL) {
        return NULL;
    }

    char line[MAXLINELENGTH];
    int lineNumber = 0;

    // read from file until we hit empty line
    while (fgets(line, MAXLINELENGTH, readFilePointer) != NULL) {
        lineNumber++;

        // check if we are reading the first three lines of the file
        if (lineNumber >= 1 && lineNumber <= 3) {
            // assign the user information to the corresponding fields in the User struct
            sscanf(line, "ID: %u, Type: %d, Status: %d, First name: %s Last name: %s",
                   &memoryPointer[lineNumber - 1].ID,
                   &memoryPointer[lineNumber - 1].type,
                   &memoryPointer[lineNumber - 1].status,
                   memoryPointer[lineNumber - 1].firstName,
                   memoryPointer[lineNumber - 1].lastName
            );
        }
    }
    fclose(readFilePointer);
    return memoryPointer;
*/
}

// MODIFY READ USER TABLE TO WORK WITH WHILE FGETS SO IT READ THE WHOLE FILE ALWAYS !!!!!!!!!!!!!!!


/*
struct Action *readActionTable(int numberOfUsers, int numberOfActions, char *filename) {
    struct Action *memoryPointer = NULL;

    memoryPointer = (struct Action *) malloc(numberOfActions * sizeof(struct Action));


    // check successfulity of memory allocation
    if (memoryPointer == NULL) {
        return NULL;
    }


    FILE *readFilePointer = NULL;

    readFilePointer = fopen(filename, "r");

    // check was file opened correctly
    if (readFilePointer == NULL) {
        return NULL;
    }

    char line[MAXLINELENGTH];
    int lineNumber = 0;

    // read from file until we hit empty line
    while (fgets(line, MAXLINELENGTH, readFilePointer) != NULL) {
        lineNumber++;

        // check are we pass user information so we start reading action information
        if (lineNumber >= numberOfUsers && lineNumber <= (numberOfUsers + numberOfActions)) {

            // assign the action information to the corresponding fields in the Action struct
            // index determins that action information is added to correct struct Action instance in allocated memory
            sscanf(line,
                   "usedID: %d, actionType: %d, Day: %d, Hour: %d, Minutes: %d, Month: %d, Second: %d, Year: %d,",
                   &memoryPointer[lineNumber - INDEXCORRECTOR].usedID,
                   &memoryPointer[lineNumber - INDEXCORRECTOR].actionType,
                   &memoryPointer[lineNumber - INDEXCORRECTOR].day,
                   &memoryPointer[lineNumber - INDEXCORRECTOR].hour,
                   &memoryPointer[lineNumber - INDEXCORRECTOR].minute,
                   &memoryPointer[lineNumber - INDEXCORRECTOR].month,
                   &memoryPointer[lineNumber - INDEXCORRECTOR].second,
                   &memoryPointer[lineNumber - INDEXCORRECTOR].year
            );
        }
    }
    fclose(readFilePointer);
    return memoryPointer;

}
 */

