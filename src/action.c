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

// States: 0 - working, 1 - on break, 2 - off work
/**

* @brief calculates the time spent in a certain state.
* @param[in] state The state to calculate time spent for (0 - working, 1 - on break, 2 - off work).
* @param[in] userID The ID of the user whose time is being calculated.
* @param[in] year The year to calculate time spent for.
* @param[in] month The month to calculate time spent for.
* @param[in] day The day to calculate time spent for.
* @param[in] actions A pointer to an array of actions.
* @return The time spent in seconds.
*/
int timeSpent(int state, unsigned int userID, int year, int month, int day, struct Action *actions)
{
    // We store the time spent doing action 'state' in variable counter
    int counter = 0;

    // Get number of structs in array actions
    int numberOfActions = (actions != NULL) ? sizeof(*actions) / sizeof(actions[0]) : 0;

    // Make sure the array is sorted
    sortActions(actions, numberOfActions);

    // Get current time
    time_t currentTime = time(NULL);

    // Convert time to local time
    struct tm *localTime = localtime(&currentTime);

    // If date = (0, 0, 0), store current date to those variables.
    if (year == 0 && month == 0 && day == 0)
    {
        year = localTime->tm_year + 1900;
        month = localTime->tm_mon + 1;
        day = localTime->tm_mday;
    }

    int index = 0;
    int searchFlag = 0;
    if (state == 2)
    {
        // We're measuring time spent at mode 2 - off work. Following code iterates over the whole
        // table and takes action according to searchFlag - 0: Search for initial start work action,
        // 1: Search for 'end work' type, 2: End work found, searching for endpoint
        for (int i = 0; i<numberOfActions; i++)
        {
            // Only perform operation if we're on the correct day
            if (actions[i].year == year && actions[i].month == month && actions[i].day == day)
            {
                // Start work
                if (actions[i].actionType == 0 && actions[i].usedID == userID && searchFlag == 0)
                {
                    counter += 3600 * actions[i].hour + 60 * actions[i].minute + actions[i].second;
                    searchFlag = 1;
                }
                    // Get off work
                else if (actions[i].actionType == 2 && actions[i].usedID == userID)
                {
                    index = i;
                    searchFlag = 2;
                }
                    // Seeing if user returns to work afterwards
                else if (searchFlag == 2 && actions[i].actionType != 2 && actions[i].usedID == userID)
                {
                    counter += 3600 * (actions[i].hour - actions[index].hour);
                    counter += 60 * (actions[i].minute - actions[index].minute);
                    counter += (actions[i].second - actions[index].second);
                    searchFlag = 1;
                }
            }
        }
        // If, after the for loop, search flag is at 2, calculate and add time to now, or end of the day,
        // whichever comes first
        if (searchFlag == 2)
        {
            if (year == (localTime->tm_year + 1900) && month == (localTime->tm_mon + 1) && day == localTime->tm_mday)
                // Date is today, measure time to current time
            {
                counter += 3600 * (localTime->tm_hour - actions[index].hour);
                counter += 60 * (localTime->tm_min - actions[index].minute);
                counter += (localTime->tm_sec - actions[index].second);
            }
            else
                // Count time till the end of the day
            {
                counter += 3600 * (23 - actions[index].hour);
                counter += 60 * (60 - actions[index].minute);
                counter += (60 - actions[index].second);
            }
        }
    }
    else if (state == 0)
    {
        // state = 0 means time spent working, so we must find starting points with actionType=0 and
        // connect them to endpoints with actionType=1 or 2 and add up the differences
        // searchFlag = 0 is interpreted as looking for a starting point in this branch
        // searchFlag = 1 means we are looking for an endpoint
        for (int i = 0; i<numberOfActions; i++)
        {
            // Only perform operation if we're on the correct day and user
            if (actions[i].year == year && actions[i].month == month &&
                actions[i].day == day && actions[i].usedID == userID)
            {
                if (searchFlag == 0 && actions[i].actionType == 0)
                    // Startpoint found
                {
                    index = i;
                    searchFlag = 1;
                }
                else if (searchFlag == 1 && (actions[i].actionType == 1 || actions[i].actionType == 2))
                    // Endpoint found
                {
                    counter += 3600 * (actions[i].hour - actions[index].hour);
                    counter += 60 * (actions[i].minute - actions[index].minute);
                    counter += (actions[i].second - actions[index].second);
                    searchFlag = 0;     // Look for a startpoint again
                }
            }
        }
        // For loop ends. If we're still looking for an endpoint, Add the difference from end of the
        // day or current time as in the case of state = 2
        if (searchFlag == 1)
        {
            if (year == (localTime->tm_year + 1900) && month == (localTime->tm_mon + 1) && day == localTime->tm_mday)
                // Date is today, measure time to current time
            {
                counter += 3600 * (localTime->tm_hour - actions[index].hour);
                counter += 60 * (localTime->tm_min - actions[index].minute);
                counter += (localTime->tm_sec - actions[index].second);
            }
            else
                // Count time till the end of the day
            {
                counter += 3600 * (23 - actions[index].hour);
                counter += 60 * (60 - actions[index].minute);
                counter += (60 - actions[index].second);
            }
        }
    }
        // Last case to be considered is state = 1 - on a break. These periods end when the user
        // begins working again or ends their workday
    else if (state == 1)
    {
        // searchFlag = 0 is interpreted as looking for a starting point in this branch
        // searchFlag = 1 means we are looking for an endpoint
        for (int i = 0; i<numberOfActions; i++)
        {
            // Only perform operation if we're on the correct day and user
            if (actions[i].year == year && actions[i].month == month &&
                actions[i].day == day && actions[i].usedID == userID)
            {
                if (searchFlag == 0 && actions[i].actionType == 1)
                    // Startpoint found
                {
                    index = i;
                    searchFlag = 1;
                }
                else if (searchFlag == 1 && (actions[i].actionType == 0 || actions[i].actionType == 2))
                    // Endpoint found
                {
                    counter += 3600 * (actions[i].hour - actions[index].hour);
                    counter += 60 * (actions[i].minute - actions[index].minute);
                    counter += (actions[i].second - actions[index].second);
                    searchFlag = 0;     // Look for a startpoint again
                }
            }
        }
        // For loop ends. If we're still looking for an endpoint, Add the difference from end of the
        // day or current time as in the case of state = 2
        if (searchFlag == 1)
        {
            if (year == (localTime->tm_year + 1900) && month == (localTime->tm_mon + 1) && day == localTime->tm_mday)
                // Date is today, measure time to current time
            {
                counter += 3600 * (localTime->tm_hour - actions[index].hour);
                counter += 60 * (localTime->tm_min - actions[index].minute);
                counter += (localTime->tm_sec - actions[index].second);
            }
            else
                // Count time till the end of the day
            {
                counter += 3600 * (23 - actions[index].hour);
                counter += 60 * (60 - actions[index].minute);
                counter += (60 - actions[index].second);
            }
        }
    }
    return counter;
}


