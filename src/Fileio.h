/**

* @file fileio.h
* @brief Header file for file input/output operations
* @author Uras Ayanoglu
* @author Jan-Krister Helenius
* @author Sebastian Sopola
*/

#ifndef TIME_TRACKING_SSP_FILEIO_H
#define TIME_TRACKING_SSP_FILEIO_H

/**

* @def NAMELENGTH
* @brief Maximum length of user's first and last name
*/
#define NAMELENGTH 50

/**

* @def MAXLINELENGTH
* @brief Maximum length of a line in a file
*/
#define MAXLINELENGTH 2000

/**

* @def INDEXCORRECTOR
* @brief Correction factor for array indexing (subtracts 1 from user/action ID)
*/
#define INDEXCORRECTOR 4

#include "action.h"

/**

* @struct User
* @brief Struct for storing user information
*/
struct User
{
    unsigned int ID;

    // Using type=0 for the main user, other types may be added if there's time
    // for subordinate and remote users
    int type;

    // status = last action
    int status;
    char firstName[NAMELENGTH];
    char lastName[NAMELENGTH];
};


/**

* @brief Writes binary data to "filename".
* @details Writes the binary data in the following order:
* 1. Number of users (int numberOfUsers)
* 2. Number of actions in the array (int numberOfActions)
* 3. Array of User structs found at location pointed to by *users
* 4. Array of Action structs found at location pointed to by *actions
* The intention is to make this a static storage, loaded upon starting the program,
* and saved to periodically during runtime, as well as at termination
* @param[in] numberOfUsers Number of users to be written to file
* @param[in] numberOfActions Number of actions to be written to file
* @param[in] userdataFilename Name of the file to which user data will be written
* @param[in] actionFilename Name of the file to which action data will be written
* @param[in] users Pointer to an array of User structs
* @param[in] actions Pointer to an array of Action structs
* @return 0 for failure, 1 for success
*/
int writeDB(int numberOfUsers, int numberOfActions, char *userdataFilename, char *actionFilename, struct User *users, struct Action *actions);


/**

* @brief Reads the number of users from the file, then reserves enough memory for the user table and reads it. 
* @param filename Name of the file from which user data will be read
* @return Pointer to an array of User structs. Returns 0 upon failure
*/
struct User *readUserTable(char *filename);


/**

* @brief Reads the number of actions from the file, then reserves enough memory for the action array and reads it.
* @param filename Name of the file from which action data will be read
* @return Pointer to an array of Action structs. Returns NULL upon failure
*/
struct Action *readActionTable(char *filename);

/**

* @brief Prompts user for input and saves input in target
* @param[in] prompt Prompt to be displayed to user
* @param[in] target Pointer to string where input will be saved
*/
void stringInput(char *prompt, char *target);


#endif //TIME_TRACKING_SSP_FILEIO_H
