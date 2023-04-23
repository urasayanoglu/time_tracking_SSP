/*
 * File:        action.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Functions for manipulating the Action struct arrays
 */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "action.h"

// compare each attribute of previous and current struct to determine which of the two is greater
int isEarlier(struct Action *previousStruct, struct Action *currentStruct) {
    if (previousStruct->year < currentStruct->year) {
        return 1;
    } else if (previousStruct->year > currentStruct->year) {
        return 0;
    } else if (previousStruct->month < currentStruct->month) {
        return 1;
    } else if (previousStruct->month > currentStruct->month) {
        return 0;
    } else if (previousStruct->day < currentStruct->day) {
        return 1;
    } else if (previousStruct->day > currentStruct->day) {
        return 0;
    } else if (previousStruct->hour < currentStruct->hour) {
        return 1;
    } else if (previousStruct->hour > currentStruct->hour) {
        return 0;
    } else if (previousStruct->minute < currentStruct->minute) {
        return 1;
    } else if (previousStruct->minute > currentStruct->minute) {
        return 0;
    } else if (previousStruct->second < currentStruct->second) {
        return 1;
    } else if (previousStruct->second > currentStruct->second) {
        return 0;
    } else {
        return 0;
    }
}

// sort structs with qsort() algoritm from stdlib library
void sortActions(struct Action *actions, int lengthOfArray) {
    // qsort(pointer, total structs, size of single struct, function to compare all structs)
    qsort(actions, lengthOfArray, sizeof(struct Action), comparisonFunction);
}

// compare previous and current struct which result is passed to qsort() function
int comparisonFunction(const void *previous, const void *current) {

    // make type conversion for using another function to compare structs. This is VERY IMPORTANT.
    struct Action *previousStruct = (struct Action *) previous;
    struct Action *currentStruct = (struct Action *) current;

    // in case previous is greater than current
    if (isEarlier(previousStruct, currentStruct)) {
        return -1;
    }

        // in case current is greater than previous
    else if (isEarlier(currentStruct, previousStruct)) {
        return 1;
    }

        // in case previous and current are equal
    else {
        return 0;
    }
}

// create a struct for current time
struct Action *addAction(int userID, int actionType, struct Action *actions, int lengthOfArray) {
    // Get current time
    time_t currentTime = time(NULL);

    // Convert time to local time
    struct tm *localTime = localtime(&currentTime);

    // allocate memory for struct
    struct Action *newActions = NULL;
    newActions = (struct Action *) malloc((lengthOfArray + 1) * sizeof(struct Action));

    // loop is copying the elements from the input array actions to the newly created array newActions
    for (int index = 0; index < lengthOfArray; index++) {
        newActions[index] = actions[index];
    }

    // sets the values of the new struct Action element at the end of the new array newActions
    newActions[lengthOfArray].usedID = userID;
    newActions[lengthOfArray].actionType = actionType;
    newActions[lengthOfArray].year = localTime->tm_year + 1900;
    newActions[lengthOfArray].month = localTime->tm_mon + 1;
    newActions[lengthOfArray].day = localTime->tm_mday;
    newActions[lengthOfArray].hour = localTime->tm_hour;
    newActions[lengthOfArray].minute = localTime->tm_min;
    newActions[lengthOfArray].second = localTime->tm_sec;

    // Finally, returns the pointer to the new array newActions which contains all the old elements from the input array actions 
    // and the new struct Action element at the end.
    return newActions;
}

int findNext(int currentIndex, struct Action *actions, int length) {
    unsigned int userID = actions[currentIndex].usedID;
    do {
        currentIndex++;
    } while (userID != actions[currentIndex].usedID && currentIndex < length);
    if (currentIndex < length) {
        return currentIndex;
    } else {
        return -1;
    }
}

int sameDay(struct Action *x, struct Action *y) {
    return (x->day == y->day && x->month == y->month && x->year == y->year);
}


int timeSpent(int state, unsigned int userID, int year, int month, int day, struct Action *actions) {
    int counter = 0;
    int numberOFActions = 0;
    int actionIndex = 0;
    int endpoint = 0;
    int swap = 0;
    if (actions == NULL) {
        return 0;
    } else {
        numberOFActions = sizeof(*actions) / sizeof(actions[0]);
    }

    sortActions(actions, numberOFActions);
    if (year == 0 && month == 0 && day == 0)
    {
        // Get current time
        time_t currentTime = time(NULL);

        // Convert time to local time
        struct tm *localTime = localtime(&currentTime);
        year = localTime->tm_year + 1900;
        month = localTime->tm_mon + 1;
        day = localTime->tm_mday;
    }

    while (actionIndex < numberOFActions && actions[actionIndex].actionType != state &&
           actions[actionIndex].usedID != userID) {
        actionIndex++;
    }

    endpoint = findEndPoint(actionIndex, userID, state, actions, numberOFActions);
    while (endpoint != -1) {
        counter += 3600 * (actions[endpoint].hour - actions[endpoint].hour);
        counter += 60 * (actions[endpoint].minute - actions[endpoint].minute);
        counter += (actions[endpoint].second - actions[endpoint].second);
        swap = findEndPoint(endpoint, userID, state, actions, numberOFActions);
        if (swap == -1) {
            endpoint = swap;
        }
        else
        {
            actionIndex = endpoint;
            endpoint = swap;
        }
    }

    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    counter += 3600 * (localTime->tm_hour - actions[actionIndex].hour) + 60 * (localTime->tm_min -
            actions[actionIndex].minute) + (localTime->tm_sec - actions[actionIndex].second);


    return counter;
}

int findEndPoint(int index, unsigned int userID, int status, struct Action *actions, int numberOfActions) {
    if (actions[findNext(index, actions, numberOfActions)].actionType != status)
    {
        return findNext(index, actions, numberOfActions);
    }
    else
    {
        return findEndPoint(findNext(index, actions, numberOfActions), userID, status,
                            actions, numberOfActions);
    }
}

