/*
 * File:        fileio.h
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Header file for fileio.c
 */
#ifndef TIME_TRACKING_SSP_FILEIO_H
#define TIME_TRACKING_SSP_FILEIO_H

#define NAME_LENGTH 30

struct User
{
    unsigned int ID;

    // Using type=0 for the main user, other types may be added if there's time
    // for subordinate and remote users
    int type;

    // status = last action
    int status;
    char firstName[NAME_LENGTH];
    char lastName[NAME_LENGTH];
};


// Writes binary data to "filename" in the following order:
// 1. Number of users (int numberOfUsers)
// 2. Number of actions in the array (int numberOfActions)
// 3. Array of User structs found at location pointed to by *users
// 4. Array of Action structs found at location pointed to by *actions
// The intention is to make this a static storage, loaded upon starting the program,
// and saved to periodically during runtime, as well as at termination
// return 0 for failure, 1 for success
int writeDB(int numberOfUsers, int numberOfActions, char *filename, struct User *users, struct Action *actions);

// Reads the number of users from the file, then reserves enough memory for
// the user table and reads it. Finally returns the pointer to the array of
// user structs
// Returns NULL upon failure
struct User *readUserTable(char *filename);

// Reads the number of actions from the file, then reserves enough memory for
// the action array and reads it. Finally returns the pointer to the array of
// action structs
// Returns NULL upon failure
struct Action *readActionTable(char *filename);


#endif //TIME_TRACKING_SSP_FILEIO_H
