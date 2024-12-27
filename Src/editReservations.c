#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "./headerFiles/reservations.h"
#include "./headerFiles/editReservations.h"
#include "./headerFiles/colors.h"

Customer ViewCustomerDetails()
{
    long id;
    textcolor(LIGHTGREEN);
    int y = 1;
    printf("Enter reservation id or room id to view your data..\n");
    textcolor(LIGHTGRAY);
    scanf("%ld", &id);
    FILE *file = fopen("output/Reservations.txt", "r");
    if (!file)
    {
        perror("Error opening Reservations.txt");
        exit(EXIT_FAILURE);
    }
    char line[200];
    int found = 0;
    while (fgets(line, 200, file))
    {
        Customer csv;
        char *token;
        
        token = strtok(line, ",");
        csv.reservationID = atol(token);
        
        token = strtok(NULL, ",");
        csv.room_id = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(csv.status, token);
        
        token = strtok(NULL, ",");
        strcpy(csv.name, token);
        
        token = strtok(NULL, ",");
        strcpy(csv.nationalId, token);
        
        token = strtok(NULL, ",");
        csv.numberOfnights = atoi(token);
        
        token = strtok(NULL, "-");
        csv.day = atoi(token);
        token = strtok(NULL, "-");
        csv.month = atoi(token);
        token = strtok(NULL, ",");
        csv.year = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(csv.email, token);
        
        token = strtok(NULL, "\n");
        strcpy(csv.phone, token);

        if (id == csv.reservationID || id == csv.room_id)
        {
            textcolor(LIGHTBLUE);
            printf("Name : %s \n Phone Number: %s \n Email: %s \n National Id: %s \n Number of Nights: %d \n Check in date : %02d %02d %02d\n\n", 
                   csv.name, csv.phone, csv.email, csv.nationalId, csv.numberOfnights, csv.day, csv.month, csv.year);
                   
            textcolor(LIGHTGRAY);
            fclose(file);
            return csv;
        }
    }
    fclose(file);
    textcolor(RED);
    printf("No reservation found with ID: %ld\n", id);
    textcolor(LIGHTGRAY);
    Customer emptyCustomer = {0};
    return emptyCustomer;
}

int changeRoomStat(int roomId)
{
    FILE *roomFile = fopen("output/Room.txt", "r");
    if (!roomFile)
    {
        perror("Error opening Room.txt");
        exit(EXIT_FAILURE);
    }

    char line[200];
    Room rooms[200];
    int i = 0, found = 0;
    while (fgets(line, 200, roomFile))
    {
        char *token;
        token = strtok(line, " ");
        rooms[i].room_id = atoi(token);
        
        token = strtok(NULL, " ");
        strcpy(rooms[i].status, token);
        
        token = strtok(NULL, " ");
        strcpy(rooms[i].category, token);
        
        token = strtok(NULL, "\n");
        rooms[i].price = atoi(token);

        if (rooms[i].room_id == roomId)
        {
            found = 1;
            if (!strcmp(rooms[i].status, "Reserved"))
                strcpy(rooms[i].status, "Available");
            else
                strcpy(rooms[i].status, "Reserved");
        }
        i++;
    }
    fclose(roomFile);
    roomFile = fopen("output/Room.txt", "w");
    if (!roomFile)
    {
        perror("Error opening Room.txt");
        exit(EXIT_FAILURE);
    }
    if (!found)
    {
        textcolor(RED);
        printf("Error room not found..\n");
        textcolor(LIGHTGRAY);
    }

    int j = 0;
    while (j < i)
    {
        fprintf(roomFile, "%d %s %s %d\n", rooms[j].room_id, rooms[j].status, rooms[j].category, rooms[j].price);
        j++;
    }
    fclose(roomFile);
    return found;
}

void cancel(long id, int edit)
{
    int room_id = 0, found = 0;
    int deletedLine;
    FILE *res = fopen("output/Reservations.txt", "r");
    if (!res)
    {
        perror("Error opening Reservations.txt");
        exit(EXIT_FAILURE);
    }

    char reservation[200];
    Customer customers[200];
    int i = 0;
    while (fgets(reservation, sizeof(reservation), res))
    {
        char *token;
        token = strtok(reservation, ",");
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

        if ((id == customers[i].reservationID || id == customers[i].room_id))
        {
            if (!strcmp(customers[i].status, "unconfirmed") || edit == 1)
            {
                found = 1;
                room_id = customers[i].room_id;
                deletedLine = i;
            }
        }
        i++;
    }

    fclose(res);

    if (!found)
    {
        textcolor(RED);
        printf("No reservation found with ID: %ld\n", id);
        textcolor(LIGHTGRAY);
        return;
    }

    res = fopen("output/Reservations.txt", "w");
    if (!res)
    {
        perror("Error opening Reservations.txt");
        exit(EXIT_FAILURE);
    }
    int j = 0;
    while (j < i)
    {
        if (j != deletedLine)
        {
            fprintf(res, "%ld,%d,%s,%s,%s,%d,%02d-%02d-%02d,%s,%s\n", 
                   customers[j].reservationID, customers[j].room_id, customers[j].status, 
                   customers[j].name, customers[j].nationalId, customers[j].numberOfnights, 
                   customers[j].day, customers[j].month, customers[j].year, 
                   customers[j].email, customers[j].phone);
        }
        j++;
    }

    fclose(res);
    if (edit == 0)
    {
        textcolor(RED);
        printf("Reservation cancelled and file updated successfully.\n");
        textcolor(LIGHTGRAY);
    }

    if (room_id)
    {
        changeRoomStat(room_id);
    }
}

int save()
{
    printf("Do you want to save the edits?\n");
    printf("Press 'c' to cancel or any other key to save\n");
    int choose = getch();
    switch (choose)
    {
    case 'c':
        return 0;

    default:
        return 1;
    }
}

void edit()
{
    long id;
    FILE *res = fopen("output/Reservations.txt", "r");
    if (!res)
    {
        perror("Error opening Reservations.txt");
        exit(EXIT_FAILURE);
    }
    printf("Please enter reservation id or room id...\n");
    scanf("%ld", &id);
    char line[200];
    Customer cust;
    int stat = 0;
    int found = 0;
    while (fgets(line, 200, res))
    {
        char *token;
        token = strtok(line, ",");
        cust.reservationID = atol(token);
        
        token = strtok(NULL, ",");
        cust.room_id = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(cust.status, token);
        
        token = strtok(NULL, ",");
        strcpy(cust.name, token);
        
        token = strtok(NULL, ",");
        strcpy(cust.nationalId, token);
        
        token = strtok(NULL, ","); 
        cust.numberOfnights = atoi(token);
        
        token = strtok(NULL, "-");
        cust.day = atoi(token);
        token = strtok(NULL, "-");
        cust.month = atoi(token);
        token = strtok(NULL, ",");
        cust.year = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(cust.email, token);
        
        token = strtok(NULL, "\n");
        strcpy(cust.phone, token);

        if (id == cust.reservationID || id == cust.room_id)
        {
            found = 1;
            if (!strcmp(cust.status, "confirmed"))
                stat = 1;
            else
                stat = 0;
            break;
        }
    }
    fclose(res);
    if (!found)
    {
        textcolor(RED);
        printf("No reservation found with ID: %ld\n", id);
        textcolor(LIGHTGRAY);
        return;
    }
    
    printf("Please re enter the new data....\n");
    int newId = RoomReservation(stat, cust.reservationID, cust.nationalId);
    if (!save())
    {
        cancel(newId, 1);
        textcolor(RED);
        printf("Edits not saved\n");
        textcolor(LIGHTGRAY);
    }
    else
    {
        cancel(id, 1);
        textcolor(RED);
        printf("Edits saved successfully\n");
        textcolor(LIGHTGRAY);
    }
}