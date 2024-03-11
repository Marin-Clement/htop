#include "display.h"

void display_processes(ProcessInfo *processes, int start_index, int total_processes, int current_sort) {
    int row = 0;

    switch (current_sort) {
        case 0:
            attron(A_REVERSE);
            attron(COLOR_PAIR(1)); // Add this line to set color pair
            mvprintw(row, 0, "%-10s", "PID");
            attroff(A_REVERSE);
            attroff(COLOR_PAIR(1));
            printw(" %-25s %-15s", "NAME", "MEM");
            break;
        case 1:
            mvprintw(row, 0, "%-10s", "PID");
            attron(A_REVERSE);
            attron(COLOR_PAIR(1)); // Add this line to set color pair
            printw(" %-25s", "NAME");
            attroff(A_REVERSE);
            attroff(COLOR_PAIR(1));
            printw(" %-15s", "MEM");
            break;
        case 2:
            mvprintw(row, 0, "%-10s %-25s", "PID", "NAME");
            attron(A_REVERSE);
            attron(COLOR_PAIR(1)); // Add this line to set color pair
            printw(" %-15s", "MEM");
            attroff(A_REVERSE);
            attroff(COLOR_PAIR(1));
            break;
        default:
            mvprintw(row, 0, "%-10s %-25s %-15s", "PID", "NAME", "MEM");
            break;
    }

    row += 2;

    int end_index = start_index + MAX_PROCESSES_DISPLAYED;
    if (end_index > total_processes) {
        end_index = total_processes;
    }

    int show_scrollbar = total_processes > MAX_PROCESSES_DISPLAYED;

    for (int i = start_index; i < end_index; i++) {
        mvprintw(row, 0, "%-10s %-25s %-15lu", processes[i].pid, processes[i].name, processes[i].memory);
        row++;
    }

    if (show_scrollbar) {
        float scrollbar_position = (float)start_index / (total_processes - 19);
        int scrollbar_row = 2 + (int)(scrollbar_position * MAX_PROCESSES_DISPLAYED);
        mvprintw(scrollbar_row, 50, "||");
    }
}

void display_ram_bar(RAMInfo ramInfo) {
    float ram_percent = 100.0 - ((ramInfo.freeMem + ramInfo.buffers + ramInfo.cached) * 100.0 / ramInfo.totalMem);
    int bar_width = (int)(ram_percent / 100.0 * MAX_RAM_BAR_WIDTH);

    mvprintw(LINES - 4, 0, "Global RAM Usage: [");
    attron(A_REVERSE);
    attron(COLOR_PAIR(2));
    for (int i = 0; i < MAX_RAM_BAR_WIDTH; i++) {
        if (i < bar_width) {
            printw("=");
        } else {
            printw(" ");
        }
    }
    attroff(A_REVERSE);
    attroff(COLOR_PAIR(2));
    printw("] %.2f%%", ram_percent);
}

void display_cpu_bar(float cpu_usage) {
    int bar_width = (int)(cpu_usage / 100.0 * MAX_CPU_BAR_WIDTH);

    mvprintw(LINES - 3, 0, "Global CPU Usage: [");
    attron(A_REVERSE);
    attron(COLOR_PAIR(2));
    for (int i = 0; i < MAX_CPU_BAR_WIDTH; i++) {
        if (i < bar_width) {
            printw("=");
        } else {
            printw(" ");
        }
    }
    attroff(A_REVERSE);
    attroff(COLOR_PAIR(2));
    printw("] %.2f%%", cpu_usage);
}

void display_banner(int current_sort, int pid_sort_order, int name_sort_order, int memory_sort_order) {
    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, " Sorting Order:");
    attroff(A_REVERSE);
    switch (current_sort) {
        case 0:
            printw(" PID %s | Name | Memory", pid_sort_order > 0 ? "^" : "v");
            break;
        case 1:
            printw(" PID | Name %s | Memory", name_sort_order > 0 ? "^" : "v");
            break;
        case 2:
            printw(" PID | Name | Memory %s", memory_sort_order > 0 ? "^" : "v");
            break;
        default:
            printw(" PID | Name | Memory");
            break;
    }
    printw(" | Use mouse to change sorting order | Press 'q' to quit | Press F1 to kill a process");
}

void display_popup(const char *title, const char *prompt, char *input) {
    int height = 10;
    int width = 40;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;

    WINDOW *popup = newwin(height, width, starty, startx);
    box(popup, 0, 0);

    mvwprintw(popup, 1, 1, title);
    mvwprintw(popup, 2, 1, prompt);

    wrefresh(popup);

    curs_set(1);
    echo();

    mvwgetnstr(popup, 3, 1, input, MAX_INPUT_LEN);

    curs_set(0);
    noecho();

    delwin(popup);
}