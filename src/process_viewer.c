#include "process_viewer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficher_processus() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Error while opening /proc");
        exit(EXIT_FAILURE);
    }

    mvprintw(2, 0, "PID\tCOMMAND");
    mvprintw(3, 0, "---------------------");

    int ligne = 4;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0) {
            char path[256];
            snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);

            FILE *comm_file = fopen(path, "r");
            if (comm_file != NULL) {
                struct Process current_process;

                strcpy(current_process.pid, entry->d_name);

                fgets(current_process.command, sizeof(current_process.command), comm_file);
                fclose(comm_file);

                mvprintw(ligne++, 0, "%s\t%s", current_process.pid, current_process.command);
            }
        }
    }

    closedir(dir);
}
