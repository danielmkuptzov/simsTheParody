//
// Created by danie on 29/12/2021.
//

#ifndef DANIELCITY_RATIONAL_H
#define DANIELCITY_RATIONAL_H

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
 * @param rational
 * @return
 * NULL -if the memory allocation was a problem or problematic input
 */
Rational rationalCopy(Rational rational);

/**
 *   rationalCompeare       -compares between rationals
 * @param rational1
 * @param rasional2
 * @return
 * 0 -f equal
 * negative if rational2> rational1
 * positive if rational2< rational1
 */
int rationalCompare(Rational rational1, Rational rasional2);

/**
 *   rationalAddition       -adds two rational
 * @param rational1
 * @param rational2
 * @return
 * NULL if there was a a null argument
 * sum otherwise
 */
Rational rationalAddition(Rational rational1, Rational rational2);

/**
 *   rationalNegate         -negate the rational
 * @param rational
 * @return
 * NULL if there was a NULL argument
 * rational otherwise
 */
Rational rationalNegate(Rational rational);

/**
 *   rationalMultiply       -multiplies two rationals
 * @param rational1
 * @param rational2
 * @return
 * NULL if one of the arguments is NULL
 */
Rational rationalMultiply(Rational rational1, Rational rational2);

/**
 *   rationalPower          -takes rational to an integer power
 * @param base
 * @param power
 * @return
 */
Rational rationalPower(Rational base, int power);

/**
 *   rationalTransform      -answers to the question 1/(given rational)
 * @param rational
 * @return
 * NULL for NULL argument
 * rational otherwise
 */
Rational rationalTransform(Rational rational);

/**
 *   rationalEqual          -the == operator
 * @param rational1
 * @param rational2
 * @return
 * true for equal
 * false for not
 */
bool rationalEqual(Rational rational1,Rational rational2);

/**
 *   rationalGrater         -the > operator
 * @param rational1
 * @param rational2
 * @return
 * true if rational1> rational2
 * false otherwise
 */
bool rationalGrater(Rational rational1, Rational rational2);

/**
 *   rationalLesser         -the < operator
 * @param rational1
 * @param rational2
 * @return
 * true if rational2> rational1
 * false otherwise
 */
bool rationalLesser(Rational rational1, Rational rational2);

#endif //DANIELCITY_RATIONAL_H
