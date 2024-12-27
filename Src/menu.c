#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "./headerFiles/login.h"
#include "./headerFiles/reservations.h"
#include "./headerFiles/editReservations.h"
#include "./headerFiles/menu.h"
#include "./headerFiles/tracking.h"
#include "./headerFiles/checkOut.h"
#include "./headerFiles/colors.h"

// Global variables
int isLoggedIn = 0;

void secondaryMenu() {
    const char *choices[] = {
        "Reserve a Room",
        "Check-In",
        "Cancel Reservation",
        "Check-Out",
        "Check Room Availability",
        "View Customer Details",
        "Edit Reservation Details",
        "Query(Search)",
        "Reservation Report",
        "Exit"
    };
    int choice = 0;
    int numChoices = sizeof(choices) / sizeof(choices[0]);
    char key;

    while(1) {
        clearScreen();
        textcolor(WHITE);
        printCentered("Hotel Management System - Main Menu", 2);

        for(int i = 0; i < numChoices; i++) {
            if(i == choice) {
            textcolor(YELLOW);
            printCentered(choices[i], (i * 2) + 4);
            } else {
            textcolor(CYAN);
            printCentered(choices[i], (i * 2) + 4);
            }
        }

        key = getch();
        switch(key) {
            case 72: // Up arrow
                choice = (choice - 1 + numChoices) % numChoices;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % numChoices;
                break;
            case 13: // Enter
                clearScreen();
                switch(choice + 1) {
                    case 1:
                        RoomReservation(0, 0, NULL);
                        textcolor(GREEN);
                        printf("\nReservation saved!\n");
                        textcolor(WHITE);
                        break;
                    case 2:
                        printf("Check-In selected.\n");
                        if(validateCheckIn()) {
                            textcolor(GREEN);
                            printf("Your reservation was confirmed successfully.");
                            textcolor(WHITE);
                        } else {
                            textcolor(RED);
                            printf("Reservation not found or invalid details.\n");
                            textcolor(WHITE);
                        }
                        break;
                    case 3:
                        printf("Cancel Reservation Selected...\n");
                        long id;
                        printf("Enter reservation_id or Room_id...\n");
                        scanf("%ld", &id);
                        cancel(id, 0);
                        break;
                    case 4:
                        printf("Check-Out Selected...\n");
                        checkOut();
                        break;
                    case 5:
                        printf("Check Room Availability Selected...\n");
                        track();
                        break;
                    case 6:
                        printf("View Customer Details...\n");
                        ViewCustomerDetails();
                        break;
                    case 7:
                        printf("Edit Reservation Selected...\n");
                        edit();
                        break;
                    case 8:
                        printf("Query(Search) Selected...\n");
                        query();
                        break;
                    case 9:
                        printf("Reservation Report Selected...\n");
                        check_the_date();
                        break;
                    case 10:
                        printf("\nExiting the program...\n");
                        return;
                    default:
                        printf("Invalid choice!\n");
                        break;
                }
                printf("\nPress 'c' to go back to the menu or any other key to exit...");
                if(getch() != 'c') {
                    clearScreen();
                    printf("Exiting the program...\n");
                    return;
                }
                break;
        }
    }
}

void mainMenu() {
    const char *mainChoices[] = {
        "Login",
        "Quit"
    };
    int choice = 0;
    int numChoices = sizeof(mainChoices) / sizeof(mainChoices[0]);
    char key;

    while(!isLoggedIn) {
        clearScreen();
        textcolor(WHITE);
        printCentered("Hotel Management System", 2);

        for(int i = 0; i < numChoices; i++) {
            if(i == choice) {
                textcolor(YELLOW);
                printCentered(mainChoices[i], (i*2) + 4);
            } else {
                textcolor(LIGHTMAGENTA);
                printCentered(mainChoices[i], (i*2) + 4);
            }
        }

        key = getch();
        switch(key) {
            case 72: // Up arrow
                choice = (choice - 1 + numChoices) % numChoices;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % numChoices;
                break;
            case 13: // Enter
                clearScreen();
                switch(choice + 1) {
                    case 1:
                        printCentered("Login...", 13);
                        if(login()) {
                            isLoggedIn = 1;
                            textcolor(GREEN);
                            printCentered("Login successful! Redirecting...", 15);
                            textcolor(WHITE);
                            printCentered("Press any Key to continue...", 16);
                            getch();
                            secondaryMenu();
                            return;
                        } else {
                            textcolor(RED);
                            printCentered("Login failed. Try again.", 15);
                            textcolor(WHITE);
                        }
                        break;
                    case 2:
                        printCentered("Exiting the program...", 13);
                        return;
                }
                getch();
                break;
        }
    }
}
