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

#define CTR_POS(x) ((COLS - strlen(x)) / 2)

char *choices[] = {
    "Start day",
    "Break",
    "End break",
    "End day",
    "Exit",
};

void printMenu()
{
	// Print the title of the menu: (row,built-int print-function(string),string format, the string)
	char *title = "Time Tracing Menu";
    mvprintw(0, CTR_POS(title), "%s", title);
    
    // Print the selection prompt
    mvprintw(2, CTR_POS("Select an option"), "Select an option");

	// Print the menu items: (row,built-int print-function(string),string format, the string)
    for (int index = 0; index < 5; index++) {
        mvprintw(4 + index, CTR_POS(choices[index]), "%s", choices[index]);
    }
    
    // Refresh the screen to show the menu items
    refresh();
}

int main()
{
    // Initialize ncurses
    initscr();

   	/*
   	RETURN DRAWING PAGE TO HERE IN SAME ORDER AS IT IS IN THE FUNCTION IF NECESSARY
   	*/
    
    // TESTING BELOW ----------------------
    // Get the number of menu items
    int numChoices = sizeof(choices) / sizeof(char *);
    
    // the key user pressed at any given time, start at top menu item
    int keyPressed = 0;
    
    // Initialize the highlight to the first choice
    int highlightCurrentOption = 0;

	
    // Loop until the user selects "Exit"
    while (1) {
    
    	// get user input
        keyPressed = getch();
        
        for (int index = 0; index < 5; index++) {
            if (index == highlightCurrentOption) {
                attron(A_REVERSE);
            }
            printMenu();
            attroff(A_REVERSE);
        }
        
        
        if (keyPressed == KEY_UP) {
        	// Move selection up
        	
    	} else if (keyPressed == KEY_DOWN) {
        	// Move selection down
    	}
    }
    
    // TESTING ABOVE -----------------------
    
    

    // Wait for user input
    getch();
    
    

    // End program
    endwin();

    return 0;
}



