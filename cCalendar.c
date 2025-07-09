#include <stdio.h>
#include <stdlib.h>

int get_1st_weekday(int year) // Function to calculate the first weekday of the year
{
    int day;
    day = ((year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + 1) % 7;
    return day;
}

int main()
{
    system("color 0A"); // Set console text color to green
    int year, month, day, daysInMonth, weekDay, startingDay;

    // Input validation for year
    do
    {
        printf("Enter the Year (between 1900 and 2100): ");
        scanf("%d", &year);
        if (year < 1900 || year > 2100)
        {
            printf("Year must be between 1900 and 2100. Please enter a valid year.\n");
        }
    } while (year < 1900 || year > 2100); // Loop until a valid year is entered

    char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
    int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check for leap year
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        monthDays[1] = 29; // February has 29 days in a leap year
    }

    startingDay = get_1st_weekday(year); // Get the first weekday of the year

    for (month = 0; month < 12; month++)
    {
        daysInMonth = monthDays[month]; // Get the number of days in the month
        printf("\n\n----------%s----------\n", months[month]);
        printf("\n  Sun  Mon  Tue  Wed  Thr  Fri  Sat \n");

        // Print empty spaces for the days before the first day of the month
        for (weekDay = 0; weekDay < startingDay; weekDay++)
        {
            printf("     ");
        }

        // Print the days of the month
        for (day = 1; day <= daysInMonth; day++)
        {
            printf("%5d ", day);

            // Update the weekDay and check if it exceeds 6 (Saturday)
            if (++weekDay > 6)
            {
                printf("\n"); // Move to the next line after Saturday
                weekDay = 0;  // Reset weekDay after Saturday
            }
        }

        // Update startingDay for the next month
        startingDay = weekDay; // The next month's starting day is the current weekDay
    }

    return 0;
}
