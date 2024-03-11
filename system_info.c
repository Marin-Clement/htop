#include "system_info.h"

void get_ram_info(RAMInfo *ramInfo) {
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        perror("Error opening /proc/meminfo file");
        exit(EXIT_FAILURE);
    }

    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "MemTotal: %ld kB", &ramInfo->totalMem) == 1) {
            continue;
        } else if (sscanf(line, "MemFree: %ld kB", &ramInfo->freeMem) == 1) {
            continue;
        } else if (sscanf(line, "Buffers: %ld kB", &ramInfo->buffers) == 1) {
            continue;
        } else if (sscanf(line, "Cached: %ld kB", &ramInfo->cached) == 1) {
            break;
        }
    }

    fclose(file);
}