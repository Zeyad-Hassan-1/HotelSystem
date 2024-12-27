#include <windows.h>
#include <stdio.h>
#include <conio.h>

void textcolor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBox(int x, int y, int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = 0; i < width; i++) {
        gotoxy(x+i, y);
        printf("-");
        gotoxy(x+i, y+height);
        printf("-");
    }
    for(int i = 0; i < height; i++) {
        gotoxy(x, y+i);
        printf("|");
        gotoxy(x+width, y+i);
        printf("|");
    }
}

void clearScreen() {
    system("cls");
}

void printCentered(const char *text, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width;
    
    // Get the actual console window info
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    
    int len = strlen(text);
    int x = (width - len) / 2;
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
    printf("%s", text);
}