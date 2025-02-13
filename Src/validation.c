#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "headerFiles/getDate.h"

int is_valid_email(const char *email)
{
    const char *at = strchr(email, '@');
    if (!at || at == email)
        return 0;
    const char *dot = strchr(at, '.');
    if (!dot || dot == at + 1)
        return 0;
    if (dot[1] == '\0')
        return 0;

    return 1;
}

int is_valid_date(int day, int month, int year)
{
    
    CurrentDate current = getDate();
    

    if (year < current.year)
        return 0;
    if (year == current.year && month < current.month)
        return 0;
    if (year == current.year && month == current.month && day < current.day)
        return 0;

    // Basic date validation
    if (month < 1 || month > 12)
        return 0;
    int days_in_month;
    switch (month) {
        case 2:  // February
            // Check for leap year
            if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
                days_in_month = 29;
            } else {
                days_in_month = 28;
            }
            break;
        case 4: case 6: case 9: case 11:  // Months with 30 days
            days_in_month = 30;
            break;
        default:  // Months with 31 days
            days_in_month = 31;
            break;
    }
    if (day < 1 || day > days_in_month)
        return 0;

    return 1;
}

int is_valid_phone(const char *phone)
{
    if (strlen(phone) < 5)
    {
        return 0;
    }

    for (int i = 0; i < strlen(phone); i++)
    {
        if (!isdigit(phone[i]))
        {
            return 0;
        }
    }

    return 1;
}

int is_valid_national_id(const char *national_id)
{
    for (int i = 0; i < strlen(national_id); i++)
    {
        if (!isdigit(national_id[i]))
        {
            return 0;
        }
    }

    return 1;
}

int is_valid_nights(int nights)
{
    if (nights < 1 || nights > 30)
    {
        return 0;
    }

    return 1;
}

int is_valid_name(const char *name)
{
    // Check if name is empty or too long
    size_t len = strlen(name);
    if (len < 2 || len > 50)
    {
        return 0;
    }

    // Check first character is a letter
    if (!isalpha(name[0]))
    {
        return 0;
    }

    // Check each character
    for (int i = 0; i < len; i++)
    {
        // Allow only letters and spaces
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            return 0;
        }

        // Don't allow consecutive spaces
        if (name[i] == ' ' && name[i + 1] == ' ')
        {
            return 0;
        }
    }
    return 1;
}
