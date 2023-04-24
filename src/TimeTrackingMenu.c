/**

* @file Timetrackingnc.c
* @author Uras Ayanoglu
* @author Jan-Krister Helenius
* @author Sebastian Sopola
* @details This file contains the ncurses interface for the time tracking project.
* libncurses-dev is required to compile this file. For installation: sudo apt install libncurses-dev
* @brief Time tracking project Ncurses interface
*/

// required headers
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "action.h"
#include "Fileio.h"
#include "Fileio.c"

//constant definitions
#define USERFILENAME "userdata.tt"
#define ACTIONFILENAME "actiondata.tt"
#define CTR_POS(x) ((COLS - strlen(x)) / 2)

// Array containing the menu options
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

// Text blocks to be displayed beneath the menu
char infotext1[60] ="\n";
char infotext2[60] ="\n";
char infotext3[60] ="\n";

int userNumber = 0;

void clearMenu();
void printMenu(struct User *users);
void initialNcurses();
void navigateMenu(int highlightCurrentOption);
void terminateProgram();
void keyPresses(struct User *users, struct Action *actions);
void runProgram (struct User *users, struct Action *actions);
void setWindowStyle();
void printMainMenu();
struct User getUserInfo();
void continueToNextMenu(struct User user);
void runMainMenu();

/**

* @brief The main function of the program.
* @details This function starts the program by calling the runMainMenu function which runs the main menu.
* @return An integer value of 0 for successful execution and any non-zero value for unsuccessful execution.
*/
int main()
{

    runMainMenu();

    return 0;
}

/**

* @brief Clears the menu screen and prints the menu options.
* @note Should be called when the user wants to clear the menu and return to the initial state.
* @return void
*/
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


/**

* @brief Prints the menu with highlighted item based on user position in menu.
* @param[in] users Array of User structs
* @note Should be called when the user navigates in the menu, and the program draws the menu again with the changes to user position.
* @return void
*/
void printMenu(struct User *users)
{
    // Print the title of the menu: (row,built-int print-function(string),string format, the string)
    char *title = "Time Tracking Menu";
    mvprintw(0, CTR_POS(title), "%s", title);

    // Print the selection prompt
    mvprintw(2, CTR_POS("Select an option"), "Select an option");

    // This name is indexed with the very first one and
    //should be further implemented when we allow multiple users
    mvprintw(0,3, "Online: %s %s", users[userNumber].firstName,users[userNumber].lastName);


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

/**

* @brief Initializes ncurses and sets it up for use in the program.
* @details This function initializes the ncurses library by calling the initscr() function.
* It also enables cbreak mode to make button presses immediately available to the program.
* Additionally, it disables automatic printing of typed characters using noecho().
* Finally, it sets the stdscr screen up to receive special keys by calling the keypad() function with TRUE as the argument.
* @note This function should be called at the beginning of any program that uses ncurses.
* @return void
*/
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


/**

* @brief Allows user to navigate a menu by moving the cursor to the highlighted option.
* @param[in] highlightCurrentOption The index of the currently highlighted option in the menu.
* @details Function takes in the index of the currently highlighted option in the menu and calculates the corresponding
* row and column position of the option on the screen. It then moves the cursor to that position and refreshes the screen
* to show the updated cursor position.
* @return void
*/
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


/**

* @brief Terminates the program by ending ncurses mode and closing the program
* @return void
*/
void terminateProgram()
{
    // End ncurses mode
    endwin();

    // Close program
    exit(0);
}


/**

* @brief Check user key presses and execute corresponding code
* @param[in] users Pointer to an array of User structures
* @param[in] actions Pointer to an array of Action structures
* @return void
*/
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
            addAction(users[userNumber].ID, 0, actions, numActions);
            strcpy(infotext1, "Working\n");
            strcpy(infotext2, "\n");
            strcpy(infotext3, "\n");
        } else if (highlightCurrentOption == 1) {
            // Execute code for "Break" option
            addAction(users[userNumber].ID, 1, actions, numActions);
            strcpy(infotext1, "On break\n");
            strcpy(infotext2, "\n");
            strcpy(infotext3, "\n");
        } else if (highlightCurrentOption == 2) {
            // Execute code for "End break" option
            addAction(users[userNumber].ID, 0, actions, numActions);
            strcpy(infotext1, "Working\n");
            strcpy(infotext2, "\n");
            strcpy(infotext3, "\n");
        } else if (highlightCurrentOption == 3) {
            // Execute code for "End day" option
            addAction(users[userNumber].ID, 2, actions, numActions);
            strcpy(infotext1, "Day ended\n");
            strcpy(infotext2, "\n");
            strcpy(infotext3, "\n");
        } else if (highlightCurrentOption == 4) {
            // Execute code for "Report Day" option


            int hoursWorked = timeSpent(0, users[userNumber].ID, 0, 0, 0, actions) / 3600;
            int minutesWorked = (timeSpent(0, users[userNumber].ID, 0, 0, 0, actions) % 3600) * 60;
            int hoursBreak = timeSpent(1, users[userNumber].ID, 0, 0, 0, actions) / 3600;
            int minutesBreak = (timeSpent(1, users[userNumber].ID, 0, 0, 0, actions) % 3600) * 60;

            // Variable for storing integer as string before concatenation
            char intConversion[10] = "0";

            // Composes the displayed string, each line in its own variable to avoid formatting snafu
            sprintf(infotext1, "Today ");
            strcat(infotext1, users[userNumber].firstName);
            strcat(infotext1, " ");
            strcat(infotext1, users[userNumber].lastName);
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


/**

* @brief Runs the time tracking program and enters an infinite loop to display and navigate the menu
* @param[in] users Pointer to the array of users
* @param[in] actions Pointer to the array of actions
* @return void
*/
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

/**

* @brief Sets the window style by enabling colors and setting background and foreground colors.
* @details Function uses the ncurses library to enable colors and set the background and foreground colors
* of the standard screen to white on blue.
* @return void
*/
void setWindowStyle()
{
    // enable colors
    start_color();

    // set the background and foreground colors
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    wbkgd(stdscr, COLOR_PAIR(1));
}


/**

* @brief Prints the main menu with options to sign in.
* @details Function prints the title of the menu and the option to sign in with the user's name. The function refreshes the screen to show the menu items.
* @return void
*/
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



/**
* @brief Function to prompt user for first and last name and return a User struct
* @return struct User - User struct containing user information entered by the user
*/
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
    user.type = 0;										// initialize rest of the values accordingly
    user.ID = 0;
    user.status = 0;
    return user;										// return user struct which is then passed to continueToNextFunction after names
}														// were given


/**

* @brief Function to clear current menu and continue to the next one
* @details This function clears the current menu and initializes two static pointers to arrays: users and actions. It reads the tables from files USERFILENAME and ACTIONFILENAME, and if users is null, it allocates memory for a User struct and assigns the given user to the first element. Finally, it calls the runProgram() function with users and actions as arguments to run the Time Tracking Menu.
* @param[in] user A User struct containing the user information entered by the user in the previous menu.
* @return void
*/
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

    if (idxUser(user.firstName, user.lastName, users) == -1)
    {
        users = addUser(user.firstName, user.lastName, users);
        if (users != NULL)
        {
            userNumber = (sizeof(*users) / sizeof(users[0])) - 1;
        }
        else
        {
            exit(1);
        }
    }
    else
    {
        userNumber = idxUser(user.firstName, user.lastName, users);
    }

    // function to run Time Tracking Menu
    runProgram(users, actions);
}


/**

* @brief Function to run the main menu which directs user to TimeTrackingMenu after logging in
* @details Initializes ncurses, terminal environment and menu. Sets window style and prints the main menu.
* Prompts the user to enter their first and last name and returns a User struct. Then, it continues to
* the TimeTrackingMenu using the continueToNextMenu function. Ends ncurses mode at the end of the function.
* @return void
*/
void runMainMenu()
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


