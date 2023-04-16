/*
 * File:        Timetrackingnc.c
 * Authors:     Uras Ayanoglu, Jan-Krister Helenius, Sebastian Sopola
 * Description: Time tracking project Ncurses interface
 */

#include <ncurses.h>
#include <ncursesw/menu.h>
#include <stdlib.h>

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


    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

    for(i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], choices[i]);
    my_items[n_choices] = (ITEM *)NULL;

    my_menu = new_menu((ITEM **)my_items);
    mvprintw(LINES - 2, 0, "F1 to Exit");
    post_menu(my_menu);
    refresh();

    while((c = getch()) != KEY_F(1))
    {   switch(c)
        {	case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
        }
    }

    free_item(my_items[0]);
    free_item(my_items[1]);
    free_menu(my_menu);
    endwin();
}
