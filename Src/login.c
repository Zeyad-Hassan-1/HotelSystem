// login.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "./headerFiles/login.h"
#include "./headerFiles/colors.h"

#define max_linelength 100

int check_info(char *username, char *password)
{
    FILE *f2;
    f2 = fopen("output/users.txt", "r");
    char line[max_linelength];
    char st_username[max_usernamelength];
    char st_password[max_passwordlength];
    
    if (f2 == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    while (fgets(line, sizeof(line), f2))
    {
        char *token = strtok(line, " ");
        strcpy(st_username, token);
        token = strtok(NULL, "\n");
        strcpy(st_password, token);
        
        if (strcmp(username, st_username) == 0 && strcmp(password, st_password) == 0)
        {
            fclose(f2);
            return 1;
        }
    }
    fclose(f2);
    return 0;
}

int login()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char username[20], password[20];
    int i;
    
    while (1)
    {
        system("cls");
        textcolor(LIGHTGRAY);
        printf("\n\n\t\tLOGIN SCREEN");
        printf("\n\n\t\tEnter username: ");
        scanf("%s", username);
        
        printf("\n\t\tEnter password: ");
        i = 0;
        while (1)
        {
            char ch = getch();
            if (ch == 13) // Enter key
            {
                password[i] = '\0';
                break;
            }
            else if (ch == 8 && i > 0) // Backspace
            {
                i--;
                printf("\b \b");
            }
            else if (i < 19 && ch != 8)
            {
                password[i++] = ch;
                printf("*");
            }
        }

        if (check_info(username, password))
        {
            system("cls");
            textcolor(GREEN);
            printf("\n\n\t\tLogin Successful!\n");
            textcolor(LIGHTGRAY);
            return 1;
        }
        else
        {
            textcolor(RED);
            printf("\n\n\t\tInvalid username or password!\n");
            textcolor(YELLOW);
            printf("\t\tPress any key to try again or ESC to exit...");
            textcolor(LIGHTGRAY);
            char ch = getch();
            if (ch == 27) // ESC key
                exit(0);
        }
    }
    return 0;
}