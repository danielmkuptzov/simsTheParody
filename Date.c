//
// Created by danie on 25/12/2021.
//
#include "Date.h"


#define MIN_DAY 1
#define INVALID_MONTH 0
#define MONTH_NUM 12
#define DAYS_IN_YEAR 365
#define MONTH_STR_LEN 4

typedef enum months{ JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC} Months;

static int dayInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31,
                                 30, 31, 30, 31};

struct Date_t{
    int day;
    Months month;
    int year;
};

/**
 *  dateCreate         - Creates a new date (in the calendar)
 * @param day- the day in the month (of course positive and according to the month)
 * @param month- month you want (if you enter febuary please check which year)
 * @param year-  the year we want to enter (we have positive years so deal whith this)
 * @return
 *
 * NULL- if the requirement don't mach the enter
 * date- otherwise
 */
Date dateCreate(int day, int month, int year);


/**
 * dateDestroy        - Deletes an existing date and frees all resources
 * @param date- the date we whish to destroy
 */
void dateDestroy(Date date);


/**
 * dateCopy           - Copies an existing date
 * @param date - the date we wish to copy
 * @return
 * NULL- for wrong format or null argument
 * date- otherwise
 */
Date dateCopy(Date date);

/**
 * dateEquals         -checks if the dates are the same
 * @param date1 -the date we check
 * @param date2 - the date we check
 * @return
 * true- the same dates
 * false- otherwise
 */
bool dateEquals(Date date1, Date date2);

/**
 *   dateDifference     -Returns the number of days between the dates
 * @param date1 same as the function above
 * @param date2 same as function above
 * @return
 * 0 if equals
 * positive- date 1 greater than date2
 * negative- the option that left
 */
int dateDifference(Date date1, Date date2);

/**
 * monthToInt         -Translates a month string to an integer
 * @param month- the month you wish to convert
 * @return month's order
 */
int monthToInt(char* month);

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
 * leapYearChecker    -finds if the year is a leap year
 * @param date
 * @return
 * false- not a leap year or null argument
 * true- leap year
 */
bool leapYearChecker(Date date);
