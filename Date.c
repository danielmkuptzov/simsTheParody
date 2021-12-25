//
// Created by danie on 25/12/2021.
//
#include <stdlib.h>

#include "Date.h"


#define MIN_DAY 1

typedef struct ReferenceDate_t{
    Date initialisationDate;
    int times;
}*date;

static int dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31,
                                 30, 31, 30, 31};

struct Date_t{
    int day;
    Months month;
    int year;
};

//first thing to implement
static bool leapYearChecker(int year);

static void yearFixer(int year)
{
    if(leapYearChecker(year))
    {
        dayInMonth[FEB]=29;
        return;
    }
    dayInMonth[FEB]=28;
}

static int yearCalculator(int year)
{
    yearFixer(year);
    int sum=0;
    for(Months i=JAN; i<=DEC; i++)
    {
        sum=dayInMonth[i];
    }
    return sum;
}

Date dateCreate(int day, int month, int year)
{
    if(year<0)
    {
        return NULL;
    }
    if(month<JAN||month>DEC)
    {
        return NULL;
    }
    if(leapYearChecker(year))
    {
        dayInMonth[FEB]=29;
    }
    if(day<MIN_DAY||day>dayInMonth[month])
    {
        return NULL;
    }
    Date new= malloc(sizeof(struct Date_t));
    if(!new)
    {
        return NULL;
    }
    new->day=day;
    new->month=month-1;
    new->year=year;
    return new;
}

void dateDestroy(Date date)
{
    if(!date)
    {
        return;
    }
    free(date);
}


Date dateCopy(Date date)
{
    if(!date)
    {
        return NULL;
    }
    return dateCreate(date->day,date->month,date->year);
}

bool dateEquals(Date date1, Date date2)
{
    if(!date1||!date2||dateCompeare(date1,date2)!=0)
    {
        return false;
    }
    return true;
}

int dateDifference(Date date1, Date date2)
{
    if(date1->year!=date2->year)
    {
        return date1->year-date2->year;
    }
    if(date1->month!=date2->month)
    {
        return date1->month-date2->month;
    }
    return date1->day-date2->day;
}

int monthToInt(Months month)
{
    return dayInMonth[month];
}

/**
 *   dateToDays         -Calculates the number of days since 01/01/0000
 * @param date- the date we need to convert
 * @return
 * -1 if the date was in the wrong format
 * oterwise a positive number
 */
int dateToDays(Date date);

/**
 *    dateIsValid        -Checks if the date has valid values
 * @param date the date we need to check the validity of
 * @return
 * false- null argument or illegal date
 * true- oterwise
 */
bool dateIsValid(Date date);

/**
 *    dateCompare        -compeares between dates
 * @param date1
 * @param date2
 * @return standart comparison returns
 */
int dateCompeare(Date date1, Date date2);

/**
 *    dateGenerate       -for standartisation in creating objects
 * @return date generated according to the
 */
Date dateGenerate();

/**
 *   dateAdvance        -moves the date a day forward
 * @param date the date we wish to advance
 * @return
 * DATE_ERROR- null argument was send
 * WRONG_MONTH- wrong format
 * NEGATIVE_YEAR- wrong format
 * DATE_SUCSESS- the date is one day forward
 */
DateErorCode dateAdvance(Date date);

/**
 * intDateAdvance     -moves a user requested amount the day
 * @param date the date we need to advance
 * @param advance the amount of days needed
 * @return
 * DATE_ERROR- null argument or negative days
 * WRONG_MONTH- wrong format
 * NEGATIVE_YEAR- wrong format
 * DATE_SUCSESS- the operation ended sucsessfuly
 */
DateErorCode intDateAdvance(Date date, int advance);

/**
 * dateInitialiser    -create a point of referance to calculate
 */
void dateInitialiser();
