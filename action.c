/*
 * File:        action.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Functions for manipulating the Action struct arrays
 */

#include <stdlib.h>
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

void sortActions(struct Action *actions)
{

}

struct Action *addAction(int userID, int actionType, struct Action *actions)
{
    return NULL;
}