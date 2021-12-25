//
// Created by danie on 25/12/2021.
//

#ifndef DATE_H
#define DATE_H

typedef struct Date_t{} *Date;
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MIN_DAY 1
#define MAX_DAY 31
#define INVALID_MONTH 0
#define MONTH_NUM 12
#define DAYS_IN_YEAR 365
#define MONTH_STR_LEN 4
const char* const months[] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
"JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

/** writes the date to the standard output */
void datePrint(Date date);
/** Reads a date from the standard input.
* Returns true if valid, false otherwise */
bool dateRead(Date* date);
/** Returns true if both dates are identical */
bool dateEquals(Date date1, Date date2);
/** Returns the number of days between the dates */
int dateDifference(Date date1, Date date2);
/** Translates a month string to an integer */
int monthToInt(char* month);
/** Calculates the number of days since 01/01/0000 */
int dateToDays(Date date);
/** Checks if the date has valid values */
bool dateIsValid(Date date);


#endif //DATE_H
