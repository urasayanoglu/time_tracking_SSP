/*
 * File:        action.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Functions for manipulating the Action struct arrays
 */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "action.h"

int isEarlier(struct Action *x, struct Action *y)
{
    if (x->year < y->year)
    {
        return 1;
    }
    else if (x->year > y->year)
    {
        return 0;
    }
    else if (x->month < y->month)
    {
        return 1;
    }
    else if (x->month > y->month)
    {
        return 0;
    }
    else if (x->day < y->day)
    {
        return 1;
    }
    else if (x->day > y->day)
    {
        return 0;
    }
    else if (x->hour < y->hour)
    {
        return 1;
    }
    else if (x->hour > y->hour)
    {
        return 0;
    }
    else if (x->minute < y->minute)
    {
        return 1;
    }
    else if (x->minute > y->minute)
    {
        return 0;
    }
    else if (x->second < y->second)
    {
        return 1;
    }
    else if (x->second > y->second)
    {
        return 0;
    }
    else {
        return 0;
    }
}

// The intention here is to use the qsort function in stdlib.h (try Google or ChatGPT...)
// Qsort requires a comparison function, which you need to implement too. (isEarlier might be handy)
void sortActions(struct Action *actions)
{

}

struct Action *addAction(int userID, int actionType, struct Action *actions, int length)
{
    // Get current time
    time_t currentTime = time(NULL);

    // Convert time to local time
    struct tm* local_time = localtime(&currentTime);

    struct Action *newActions = NULL;
    newActions = (struct Action *) malloc((length + 1) * sizeof(struct Action));
    for (int i = 0; i < length; i++)
    {
        newActions[i] = actions[i];
    }

    newActions[length].usedID = userID;
    newActions[length].actionType = actionType;
    newActions[length].year = local_time->tm_year + 1900;
    newActions[length].month = local_time->tm_mon + 1;
    newActions[length].day = local_time->tm_mday;
    newActions[length].hour = local_time->tm_hour;
    newActions[length].minute = local_time->tm_min;
    newActions[length].second = local_time->tm_sec;

    return newActions;
}