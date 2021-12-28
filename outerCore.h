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
 * functions that need to be used seperetly:
 *   dateInitialiser    -create a point of referance to calculate
 *   dateGenerate       -for standartisation in creating objects
 *   asCreate           - Creates a new empty set
 *   asGetSize          - Returns the size of the set
 *   asContains         - Checks if an element exists in the set
 *   asRegister         - Add a new element into the set
 *   asDelete           - Delete an element completely from the set
 *   asClear            - Deletes all elements from target set
 *   asGetFirst         - Sets the internal iterator to the first element
 *                        in the set, and returns it.
 *   asGetNext          - Advances the internal iterator to the next element
 *                        and returns it.
 *   asCompeare         -compares between amount sets
 *   asFilter           -filters the amountset according to the user
 *   asValid            - checks the validity of the set
 *   AS_FOREACH         - A macro for iterating over the set's elements
 */

/**
 * the core unit
 */
typedef struct CoreUnit_t* CoreUnit;

/**
 *   coreCreate         -Creates the unit.
 * @param type as we explained prevoiously, this way we overcome the void* problem
 * @param element -the elment itself, note that we whould check the coralation between type and number
 * @return
 * NULL -if the elemement was null or wasn't same as stated in the type
 * coreUnit otherwise
 */
CoreUnit coreCreate(int type, void* element);

/**
 *   coreDestroy        -Deletes an existing unit and frees all resources
 * @param unit
 */
void coreDestroy(void* unit);

/**
 *   unitCopy           -Copies an existing unit
 * @param orgUnit
 * @return
 * NULL -problems with the input
 * core unit othewise
 */
void* unitCopy(void* orgUnit);

/**
 *   unitCompeare       -compares between amount sets
 * @param first
 * @param second
 * @return
 * 0- if the units are the same
 * positive- first> second
 * negative- second> first
 */
int unitCompeare(void* first, void* second);

/**
 *   unitValid           -checks the validity of the unit
 * @param unit
 * @return
 */
bool unitValid(void* unit);


#endif //OUTERCORE_H
