#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./headerFiles/reservations.h"

Customer separateResLine(char *line)
{
    Customer customer;
    char *token;
    token = strtok(line, ",");
    customer.reservationID = atol(token);

    token = strtok(NULL, ",");
    customer.room_id = atoi(token);

    token = strtok(NULL, ",");
    strcpy(customer.status, token);

    token = strtok(NULL, ",");
    strcpy(customer.name, token);

    token = strtok(NULL, ",");
    strcpy(customer.nationalId, token);

    token = strtok(NULL, ",");
    customer.numberOfnights = atoi(token);

    token = strtok(NULL, "-");
    customer.day = atoi(token);
    token = strtok(NULL, "-");
    customer.month = atoi(token);
    token = strtok(NULL, ",");
    customer.year = atoi(token);

    token = strtok(NULL, ",");
    strcpy(customer.email, token);

    token = strtok(NULL, "\n");
    strcpy(customer.phone, token);

    return customer;
}

Room separateRoomLine(char *line)
{
    Room room;
    char *token;
    token = strtok(line, " ");
    room.room_id = atoi(token);

    token = strtok(NULL, " ");
    strcpy(room.status, token);

    token = strtok(NULL, " ");
    strcpy(room.category, token);

    token = strtok(NULL, "\n");
    room.price = atoi(token);

    return room;
}