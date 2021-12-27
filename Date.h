#ifndef DATE_H
#define DATE_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Date adt
 *
 * Implements a date variable type.
 * The date is calculated by the gregorian calendar (sorry, but this is the standard date).
 * For all functions the date standard is kept in check by the validity program.
 *
 * @important- please use to initialize the system the function dateInitialiser
 *
 * The following functions are available:
 *   dateInitialiser    -create a point of referance to calculate
 *   dateGenerate       -for standartisation in creating objects
 *   dateDestroy        - Deletes an existing date and frees all resources
 *   dateCopy           - Copies an existing date
 *   dateToDays         -Calculates the number of days since initialisation Date
 *   dateCompare        -compeares between dates
 *
 */

/**
 * for our users who can't convert to the standard we give you the option to standard the date
 * according to your preaferance
 */
typedef void* ReferanceDate;

/**
 * for copy purposes
 */
typedef ReferanceDate(*CopyRefDate)(ReferanceDate);

/**
 * for destruction purposes
 */
typedef void (*FreeRefDate)(ReferanceDate);


/**
 * advancement function
 */
typedef void(*RefDateAdvance)(ReferanceDate);

/**
 * year difference calculator for standatisation
 */
typedef int (*DifferenceCalculator)();

/**
 * function for moving the clock back
 */
typedef int (*DayOne)();

typedef struct Date_t *Date;

typedef enum months{ JAN=1,FEB=2,MAR=3,APR=4,MAY=5,JUN=6,JUL=7,AUG=8,SEP=9,OCT=10,NOV=11,DEC=12} Months;

typedef enum DateErorCode_t{
    DATE_ERROR,
    WRONG_MONTH,
    NEGATIVE_YEAR,
    DATE_SUCSESS
}DateErorCode;

/**
 *   dateInitialiser    -create a point of referance to calculate
 * @param copyFunc- for the calendar we syncronise with
 * @param freeFunc- for the calendar we syncronise with
 * @param compFunc- comparison (for cheking that we didn't mess up)
 * @param advanceFunc- the ++ operator
 */
void dateInitialiser(CopyRefDate copyFunc, FreeRefDate freeFunc,
                     RefDateAdvance advanceFunc,DifferenceCalculator diffFunc,
                     ReferanceDate date, DayOne firstDay);

/**
 *   dateGenerate       -for standartisation in creating objects
 * @return date generated according to the
 */
Date dateGenerate();

/**
 *   dateDestroy        - Deletes an existing date and frees all resources
 * @param date- the date we whish to destroy
 */
void dateDestroy(Date date);

/**
 *   dateCopy           - Copies an existing date
 * @param date - the date we wish to copy
 * @return
 * NULL- for wrong format or null argument
 * date- otherwise
 */
Date dateCopy(Date date);

/**
 *   dateToDays         -Calculates the number of days since initialisation Date
 * @param date- the date we need to convert
 * @return
 * -1 if the date was in the wrong format
 * oterwise a positive number
 */
int dateToDays(Date date);

/**
 *    dateCompare        -compeares between dates
 * @param date1
 * @param date2
 * @return standart comparison returns
 */
int dateCompeare(Date date1, Date date2);

#endif //DATE_H

