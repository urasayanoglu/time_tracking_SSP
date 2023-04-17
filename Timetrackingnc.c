/*
 * File:        Timetrackingnc.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Time tracking project Ncurses interface
 */

// You may need to install a package like libncurse-dev to use these
// e.g. sudo apt install libncurses-dev
#include <ncurses.h>
#include <ncursesw/menu.h>
#include <stdlib.h>

#include "src/Fileio.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

char *choices[] = {
        "Choice 1",
        "Choice 2",
        "Choice 3",
        "Choice 4",
        "Exit",
};

int main()
{	ITEM **my_items = NULL;
    int c = 0;
    MENU *my_menu = NULL;
    int n_choices = 0, i = 0;
    ITEM *cur_item = NULL;

    // Initialize the terminal for ncurses
    initscr();

    // Cbreak mode  makes button presses immediately available to the program
    cbreak();

    // noecho() disables automatic printing of typed characters
    noecho();

    // sets the stdscr screen up to receive special keys
    keypad(stdscr, TRUE);

    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

    for(i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], choices[i]);
    my_items[n_choices] = (ITEM *)NULL;

    my_menu = new_menu((ITEM **)my_items);
    mvprintw(LINES - 2, 0, "ESC to Exit");
    post_menu(my_menu);
    refresh();

    while((c = getch()) != 27)
    {   switch(c)
        {	case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
        }
    }

    // ncurses functions to free up memory reserved by items and menus
    free_item(my_items[0]);
    free_item(my_items[1]);
    free_menu(my_menu);

    // Restores the terminal to its original state
    endwin();
}
