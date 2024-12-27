#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "./headerFiles/reservations.h"
#include "./headerFiles/validation.h"
#include "./headerFiles/editReservations.h"
#include "./headerFiles/sorting.h"
#include "./headerFiles/colors.h"

long generateUniqueID()
{
    time_t now = time(NULL);
    return now % 100000000;
}

int RoomReservation(int stat, long resID, char *nId)
{
    Customer cst;
    
    printf("Enter number of nights: ");
    while (scanf("%d", &cst.numberOfnights) != 1 || !is_valid_nights(cst.numberOfnights))
    {
        textcolor(YELLOW);
        printf("Please Enter A valid number of nights from 1 to 30 ...\n");
        while (getchar() != '\n'); // Clear input buffer
        textcolor(LIGHTGRAY);
    }
    textcolor(LIGHTGRAY);
    
    printf("Enter day, month, year: ");
    while (scanf("%d %d %d", &cst.day, &cst.month, &cst.year) != 3 || !is_valid_date(cst.day, cst.month, cst.year))
    {
        textcolor(YELLOW);
        printf("Please Enter A valid check-in date in form of dd mm yyyy\n");
        while (getchar() != '\n'); // Clear input buffer
        textcolor(LIGHTGRAY);
    }
    textcolor(LIGHTGRAY);
    getchar();
    printf("Enter name: ");
    gets(cst.name);
    textcolor(YELLOW);
    while (!is_valid_name(cst.name))
    {
        printf("Please Enter A valid name...\n");
        gets(cst.name);
    }
    textcolor(LIGHTGRAY);

    if(nId != NULL)
        strcpy(cst.nationalId, nId);
    else
    {
        printf("Enter national ID: ");
        gets(cst.nationalId);
        textcolor(YELLOW);
        while (!is_valid_national_id(cst.nationalId))
        {
            printf("Please Enter A valid national ID....\n");
            gets(cst.nationalId);
        }
        textcolor(LIGHTGRAY);
    }

    printf("Enter email: ");
    gets(cst.email);
    textcolor(YELLOW);
    while (!is_valid_email(cst.email))
    {
        printf("Please Enter valid email ex:student@gmail.com\n");
        gets(cst.email);
    }
    textcolor(LIGHTGRAY);

    printf("Enter phone: ");
    gets(cst.phone);
    textcolor(YELLOW);
    while (!is_valid_phone(cst.phone))
    {
        printf("Please enter valid phone number containing at least 5 digits...\n");
        gets(cst.phone);
    }
    textcolor(LIGHTGRAY);

    textcolor(GREEN);
    printf("Select a category:\n1. SeaView\n2. GardenView\n3. LakeView\n");
    textcolor(LIGHTGRAY);

    int categoryChoice;
    do
    {
        categoryChoice = _getch() - '0';
        switch (categoryChoice)
        {
        case 1:
            strcpy(cst.catogary, "SeaView");
            break;
        case 2:
            strcpy(cst.catogary, "GardenView");
            break;
        case 3:
            strcpy(cst.catogary, "LakeView");
            break;
        default:
            textcolor(YELLOW);
            printf("Invalid choice! Please select a valid category.\n");
            textcolor(LIGHTGRAY);
        }
    } while (categoryChoice < 1 || categoryChoice > 3);

    FILE *fptr = fopen("output/Reservations.txt", "a");
    FILE *roomFile = fopen("output/Room.txt", "r");
    if (roomFile == NULL)
    {
        printf("Error: Could not open file.\n");
        exit(0);
    }

    char rooms[200];
    int found = 0;
    Room room;
    while (fgets(rooms, sizeof(rooms), roomFile))
    {
        char *token;
        token = strtok(rooms, " ");
        room.room_id = atoi(token);
        
        token = strtok(NULL, " ");
        strcpy(room.status, token);
        
        token = strtok(NULL, " ");
        strcpy(room.category, token);
        
        token = strtok(NULL, "\n");
        room.price = atoi(token);

        if (strcmp(room.status, "Available") == 0 && strcmp(room.category, cst.catogary) == 0)
        {
            cst.room_id = room.room_id;
            found = 1;
            break;
        }
    }
    fclose(roomFile);

    while (!found)
    {
        textcolor(YELLOW);
        printf("\nNo available room found for the selected category.\n");
        printf("Press 'c' to cancel reservation or any other key to choose another category.\n");
        textcolor(LIGHTGRAY);
        
        int choice = _getch();
        if (choice == 'c' || choice == 'C')
        {
            printf("Reservation cancelled.\n");
            return 0;
        }
        else
        {
            textcolor(GREEN);
            printf("Select a category:\n1. SeaView\n2. GardenView\n3. LakeView\n");
            textcolor(LIGHTGRAY);
            
            categoryChoice = _getch() - '0';

            switch (categoryChoice)
            {
            case 1:
                strcpy(cst.catogary, "SeaView");
                break;
            case 2:
                strcpy(cst.catogary, "GardenView");
                break;
            case 3:
                strcpy(cst.catogary, "LakeView");
                break;
            default:
                printf("Invalid choice! Defaulting to Standard.\n");
                strcpy(cst.catogary, "Standard");
                break;
            }

            roomFile = fopen("output/Room.txt", "r");
            if (roomFile == NULL)
            {
                printf("Error: Could not open file.\n");
                exit(0);
            }

            while (fgets(rooms, sizeof(rooms), roomFile))
            {
                Room room;

                sscanf(rooms, "%d %s %s %d", &room.room_id, room.status, room.category, &room.price);

                if (strcmp(room.status, "Available") == 0 && strcmp(room.category, cst.catogary) == 0)
                {
                    cst.room_id = room.room_id;
                    found = 1;
                    break;
                }
            }
            fclose(roomFile);
        }
    }

    changeRoomStat(cst.room_id);
    if(stat)
         strcpy(cst.status, "confirmed");
    else
        strcpy(cst.status, "unconfirmed");

    if(resID != 0)
        cst.reservationID = resID;
    else
        cst.reservationID = generateUniqueID();

    fprintf(fptr, "%ld,%d,%s,%s,%s,%d,%02d-%02d-%02d,%s,%s\n", cst.reservationID, cst.room_id, cst.status, cst.name, cst.nationalId, cst.numberOfnights, cst.day, cst.month, cst.year, cst.email, cst.phone);
    fclose(fptr);
    sort();
    return cst.room_id;
}

int validateCheckIn()
{
    long res_ID;
    int d, m, y;
    
    printf("Enter the reservation ID: ");
    scanf("%ld", &res_ID);
    printf("Enter the check-in date (day month year): ");
    scanf("%d %d %d", &d, &m, &y);
    char line1[200];
    FILE *fptr1 = fopen("output/Reservations.txt", "r");
    if (fptr1 == NULL)
    {
        printf("Error: Could not open Reservation.txt\n");
        return 0;
    }

    int room, found = 0, i = 0;
    Customer customers[200];
    while (fgets(line1, sizeof(line1), fptr1))
    {
        char *token;
        token = strtok(line1, ",");
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

        if (res_ID == customers[i].reservationID && d == customers[i].day && m == customers[i].month && y == customers[i].year)
        {
            strcpy(customers[i].status, "confirmed");
            found = 1;
        }

        i++;
    }

    fclose(fptr1);

    fptr1 = fopen("output/Reservations.txt", "w");
    int j = 0;
    while (j < i)
    {
        fprintf(fptr1, "%ld,%d,%s,%s,%s,%d,%02d-%02d-%02d,%s,%s\n", customers[j].reservationID, customers[j].room_id, customers[j].status, customers[j].name, customers[j].nationalId, customers[j].numberOfnights, customers[j].day, customers[j].month, customers[j].year, customers[j].email, customers[j].phone);
        j++;
    }
    fclose(fptr1);

    return found;
}
