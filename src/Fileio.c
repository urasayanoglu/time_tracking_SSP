/*
 * File:        fileio.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Disk operations for Time Tracking project
 */

#include "Fileio.h"
#include "action.h"
#include "action.c"
#include <stdbool.h>

// add user information and actions to database, to 'data.txt' file
int writeDB(int numberOfUsers, int numberOfActions, char *filename, struct User *users, struct Action *actions)
{
	bool status = false;

	if (!status)
	{
		FILE *filePointer = NULL;
		
		// open the file
		filePointer = fopen(filename,"a");
		
		// check was file opened correctly
		if ( filePointer == NULL ) {
			printf("There was issue opening the file...\n");
			exit(1);
		}
		
		// loop through all users to add them to file
		for (int index = 0; index < numberOfUsers; index++) {
			fprintf(filePointer, "ID: %d, Type: %d, Status: %d, First name: %s, Last name: %s\n", 
			(users + index)->ID, 
			(users + index)->type, 
			(users + index)->status,
			(users + index)->firstName,
			(users + index)->lastName
			);
				
		}
		
		// loop through all actions to add them to file
		for (int index = 0; index < numberOfActions; index++) {
			fprintf(filePointer, "usedID: %d, actionType: %d, Day: %d, Hour: %d, Minutes: %d, Month: %d, Second: %d. Year: %d\n", 
			(actions + index)->usedID, 
			(actions + index)->actionType, 
			(actions + index)->year,
			(actions + index)->month,
			(actions + index)->day,
			(actions + index)->hour,
			(actions + index)->minute,
			(actions + index)->second
			);
				
		}

		// close connection to file after information has been saved into it	
		fclose(filePointer);	
		
		// in case writing to file ran without errors we set function status to true ('succesfully ran mark')
		status = true;
	}
	
	// in case program couldn't run writing to file all the way through, status remains false
	if (!status)
	{
		return 0;
	}
	// in case program could run writing to file all the way through, status is true
	else
	{
		return 1;
	}
}

// for reading, the implementer needs to loo look up hoq fseek works and use it
// to set the pointer to the correct place after reading the ints at
// the beginning of the file
struct User *readUserTable(char *filename)
{
    return NULL;
}

struct Action *readActionTable(char *filename)
{
    return NULL;
}
