#include "../include/monitor.h"

void show_menu() {
    system("cls");
    printf("=== PC MONITOR ===\n");
    printf("1. Real-time мониторинг CPU\n");
    printf("2. Real-time мониторинг памяти\n");
    printf("3. Информация о дисках\n");
    printf("4. Выход\n");
    printf("Выбор: ");
}

int main() {
    SetConsoleOutputCP(65001);
    
    int choice;
    while(1) {
        show_menu();
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Очистка буфера
            printf("Ошибка ввода!\n");
            printf("\nНажмите Enter...");
            getchar();
            continue;
        }
        
        switch(choice) {
            case 1: show_cpu_info_real_time(); break;
            case 2: show_memory_info_real_time(); break;
            case 3: show_disk_info(); break;
            case 4: return 0;
            default: printf("Неверный выбор!\n");
        }
        printf("\nНажмите Enter...");
        while(getchar() != '\n'); // Очистка буфера
        getchar();
    }
    return 0;
}