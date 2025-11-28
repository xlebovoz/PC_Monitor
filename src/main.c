#include "../include/monitor.h"

void show_menu() {
    system("cls");
    printf("=== PC MONITOR ===\n");
    printf("1. Информация о CPU\n");
    printf("2. Информация о памяти\n");
    printf("3. Выход\n");
    printf("Выбор: ");
}

int main() {
    SetConsoleOutputCP(65001);
    
    int choice;
    while(1) {
        show_menu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: show_cpu_info(); break;
            case 2: show_memory_info(); break;
            case 3: return 0;
            default: printf("Неверный выбор!\n");
        }
        printf("\nНажмите Enter...");
        getchar(); getchar();
    }
    return 0;
}