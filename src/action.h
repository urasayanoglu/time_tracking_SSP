/**
 * @file action.h
 * @author Uras Ayanoglu
 * @author Jan-Krister Helenius
 * @author Sebastian Sopola
 * @brief Functions for manipulating the Action struct arrays
 */


#ifndef TIME_TRACKING_SSP_ACTION_H
#define TIME_TRACKING_SSP_ACTION_H

/**
* @struct Action
* @brief Structure representing an action performed by a user
* @details Structure represents an action performed by a user, including the user ID, action type, date, and time.
*/
struct Action
{
    unsigned int usedID;/**< The ID of the user who performed the action */

    /// 0 = Start working, 1 = Stop working
    /// With room to add multiple types of breaks
    int actionType;/**< The type of action (0 = Start working, 1 = Stop working) */

    /// Dates follow meatspace conventions, here clarified where not immediately apparent
    int year;/**< The year of the action */
    int month;/**< The month of the action */
    int day;/**< The day of the action */

    /// Hours since midnight (0-23)
    int hour;

    /// Minutes past the hour (0-59)
    int minute;

    /// Seconds past the minute (0-59)
    int second;
};


/**
* @brief Determines whether the time/date of x is earlier than y
* @param[in] previousStruct Pointer to the previous Action structure
* @param[in] currentStruct Pointer to the current Action structure
* @return True if the time/date of x is earlier than y; false otherwise
*/
int isEarlier(struct Action *previousStruct, struct Action *currentStruct);

// The intention here is to use the qsort function in stdlib.h to sort Action structs to order
/**
* @brief Sorts Action structs to order
* @param actions Pointer to the array of Action structures
* @param lengthOfArray The length of the array of Action structures
* @return void
*/
void sortActions(struct Action *actions, int lengthOfArray);

// The intention here is compare current and previous Action structs attribute by attribute
// 1. return positive integer in case current is greater than previous 
// 2. return negative in case current is less than previous
// 3. return 0 in case current and previous are equal

/**
* @brief Compares current and previous Action structs attribute by attribute
* @details This function compares the current and previous Action structs attribute by attribute and returns:
* 1. Return a positive integer in case current is greater than previous
* 2. Return a negative integer in case current is less than previous
* 3. Return 0 in case current and previous are equal
* @param[in] previous Pointer to the previous Action structure
* @param[in] current Pointer to the current Action structure
* @return An integer based on the result of the comparison
*/
int comparisonFunction(const void *previous, const void *current);

// Adds an Action struct to an array of such structs, using current time
// return NULL for failure.

/**
* @brief Adds an Action struct to an array of such structs, using current time
* @details This function adds an Action struct to an array of such structs, using the current time, and returns
* a pointer to the newly added Action structure.
* @param[in] userID The ID of the user who performed the action
* @param[in] actionType The type of action (0 = Start working, 1 = Stop working)
* @param[in] actions Pointer to the array of Action structures
* @param[in] length The length of the array of Action structures
* @return A pointer to the newly added Action structure; NULL for failure
*/
struct Action *addAction(int userID, int actionType, struct Action *actions, int *numberOfActions);

// Returns the index of the next action from the same user. Returns -1 if no such actions exists
/**
* @brief Returns the index of the next action from the same user. Returns -1 if no such actions exist.
* @param[in] currentIndex The index of the current action.
* @param[in] actions Pointer to the array of Action structs.
* @param[in] length The length of the array of Action structs.
* @return int The index of the next action from the same user, or -1 if none exist.
*/
int findNext(int currentIndex, struct Action *actions, int length);


/**
* @brief Returns the time spent on the specified state on the specified date (0, 0, 0 for today) in seconds.
* @param[in] state The state to calculate the time spent on.
* @param[in] userID The ID of the user.
* @param[in] year The year to calculate the time spent on.
* @param[in] month The month to calculate the time spent on.
* @param[in] day The day to calculate the time spent on.
* @param[in] actions Pointer to the array of Action structs.
* @return int The time spent on the specified state on the specified date in seconds.
*/
int timeSpent(int state, unsigned int userID, int year, int month, int day, struct Action *actions, int numberOfActions);

// Returns true if the actions are dated to the same day
/**
* @brief Returns true if the two given Action structs are dated to the same day.
* @param[in] x Pointer to the first Action struct.
* @param[in] y Pointer to the second Action struct.
* @return int Returns 1 if the two Action structs are dated to the same day, 0 otherwise.
*/
int sameDay(struct Action *x, struct Action *y);

#endif //TIME_TRACKING_SSP_ACTION_H
