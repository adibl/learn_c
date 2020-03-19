#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(void)
{
    printf("%d %d\n", day_of_year(2001, 5, 19), day_of_year(3004, 12, 45));
    int month, day;
    month_day(2001, 358, &month, &day);
    printf("%d %d\n", month, day);
    month_day(2001, 366, &month, &day);
    printf("%d %d\n", month, day);
    return 0;
}



static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    if (month > 12) {
        printf("month cant be greater then 12\n");
        return -1;
    }
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (day > daytab[leap][month]) {
        printf("month %d contain only %d days\n", month, daytab[leap][month]);
        return -1;
    }
        
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    int total_days = yearday;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; yearday > daytab[leap][i] && i <= 12; i++)
        yearday -= daytab[leap][i];
    if (i > 12) {
        printf("year %d dont have %d days but only %d days\n", year, total_days, total_days - yearday);
        *pmonth = -1;
        *pday = -1;
    }
    else {
        *pmonth = i;
        *pday = yearday;
    }
}
