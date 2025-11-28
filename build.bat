@echo off
echo Компиляция...
gcc -o PC_Monitor.exe src/main.c src/cpu_info.c src/memory_info.c -Iinclude
if exist PC_Monitor.exe (
    echo УСПЕХ!
    PC_Monitor.exe
) else (
    echo ОШИБКА!
)
pause