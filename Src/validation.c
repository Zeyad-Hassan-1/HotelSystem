#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

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
    // Get current date
    time_t t = time(NULL);
    struct tm *current = localtime(&t);
    int curr_year = current->tm_year + 1900;
    int curr_month = current->tm_mon + 1;
    int curr_day = current->tm_mday;

    // Check if date is in past
    if (year < curr_year)
        return 0;
    if (year == curr_year && month < curr_month)
        return 0;
    if (year == curr_year && month == curr_month && day < curr_day)
        return 0;

    // Basic date validation
    if (month < 1 || month > 12)
        return 0;
    if (day < 1 || day > 30)
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
