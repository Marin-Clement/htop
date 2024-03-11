#include "cpu_info.h"

float get_cpu_usage() {
    FILE *file = fopen("/proc/stat", "r");
    if (file == NULL) {
        perror("Error opening /proc/stat file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    fgets(line, sizeof(line), file);

    int user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    sscanf(line, "cpu %d %d %d %d %d %d %d %d %d %d", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);

    fclose(file);

    int prev_idle = idle + iowait;
    int prev_non_idle = user + nice + system + irq + softirq + steal;
    int prev_total = prev_idle + prev_non_idle;

    usleep(100000);

    file = fopen("/proc/stat", "r");
    if (file == NULL) {
        perror("Error opening /proc/stat file");
        exit(EXIT_FAILURE);
    }

    fgets(line, sizeof(line), file);
    sscanf(line, "cpu %d %d %d %d %d %d %d %d %d %d", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);

    fclose(file);

    int idle_time = idle + iowait;
    int non_idle_time = user + nice + system + irq + softirq + steal;
    int total_time = idle_time + non_idle_time;

    float total_diff = (float)(total_time - prev_total);
    float idle_diff = (float)(idle_time - prev_idle);

    return 100.0 * (total_diff - idle_diff) / total_diff;
}