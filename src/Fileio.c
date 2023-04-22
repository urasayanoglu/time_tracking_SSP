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
			fprintf(filePointer, "usedID: %d, actionType: %d, Day: %d, Hour: %d, Minutes: %d, Month: %d, Second: %d, Year: %d,\n", 
			(actions + index)->usedID, 
			(actions + index)->actionType, 
			(actions + index)->day,
			(actions + index)->hour,
			(actions + index)->minute,
			(actions + index)->month,
			(actions + index)->second,
			(actions + index)->year
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
    struct User *memoryPointer = NULL;
    if (!status)
    {
        memoryPointer = (struct User*) malloc(numberOfUsers * sizeof(struct User));
        
        // check successfulity of memory allocation
        if ( memoryPointer == NULL ) {
            printf("There was an issue opening the file...\n");
            return NULL;
        }
        
        FILE *readFilePointer = NULL;
        
        readFilePointer = fopen(filename, "r");
        
        // check was file opened correctly
        if (readFilePointer == NULL) {
            printf("There was an issue opening the file...\n");
            return NULL;
        }
        
        char line[MAXLINELENGTH];
        int lineNumber = 0;
        
        // read from file until we hit empty line
        while (fgets(line, MAXLINELENGTH, readFilePointer) != NULL)
        {
            lineNumber++;
            
            // check if we are reading the first three lines of the file
            if (lineNumber >= 1 && lineNumber <= 3)
            {
                // assign the user information to the corresponding fields in the User struct
                sscanf(line, "ID: %u, Type: %d, Status: %d, First name: %s Last name: %s",
                        &memoryPointer[lineNumber-1].ID,
                        &memoryPointer[lineNumber-1].type,
                        &memoryPointer[lineNumber-1].status,
                        memoryPointer[lineNumber-1].firstName,
                        memoryPointer[lineNumber-1].lastName
                        );
            }
        }
        fclose(readFilePointer);
        status = true;
    }
    
    // in case program couldn't run reading from file all the way through, status remains NULL
    if (!status)
    {
        return NULL;
    }
    
    // in case program could run reading from file all the way through, status remains true 
    // and we return pointer to allocated memory of User structs
    else
    {
        return memoryPointer;
    }
}

// MODIFY READ USER TABLE TO WORK WITH WHILE FGETS SO IT READ THE WHOLE FILE ALWAYS !!!!!!!!!!!!!!!


struct Action *readActionTable(int numberOfUsers, int numberOfActions, char *filename)
{
    bool status = false;
    struct Action *memoryPointer = NULL;
    if (!status)
    {
        memoryPointer = (struct Action*) malloc(numberOfActions * sizeof(struct Action));
        
        
        // check successfulity of memory allocation
		if ( memoryPointer == NULL ) {
			printf("There was an issue opening the file...\n");
            return NULL;
		}
        
        
        FILE *readFilePointer = NULL;
        
        readFilePointer = fopen(filename, "r");
        
        // check was file opened correctly
        if (readFilePointer == NULL) {
            printf("There was an issue opening the file...\n");
            return NULL;
        }
        
        char line[MAXLINELENGTH];
        int lineNumber = 0;
        
        // read from file until we hit empty line
        while (fgets(line, MAXLINELENGTH, readFilePointer) != NULL)
        {
            lineNumber++;
            
            // check are we pass user information so we start reading action information
            if ( lineNumber >= numberOfUsers && lineNumber <= (numberOfUsers+numberOfActions))
            {
            
            	// assign the action information to the corresponding fields in the Action struct
				// index determins that action information is added to correct struct Action instance in allocated memory
                sscanf(line, "usedID: %d, actionType: %d, Day: %d, Hour: %d, Minutes: %d, Month: %d, Second: %d, Year: %d,", 
                        &memoryPointer[lineNumber-INDEXCORRECTOR].usedID,
                        &memoryPointer[lineNumber-INDEXCORRECTOR].actionType,
                        &memoryPointer[lineNumber-INDEXCORRECTOR].day,
                        &memoryPointer[lineNumber-INDEXCORRECTOR].hour,
                        &memoryPointer[lineNumber-INDEXCORRECTOR].minute,
                        &memoryPointer[lineNumber-INDEXCORRECTOR].month,
                        &memoryPointer[lineNumber-INDEXCORRECTOR].second,
                        &memoryPointer[lineNumber-INDEXCORRECTOR].year
                        );
            }
        }
        fclose(readFilePointer);
        status = true;
    }
    
    // in case program couldn't run reading from file all the way through, status remains NULL
    if (!status)
    {
        return NULL;
    }
    
    // in case program could run reading from file all the way through, status remains true 
    // and we return pointer to allocated memory of actions structs
    else
    {
        return memoryPointer;
    }
}

