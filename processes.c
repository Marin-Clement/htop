#include "processes.h"

int is_numeric(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int compare_by_pid(const void *a, const void *b) {
    const ProcessInfo *pa = (const ProcessInfo *)a;
    const ProcessInfo *pb = (const ProcessInfo *)b;
    int pid_a = atoi(pa->pid);
    int pid_b = atoi(pb->pid);
    return pid_sort_order * (pid_a - pid_b);
}

int compare_by_name(const void *a, const void *b) {
    const ProcessInfo *pa = (const ProcessInfo *)a;
    const ProcessInfo *pb = (const ProcessInfo *)b;
    return name_sort_order * strcasecmp(pa->name, pb->name);
}

int compare_by_memory(const void *a, const void *b) {
    const ProcessInfo *pa = (const ProcessInfo *)a;
    const ProcessInfo *pb = (const ProcessInfo *)b;
    return memory_sort_order * ((pa->memory > pb->memory) - (pa->memory < pb->memory));
}

char* get_process_name(const char *pid) {
    char path[MAX_PATH_LEN];
    snprintf(path, sizeof(path), "/proc/%s/comm", pid);

    FILE *file = fopen(path, "r");
    if (file) {
        static char name[MAX_NAME_LEN];
        fgets(name, MAX_NAME_LEN, file);
        fclose(file);

        size_t len = strlen(name);
        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '\0';
        }
        return name;
    }
    return NULL;
}

unsigned long get_process_memory(const char *pid) {
    char path[MAX_PATH_LEN];
    snprintf(path, sizeof(path), "/proc/%s/statm", pid);

    FILE *statm_file = fopen(path, "r");
    if (statm_file) {
        unsigned long mem_pages;
        fscanf(statm_file, "%lu", &mem_pages);
        fclose(statm_file);
        return mem_pages * 4;
    }
    return 0;
}

void update_processes(ProcessInfo *processes, int *total_processes) {
    DIR *dir;
    struct dirent *entry;
    dir = opendir("/proc");
    if (dir == NULL) {
        printf("Erreur lors de l'ouverture de /proc\n");
        exit(1);
    }

    *total_processes = 0;
    int process_count = 0;
    while ((entry = readdir(dir)) != NULL && process_count < MAX_TOTAL_PROCESSES) {
        if (is_numeric(entry->d_name)) {
            strncpy(processes[process_count].pid, entry->d_name, MAX_NAME_LEN);
            processes[process_count].pid[MAX_NAME_LEN - 1] = '\0';
            char* process_name = get_process_name(entry->d_name);
            if (process_name) {
                strncpy(processes[process_count].name, process_name, MAX_NAME_LEN);
            } else {
                strncpy(processes[process_count].name, "N/A", MAX_NAME_LEN);
            }
            processes[process_count].memory = get_process_memory(entry->d_name);
            (*total_processes)++;
            process_count++;
        }
    }
    closedir(dir);
}

void sort_processes(ProcessInfo *processes, int total_processes, int current_sort) {
    int (*compare_function)(const void *, const void *);
    switch (current_sort) {
        case 0:
            compare_function = compare_by_pid;
            break;
        case 1:
            compare_function = compare_by_name;
            break;
        case 2:
            compare_function = compare_by_memory;
            break;
        default:
            compare_function = compare_by_pid;
            break;
    }
    qsort(processes, total_processes, sizeof(ProcessInfo), compare_function);
}

void kill_process(const char *pid) {
    char command[MAX_PATH_LEN];
    snprintf(command, sizeof(command), "kill -9 %s", pid);
    system(command);
}