/*
 * File:        fileio.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Disk operations for Time Tracking project
 */

#include "Fileio.h"
#include "action.h"
#include "action.c"
#include <stdbool.h>
#include <ctype.h>

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
			fprintf(filePointer, "ID: %d, Type: %d, Status: %d, First name: %s Last name: %s\n", 
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

// Reads the number of users from the file, then reserves enough memory for
// the user table and reads it. Finally returns the pointer to the array of
// user structs
// Returns NULL upon failure
struct User *readUserTable(int numberOfUsers, char *filename)
{

	bool status = false;
	
	// create struct memory pointer so we can add read user information to allocated memory
	struct User *memoryPointer = NULL;
	
	
	if (!status)
	{
		// create struct memory pointer so we can add read user information to allocated memory
		//struct User *memoryPointer = NULL;
		
		// allocate memory for array of structs of fixed size of numberOfUsers
		memoryPointer = ( struct User *) malloc(numberOfUsers * sizeof(struct User) );

		// then continue to read the user data from file
		FILE *readFilePointer = NULL;
		
		readFilePointer = fopen(filename, "r");
		
		// check was file opened correctly
		if ( readFilePointer == NULL ) {
			printf("There was issue opening the file...\n");
			return NULL;
		}

		// Read the first three lines of the file (which contain only user information)
	    	char line[MAXLINELENGTH];
	    	
	    	// loop for the number of users times
	    	for (int index = 0; index < numberOfUsers; index++)
	    	{
	    		// read from file until we hit empty line
	    		if (fgets(line, MAXLINELENGTH, readFilePointer) != NULL)
	    		{
	    			printf("Input line: %s\n", line); // print the input line for debugging
	    			
				// assign the user information to the corresponding fields in the User struct
				// index determins that user information is added to correct struct User instance in allocated memory
				sscanf(line, "ID: %u, Type: %u, Status: %d, First name: %s, Last name: %s,", 
					    &memoryPointer[index].ID, 
					    &memoryPointer[index].type, 
					    &memoryPointer[index].status, 
					    memoryPointer[index].firstName, 
					    memoryPointer[index].lastName);
				printf("lastName: %s\n", memoryPointer[index].lastName); // print the lastName for debugging
	    		}
	    		
	    		// in case there were fewer than the supposed amount of users in the file
	    		else
	    		{
	    			break;
	    		}
	    	}
	    	status = true;
    }	
    	
    
    // in case program couldn't run reading from file all the way through, status remains NULL
    if (!status)
    {
    	return NULL;
    }
    
    // in case program could run reading from file all the way through, status remains true 
    // and we return pointer to allocated memory of user structs
    else
    {
    	return memoryPointer;
    }
}

struct Action *readActionTable(char *filename)
{
    return NULL;
}
