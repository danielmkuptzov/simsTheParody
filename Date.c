//
// Created by danie on 25/12/2021.
//
#include <stdlib.h>

#include "Date.h"


#define MIN_DAY 1

typedef struct ReferenceDate_t{
    Date initialisationDate;
    int times;
}*Refdate;

Refdate first;

static int dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31,
                                 30, 31, 30, 31};

struct Date_t{
    int day;
    Months month;
    int year;
    ReferanceDate outerDate;
    CopyRefDate copyFunc;
    FreeRefDate freeRefDate;
    CopmRefDate copmRefDate;
    RefDateAdvance refDateAdvance;
    DifferenceCalculator diffFunc;
};

static bool leapYearChecker(int year)
{
    if(year%4==0)
    {
        if(year%100==0)
        {
            if(year%400==0)
            {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

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

Date dateCreate(int day, int month, int year,
                CopyRefDate copyFunc, FreeRefDate freeFunc,
                CopmRefDate compFunc, RefDateAdvance advanceFunc,
                DifferenceCalculator diffFunc,ReferanceDate refDate)
{
    if(month<JAN||month>DEC||year<diffFunc()||!copyFunc||!freeFunc||
    !compFunc||!advanceFunc||!diffFunc)
    {
        return NULL;
    }
    yearFixer(year);
    if(day<MIN_DAY||day>dayInMonth[month])
    {
        return NULL;
    }
    Date new= malloc(sizeof(struct Date_t));
    if(!new)
    {
        return NULL;
    }
    new->copyFunc=copyFunc;
    new->outerDate=new->copyFunc(refDate);
    if(!new->outerDate)
    {
        free(new);
        return NULL;
    }
    new->freeRefDate=freeFunc;
    new->copmRefDate=compFunc;
    new->refDateAdvance=advanceFunc;
    new->diffFunc=diffFunc;
    new->day=day;
    new->month=month;
    new->year=year;
    return new;
}

void dateDestroy(Date date)
{
    if(!date)
    {
        return;
    }
    if(date->outerDate)
    {
        date->freeRefDate(date->outerDate);
    }
    free(date);
}

Date dateCopy(Date date)
{
    if(!dateIsValid(date))
    {
        return NULL;
    }
    return dateCreate(date->day,date->month,date->year,date->copyFunc,
                      date->freeRefDate,date->copmRefDate,date->refDateAdvance,
                      date->diffFunc,date->outerDate);
}

bool dateEquals(Date date1, Date date2)
{
    if(!dateIsValid(date1)||!dateIsValid(date2)||dateCompeare(date1,date2)!=0)
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
    if(month<JAN||month>DEC)
    {
        return -1;
    }
    return dayInMonth[month];
}

int dateToDays(Date date)
{
    if(!dateIsValid(date))
    {
        return -1;
    }
    int days=0;
    for (int i = 0; i < date->year; ++i)
    {
        days+= yearCalculator(i);
    }
    yearFixer(date->year);
    for (int i = 0; i < date->month; ++i)
    {
        days+=dayInMonth[i];
    }
    days+=date->day;
    return days;
}

bool dateIsValid(Date date)
{
    if(!date)
    {
        return false;
    }
    if(date->year<date->diffFunc())
    {
        return false;
    }
    yearFixer(date->year);
    if(date->day<MIN_DAY||date->day>dayInMonth[date->month])
    {
        return false;
    }
    return true;
}

int dateCompeare(Date date1, Date date2)
{
    return dateToDays(date1)- dateToDays(date2);
}

Date dateGenerate()
{
    first->times++;
    Date toSend= dateCopy(first->initialisationDate);
    if(dateAdvance(first->initialisationDate)==DATE_SUCSESS)
    {
        return toSend;
    }
    return NULL;
}

DateErorCode dateAdvance(Date date)
{
    if(!dateIsValid(date))
    {
        return DATE_ERROR;
    }
    date->refDateAdvance(date->outerDate);
    yearFixer(date->year);
    if(date->day==dayInMonth[date->month])
    {
        if(date->month==DEC)
        {
            date->year++;
            date->month=JAN;
            date->day=1;
            return DATE_SUCSESS;
        }
        date->month++;
        date->day=1;
        return DATE_SUCSESS;
    }
    date->day++;
    return DATE_SUCSESS;
}

DateErorCode intDateAdvance(Date date, int advance)
{
    if(!dateIsValid(date))
    {
        return WRONG_MONTH;
    }
    Date tmpDade= dateCopy(date);
    for(int i=0; i<advance; i++)
    {
        if(dateAdvance(tmpDade)!=DATE_SUCSESS)
        {
            return DATE_ERROR;
        }
    }
    date= dateCopy(tmpDade);
    return DATE_SUCSESS;
}

void dateInitialiser(CopyRefDate copyFunc, FreeRefDate freeFunc,
                     CopmRefDate compFunc, RefDateAdvance advanceFunc,DifferenceCalculator diffFunc,
                     ReferanceDate date, YearOneGiver dayOne)
{
    first= malloc(sizeof(struct Date_t));
    first->initialisationDate= dateCreate(dayOne()->day,dayOne()->month,dayOne()->year,
                                          copyFunc,freeFunc,compFunc,advanceFunc,diffFunc,date);
    first->times=0;
}
