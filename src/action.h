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
int isEarlier(struct Action *previousStruct, struct Action *currentStruct);

// The intention here is to use the qsort function in stdlib.h to sort Action structs to order
void sortActions(struct Action *actions, int lengthOfArray);

// The intention here is compare current and previous Action structs attribute by attribute
// 1. return positive integer in case current is greater than previous 
// 2. return negative in case current is less than previous
// 3. return 0 in case current and previous are equal
int comparisonFunction(const void *previous, const void *current);

// Adds an Action struct to an array of such structs, using current time
// return NULL for failure.
struct Action *addAction(int userID, int actionType, struct Action *actions, int length);

// Returns the index of the next action from the same user. Returns -1 if no such actions exists
int findNext(int currentIndex, struct Action *actions, int length);

// Returns the time spent on the specified state on the specified date (0, 0, 0 for today)
// in seconds
int timeSpent(int state, unsigned int userID, int year, int month, int day, struct Action *actions);

// Returns true if the actions are dated to the same day
int sameDay(struct Action *x, struct Action *y);

// Finds the index of the next action from the same user that does
// NOT have the same status. Returns -1 if no such index exists
int findEndPoint(int index, unsigned int userID, int status, struct Action *actions, int numberOfActions);

#endif //TIME_TRACKING_SSP_ACTION_H
