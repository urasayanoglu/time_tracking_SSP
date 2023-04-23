/**
 * @file action.c
 * @author Uras Ayanoglu 
 * @author Jan-Krister Helenius
 * @author Sebastian Sopola
 * @brief Functions for manipulating the Action struct arrays
 */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "action.h"

/**

* @brief Compare each attribute of previous and current struct to determine which of the two is greater
* @param[in] previousStruct pointer to the previous struct Action
* @param[in] currentStruct pointer to the current struct Action
* @return 1 if previousStruct is earlier than currentStruct, 0 otherwise
*/
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

/**

* @brief Sort structs with qsort() algorithm from stdlib library
* @param[in,out] actions pointer to the array of struct Actions to be sorted
* @param[in] lengthOfArray the number of elements in the array
*/
void sortActions(struct Action *actions, int lengthOfArray) {
    // qsort(pointer, total structs, size of single struct, function to compare all structs)
    qsort(actions, lengthOfArray, sizeof(struct Action), comparisonFunction);
}

/**

* @brief Compare previous and current struct which result is passed to qsort() function
* @param[in] previous pointer to the previous struct Action
* @param[in] current pointer to the current struct Action
* @return -1 if previous is greater than current, 1 if current is greater than previous, 0 if previous and current are equal
*/
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

/**

* @brief Creates a new struct Action element and adds it to the end of an existing array of struct Action.
* @param userID The ID of the user performing the action.
* @param actionType The type of action being performed.
* @param actions The existing array of struct Action to which the new element will be added.
* @param lengthOfArray The number of elements in the existing array.
* @return A pointer to the new array of struct Action, which contains all the old elements from the input array and the new struct Action element at the end.
*/
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
/**

* @brief Finds the index of the next struct Action element with a different user ID than the current element.
* @param currentIndex The index of the current struct Action element in the array.
* @param actions The array of struct Action elements.
* @param length The number of elements in the array.
* @return The index of the next struct Action element with a different user ID than the current element, or -1 if no such element exists.
*/
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

/**

* @brief Checks whether two struct Action elements occurred on the same day.
* @param x A pointer to the first struct Action element.
* @param y A pointer to the second struct Action element.
* @return 1 if both elements occurred on the same day, and 0 otherwise.
*/
int sameDay(struct Action *x, struct Action *y) {
    return (x->day == y->day && x->month == y->month && x->year == y->year);
}

/**

* @brief Calculates the time spent in a given state by a given user on a given day.

* @param state An integer representing the state.

* @param userID An unsigned integer representing the user ID.

* @param year An integer representing the year.

* @param month An integer representing the month.

* @param day An integer representing the day.

* @param actions A pointer to an array of struct Action elements.

* @return An integer representing the time spent in seconds.
*/
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
/**

* @brief Finds the index of the last action with the same status as the input status and with the same user ID as the input user ID.
* @param index The index of the first action with the same status and user ID.
* @param userID The ID of the user.
* @param status The status of the action.
* @param actions The array of actions.
* @param numberOfActions The number of actions in the array.
* @return int The index of the last action with the same status and user ID as the input,or -1 if such an action is not found.
*/
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

