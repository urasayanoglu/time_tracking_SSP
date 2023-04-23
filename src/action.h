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
* This structure represents an action performed by a user, including the user ID, action type, date, and time.
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
    int hour;/**< The hour of the action (0-23) */

    /// Minutes past the hour (0-59)
    int minute;/**< The minute of the action (0-59) */

    /// Seconds past the minute (0-59)
    int second;/**< The second of the action (0-59) */
};

// returns true if the time/date of x is earlier than y
/**
* @brief Determines whether the time/date of x is earlier than y
* @param previousStruct Pointer to the previous Action structure
* @param currentStruct Pointer to the current Action structure
* @return True if the time/date of x is earlier than y; false otherwise
*/
int isEarlier(struct Action *previousStruct, struct Action *currentStruct);

// The intention here is to use the qsort function in stdlib.h to sort Action structs to order
/**
* @brief Sorts Action structs to order
* @param actions Pointer to the array of Action structures
* @param lengthOfArray The length of the array of Action structures
*/
void sortActions(struct Action *actions, int lengthOfArray);

// The intention here is compare current and previous Action structs attribute by attribute
// 1. return positive integer in case current is greater than previous 
// 2. return negative in case current is less than previous
// 3. return 0 in case current and previous are equal

/**
* @brief Compares current and previous Action structs attribute by attribute
* This function compares the current and previous Action structs attribute by attribute and returns:
* a positive integer in case current is greater than previous
* a negative integer in case current is less than previous
* 0 in case current and previous are equal
* @param previous Pointer to the previous Action structure
* @param current Pointer to the current Action structure
* @return The result of the comparison
*/
int comparisonFunction(const void *previous, const void *current);

// Adds an Action struct to an array of such structs, using current time
// return NULL for failure.

/**
* @brief Adds an Action struct to an array of such structs, using current time
* This function adds an Action struct to an array of such structs, using the current time, and returns
* a pointer to the newly added Action structure.
* @param userID The ID of the user who performed the action
* @param actionType The type of action (0 = Start working, 1 = Stop working)
* @param actions Pointer to the array of Action structures
* @param length The length of the array of Action structures
* @return A pointer to the newly added Action structure; NULL for failure
*/
struct Action *addAction(int userID, int actionType, struct Action *actions, int length);

// Returns the index of the next action from the same user. Returns -1 if no such actions exists
/**
* @brief Returns the index of the next action from the same user. Returns -1 if no such actions exist.
* @param currentIndex The index of the current action.
* @param actions Pointer to the array of Action structs.
* @param length The length of the array of Action structs.
* @return int The index of the next action from the same user, or -1 if none exist.
*/
int findNext(int currentIndex, struct Action *actions, int length);

// Returns the time spent on the specified state on the specified date (0, 0, 0 for today)
// in seconds
/**
* @brief Returns the time spent on the specified state on the specified date (0, 0, 0 for today) in seconds.
* @param state The state to calculate the time spent on.
* @param userID The ID of the user.
* @param year The year to calculate the time spent on.
* @param month The month to calculate the time spent on.
* @param day The day to calculate the time spent on.
* @param actions Pointer to the array of Action structs.
* @return int The time spent on the specified state on the specified date in seconds.
*/
int timeSpent(int state, unsigned int userID, int year, int month, int day, struct Action *actions);

// Returns true if the actions are dated to the same day
/**
* @brief Returns true if the two given Action structs are dated to the same day.
* @param x Pointer to the first Action struct.
* @param y Pointer to the second Action struct.
* @return int Returns 1 if the two Action structs are dated to the same day, 0 otherwise.
*/
int sameDay(struct Action *x, struct Action *y);

// Finds the index of the next action from the same user that does
// NOT have the same status. Returns -1 if no such index exists
/**
* @brief Finds the index of the next action from the same user that does NOT have the same status.
* Returns -1 if no such index exists.
* @param index The starting index.
* @param userID The ID of the user.
* @param status The status to compare to.
* @param actions Pointer to the array of Action structs.
* @param numberOfActions The number of actions in the array.
* @return int The index of the next action from the same user that does NOT have the same status, or -1 if none exist.
*/
int findEndPoint(int index, unsigned int userID, int status, struct Action *actions, int numberOfActions);

#endif //TIME_TRACKING_SSP_ACTION_H
