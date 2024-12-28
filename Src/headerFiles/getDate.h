#ifndef GETDATE_H
#define GETDATE_H

typedef struct{
    int day;
    int month;
    int year;
}CurrentDate;

CurrentDate getDate();



#endif