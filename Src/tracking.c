#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "./headerFiles/tracking.h"
#include "./headerFiles/colors.h"
#include "./headerFiles/reservations.h"
#include "./headerFiles/Load.h"

void track() {
    system("cls");
    
    FILE *room = fopen("output/Room.txt", "r");
    if (room == NULL) {
        printf("error opening file\n\n");
        exit(1);
    }

    drawBox(2, 2, 76, 20);
    
    char line[200];
    int y = 3;
    while (fgets(line, 200, room)) {
        gotoxy(4, y);
        textcolor(LIGHTGREEN);
        printf("%s", line);
        textcolor(LIGHTGRAY);
        y++;
    }

    fclose(room);
    printf("\nPress any key to continue...");
    getch();
}

void find_by_name(char *name) {
    system("cls");
    Customer customer;

    FILE *f = fopen("output/Reservations.txt", "r");
    if (f == NULL) {
        printf("error opening file\n\n");
        exit(1);
    }

    drawBox(2, 2, 76, 20);
    gotoxy(30, 3);
    printf("Customer Information");

    char line[1000];
    int found = 0;
    
    while (fgets(line, 1000, f)) {
        
        customer = separateResLine(line);

        if (strcasecmp(name, customer.name) == 0) {
            found = 1;
            textcolor(LIGHTGREEN);
            gotoxy(4, 5);
            printf("Name: %s", customer.name);
            gotoxy(4, 6);
            printf("Reservation ID: %d", customer.reservationID);
            gotoxy(4, 7);
            printf("Room ID: %d", customer.room_id);
            gotoxy(4, 8);
            printf("Reservation Status: %s", customer.status);
            gotoxy(4, 9);
            printf("Number of Nights: %d", customer.numberOfnights);
            gotoxy(4, 10);
            printf("Check-in Date: %d-%d-%d", customer.day, customer.month, customer.year);
            gotoxy(4, 11);
            printf("Email: %s", customer.email);
            gotoxy(4, 12);
            printf("National ID: %s", customer.nationalId);
            gotoxy(4, 13);
            printf("Mobile: %s", customer.phone);
            textcolor(LIGHTGRAY);
            break;
        }
    }

    if (!found) {
        gotoxy(30, 10);
        textcolor(YELLOW);
        printf("Customer not found");
        textcolor(LIGHTGRAY);
    }

    fclose(f);
}

int find_by_roomID(int rid) {
    system("cls");
    Room room;

    FILE *f = fopen("output/Room.txt", "r");
    if (f == NULL) {
        printf("error opening file\n\n");
        exit(1);
    }

    drawBox(2, 2, 76, 20);
    gotoxy(30, 3);
    printf("Room Information");

    char line[1000];
    int found = 0;
    
    while (fgets(line, 1000, f)) {
        room = separateRoomLine(line);

        if (rid == room.room_id) {
            found = 1;
            textcolor(LIGHTGREEN);
            gotoxy(4, 5);
            printf("Room ID: %d", room.room_id);
            gotoxy(4, 6);
            printf("Room State: %s", room.status);
            gotoxy(4, 7);
            printf("Room Category: %s", room.category);
            gotoxy(4, 8);
            printf("Room Price: %d", room.price);
            textcolor(LIGHTGRAY);

            if (strcmp(room.status, "Reserved") == 0) {
                Customer customer;

                FILE *fc = fopen("output/Reservations.txt", "r");
                if (fc == NULL) {
                    printf("error opening file\n\n");
                    exit(1);
                }

                char linec[1000];
                while (fgets(linec, 1000, fc)) {
                    customer = separateResLine(linec);
                    if (rid == customer.room_id) {
                        textcolor(LIGHTGREEN);
                        gotoxy(4, 10);
                        printf("Guest Name: %s", customer.name);
                        gotoxy(4, 11);
                        printf("Reservation ID: %d", customer.reservationID);
                        gotoxy(4, 12);
                        printf("Reservation Status: %s", customer.status);
                        gotoxy(4, 13);
                        printf("Number of Nights: %d", customer.numberOfnights);
                        gotoxy(4, 14);
                        printf("Check-in Date: %d-%d-%d", customer.day, customer.month, customer.year);
                        gotoxy(4, 15);
                        printf("Email: %s", customer.email);
                        gotoxy(4, 16);
                        printf("National ID: %s", customer.nationalId);
                        gotoxy(4, 17);
                        printf("Mobile: %s", customer.phone);
                        textcolor(LIGHTGRAY);
                        break;
                    }
                }
                fclose(fc);
            }
            break;
        }
    }

    if (!found) {
        gotoxy(30, 10);
        textcolor(YELLOW);
        printf("Room not found");
        textcolor(LIGHTGRAY);
    }

    fclose(f);
    return 0;
}

void statues_room(char *state) {
    system("cls");
    Room room;

    FILE *f = fopen("output/Room.txt", "r");
    if (f == NULL) {
        printf("error opening file\n\n");
        exit(1);
    }

    drawBox(2, 2, 76, 20);
    gotoxy(30, 3);
    printf("Room Status");

    char line[1000];
    int y = 5;
    
    while (fgets(line, 1000, f)) {
        room = separateRoomLine(line);

        if (strcmp(state, room.status) == 0) {
            textcolor(LIGHTGREEN);
            gotoxy(4, y++);
            printf("Room ID: %d", room.room_id);
            gotoxy(4, y++);
            printf("Room Category: %s", room.category);
            gotoxy(4, y++);
            printf("Room Price: %d", room.price);
            textcolor(LIGHTGRAY);
        }
    }

    fclose(f);
}

void query() {
    system("cls");

    drawBox(2, 2, 76, 20);
    gotoxy(30, 3);
    printf("Look Up Information");

    textcolor(LIGHTGREEN);
    gotoxy(4, 5);
    printf("1. Inquire about guest information by customer name");
    gotoxy(4, 6);
    printf("2. Inquire about room and guest information by room number");
    gotoxy(4, 7);
    printf("3. Inquire about available and reserved rooms by room state");
    gotoxy(4, 8);
    printf("What do you want: ");
    textcolor(LIGHTGRAY);

    int i = getch() - '0';

    if (i == 1) {
        char name[100];
        gotoxy(4, 10);
        printf("Enter the customer name: ");
        fflush(stdin);  // Clear input buffer
        gets(name);
        find_by_name(name);
    } else if (i == 2) {
        int rid;
        gotoxy(4, 10);
        printf("Enter the room number: ");
        scanf("%d", &rid);
        find_by_roomID(rid);
    } else if (i == 3) {
        char state[100];
        gotoxy(4, 10);
        printf("Enter 'a' for available rooms or 'r' for reserved rooms: ");
        int choose = getch();
        if (choose == 'a') {
            statues_room("Available");
        } else if (choose == 'r') {
            statues_room("Reserved");
        } else {
            gotoxy(4, 12);
            printf("This option not found\n\n");
        }
    } else {
        gotoxy(4, 12);
        printf("This option not found\n\n");
    }

    printf("\nPress any key to continue...");
    getch();
}

void check_the_date() {
    system("cls");
    Customer customer;

    FILE *f = fopen("output/Reservations.txt", "r");
    if (f == NULL) {
        printf("error opening file\n\n");
        exit(1);
    }

    int day, month, year;
    // drawBox(2, 2, 76, 20);
    gotoxy(30, 3);
    printf("Check the date for customer registration");

    gotoxy(4, 5);
    printf("day: ");
    scanf("%d", &day);
    gotoxy(4, 6);
    printf("month: ");
    scanf("%d", &month);
    gotoxy(4, 7);
    printf("year: ");
    scanf("%d", &year);

    char line[1000];
    int found = 0;
    int y = 9;

    while (fgets(line, 1000, f)) {
        customer = separateResLine(line);

        if (customer.day == day && customer.month == month && customer.year == year) {
            found = 1;
            textcolor(LIGHTGREEN);
            gotoxy(4, y++);
            printf("Name: %s", customer.name);
            gotoxy(4, y++);
            printf("Reservation ID: %d", customer.reservationID);
            gotoxy(4, y++);
            printf("Room ID: %d", customer.room_id);
            gotoxy(4, y++);
            printf("Reservation Status: %s", customer.status);
            gotoxy(4, y++);
            printf("Number of Nights: %d", customer.numberOfnights);
            gotoxy(4, y++);
            printf("Check-in Date: %d-%d-%d", customer.day, customer.month, customer.year);
            gotoxy(4, y++);
            printf("Email: %s", customer.email);
            gotoxy(4, y++);
            printf("National ID: %s", customer.nationalId);
            gotoxy(4, y++);
            printf("Mobile: %s", customer.phone);
            textcolor(LIGHTGRAY);
            gotoxy(4, y++);
            printf("-------------------------------------------------");
        }
    }

    if (!found) {
        gotoxy(30, 10);
        textcolor(YELLOW);
        printf("Customer not found");
        textcolor(LIGHTGRAY);
    }

    fclose(f);
    printf("\nPress any key to continue...");
    getch();
}
