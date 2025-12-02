#include "../include/monitor.h"
#include <conio.h>

void print_disk_bar(int percentage, int length) {
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

void show_disk_info() {
    printf("=== ИНФОРМАЦИЯ О ДИСКАХ ===\n");
    printf("\n");
    
    DWORD drives = GetLogicalDrives();
    char driveLetter[] = "A:";
    char drivePath[] = "A:\\";
    
    printf("Доступные диски:\n");
    printf("=================\n");
    
    for(char letter = 'A'; letter <= 'Z'; letter++) {
        if(drives & 1) {
            driveLetter[0] = letter;
            drivePath[0] = letter;
            
            DWORD sectorsPerCluster, bytesPerSector;
            DWORD freeClusters, totalClusters;
            
            if(GetDiskFreeSpace(drivePath, 
                              &sectorsPerCluster, 
                              &bytesPerSector, 
                              &freeClusters, 
                              &totalClusters)) {
                
                // Вычисляем размеры
                DWORDLONG totalSize = (DWORDLONG)totalClusters * 
                                     sectorsPerCluster * 
                                     bytesPerSector;
                DWORDLONG freeSize = (DWORDLONG)freeClusters * 
                                    sectorsPerCluster * 
                                    bytesPerSector;
                DWORDLONG usedSize = totalSize - freeSize;
                
                // Конвертируем в GB
                double totalGB = totalSize / (1024.0 * 1024.0 * 1024.0);
                double freeGB = freeSize / (1024.0 * 1024.0 * 1024.0);
                double usedGB = usedSize / (1024.0 * 1024.0 * 1024.0);
                int usagePercent = (int)((usedSize * 100) / totalSize);
                
                // Тип диска
                UINT driveType = GetDriveType(drivePath);
                char* typeStr;
                switch(driveType) {
                    case DRIVE_FIXED: typeStr = "Жесткий диск"; break;
                    case DRIVE_REMOVABLE: typeStr = "Съемный диск"; break;
                    case DRIVE_CDROM: typeStr = "CD/DVD"; break;
                    case DRIVE_REMOTE: typeStr = "Сетевой диск"; break;
                    case DRIVE_RAMDISK: typeStr = "RAM диск"; break;
                    default: typeStr = "Неизвестно";
                }
                
                // Выводим информацию
                printf("\nДиск %s (%s)\n", driveLetter, typeStr);
                printf("  Всего места:   %.2f GB\n", totalGB);
                printf("  Использовано:  %.2f GB\n", usedGB);
                printf("  Свободно:      %.2f GB\n", freeGB);
                printf("  Заполнение:    ");
                print_disk_bar(usagePercent, 20);
                printf("\n");
            }
        }
        drives >>= 1;
    }
    
    printf("\n\nНажмите любую клавишу для выхода...");
    getch();
}