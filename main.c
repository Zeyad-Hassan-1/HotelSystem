#include <stdlib.h>
#include <conio.h>
#include <windows.h>  // For color functions
#include "Src/headerFiles/menu.h"

int main()
{
    // Set console mode for special keys
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Define color constants
    enum {
        BLACK = 0,
        WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
        YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        RED = FOREGROUND_RED | FOREGROUND_INTENSITY,
        GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY
    };

    // Set initial text color to white on black
    SetConsoleTextAttribute(hConsole, WHITE);

    mainMenu();

    return 0;
}
