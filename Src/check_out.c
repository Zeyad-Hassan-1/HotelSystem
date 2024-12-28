#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "./headerFiles/reservations.h"
#include "./headerFiles/editReservations.h"
#include "./headerFiles/colors.h"
#include "./headerFiles/Load.h"


void changereservation(int roomId)
{
    FILE *reservationFile = fopen("output/reservations.txt", "r");
    if (!reservationFile)
    {
        textcolor(RED);
        printf("Error opening file\n");
        textcolor(LIGHTGRAY);
        exit(EXIT_FAILURE);
    }

    char line[200];
    Customer customers[200];
    int i = 0, deleted_line;
    while (fgets(line, 200, reservationFile))
    {
        customers[i] = separateResLine(line);

        if (customers[i].room_id == roomId)
        {
            deleted_line = i;
        }
        i++;
    }
    fclose(reservationFile);

    reservationFile = fopen("output/reservations.txt", "w");
    int j = 0;
    while (j < i)
    {
        if (j != deleted_line)
        {
            fprintf(reservationFile, "%ld,%d,%s,%s,%s,%d,%02d-%02d-%02d,%s,%s\n", 
                customers[j].reservationID, customers[j].room_id, 
                customers[j].status, customers[j].name, customers[j].nationalId, 
                customers[j].numberOfnights, customers[j].day, customers[j].month, 
                customers[j].year, customers[j].email, customers[j].phone);
        }
        j++;
    }
    fclose(reservationFile);
}

void checkOut(){
    system("cls");

    FILE *reservationFile, *roomFile;
    int no_of_nights = 0, room_number, found = 0;
    int price;
    char line1[200];
    int total_bill;
    Customer customers;
    Room room;
    int receipt;

    printf("Enter the room number to check out: ");
    scanf("%d", &room_number);

    reservationFile = fopen("output/reservations.txt", "r");
    if (reservationFile == NULL)
    {
        textcolor(RED);
        printf("Error opening file.\n");
        textcolor(LIGHTGRAY);
        return;
    }

    while (fgets(line1, sizeof(line1), reservationFile))
    {
        customers = separateResLine(line1);

        if (customers.room_id == room_number && strcmp(customers.status, "confirmed") == 0)
        {
            printf("Do you want to check out?\n");
            printf("Press 'c' to cancel.... or any other key to confirm\n");
            if(!save()){
                fclose(reservationFile);
                return;
            }
            found = 1;
            no_of_nights = customers.numberOfnights;
            changeRoomStat(room_number);
            break;
        }
    }

    roomFile = fopen("output/Room.txt", "r");
    while (fgets(line1, sizeof(line1), roomFile) && no_of_nights > 0)
    {
        room = separateRoomLine(line1);

        if (room.room_id == room_number)
        {
            price = room.price;
            break;
        }
    }

    fclose(reservationFile);
    fclose(roomFile);

    if (found)
    {
        textcolor(LIGHTGREEN);
        printf("\nCheck-out completed for room %d.\n", room_number);
        printf("Number of nights: %d\n", no_of_nights);
        printf("Price per night: $%d\n", price);
        receipt = no_of_nights * price;
        printf("Your receipt total: $%d\n", receipt);
        textcolor(LIGHTGRAY);
        changereservation(room_number);
    }
    else
    {
        textcolor(RED);
        printf("\nNo confirmed reservation found for room %d.\n", room_number);
        textcolor(LIGHTGRAY);
    }

    printf("\nPress any key to continue...");
    getch();
}
