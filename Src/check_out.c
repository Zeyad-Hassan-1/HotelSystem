#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "./headerFiles/reservations.h"
#include "./headerFiles/editReservations.h"
#include "./headerFiles/colors.h"


void changereservation(int roomId)
{
    FILE *reservationFile = fopen("output/Reservations.txt", "r");
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
        char *token;
        token = strtok(line, ",");
        customers[i].reservationID = atol(token);
        
        token = strtok(NULL, ",");
        customers[i].room_id = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(customers[i].status, token);
        
        token = strtok(NULL, ",");
        strcpy(customers[i].name, token);
        
        token = strtok(NULL, ",");
        strcpy(customers[i].nationalId, token);
        
        token = strtok(NULL, ",");
        customers[i].numberOfnights = atoi(token);
        
        token = strtok(NULL, "-");
        customers[i].day = atoi(token);
        token = strtok(NULL, "-");
        customers[i].month = atoi(token);
        token = strtok(NULL, ",");
        customers[i].year = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(customers[i].email, token);
        
        token = strtok(NULL, "\n");
        strcpy(customers[i].phone, token);

        if (customers[i].room_id == roomId)
        {
            deleted_line = i;
        }
        i++;
    }
    fclose(reservationFile);

    reservationFile = fopen("output/Reservations.txt", "w");
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

void checkOut()
{
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

    reservationFile = fopen("output/Reservations.txt", "r");
    if (reservationFile == NULL)
    {
        textcolor(RED);
        printf("Error opening file.\n");
        textcolor(LIGHTGRAY);
        return;
    }

    while (fgets(line1, sizeof(line1), reservationFile))
    {
        char *token;
        token = strtok(line1, ",");
        customers.reservationID = atol(token);
        
        token = strtok(NULL, ",");
        customers.room_id = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(customers.status, token);
        
        token = strtok(NULL, ",");
        strcpy(customers.name, token);
        
        token = strtok(NULL, ",");
        strcpy(customers.nationalId, token);
        
        token = strtok(NULL, ",");
        customers.numberOfnights = atoi(token);
        
        token = strtok(NULL, "-");
        customers.day = atoi(token);
        token = strtok(NULL, "-");
        customers.month = atoi(token);
        token = strtok(NULL, ",");
        customers.year = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(customers.email, token);
        
        token = strtok(NULL, "\n");
        strcpy(customers.phone, token);

        if (customers.room_id == room_number && strcmp(customers.status, "confirmed") == 0)
        {
            found = 1;
            no_of_nights = customers.numberOfnights;
            changeRoomStat(room_number);
            break;
        }
    }

    roomFile = fopen("output/Room.txt", "r");
    while (fgets(line1, sizeof(line1), roomFile) && no_of_nights > 0)
    {
        char *token;
        token = strtok(line1, " ");
        room.room_id = atoi(token);
        
        token = strtok(NULL, " ");
        strcpy(room.status, token);
        
        token = strtok(NULL, " ");
        strcpy(room.category, token);
        
        token = strtok(NULL, "\n");
        room.price = atoi(token);

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
    _getch();
}