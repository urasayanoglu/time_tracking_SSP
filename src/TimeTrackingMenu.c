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
char infotext1[60] ="\n";
char infotext2[60] ="\n";
char infotext3[60] ="\n";
    

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
void printMenu(struct User *users)
{
	// Print the title of the menu: (row,built-int print-function(string),string format, the string)
	char *title = "Time Tracking Menu";
    mvprintw(0, CTR_POS(title), "%s", title);
    
    // Print the selection prompt
    mvprintw(2, CTR_POS("Select an option"), "Select an option");
    
    // This name is indexed with the very first one and 
	//should be further implemented when we allow multiple users
	mvprintw(0,3, "Online: %s %s", users[0].firstName,users[0].lastName);
    
	
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
    mvprintw(12 , CTR_POS(infotext1), "%s", infotext1);
    mvprintw(13 , CTR_POS(infotext2), "%s", infotext2);
    mvprintw(14 , CTR_POS(infotext3), "%s", infotext3);

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
            strcpy(infotext1, "Working\n");
            strcpy(infotext2, "\n");
            strcpy(infotext3, "\n");
        } else if (highlightCurrentOption == 1) {
            // Execute code for "Break" option
            addAction(users[0].ID, 1, actions, numActions);
            strcpy(infotext1, "On break\n");
            strcpy(infotext2, "\n");
            strcpy(infotext3, "\n");
        } else if (highlightCurrentOption == 2) {
            // Execute code for "End break" option
            addAction(users[0].ID, 0, actions, numActions);
            strcpy(infotext1, "Working\n");
            strcpy(infotext2, "\n");
            strcpy(infotext3, "\n");
        } else if (highlightCurrentOption == 3) {
            // Execute code for "End day" option
            addAction(users[0].ID, 2, actions, numActions);
            strcpy(infotext1, "Day ended\n");
            strcpy(infotext2, "\n");
            strcpy(infotext3, "\n");
        } else if (highlightCurrentOption == 4) {
            // Execute code for "Report Day" option


            int hoursWorked = timeSpent(0, 0, 0, 0, 0, actions) / 3600;
            int minutesWorked = (timeSpent(0, 0, 0, 0, 0, actions) % 3600) * 60;
            int hoursBreak = timeSpent(1, 0, 0, 0, 0, actions) / 3600;
            int minutesBreak = (timeSpent(1, 0, 0, 0, 0, actions) % 3600) * 60;

            // Variable for storing integer as string before concatenation
            char intConversion[10] = "0";

            // Composes the displayed string, each line in its own variable to avoid formatting snafu
            sprintf(infotext1, "Today ");
            strcat(infotext1, users[0].firstName);
            strcat(infotext1, " ");
            strcat(infotext1, users[0].lastName);
            strcat(infotext1, "\n");

            sprintf(infotext2, "has worked ");
            sprintf(intConversion, "%d", hoursWorked);
            strcat(infotext2, intConversion);
            strcat(infotext2, " hours and ");
            sprintf(intConversion, "%d", minutesWorked);
            strcat(infotext2, intConversion);
            strcat(infotext2, " minutes, and\n");

            sprintf(infotext3, "been on break for ");
            sprintf(intConversion, "%d", hoursBreak);
            strcat(infotext3, intConversion);
            strcat(infotext3, " hours and ");
            sprintf(intConversion, "%d", minutesBreak);
            strcat(infotext3, intConversion);
            strcat(infotext3, " minutes\n");


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

// function to run time tracking menu 
void runProgram (struct User *users, struct Action *actions)
{
	// initialize ncurses, initialize terminal environment, initialize menu
	initialNcurses();	
	
	// infinite loop to run menu
	while(1)
	{
		// Print the time tracking menu , with the user info top right corner
		printMenu(users);
		
		// check for user key presses to navigate in the menu
		keyPresses(users, actions);
	}
}


void setWindowStyle () 
{
	// enable colors
    start_color();

    // set the background and foreground colors
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    wbkgd(stdscr, COLOR_PAIR(1));
}

// function to be called when program is first ran
void printMainMenu()
{
		// Print the title of the menu: (row,built-int print-function(string),string format, the string)
    	char *title = "Main Menu";
    	attron(A_BOLD | A_UNDERLINE);
    	mvprintw(2, CTR_POS(title), "%s", title);
    	attroff(A_BOLD | A_UNDERLINE);
    	
    	// print the option to sign in
    	mvprintw(4, (COLS - strlen("Sign in with your name")) / 2, "Sign in with your name");
    	
    	// Refresh the screen to show the menu items
   		refresh();
} 


// function to prompt user for first and last name and return a User struct
struct User getUserInfo() {
    struct User user;
    memset(user.firstName, 0, NAMELENGTH);  			// Clear first name buffer
    memset(user.lastName, 0, NAMELENGTH);  				// Clear last name buffer
    stringInput("Enter First name: ", user.firstName);	// ask first name and assign it
    mvprintw(8, 32, "First name: %s", user.firstName);  // Display first name below input prompt
    clear();											// clear screen when user presses enter	
    printMainMenu();									// make main menu again
    stringInput("Enter last name: ", user.lastName);	// ask for last name
    mvprintw(8, 32, "Last name: %s", user.lastName);  	// Display last name below input prompt
    user.type = 0;										// initialize rest values accordinly
    user.ID = 0;
    user.status = 0;
    return user;										// return user struct which is then passed to continueToNextFunction after names 
}														// were given



// function to allow change to next menu
void continueToNextMenu(struct User user)
{
    // function to be called when user want to clear menu 
    clearMenu();
    
    // Pointers to arrays
    static struct User *users = NULL;
    static struct Action *actions = NULL;

    // Read the tables from file
    users = readUserTable(USERFILENAME);
    actions = readActionTable(ACTIONFILENAME);

    if (users == NULL) {
        users = (struct User *) malloc(sizeof(struct User));
        users[0] = user;
    }

    // function to run Time Tracking Menu
    runProgram(users, actions);
}



// function to run main menu from where user is directed to TimeTrackingMenu after loggin in 
void runMainMenu () 
{
    // initialize ncurses, initialize terminal environment, initialize menu
	initialNcurses();

	setWindowStyle ();
	
	printMainMenu();
    
    struct User user = getUserInfo();
    continueToNextMenu(user);

    // End ncurses mode, IMPORTANT; WITHOUT THIS WINDOW CRASHES AND/OR WORKS WEIRDLY
    endwin();
}

int main()
{

    runMainMenu();

    return 0;
}


