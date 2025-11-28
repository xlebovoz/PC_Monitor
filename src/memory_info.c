#include "../include/monitor.h"

void show_memory_info() {
    printf("\n=== ИНФОРМАЦИЯ О ПАМЯТИ ===\n");
    
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    
    if(GlobalMemoryStatusEx(&memInfo)) {
        DWORDLONG totalPhys = memInfo.ullTotalPhys / 1024 / 1024;
        DWORDLONG freePhys = memInfo.ullAvailPhys / 1024 / 1024;
        DWORDLONG usedPhys = totalPhys - freePhys;
        
        printf("Оперативная память:\n");
        printf("  Всего: %lld MB\n", totalPhys);
        printf("  Использовано: %lld MB\n", usedPhys);
        printf("  Свободно: %lld MB\n", freePhys);
        printf("  Загрузка: %.1f%%\n", memInfo.dwMemoryLoad * 1.0);
    }
}