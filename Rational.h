//
// Created by danie on 29/12/2021.
//

#ifndef DANIELCITY_RATIONAL_H
#define DANIELCITY_RATIONAL_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/**
 *  Rational numbers adt
 *
 * this header implements the rational numbers. we will recive in the creator only integers (no doubles)
 * please use with care
 *
 * The following functions are available:
 *   rationalCreate         -Creates the rational number.
 *   rationalDestroy        -Deletes an existing rational and frees all resources
 *   rationalCopy           -Copies an existing rational
 *   rationalCompeare       -compares between rationals
 *   rationalAddition       -adds two rational
 *   rationalNegate         -negate the rational
 *   rationalAdvance        -addition but to one of the rationals given
 *   rationalMultiply       -multiplies two rationals
 *   rationalPower          -takes rational to an integer power
 *   rationalTransform      -answers to the question 1/(given rational)
 *   rationalEqual          -the == operator
 *   rationalGrater         -the > operator
 *   rationalLesser         -the < operator
 */

typedef struct Rational_t* Rational;

/**
 *   rationalCreate         -Creates the rational number
 * @param numerator- the upper half of the fraction
 * @param denumerator -the lower half of the fraction (don't enter 0 this isn't calculus)
 * @return
 *  NULL -0 as a denumerator or memory allocation problems
 *  rational otherwise
 */
Rational rationalCreate(int numerator,int denumerator);

/**
 *   rationalDestroy        -Deletes an existing rational and frees all resources
 * @param rational
 */
void rationalDestroy(Rational rational);

/**
 *   rationalCopy           -Copies an existing rational
 *   rationalCompeare       -compares between rationals
 *   rationalAddition       -adds two rational
 *   rationalNegate         -negate the rational
 *   rationalAdvance        -addition but to one of the rationals given
 *   rationalMultiply       -multiplies two rationals
 *   rationalPower          -takes rational to an integer power
 *   rationalTransform      -answers to the question 1/(given rational)
 *   rationalEqual          -the == operator
 *   rationalGrater         -the > operator
 *   rationalLesser         -the < operator
 * @param rational
 * @return
 * NULL -if the memory allocation was a problem or problematic input
 */
Rational rationalCopy(Rational rational);

int rationalCompare(Rational rational1, Rational rasional2);
#endif //DANIELCITY_RATIONAL_H
