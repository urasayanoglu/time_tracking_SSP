/**

* @file TestFileio.c
* @author Uras Ayanoglu
* @author Jan-Krister Helenius
* @author Sebastian Sopola
* @details This file contains unit tests for fileio.c functions. The constraints
* on the name format are: the first name and last name must be separated by a
* space, and the name format must be 'CarMagnus' or 'Carl', which means names
* like 'Carl Magnus' or 'Carl-Magnus' are not allowed.
* @brief Unit tests for fileio.c
*/

#include <stdio.h> 
#include <string.h>
#include "Fileio.h"
#include "Fileio.h"
#include "action.h"
#include "Fileio.c"


#define USERFILENAME "userdata.tt"
#define ACTIONFILENAME "actiondata.tt"

// All three function pretty much need to be implemented to use this
/**
* @brief Main function for unit testing the fileio.c functions.
* @return int Return 0 on success
* @details This function creates user and action structs, writes them to files using the writeDB function,
* then reads the files using the readUserTable and readActionTable functions to verify the
* correctness of the reading and writing process. The function returns 0 on success.
*/
int main()
{
    int counter = 0;

    /// Create user struct
    struct User users[3];
    users[0].ID = 1111;
    users[1].ID = 1221;
    users[2].ID = 3;
    users[0].type = 0;
    users[1].type = 1;
    users[2].type = 2;
    users[0].status = 0;
    users[1].status = 1;
    users[2].status = 0;
    strcpy(users[0].firstName,"Uras");
    strcpy(users[1].firstName,"Carl");
    strcpy(users[2].firstName,"Sebastian");
    strcpy(users[0].lastName,"Ayanoglu");
    strcpy(users[1].lastName,"vonAnckarswert");
    strcpy(users[2].lastName,"Sopola");

    /// action struct, copypaste from Testaction
    struct Action testActions[3];
    testActions[0].usedID=1;
    testActions[0].actionType = 0;
    testActions[0].day=2;
    testActions[0].hour=11;
    testActions[0].minute=33;
    testActions[0].month=8;
    testActions[0].second=22;
    testActions[0].year=2011;
    testActions[1].usedID=6;
    testActions[1].actionType = 1;
    testActions[1].day=7;
    testActions[1].hour=16;
    testActions[1].minute=25;
    testActions[1].month=5;
    testActions[1].second=34;
    testActions[1].year=2011;
    testActions[2].usedID=0;
    testActions[2].actionType = 1;
    testActions[2].day=21;
    testActions[2].hour=9;
    testActions[2].minute=44;
    testActions[2].month=7;
    testActions[2].second=54;
    testActions[2].year=2023;
	
    
    int numberOfUsers = sizeof(users) / sizeof(users[0]);
    int numberOfActions = sizeof(testActions) / sizeof(testActions[0]);

    /// Pointers for loading
    struct User *loadedUsers = NULL;
    struct Action *loadedActions = NULL;

    /// save structs
    if (writeDB(numberOfUsers, numberOfActions,USERFILENAME, ACTIONFILENAME, &users[0], &testActions[0]))
    {
        printf("Saving reported success.\n");
    }
    else
    {
        printf("Saving reported failure!\n");
        return 0;
    }

    /// load users 
    ///  in case reading users from database was not succesfull
    if(readUserTable(USERFILENAME) == NULL)
    {
    	printf("loadedUsers did not pass the test\n\n");
    }
    
    /// in case reading users from database was successfull
	else
	{
		loadedUsers = readUserTable(USERFILENAME);
		/// Verify users:
		for (int index = 0; index<numberOfUsers; index++)
		{
		    if (strcmp(users[index].lastName, loadedUsers[index].lastName) == 0)
		    {
		        counter++;
		    }
		    if (strcmp(users[index].firstName, loadedUsers[index].firstName) == 0)
		    {
		        counter++;
		    }
		    if (users[index].status == loadedUsers[index].status)
		    {
		        counter++;
		    }
		    if (users[index].ID == loadedUsers[index].ID)
		    {
		        counter++;
		    }
		    if (users[index].type == loadedUsers[index].type)
		    {
		        counter++;
		    }
		}
		printf("Loading User file passed %d out of %d tests.\n\n\n", counter, 5*numberOfUsers);
    }

    /// load actions   
    /// in case reading actions from database was not succesfull
    if(readUserTable(ACTIONFILENAME) == NULL)
    {
    	printf("loadedActions did not pass the test\n\n");
    }
    
    /// in case reading actions from database was successfull
    else 
    {
    	    loadedActions = readActionTable(ACTIONFILENAME);
	    /// Verify actions
	    counter = 0;
	    for (int index = 0; index < numberOfActions; index++)
	    {
		counter = (loadedActions[index].minute == testActions[index].minute) ? counter+1 : counter;
		counter = (loadedActions[index].hour == testActions[index].hour) ? counter+1 : counter;
		counter = (loadedActions[index].second == testActions[index].second) ? counter+1 : counter;
		counter = (loadedActions[index].day == testActions[index].day) ? counter+1 : counter;
		counter = (loadedActions[index].month == testActions[index].month) ? counter+1 : counter;
		counter = (loadedActions[index].year == testActions[index].year) ? counter+1 : counter;
		counter = (loadedActions[index].actionType == testActions[index].actionType) ? counter+1 : counter;
		counter = (loadedActions[index].usedID == testActions[index].usedID) ? counter+1 : counter;
	    }
	    printf("Loading Action file passed %d out of %d tests.\n\n\n", counter, 8*numberOfActions);
    }
    
    /// Deallocate memory
    free(loadedUsers);
    free(loadedActions);

    return 0;
}
