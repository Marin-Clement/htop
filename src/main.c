#include <ncurses.h>
#include "process_viewer.h"

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    raw();
    keypad(stdscr, TRUE);
    int ch;
    while (1) {
        clear();
        show_process();

        attron(COLOR_PAIR(4));
        mvprintw(LINES - 2, 0, "Press 'q' to quit or 'r' to refresh");
        attroff(COLOR_PAIR(4));

        refresh();

        ch = getch();

        if (ch == 'q' || ch == 'Q') {
            break;
        } else if (ch == 'r' || ch == 'R') {
            show_process();
        }
    }

    endwin();
    return 0;
}
