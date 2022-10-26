#include <stdlib.h>

#include "Date.h"


#define MIN_DAY 1

typedef struct counter_t* Counter;

typedef struct ReferenceDate_t{
    Date initialisationDate;
    Counter times;
}*Refdate;

struct  counter_t{
    int lowest;
    int  middle;
    int hightest;
    int longest;
};

static Refdate first= NULL;

static int dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31,
                           30, 31, 30, 31};

typedef enum months{ JAN=1,FEB=2,MAR=3,APR=4,MAY=5,JUN=6,JUL=7,AUG=8,SEP=9,OCT=10,NOV=11,DEC=12} Months;

typedef void* Yearnum;
typedef void(*YearAdvance)(Yearnum);
typedef int(*YearDivide)(Yearnum);

struct Date_t{
    int day;
    Months month;
    int year;
    Yearnum milenia;
    Yearnum hanoyYear;
    YearAdvance advance;
    ReferanceDate outerDate;
    CopyRefDate copyFunc;
    FreeRefDate freeRefDate;
    RefDateAdvance refDateAdvance;
    DifferenceCalculator diffFunc;
};

static int counterAdvance(Counter counter)
{
    if(counter->lowest==999999999)
    {
        if(counter->middle==999999999)
        {
            if(counter->hightest==999999999)
            {
                if(counter->longest==999999999)
                {
                    return -1;
                }
                else
                {
                    counter->longest++;
                }
                counter->hightest=0;
            }
            else
            {
                counter->hightest++;
            }
            counter->middle=0;
        }
        else
        {
            counter->middle++;
        }
        counter->lowest=0;
    }
    else
    {
        counter->lowest++;
    }
    return 0;
}

static int monthToInt(Months month)
{
    if(month<JAN||month>DEC)
    {
        return -1;
    }
    if(month==JAN)
    {
        return 1;
    }
    else if(month==FEB)
    {
        return 2;
    }
    else if(month==MAR)
    {
        return 3;
    }
    else if(month== APR)
    {
        return 4;
    }
    else if(month== MAY)
    {
        return 5;
    }
    else if(month== JUN)
    {
        return 6;
    }
    else if(month== JUL)
    {
        return 7;
    }
    else if(month== AUG)
    {
        return 8;
    }
    else if(month== SEP)
    {
        return 9;
    }
    else if(month==OCT)
    {
        return 10;
    }
    else if(month== NOV)
    {
        return 11;
    }
    else
    {
        return 12;
    }
}

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
        dayInMonth[monthToInt(FEB)-1]=29;
        return;
    }
    dayInMonth[monthToInt(FEB)-1]=28;
}

static int yearCalculator(int year)
{
    yearFixer(year);
    int sum=0;
    for(Months i=monthToInt(JAN); i<=monthToInt(DEC); i++)
    {
        sum=dayInMonth[i];
    }
    return sum;
}

static void intDateReturn(Date date, int back)
{
    Date tmpDate= dateCopy(date);
    for (int i = 0; i < back; ++i)
    {
        if(tmpDate->day==1)
        {
            if(tmpDate->month==JAN)
            {
                if(tmpDate->year==0||tmpDate->year==-999999999)
                {
                    if(tmpDate->milenia==0||tmpDate->milenia==-999999999)
                    {
                        tmpDate->hanoyYear--;
                    }
                    tmpDate->milenia--;
                }
                tmpDate->year--;
                tmpDate->month=DEC;
                tmpDate->day=dayInMonth[monthToInt(DEC)-1];
            }
            else
            {
                yearFixer(tmpDate->year);
                tmpDate->month= monthToInt(tmpDate->month)-1;
                tmpDate->day=dayInMonth[monthToInt(tmpDate->month)-1];
            }
        }
        else
        {
            tmpDate->day--;
        }
    }
    date->hanoyYear=tmpDate->hanoyYear;
    date->milenia=tmpDate->milenia;
    date->year=tmpDate->year;
    date->month=tmpDate->month;
    date->day=tmpDate->day;
}

static Date dateCreate(int day, int month, int year, int milenia, int hanoyYear,
                CopyRefDate copyFunc, FreeRefDate freeFunc,
                RefDateAdvance advanceFunc, DifferenceCalculator diffFunc,
                ReferanceDate refDate)
{
    if(month<JAN||month>DEC||year<diffFunc()||!copyFunc||!freeFunc
        ||!advanceFunc||!diffFunc)
    {
        return NULL;
    }
    yearFixer(year);
    if(day<MIN_DAY||day>dayInMonth[monthToInt(month)-1])
    {
        return NULL;
    }
    Date new_date= malloc(sizeof(struct Date_t));
    if(!new_date)
    {
        return NULL;
    }
    new_date->copyFunc=copyFunc;
    if(new_date->copyFunc)
    {
        new_date->outerDate=new_date->copyFunc(refDate);
        if(!new_date->outerDate)
        {
            free(new_date);
            return NULL;
        }
    }
    new_date->freeRefDate=freeFunc;
    new_date->refDateAdvance=advanceFunc;
    new_date->diffFunc=diffFunc;
    new_date->day=day;
    new_date->month=month;
    new_date->year=year;
    new_date->milenia=milenia;
    new_date->hanoyYear=hanoyYear;
    return new_date;
}

void dateInitialiser(CopyRefDate copyFunc, FreeRefDate freeFunc,
                     RefDateAdvance advanceFunc,DifferenceCalculator diffFunc,
                     ReferanceDate date,DayOne firstDay)
{
    first= malloc(sizeof(struct Date_t));
    if(!first)
    {
        return;
    }
    Date dateOne=dateCreate(1,1,0,0,0,
                            copyFunc,freeFunc,advanceFunc,diffFunc,date);
    if(!dateOne)
    {
        free(first);
        return;
    }
    intDateReturn(dateOne,firstDay());
    first->initialisationDate=dateOne;
    first->times= malloc(sizeof(struct counter_t));
    if(!first->times)
    {
        dateDestroy(first->initialisationDate);
        free(first);
        return;
    }
    first->times->lowest=0;
    first->times->middle=0;
    first->times->hightest=0;
    first->times->longest=0;
}

void dateDestroy(Date date)
{
    if(!date)
    {
        return;
    }
    if((date->freeRefDate)&&(date->outerDate))
    {
        date->freeRefDate(date->outerDate);
    }
    free(date);
}

static int dateAdvance(Date date)
{
    date->refDateAdvance(date->outerDate);
    yearFixer(date->year);
    if(date->day==dayInMonth[monthToInt(date->month)-1])
    {
        if(date->month==DEC)
        {
            if(date->year==-1||date->year==999999999)
            {
                if(date->milenia==-1||date->milenia==999999999)
                {
                    if(date->hanoyYear==999999999)
                    {
                        return -1;
                    }
                    else
                    {
                        date->hanoyYear++;
                    }
                    date->milenia=0;
                }
                else
                {
                    date->milenia++;
                }
                date->year=0;
            }
            else
            {
                date->year++;
            }
            date->month=JAN;
        }
        else
        {
            date->month++;
        }
        date->day=1;
    }
    else
    {
        date->day++;
    }
    return 0;
}

Date dateCopy(Date date)
{
    if(!date)
    {
        return NULL;
    }
    return dateCreate(date->day,date->month,date->year,date->milenia,
                      date->hanoyYear,date->copyFunc,
                      date->freeRefDate,date->refDateAdvance,
                      date->diffFunc,date->outerDate);
}

static int dateDifference(Date date1, Date date2)
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

static int dateToDays(Date date)
{
    int days=0;
    for (int i = 0; i < (date->year)+(date->diffFunc()); ++i)
    {
        days+= yearCalculator(i);
    }
    yearFixer(date->year);
    for (int i = 0; i < monthToInt(date->month); ++i)
    {
        days+=dayInMonth[i];
    }
    days+=date->day;
    return days;
}

int dateCompeare(Date date1, Date date2)
{
    if(dateDifference(date1,date2)==0 && date1->diffFunc(date1->outerDate,date2->outerDate)==0)
    {
        return 0;
    }
    return dateToDays(date1)- dateToDays(date2);
}

Date dateGenerate()
{
    if(!first)
    {
        return NULL;
    }
    int resalt= counterAdvance(first->times);
    if(resalt==-1)
    {
        printf("the counter is in his limit");
        return NULL;
    }
    Date toSend= dateCopy(first->initialisationDate);
    resalt=dateAdvance(first->initialisationDate);
    if(resalt==-1)
    {
        printf("the last date of the calendar");
        return NULL;
    }
    return toSend;
}

void dateCleanInitializer()
{
    dateDestroy(first->initialisationDate);
    free(first);
}

Date dateSum(Date date1, Date date2)
{
    if(!date1||!date2)
    {
        return NULL;
    }
    Date sum= dateCopy(date1);
    for(int i=0; i< dateToDays(date2);i++)
    {
        dateAdvance(sum);
    }
    return sum;
}
