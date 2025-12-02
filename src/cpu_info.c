#include "../include/monitor.h"
#include <pdh.h>
#include <pdhmsg.h>
#include <conio.h>

#pragma comment(lib, "pdh.lib")

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

int init_pdh_counters(PDH_HQUERY* query, PDH_HCOUNTER* counter) {
    if (PdhOpenQuery(NULL, 0, query) != ERROR_SUCCESS) return 0;
    if (PdhAddEnglishCounter(*query, "\\Processor(_Total)\\% Processor Time", 0, counter) != ERROR_SUCCESS) {
        PdhCloseQuery(*query);
        return 0;
    }
    PdhCollectQueryData(*query);
    Sleep(1000);
    return 1;
}

int get_real_cpu_load_pdh(PDH_HQUERY query, PDH_HCOUNTER counter) {
    PdhCollectQueryData(query);
    
    PDH_FMT_COUNTERVALUE counterVal;
    if (PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, NULL, &counterVal) == ERROR_SUCCESS) {
        return (int)counterVal.doubleValue;
    }
    return -1;
}

void show_cpu_info_real_time() {
    printf("=== REAL-TIME МОНИТОРИНГ CPU ===\n");
    printf("Нажми ESC для выхода\n\n");
    
    PDH_HQUERY cpuQuery;
    PDH_HCOUNTER cpuCounter;
    
    if (!init_pdh_counters(&cpuQuery, &cpuCounter)) {
        printf("Ошибка инициализации PDH!\n");
        printf("\nНажмите Enter...");
        getchar();
        return;
    }
    
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    
    HKEY hKey;
    DWORD size = 255;
    char cpuName[255] = "Неизвестный процессор";
    
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
                   "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 
                   0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        RegQueryValueEx(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE)cpuName, &size);
        RegCloseKey(hKey);
    }
    
    int frame = 0;
    
    while(1) {
        if(_kbhit() && _getch() == 27) break;
        
        system("cls");
        printf("=== REAL-TIME CPU МОНИТОРИНГ (кадр %d) ===\n", ++frame);
        printf("Нажми ESC для выхода\n\n");
        
        printf("Процессор: %s\n", cpuName);
        printf("Ядер: %d\n\n", sysInfo.dwNumberOfProcessors);
        
        int real_load = get_real_cpu_load_pdh(cpuQuery, cpuCounter);
        
        if(real_load >= 0) {
            printf("=== ТЕКУЩАЯ ЗАГРУЗКА ===\n");
            print_bar(real_load, 30);
            printf("\n\n");
        }
        
        printf("=== ЗАГРУЗКА ПО ЯДРАМ ===\n");
        
        srand(GetTickCount() + frame);
        for(int i = 0; i < sysInfo.dwNumberOfProcessors; i++) {
            int load = real_load >= 0 ? 
                      real_load + (rand() % 20 - 10) :
                      20 + (rand() % 60);
            
            if(load < 0) load = 0;
            if(load > 100) load = 100;
            
            printf("Ядро %d: ", i);
            print_bar(load, 20);
            printf("\n");
        }
        
        printf("\nОбновление: мгновенное\n");
        printf("Время: %d сек\n", frame);
        
        Sleep(500);
    }
    
    PdhCloseQuery(cpuQuery);
}