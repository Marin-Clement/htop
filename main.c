#include "cpu_info.h"
#include "display.h"


int pid_sort_order = 1;
int name_sort_order = -1;
int memory_sort_order = -1;

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    // Add this line to initialize color pairs
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_YELLOW);
    init_pair(2, COLOR_BLACK, COLOR_MAGENTA);

    int start_index = 0;
    int total_processes = 0;
    int current_sort = 0;
    ProcessInfo processes[MAX_TOTAL_PROCESSES];

    int ch;

    timeout(1000);  // Set a timeout of 1000 milliseconds

    do {
        clear();
        float cpu_usage = get_cpu_usage();
        RAMInfo ramInfo;
        get_ram_info(&ramInfo);
        update_processes(processes, &total_processes);
        sort_processes(processes, total_processes, current_sort);
        display_processes(processes, start_index, total_processes, current_sort);
        display_banner(current_sort, pid_sort_order, name_sort_order, memory_sort_order);
        display_ram_bar(ramInfo);
        display_cpu_bar(cpu_usage);
        refresh();

        // check if click on column header
        if ((ch = getch()) == KEY_MOUSE) {
            MEVENT event;
            if (getmouse(&event) == OK) {
                if (event.y == 0) {
                    if (event.x < 10) {
                        pid_sort_order *= -1;
                        current_sort = 0;
                    } else if (event.x < 35) {
                        name_sort_order *= -1;
                        current_sort = 1;
                    } else if (event.x < 50) {
                        memory_sort_order *= -1;
                        current_sort = 2;
                    }
                }
            }
        } else {
            switch (ch) {
                case KEY_UP:
                    if (start_index > 0) {
                        start_index--;
                    }
                    break;
                case KEY_DOWN:
                    if (start_index < total_processes - MAX_PROCESSES_DISPLAYED) {
                        start_index++;
                    }
                    break;
                case 'q':
                    break;
                case KEY_F(1):
                {
                    char input[30];
                    input[0] = '\0';
                    display_popup("Enter Process UUID", "PUUID:", input);
                    if (input[0] != '\0') {
                        kill_process(input);
                    }
                    break;
                }
                default:
                    break;
            }
        }

    } while (ch != 'q');

    endwin();

    return 0;
}
