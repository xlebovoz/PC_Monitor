#include "../include/monitor.h"
#include <conio.h>

static void print_bar(int percentage, int length) {
    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;
    
    int bars = (percentage * length) / 100;
    printf("[");
    for(int i = 0; i < length; i++) {
        if(i < bars) printf("█");
        else printf("░");
    }
    printf("] %d%%", percentage);
}

void show_memory_info_real_time() {
    printf("=== REAL-TIME МОНИТОРИНГ ПАМЯТИ ===\n");
    printf("Нажми ESC для выхода\n\n");
    
    int frame = 0;
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    
    while(1) {
        if(_kbhit() && _getch() == 27) break;
        
        system("cls");
        printf("=== REAL-TIME МОНИТОРИНГ ПАМЯТИ (кадр %d) ===\n", ++frame);
        printf("Нажми ESC для выхода\n\n");
        
        if(GlobalMemoryStatusEx(&memInfo)) {
            DWORDLONG totalPhys = memInfo.ullTotalPhys / (1024 * 1024); // MB
            DWORDLONG freePhys = memInfo.ullAvailPhys / (1024 * 1024); // MB
            DWORDLONG usedPhys = totalPhys - freePhys;
            float usagePercent = memInfo.dwMemoryLoad;
            
            // Общая загрузка памяти
            printf("=== ОБЩАЯ ЗАГРУЗКА ПАМЯТИ ===\n");
            print_bar((int)usagePercent, 30);
            printf("\n\n");
            
            // Детальная информация
            printf("=== ДЕТАЛЬНАЯ ИНФОРМАЦИЯ ===\n");
            printf("Всего ОЗУ:        %lld MB\n", totalPhys);
            printf("Использовано:     %lld MB\n", usedPhys);
            printf("Свободно:         %lld MB\n", freePhys);
            printf("Загрузка:         %.1f%%\n", usagePercent);
            
            // Визуализация
            printf("\n=== ВИЗУАЛИЗАЦИЯ ===\n");
            printf("Использовано: ");
            print_bar((int)((usedPhys * 100) / totalPhys), 20);
            printf("\nСвободно:     ");
            print_bar((int)((freePhys * 100) / totalPhys), 20);
            
            // Файл подкачки (если есть)
            printf("\n\n=== ФАЙЛ ПОДКАЧКИ ===\n");
            printf("Всего:       %lld MB\n", memInfo.ullTotalPageFile / (1024 * 1024));
            printf("Использовано: %lld MB\n", (memInfo.ullTotalPageFile - memInfo.ullAvailPageFile) / (1024 * 1024));
            printf("Свободно:     %lld MB\n", memInfo.ullAvailPageFile / (1024 * 1024));
        }
        
        printf("\n\nОбновление: 500 мс | Время: %d сек", frame/2);
        
        Sleep(500); // Обновление 2 раза в секунду
    }
}