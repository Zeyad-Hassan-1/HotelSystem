#include <stdio.h>
#include <time.h>
#include "headerFiles/getDate.h"

CurrentDate getDate()
{
    time_t t = time(NULL);
    struct tm *current = localtime(&t);
    CurrentDate date;
    date.day = current->tm_mday;
    date.month = current->tm_mon + 1;
    date.year = current->tm_year + 1900;
    return date;
}