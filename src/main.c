#include <ncurses.h>
#include "process_viewer.h"

int main() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    int ch;
    while (1) {
        clear();

        mvprintw(0, 0, "Process List");
        afficher_processus();

        mvprintw(LINES - 2, 0, "Press 'q' to quit or 'r' to refresh");

        refresh();

        ch = getch();

        // Handle user input
        if (ch == 'q' || ch == 'Q') {
            break;
        } else if (ch == 'r' || ch == 'R') {
            afficher_processus();
        }
    }

    endwin();
    return 0;
}
