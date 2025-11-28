#include "../include/monitor.h"

void show_cpu_info() {
    printf("\n=== ИНФОРМАЦИЯ О CPU ===\n");
    
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    
    printf("Архитектура: ");
    switch(sysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            printf("x64 (64-битная)\n"); break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            printf("x86 (32-битная)\n"); break;
        case PROCESSOR_ARCHITECTURE_ARM:
            printf("ARM\n"); break;
        default:
            printf("Неизвестно\n");
    }
    
    printf("Тип процессора: %d\n", sysInfo.dwProcessorType);
    printf("Количество ядер: %d\n", sysInfo.dwNumberOfProcessors);
    printf("Размер страницы: %d KB\n", sysInfo.dwPageSize / 1024);
    
    // Дополнительная информация о процессоре
    HKEY hKey;
    DWORD bufferSize = 255;
    char cpuName[255];
    
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if(RegQueryValueEx(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE)cpuName, &bufferSize) == ERROR_SUCCESS) {
            printf("Модель: %s\n", cpuName);
        }
        RegCloseKey(hKey);
    }
}