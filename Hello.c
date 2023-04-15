//
// Created by jkh on 4/15/23.
//

#include <ncurses.h>

int main()
{
    initscr();
    mvprintw(LINES / 2, (COLS - 12) / 2, "Hello, World!");
    refresh();
    getch();
    endwin();
    return 0;
}