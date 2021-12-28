//
// Created by danie on 26/12/2021.
//

#ifndef OUTERCORE_H
#define OUTERCORE_H

#include "Date.h"
#include "AmountSet.h"

/**
 * Outer core switch unit
 *
 * This function implement the generic copy constructor, comparison operator and destructors needed for the amount set.
 * For accesing the units will be numbered by this order:
 *
 * type 1 is the amount set. The creator whold be supplied to the user as it is.
 * type 2 is the date adt. as explained in the previous type, the initialiser supplied as it is.
 *
 * The following functions are available:
 *   coreCreate         -Creates the unit.
 *   coreDestroy        -Deletes an existing unit and frees all resources
 *   unitCopy           -Copies an existing unit
 *   unitCompeare       -compares between amount sets
 *   unitValid           -checks the validity of the unit
 */

/**
 * functions that need to be used seperetly
 */
#endif //OUTERCORE_H
