/*
 * File:        Timetrackingnc.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Time tracking project Ncurses interface
 */
 
 #include "TimeTrackingMenu.c"
 
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



// function to collect user name
void readUserName () 
{
	// wait for user input
    getch();
}

// function to allow change to next menu
void continueToNextMenu ()
{
	// function to be called when user want to clear menu 
	clearMenu();
	
	// function to run Time Tracking Menu
	runProgram();
}
 
 
 // main menu which is run when program is started
 int main ()
 {
 	// initialize ncurses, initialize terminal environment, initialize menu
	initialNcurses();

	setWindowStyle ();
	
	printMainMenu();


    // wait for user input
    if(getch())
    {
    continueToNextMenu();
    }

    // End ncurses mode, IMPORTANT; WITHOUT THIS WINDOW CRASHES AND/OR WORKS WEIRDLY
    endwin();

	
	return 0;
	 
 }
  
 
 
 
