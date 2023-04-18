/*
 * File:        action.h
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Functions for manipulating the Action struct arrays
 */


#ifndef TIME_TRACKING_SSP_ACTION_H
#define TIME_TRACKING_SSP_ACTION_H

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

// returns true if the time/date of x is earlier than y
int isEarlier(struct Action *x, struct Action *y);

// sorts an array of Action structs so that earlier occurrences have smaller index
void sortActions(struct Action *actions);

// Adds an Action struct to an array of such structs, using current time
// return NULL for failure.
struct Action *addAction(int userID, int actionType, struct Action *actions, int length);

#endif //TIME_TRACKING_SSP_ACTION_H
