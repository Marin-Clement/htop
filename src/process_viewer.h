#ifndef PROCESS_VIEWER_H
#define PROCESS_VIEWER_H

#include <dirent.h>
#include <ncurses.h>

struct Process {
    char pid[16];
    char command[256];
};

void show_process();

#endif
