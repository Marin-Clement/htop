// processes.h

#ifndef PROCESSES_H
#define PROCESSES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>

#define MAX_PATH_LEN 512
#define MAX_TOTAL_PROCESSES 256
#define MAX_NAME_LEN 256

typedef struct {
    char pid[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    unsigned long memory;
} ProcessInfo;

extern int pid_sort_order;
extern int name_sort_order;
extern int memory_sort_order;

void update_processes(ProcessInfo *processes, int *total_processes);
void sort_processes(ProcessInfo *processes, int total_processes, int current_sort);
void kill_process(const char *pid);
int is_numeric(const char *str);
int compare_by_pid(const void *a, const void *b);
int compare_by_name(const void *a, const void *b);
int compare_by_memory(const void *a, const void *b);

#endif // PROCESSES_H
