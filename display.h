// display.h

#ifndef DISPLAY_H
#define DISPLAY_H

#include "processes.h"
#include "system_info.h"

#include <ncurses.h>

#define MAX_PROCESSES_DISPLAYED 20
#define MAX_RAM_BAR_WIDTH 50
#define MAX_CPU_BAR_WIDTH 50
#define MAX_INPUT_LEN 50

void display_processes(ProcessInfo *processes, int start_index, int total_processes, int current_sort);
void display_ram_bar(RAMInfo ramInfo);
void display_cpu_bar(float cpu_usage);
void display_banner(int current_sort, int pid_sort_order, int name_sort_order, int memory_sort_order);
void display_popup(const char *title, const char *prompt, char *input);

#endif // DISPLAY_H
