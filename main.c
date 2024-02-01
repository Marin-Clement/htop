#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ncurses.h>

struct Process {
    char pid[16];
    char command[256];
};

void afficher_processus() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du répertoire /proc");
        exit(EXIT_FAILURE);
    }

    mvprintw(2, 0, "PID\tNom du Processus");
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

int main() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    int ch;
    while (1) {
        clear();

        mvprintw(0, 0, "Liste des processus :");
        afficher_processus();

        mvprintw(LINES - 2, 0, "Appuyez sur 'q' pour quitter. Appuyez sur 'r' pour rafraîchir.");

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
