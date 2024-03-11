// system_info.h

#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long totalMem;
    long freeMem;
    long buffers;
    long cached;
} RAMInfo;

void get_ram_info(RAMInfo *ramInfo);

#endif // SYSTEM_INFO_H