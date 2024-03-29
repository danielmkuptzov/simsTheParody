#include <stdlib.h>

#include "Date.h"


#define MIN_DAY 1

struct  counter_t{
    Yearnum lowestc;
    Yearnum middlec;
    Yearnum hightestc;
    Yearnum longest;
    YearCopy ctour;
    YearAdvance advancer;
    YearComp comparator;
    MaximalYear maximum;
    Yearinit init;
    YearDestroy dtour;
};
typedef struct  counter_t* Counter;

typedef struct ReferenceDate_t{
    Date initialisationDate;
    Counter times;
}*Refdate;

static Counter countCre(Yearnum lowestc, Yearnum middlec, Yearnum hightestc, Yearnum longest,
                 YearCopy ctour, YearAdvance advancer,YearComp comparator, MaximalYear maximum,
                 Yearinit init,YearDestroy dtour)
{
    Counter counter= malloc(sizeof(struct counter_t));
    counter->lowestc=ctour(lowestc);
    if(comparator(lowestc,counter->lowestc)!=0)
    {
        free(counter);
        return NULL;
    }
    counter->middlec=ctour(middlec);
    if(comparator(middlec,counter->middlec)!=0)
    {
        dtour(counter->lowestc);
        free(counter);
        return NULL;
    }
    counter->hightestc=ctour(hightestc);
    if(comparator(hightestc,counter->hightestc)!=0)
    {
        dtour(counter->middlec);
        dtour(counter->lowestc);
        free(counter);
        return NULL;
    }
    counter->longest=ctour(longest);
    if(comparator(longest,counter->longest)!=0)
    {
        dtour(counter->hightestc);
        dtour(counter->middlec);
        dtour(counter->lowestc);
        free(counter);
        return NULL;
    }
    counter->ctour=ctour;
    counter->advancer=advancer;
    counter->comparator=comparator;
    counter->maximum=maximum;
    counter->init=init;
    counter->dtour=dtour;
    return counter;
}

static void countDest(Counter counter)
{
    if(counter==NULL)
    {
        return;
    }
    counter->dtour(counter->lowestc);
    counter->dtour(counter->middlec);
    counter->dtour(counter->hightestc);
    counter->dtour(counter->longest);
}

static int counterAdvance(Counter counter)
{
    if(counter->comparator(counter->lowestc,counter->maximum())==0)
    {
        if(counter->comparator(counter->middlec,counter->maximum())==0)
        {
            if(counter->comparator(counter->hightestc,counter->maximum())==0)
            {
                if(counter->comparator(counter->longest,counter->maximum())==0)
                {
                    printf("end of time");
                    return -1;
                }
                else
                {
                    counter->advancer(counter->longest);
                }
                counter->init(counter->hightestc);
            }
            else
            {
                counter->advancer(counter->hightestc);
            }
            counter->init(counter->middlec);
        }
        else
        {
            counter->advancer(counter->middlec);
        }
        counter->init(counter->lowestc);
    }
    else
    {
        counter->advancer(counter->lowestc);
    }
    return 0;
}



static Refdate first= NULL;

static int dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31,
                           30, 31, 30, 31};

typedef enum months{ JAN=1,FEB=2,MAR=3,APR=4,MAY=5,JUN=6,JUL=7,AUG=8,SEP=9,OCT=10,NOV=11,DEC=12} Months;

struct Date_t{
    int day;
    Months month;
    int year;
    Yearnum milenial;
    Yearnum hanoyYearl;
    YearCopy ctour;
    YearDestroy dtour;
    YearAdvance advance;
    Yearbackadvance conteradvance;
    YearZero zero;
    Yearlowestposs lowestyear;
    YearComp comparator;
    MaximalYear maximum;
    Yearinit yearinit;
    ReferanceDate outerDate;
    CopyRefDate copyFunc;
    FreeRefDate freeRefDate;
    RefDateAdvance refDateAdvance;
    Diffcalc diffFunc;
    DifferenceCalculator diffcalc;
};

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
                if(tmpDate->year==0||tmpDate->year==-999)
                {
                    if(tmpDate->comparator(tmpDate->milenial,tmpDate->zero())==0||
                        tmpDate->comparator(tmpDate->milenial,tmpDate->lowestyear())==0)
                    {
                        tmpDate->conteradvance(tmpDate->hanoyYearl);
                        if(tmpDate->comparator(tmpDate->milenial,tmpDate->lowestyear())==0)
                        {
                            tmpDate->yearinit(tmpDate->milenial);
                        }
                        else
                        {
                            while(tmpDate->comparator(tmpDate->milenial,tmpDate->lowestyear())!=0)
                            {
                                tmpDate->conteradvance(tmpDate->milenial);
                            }
                        }
                    }
                    else
                    {
                        tmpDate->conteradvance(tmpDate->milenial);
                    }
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
    date->hanoyYearl=tmpDate->ctour(tmpDate->hanoyYearl);
    date->milenial=tmpDate->ctour(tmpDate->milenial);
    date->year=tmpDate->year;
    date->month=tmpDate->month;
    date->day=tmpDate->day;
}

static Date dateCreate(int day, int month, int year,Yearnum milenia, Yearnum hanoyYear,
                CopyRefDate copyFunc, FreeRefDate freeFunc,
                RefDateAdvance advanceFunc, DifferenceCalculator diffFunc,
                ReferanceDate refDate,YearCopy ctour,YearDestroy dtour,
                YearZero zero, Yearlowestposs lowest,YearAdvance advance, MaximalYear max,
                YearComp compare, Yearinit init, Yearbackadvance contercounter, Diffcalc diffcalc)
{
    if(month<JAN||month>DEC||year<diffFunc()||!copyFunc||!freeFunc
        ||!advanceFunc||!diffFunc||!ctour||!dtour||!zero||!lowest
        ||!advance||!max||!compare||!init||!contercounter)
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
    new_date->diffcalc=diffFunc;
    new_date->freeRefDate=freeFunc;
    new_date->refDateAdvance=advanceFunc;
    new_date->diffFunc=diffcalc;
    new_date->day=day;
    new_date->month=month;
    new_date->year=year;
    new_date->ctour=ctour;
    new_date->dtour=dtour;
    new_date->conteradvance=contercounter;
    new_date->milenial=ctour(milenia);
    new_date->zero=zero;
    new_date->comparator=compare;
    new_date->advance=advance;
    new_date->lowestyear=lowest;
    new_date->maximum=max;
    new_date->yearinit=init;
    new_date->ctour=ctour;
    new_date->hanoyYearl=new_date->ctour(hanoyYear);
    return new_date;
}

void dateInitialiser(CopyRefDate copyFunc, FreeRefDate freeFunc,
                     RefDateAdvance advanceFunc,DifferenceCalculator diffFunc,
                     ReferanceDate date,DayOne firstDay,YearCopy ctour,YearDestroy dtour,
                     YearZero zero, Yearlowestposs lowest,YearAdvance advance, MaximalYear max,
                     YearComp compare, Yearinit init, Yearbackadvance contercounter,Diffcalc negative)
{
    first= malloc(sizeof(struct Date_t));
    if(!first)
    {
        return;
    }
    Date dateOne=dateCreate(1,1,0,0,0,
                            copyFunc,freeFunc,advanceFunc,diffFunc,date,ctour,dtour,zero,
                            lowest,advance,max,compare,init,contercounter,negative);
    if(!dateOne)
    {
        free(first);
        return;
    }
    intDateReturn(dateOne,firstDay());
    first->initialisationDate=dateOne;
    init(date);
    first->times= countCre(date,date,date,date,ctour,
                           advance,compare,max,init,dtour);
    if(!first->times)
    {
        dateDestroy(first->initialisationDate);
    }
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
            if(date->year==999999999)
            {
                if(date->comparator(date->milenial,date->maximum())==0)
                {
                    if(date->comparator(date->hanoyYearl,date->maximum())==0)
                    {
                        return -1;
                    }
                    else
                    {
                        date->advance(date->hanoyYearl);
                    }
                    date->milenial=date->zero();
                }
                else
                {
                    date->advance(date->milenial);
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
    return dateCreate(date->day,date->month,date->year,date->milenial,
                      date->hanoyYearl,date->copyFunc,
                      date->freeRefDate,date->refDateAdvance,
                      date->diffcalc,date->outerDate,date->ctour,date->dtour,
                      date->zero,date->lowestyear,date->advance,date->maximum,date->comparator,
                      date->yearinit,date->conteradvance,date->diffFunc);
}

static int dateDifference(Date date1, Date date2)
{
    if(date1->comparator(date1->hanoyYearl,date2->hanoyYearl)!=0)
    {
        return date1->diffFunc(date1->hanoyYearl,date2->hanoyYearl);
    }
    if(date1->comparator(date1->milenial,date2->milenial)!=0)
    {
        return date1->diffFunc(date1->milenial,date2->milenial);
    }
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
    if(date->comparator(date->hanoyYearl,date->zero())<0)
    {
        for (Yearnum i =date->hanoyYearl ;date->comparator(i,date->maximum())==0 ;date->advance(i))
        {
            days+=365.25*100*1000;
        }
    }
    else
    {
        for (Yearnum i =date->zero();date->comparator(i,date->hanoyYearl)==0 ;date->advance(i))
        {
            days+=365.25*100*1000;
        }
    }
    if(date->comparator(date->milenial,date->zero())<0)
    {
        for (Yearnum i =date->milenial; date->comparator(i,date->maximum())==0;date->advance(i))
        {
            days+=100*365.25;
        }
    }
    else
    {
        for (Yearnum i = date->zero(); date->comparator(i,date->milenial)==0;date->advance(i))
        {
            days+=100*365.25;
        }
    }
    if(date->year<0)
    {
        for (int i=date->year;i<=0;i++)
        {
            days+=yearCalculator(i);
        }
    }
    else
    {
        for (int i=0;i<date->year;i++)
        {
            days+=yearCalculator(i);
        }
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

Date dateGenerate(void)
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

void dateCleanInitializer(void)
{
    dateDestroy(first->initialisationDate);
    countDest(first->times);
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
