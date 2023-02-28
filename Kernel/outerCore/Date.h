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
 *   dateInitialiser      -create a point of referance to calculate
 *   dateGenerate         -for standartisation in creating objects
 *   dateDestroy          -Deletes an existing date and frees all resources
 *   dateCopy             -Copies an existing date
 *   dateCompare          -compeares between dates
 *   dateCleanInitializer -destroys the initialization date
 *   dateSum              -adds two dates
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
typedef int (*DifferenceCalculator)(void );

/**
 * function for moving the clock back
 */
typedef int (*DayOne)(void);

typedef struct Date_t *Date;

/**
 * functions for years
 */
typedef void* Yearnum;
typedef Yearnum(*YearCopy)(Yearnum);
typedef Yearnum (*YearDestroy)(Yearnum);
typedef void(*YearAdvance)(Yearnum);
typedef int(*YearDivide)(Yearnum);
typedef Yearnum(*MaximalYear)(void);
typedef int (*YearComp)(Yearnum,Yearnum);
typedef void(*Yearinit)(Yearnum);
typedef Yearnum (*YearZero)(void);
typedef void (*Yearbackadvance)(Yearnum);
typedef Yearnum (*Yearlowestposs)(void);
typedef int (*Diffcalc)(Yearnum,Yearnum);

/**
 *   dateInitialiser    -create a point of referance to calculate
 * @param copyFunc- for the calendar we syncronise with
 * @param freeFunc- for the calendar we syncronise with
 * @param compFunc- comparison (for cheking that we didn't mess up)
 * @param advanceFunc- the ++ operator
 */
void dateInitialiser(CopyRefDate copyFunc, FreeRefDate freeFunc,
                     RefDateAdvance advanceFunc,DifferenceCalculator diffFunc,
                     ReferanceDate date,DayOne firstDay,YearCopy ctour,YearDestroy dtour,
                     YearZero zero, Yearlowestposs lowest,YearAdvance advance, MaximalYear max,
                     YearComp compare, Yearinit init, Yearbackadvance contercounter, YearDivide div,
                     Diffcalc negative);

/**
 *   dateGenerate       -for standartisation in creating objects
 * @return date generated according to the
 */
Date dateGenerate(void );

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
 *    dateCompare        -compeares between dates
 * @param date1
 * @param date2
 * @return standart comparison returns
 */
int dateCompeare(Date date1, Date date2);

/**
 *   dateCleanInitializer -destroys the initialization date
 */
void dateCleanInitializer(void);

/**
 * dateSum              -adds two dates
 * @param date1
 * @param date2
 * @return
 * NULL -null arguments or problematic dates
 * date- othewise
 */
Date dateSum(Date date1, Date date2);

#endif //DATE_H

