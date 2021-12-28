//
// Created by danie on 26/12/2021.
//

#ifndef OUTERCORE_H
#define OUTERCORE_H

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
 *   coreCopy           -Copies an existing unit
 *   coreCompeare       -compares between amount sets
 *   coreValid          -checks the validity of the unit
 *   coreAddition       -adds two units together
 */

/**
 * functions that need to be used seperetly:
 *   dateInitialiser      -create a point of referance to calculate
 *   dateCleanInitializer -destroys the initialization date @you @better @don't @forget @to @do @it
 *                         @after @finnish
 *   dateGenerate         -for standartisation in creating objects
 *   asCreate             - Creates a new empty set
 *   asGetSize            - Returns the size of the set
 *   asContains           - Checks if an element exists in the set
 *   asRegister           - Add a new element into the set
 *   asDelete             - Delete an element completely from the set
 *   asClear              - Deletes all elements from target set
 *   asFilter             -filters the amountset according to the user
 *   AS_FOREACH           - A macro for iterating over the set's elements
 */

/**
 * the core unit
 */
typedef struct CoreUnit_t* CoreUnit;

/**
 *   coreCreate         -Creates the unit.
 * @param type as we explained prevoiously, this way we overcome the void* problem
 * @param element -the array of pointers to the functions you wish to send
 * @param size- the amount of the elements you send
 * @return
 * NULL -if the elemement was null or wasn't same as stated in the type
 * coreUnit otherwise
 */
CoreUnit coreCreate(int type, void* element, int size);

/**
 *   coreDestroy        -Deletes an existing unit and frees all resources
 * @param unit
 */
void coreDestroy(void* unit);

/**
 *   coreCopy           -Copies an existing unit
 * @param orgUnit
 * @return
 * NULL -problems with the input
 * core unit othewise
 */
void* coreCopy(void* orgUnit);

/**
 *   unitCompeare       -compares between amount sets
 * @param first
 * @param second
 * @return
 * 0- if the units are the same
 * positive- first> second
 * negative- second> first
 */
int coreCompeare(void* first, void* second);

/**
 *   coreValid           -checks the validity of the unit
 * @param unit
 * @return
 */
bool coreValid(void* unit);

/**
 * coreAddition       -adds two units together
 * @param unit1
 * @param unit2
 * @return
 * NULL -if the units are different or null
 * core unit otherwise
 */
CoreUnit coreAddition(CoreUnit unit1, CoreUnit unit2);

#endif //OUTERCORE_H
