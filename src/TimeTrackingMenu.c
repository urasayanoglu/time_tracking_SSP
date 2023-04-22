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
#include <menu.h>


#define CTR_POS(x) ((COLS - strlen(x)) / 2)

char *choices[] = {
    "Start day",
    "Break",
    "End break",
    "End day",
    "Exit",
};

// Initialize the highlight to the first choice
int highlightCurrentOption = 0;
    
    

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
    for (int index = 0; index < 5; index++) {
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
    for (int index = 0; index < 5; index++) {
        mvprintw(4 + index, CTR_POS(choices[index]), "%s", choices[index]);
    }
    
    // Print the menu with highlighted item based on user position in menu
    for (int index = 0; index < 5; index++) {
        // Check if the current index is the same as the highlightCurrentOption
        if (index == highlightCurrentOption) {

        	// Set the bold and underline attributes for the highlighted item
    		attrset(A_BOLD | A_UNDERLINE);
 
            attron(A_REVERSE); // Turn on reverse video attribute
         
        }
        mvprintw(4 + index, CTR_POS(choices[index]), "%s", choices[index]);
        if (index == highlightCurrentOption) {

        	// Reset the text attributes for the rest of the items
    		attrset(A_NORMAL);
 
            attroff(A_REVERSE); // Turn off reverse video attribute
        }
    }
    
    
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
void keyPresses() 
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
    } else if (keyPressed == '5') {
        // Exit the program when the user selects "Exit"
        terminateProgram();
    } else if (keyPressed == '\n' && highlightCurrentOption >= 0 && highlightCurrentOption < numChoices) {
        // Execute code when user presses enter on the currently highlighted item
        if (highlightCurrentOption == 0) {
            // Execute code for "Start day" option
            // ...
        } else if (highlightCurrentOption == 1) {
            // Execute code for "Break" option
            // ...
        } else if (highlightCurrentOption == 2) {
            // Execute code for "End break" option
            // ...
        } else if (highlightCurrentOption == 3) {
            // Execute code for "End day" option
            // ...
        } else if (highlightCurrentOption == 4) {
            // Execute code for "Exit" option
            terminateProgram();
        }
    }

    // Navigate the menu to the current highlighted option
    navigateMenu(highlightCurrentOption);
}

// function to run menu 
void runProgram () 
{
	// initialize ncurses, initialize terminal environment, initialize menu
	initialNcurses();	
	
	// infinite loop to run menu
	while(1)
	{
		// Print the menu initially
		printMenu();
		
		// check for user key presses to navigate in the menu
		keyPresses();
	}
}

int main()
{

	// function to run menu 
	runProgram();

    return 0;
}



