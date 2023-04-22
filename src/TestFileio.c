/*
 * File:        TestFileio.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Unit tests for fileio.c
 */

/*
	Constraints: Name must be format 'CarMagnus','Carl'
	Not allowed names: 'Carl Magnus', 'Carl-Magnus' 
*/


#include <stdio.h>
#include <string.h>
#include "Fileio.h"
#include "Fileio.h"
#include "action.h"
#include "Fileio.c"


#define FILENAME "data.txt"

// All three function pretty much need to be implemented to use this

int main()
{
    int counter = 0;

    // Create user struct
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

    // action struct, copypaste from Testaction
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

    // Pointers for loading
    struct User *loadedUsers = NULL;
    struct Action *loadedActions = NULL;

    // save structs
    // *** IDE is warning about &testActions[0] below, but not &users[0].
    // Will have to investigate at some point, or resolve when ready to run
    // (wouldn't be the first time Clion is wrong about this)
    if (writeDB(numberOfUsers, numberOfActions, FILENAME, &users[0], &testActions[0]))
    {
        printf("Saving reported success.\n");
    }
    else
    {
        printf("Saving reported failure!\n");
        return 0;
    }

    // load users
    
    // in case reading users from database was not succesfull
    if(readUserTable(numberOfUsers,FILENAME) == NULL)
    {
    	printf("loadedUsers did not pass the test\n\n");
    }
    
    // in case reading users from database was successfull
	else
	{
		loadedUsers = readUserTable(numberOfUsers,FILENAME);
		// Verify users:
		for (int index = 0; index<numberOfUsers; index++)
		{
			printf("users.lastname[%s], loadedUsers.lastname[%s]\n",users[index].lastName, loadedUsers[index].lastName);
		    if (strcmp(users[index].lastName, loadedUsers[index].lastName) == 0)
		    {
		        counter++;
		    }
		    printf("users.firstName[%s], loadedUsers.firstName[%s]\n",users[index].firstName, loadedUsers[index].firstName);
		    if (strcmp(users[index].firstName, loadedUsers[index].firstName) == 0)
		    {
		        counter++;
		    }
		    printf("users.status[%d] == loadedUsers.status[%d]\n",users[index].status, loadedUsers[index].status);
		    if (users[index].status == loadedUsers[index].status)
		    {
		        counter++;
		    }
		    printf("users.ID[%d] == loadedUsers.ID[%d]\n",users[index].ID,loadedUsers[index].ID);
		    if (users[index].ID == loadedUsers[index].ID)
		    {
		        counter++;
		    }
		    printf("users.type[%d] == loadedUsers.type[%d]\n",users[index].type,loadedUsers[index].type);
		    if (users[index].type == loadedUsers[index].type)
		    {
		        counter++;
		    }
		}
		printf("Loading User file passed %d out of %d tests.\n\n\n", counter, 5*numberOfUsers);
    }

    // load actions
    
    // in case reading actions from database was not succesfull
    if(readUserTable(numberOfUsers,FILENAME) == NULL)
    {
    	printf("loadedActions did not pass the test\n\n");
    }
    
    // in case reading actions from database was successfull
    else 
    {
    	    loadedActions = readActionTable(numberOfUsers,numberOfActions,FILENAME);
	    // Verify actions
	    counter = 0;
	    for (int index = 0; index < numberOfActions; index++)
	    {
		counter = (loadedActions[index].minute == testActions[index].minute) ? counter+1 : counter;
		
		printf("loadedActions[index].minute[%d] == testActions[index].minute[%d]\n", loadedActions[index].minute,testActions[index].minute);
		
		counter = (loadedActions[index].hour == testActions[index].hour) ? counter+1 : counter;
		
		printf("loadedActions[index].hour[%d] == testActions[index].hour[%d])\n", loadedActions[index].hour,testActions[index].hour);
		
		counter = (loadedActions[index].second == testActions[index].second) ? counter+1 : counter;
		
		printf("loadedActions[index].second[%d] == testActions[index].second[%d]\n", loadedActions[index].second,testActions[index].second);
		
		counter = (loadedActions[index].day == testActions[index].day) ? counter+1 : counter;
		
		printf("loadedActions[index].day[%d] == testActions[index].day[%d]\n", loadedActions[index].day,testActions[index].day);
		
		counter = (loadedActions[index].month == testActions[index].month) ? counter+1 : counter;
		
		printf("loadedActions[index].month[%d] == testActions[index].month[%d]\n", loadedActions[index].month,testActions[index].month);
		
		counter = (loadedActions[index].year == testActions[index].year) ? counter+1 : counter;
		
		printf("loadedActions[index].year[%d] == testActions[index].year[%d]\n", loadedActions[index].year,testActions[index].year);
		
		counter = (loadedActions[index].actionType == testActions[index].actionType) ? counter+1 : counter;
		
		printf("loadedActions[index].actionType[%d] == testActions[index].actionType[%d]\n", loadedActions[index].actionType,testActions[index].actionType);
		
		counter = (loadedActions[index].usedID == testActions[index].usedID) ? counter+1 : counter;
		
		printf("loadedActions[index].usedID[%d] == testActions[index].usedID[%d]\n", loadedActions[index].usedID,testActions[index].usedID);
	    }
	    printf("Loading Action file passed %d out of %d tests.\n\n\n", counter, 5*numberOfActions);
    }
    
    printf("Number of users [%d] and number of actions [%d]\n",numberOfUsers,numberOfActions);
    
    // Deallocate memory
    free(loadedUsers);
    free(loadedActions);

    return 0;
}
