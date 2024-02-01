#include "process_viewer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_process() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Error while opening /proc");
        exit(EXIT_FAILURE);
    }

    attron(COLOR_PAIR(2));
    mvprintw(2, 0, "PID\tCOMMAND");
    attron(COLOR_PAIR(3));
    mvprintw(3, 0, "---------------------");
    attroff(COLOR_PAIR(3));

    int ligne = 4;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strtol(entry->d_name, NULL, 10) != 0) {
            char path[256];
            snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);

            FILE *comm_file = fopen(path, "r");
            if (comm_file != NULL) {
                struct Process current_process;

                long pid_value = strtol(entry->d_name, NULL, 10);
                snprintf(current_process.pid, sizeof(current_process.pid), "%ld", pid_value);

                fgets(current_process.command, sizeof(current_process.command), comm_file);
                fclose(comm_file);

                attron(COLOR_PAIR(1));
                mvprintw(ligne++, 0, "%s\t%s", current_process.pid, current_process.command);
                attroff(COLOR_PAIR(1));
            }
        }
    }

    closedir(dir);
}
