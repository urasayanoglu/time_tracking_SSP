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

struct Action
{
    unsigned int usedID;

    // 0 = Start working, 1 = Stop working
    // With room to add multiple types of breaks
    int actionType;

    // Dates follow meatspace conventions, here clarified where not immediately apparent
    int year;
    int month;
    int day;

    // Hours since midnight (0-23)
    int hour;

    // Minutes past the hour (0-59)
    int minute;

    // Seconds past the minute (0-59)
    int second;
};

// Writes binary data to "filename" in the following order:
// 1. Number of users (int numberOfUsers)
// 2. Number of actions in the array (int numberOfActions)
// 3. Array of User structs found at location pointed to by *users
// 4. Array of Action structs found at location pointed to by *actions
// The intention is to make this a static storage, loaded upon starting the program,
// and saved to periodically during runtime, as well as at termination
void writeDB(int numberOfUsers, int numberOfActions, char *filename, struct *users, struct *actions);



#endif //TIME_TRACKING_SSP_FILEIO_H
