/*
 * File:        Timetrackingnc.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Time tracking project Ncurses interface
 */

// You may need to install a package like libncurse-dev to use these
// e.g. sudo apt install libncurses-dev
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "action.h"
#include "Fileio.h"
#include "Fileio.c"

#define USERFILENAME "userdata.tt"
#define ACTIONFILENAME "actiondata.tt"
#define CTR_POS(x) ((COLS - strlen(x)) / 2)

char *choices[] = {
    "Start day",
    "Break",
    "End break",
    "End day",
    "Report day",
    "Exit",
};

// Initialize the highlight to the first choice
int highlightCurrentOption = 0;
char infotext[120] ="\n";
    

// function to be called when user want to clear menu to original state
void clearMenu()
{
	// Clear the screen
    clear();

	// Print the title of the menu: (row,built-int print-function(string),string format, the string)
	char *title = "Time Tracking Menu";
    mvprintw(0, CTR_POS(title), "%s", title);
    
    // Print the selection prompt
    mvprintw(2, CTR_POS("Select an option"), "Select an option");

	// Print the menu items: (row,built-int print-function(string),string format, the string)
    for (int index = 0; index < 6; index++) {
        mvprintw(4 + index, CTR_POS(choices[index]), "%s", choices[index]);
    }
    
    // Reset the highlight to the first option
    highlightCurrentOption = 0;
    
    // Refresh the screen to show the menu items
    refresh();
}

// function to be called when user navigates in menu and program draws menu again with changes user position
void printMenu()
{
	// Print the title of the menu: (row,built-int print-function(string),string format, the string)
	char *title = "Time Tracking Menu";
    mvprintw(0, CTR_POS(title), "%s", title);
    
    // Print the selection prompt
    mvprintw(2, CTR_POS("Select an option"), "Select an option");

	// Print the menu items: (row,built-int print-function(string),string format, the string)
    for (int index = 0; index < 6; index++) {
        mvprintw(4 + index, CTR_POS(choices[index]), "%s", choices[index]);
    }
    
    // Print the menu with highlighted item based on user position in menu
    for (int index = 0; index < 6; index++) {
        // Check if the current index is the same as the highlightCurrentOption
        if (index == highlightCurrentOption) {

        	// Set the bold and underline attributes for the highlighted item
    		attrset(A_BOLD | A_UNDERLINE);
 
            attron(A_REVERSE); 
         
        }
        mvprintw(4 + index, CTR_POS(choices[index]), "%s", choices[index]);
        if (index == highlightCurrentOption) {

        	// Reset the bold and underline attributes for the highlighted item
    		attrset(A_NORMAL);
 
            attroff(A_REVERSE); 
        }
    }
    mvprintw(12 , CTR_POS(infotext), "%s", infotext);

    // Refresh the screen to show the menu items
    refresh();
}

void initialNcurses() 
{
	// Initialize ncurses
    initscr();
    
    // Cbreak mode  makes button presses immediately available to the program
    cbreak();

    // noecho() disables automatic printing of typed characters
    noecho();

    // sets the stdscr screen up to receive special keys
    keypad(stdscr, TRUE);
}

// function to allow move around menu
void navigateMenu(int highlightCurrentOption)
{
    // Calculate the row and column of the current highlighted option
    int row = 4 + highlightCurrentOption;
    int col = CTR_POS(choices[highlightCurrentOption]);
    
    // Move the cursor to the current highlighted option
    move(row, col);
    
    // Refresh the screen to show the updated cursor position
    refresh();
}

// function to close the program
void terminateProgram()
{
    // End ncurses mode
    endwin();
    
    // Close program
    exit(0);
}

// check user key presses
void keyPresses(struct User *users, struct Action *actions)
{
    // Get the number of menu items
    int numChoices = sizeof(choices) / sizeof(char *);

    // the key user pressed at any given time, start at top menu item
    int keyPressed = 0;

    // Get user input
    keyPressed = getch();

    if (keyPressed == KEY_UP) {
        // Move selection up
        highlightCurrentOption--;
        if (highlightCurrentOption < 0) {
            highlightCurrentOption = 0;
        }
    } else if (keyPressed == KEY_DOWN) {
        // Move selection down
        highlightCurrentOption++;
        if (highlightCurrentOption >= numChoices) {
            highlightCurrentOption = numChoices - 1;
        }
    } else if (keyPressed == '\n' && highlightCurrentOption >= 0 && highlightCurrentOption < numChoices) {
        // Execute code when user presses enter on the currently highlighted item
        int numActions = actions != NULL ? sizeof(*actions) / sizeof(actions[0]) : 0;
        if (highlightCurrentOption == 0) {
            // Execute code for "Start day" option
            addAction(users[0].ID, 0, actions, numActions);
            strcpy(infotext, "Working\n");
        } else if (highlightCurrentOption == 1) {
            // Execute code for "Break" option
            addAction(users[0].ID, 1, actions, numActions);
            strcpy(infotext, "On break\n");
        } else if (highlightCurrentOption == 2) {
            // Execute code for "End break" option
            addAction(users[0].ID, 0, actions, numActions);
            strcpy(infotext, "Working\n");
        } else if (highlightCurrentOption == 3) {
            // Execute code for "End day" option
            addAction(users[0].ID, 2, actions, numActions);
            strcpy(infotext, "Day ended\n");
        } else if (highlightCurrentOption == 4) {
            // Execute code for "Report Day" option

            /* THE LINES BELOW ARE COMMENTED OUT BECAUSE OF A BUG SOMEWHERE IN THE BACKEND
             * CAUSING A SEGFAULT. AS IT IS 4 AM I HAVE MADE THE DECISION TO POSTPONE
             * DEBUGGING UNTIL LATER TODAY (EDIT 5AM)
             * */

            // int hoursWorked = timeSpent(0, 0, 0, 0, 0, actions) / 3600;
            // int minutesWorked = (timeSpent(0, 0, 0, 0, 0, actions) % 3600) * 60;
            // int hoursBreak = timeSpent(1, 0, 0, 0, 0, actions) / 3600;
            // int minutesBreak = (timeSpent(1, 0, 0, 0, 0, actions) % 3600) * 60;
            sprintf(infotext, "Today ");
            strcat(infotext, users[0].firstName);
            strcat(infotext, " ");
            strcat(infotext, users[0].lastName);

        } else if (highlightCurrentOption == 5) {
        	// Execute code for "Exit" option
            int numUsers = sizeof(*users) / sizeof(users[0]);
            writeDB(numUsers, numActions, USERFILENAME, ACTIONFILENAME, users, actions);
            free(users);
            free(actions);
        	terminateProgram();
        }
    }

    // Navigate the menu to the current highlighted option
    navigateMenu(highlightCurrentOption);
}

// function to run menu 
void runProgram (struct User *users, struct Action *actions)
{
	// initialize ncurses, initialize terminal environment, initialize menu
	initialNcurses();	
	
	// infinite loop to run menu
	while(1)
	{
		// Print the menu initially
		printMenu();
		
		// check for user key presses to navigate in the menu
		keyPresses(users, actions);
	}
}

int main() {
    // Pointers to arrays
    static struct User *users = NULL;
    static struct Action *actions = NULL;

    // Read the tables from file
    users = readUserTable(USERFILENAME);
    actions = readActionTable(ACTIONFILENAME);


    if (users == NULL)
    // Data for our first user
    {
        users = (struct User *) malloc(sizeof(struct User));
        users[0].type = 0;
        users[0].ID = 0;
        users[0].status = 0;
        stringInput("Enter First name: ", users[0].firstName);
        stringInput("Enter last name: ", users[0].lastName);
    }

	// function to run menu 
	runProgram(users, actions);

    return 0;
}



