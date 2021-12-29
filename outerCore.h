//
// Created by danie on 26/12/2021.
//

#ifndef OUTERCORE_H
#define OUTERCORE_H
#include <stdbool.h>

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
 *   coreBeginner       -the function that you use to begin the date function
 *   coreCreate         -Creates the unit.
 *   coreDestroy        -Deletes an existing unit and frees all resources
 *   coreCopy           -Copies an existing unit
 *   coreCompeare       -compares between amount sets
 *   coreAddition       -adds two units together
 *   coreInsert         -adds to the core (only works with set)
 *   coreRemove         -removes an element (only works with sets)
 *   coreFilter         -filters core according to a criteria (only works with sets)
 *   coreFind           -finds specific element(only works with sets)
 *   coreSize           -returns the size of the element (for date will return -1)
 *   coreDestroyer      -use it to end the code
 *   coreGetElement     -return the data of the element
 */

typedef enum {
    CORE_ERROR,
    CORE_MEMORY_PROBLEM,
    CORE_NULL_ARGUMENT,
    CORE_ADDITION_FAILED,
    CORE_ELEMENT_EXIST,
    CORE_ELEMENT_DOES_NOT_EXIST,
    CORE_SUCSESS
}OuterCoreErrors;

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


/**
 * for set use
 */
typedef void* COREElement;

/** Type of function for copying an element of the set */
typedef COREElement(*CopyCOREElement)(COREElement);

/** Type of function for deallocating an element of the set */
typedef void (*FreeCOREElement)(COREElement);

/**
 * Type of function used by the set to identify equal set elements.
 * This function should return:
 *     A positive integer if the first element is greater;
 *     0 if they're equal;
 *     A negative integer if the second element is greater.
 */
typedef int (*CompareCOREElements)(COREElement ,COREElement);

/**
* Use this type to pass extra information needed by the filtering function
* when calling listFilter. (See the example for a FilterListElement function)
*/
typedef void* CoreFilterKey;

/**
* Function used for creating a filtered copy of a set.
* A element is said to pass filtering if the function returns true
* For example, the following function can be used to filter a list of strings
* from short strings:
* @code
* bool isShorterThan(SetElement str, SetFilterKey length) {
*   return strlen(str) < *(int*) length;
* }
* @endcode
*/
typedef bool(*FilterCOREElement)(COREElement, COREElement);

/**
 * the core unit
 */
typedef struct CoreUnit_t* CoreUnit;

/**
 * coreBeginner       -the function that you use to begin the date function
 */
void coreBeginner(CopyRefDate copyFunc, FreeRefDate freeFunc,
                  RefDateAdvance advanceFunc,DifferenceCalculator diffFunc,
                  ReferanceDate date, DayOne firstDay);

/**
 *   coreCreate         -Creates the unit.
 * @param type as we explained prevoiously, this way we overcome the void* problem
 * @param element -the array of pointers to the functions you wish to send
 * @param size- the amount of the elements you send
 * @return
 * NULL -if the elemement was null or wasn't same as stated in the type
 * coreUnit otherwise
 */
CoreUnit coreCreate(int type, CopyCOREElement copyfunc, FreeCOREElement freefunc,
                    CompareCOREElements compfunc, int asType);

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
 *   coreAddition       -adds two units together
 * @param unit1
 * @param unit2
 * @return
 * NULL -if the units are different or null
 * core unit otherwise
 */
CoreUnit coreAddition(CoreUnit unit1, CoreUnit unit2);

/**
 *   coreInsert         -adds to the core (only works with set)
 * @param core
 * @param element
 * @return
 * CORE_ERROR          -the operation failed
 * CORE_MEMORY_PROBLEM -memory acsess problems
 * CORE_NULL_ARGUMENT  -the arguments were nulll
 * CORE_ELEMENT_EXIST  -the addition is impossible
 * CORE_SUCSESS        -the operation was a sucsess
 */
OuterCoreErrors coreInsert(CoreUnit core,COREElement element);

/**
 *   coreRemove         -removes an element (only works with sets)
 * @param core
 * @param element
 * @return
 * CORE_ERROR          -the operation failed
 * CORE_MEMORY_PROBLEM -memory acsess problems
 * CORE_NULL_ARGUMENT  -the arguments were nulll
 * CORE_ELEMENT_DOES_NOT_EXIST  -the removle is impossible
 *  CORE_SUCSESS        -the operation was a sucsess
 */
OuterCoreErrors coreRemove(CoreUnit core, COREElement element);

/**
 *   coreFilter         -filters core according to a criteria (only works with sets)
 * @param core
 * @param filter
 * @param key
 * @return
 * NULL -if any problem accures
 * core unit otherwise
 */
CoreUnit coreFilter(CoreUnit core, FilterCOREElement filter, CoreFilterKey key);

/**
 *   coreFind           -finds specific element(only works with sets)
 * @param unit
 * @param element
 * @return
 * NULL -if there is any problem with the elements of input
 * core element otherwise
 */
COREElement coreFind(CoreUnit unit, COREElement element);

/**
 *   coreSize           -returns the size of the element (for date will return -1)
 * @param unit
 * @return
 * -2 null argument
 * -1 this is a date
 * 0 and higher- the set size
 */
int coreSize(CoreUnit unit);

/**
 *   coreDestroyer      -use it to end the code
 */
void coreDestroyer();

/**
 * coreGetElement     -return the data of the element
 * @return
 * NULL wrong format or element
 * core element otherwise
 */
COREElement coreGetElement(CoreUnit unit);

#endif //OUTERCORE_H
