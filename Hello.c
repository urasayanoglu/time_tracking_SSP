//
// Created by jkh on 4/15/23.
//

#include <ncurses.h>
#include <ncursesw/menu.h>
#include <stdlib.h>

int main()
{
    // ncurses initialization
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Define menu items
    char *menu_items[] = {"Option 1", "Option 2", "Option 3"};
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);

    // Create menu
    MENU *menu = new_menu((ITEM **)menu_items);

    // Create a window to display menu
    WINDOW *win = newwin(num_items + 2, 40, (LINES - num_items) / 2, (COLS - 40) / 2);
    keypad(win, TRUE);
    box(win, 0, 0);
    refresh();
    wrefresh(win);

    // Set menu options
    set_menu_win(menu, win);
    set_menu_sub(menu, derwin(win, num_items, 38, 1, 1));
    set_menu_format(menu, num_items, 1);
    post_menu(menu);

    // Loop to handle menu selections
    int ch;
    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10: // Enter key
            {
                ITEM *cur_item = current_item(menu);
                int iten_index = item_index(cur_item);
                mvprintw(num_items + 3, 0, "Selected: %s", menu_items[iten_index]);
                refresh();
            }
                break;
        }
    }

    // Clean up
    unpost_menu(menu);
    free_menu(menu);
    for (int i = 0; i < num_items; ++i) {
        free(menu_items[i]);
    }
    endwin();

    return 0;
}