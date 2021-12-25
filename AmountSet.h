#ifndef AMOUNT_SET_H_
#define AMOUNT_SET_H_

#include <stdio.h>
#include <stdbool.h>

/**
 * Generic Amount Set Container
 *
 * Implements a sorted amount set container type.
 * The set has an internal iterator for external use. For all functions
 * where the state of the iterator after calling that function is not stated,
 * it is undefined. That is you cannot assume anything about it.
 * The set is sorted in ascending order - iterating over the set is done in the
 * same order.
 *
 * The following functions are available:
 *   asCreate           - Creates a new empty set
 *   asDestroy          - Deletes an existing set and frees all resources
 *   asCopy             - Copies an existing set
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

/** Type for defining the set */
typedef struct AmountSet_t *AmountSet;

/** Type used for returning error codes from amount set functions */
typedef enum AmountSetResult_t {
    AS_SUCCESS = 0,
    AS_OUT_OF_MEMORY,
    AS_NULL_ARGUMENT,
    AS_ITEM_ALREADY_EXISTS,
    AS_ITEM_DOES_NOT_EXIST,
    AS_ERROR
} AmountSetResult;

/** Element data type for amount set container */
typedef void *ASElement;

/** Type of function for copying an element of the set */
typedef ASElement (*CopyASElement)(ASElement);

/** Type of function for deallocating an element of the set */
typedef void (*FreeASElement)(ASElement);

/**
 * Type of function used by the set to identify equal set elements.
 * This function should return:
 *     A positive integer if the first element is greater;
 *     0 if they're equal;
 *     A negative integer if the second element is greater.
 */
typedef int (*CompareASElements)(ASElement, ASElement);

/**
* Use this type to pass extra information needed by the filtering function
* when calling listFilter. (See the example for a FilterListElement function)
*/
typedef void* AsFilterKey;

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
typedef bool(*FilterASElement)(ASElement, AsFilterKey);

/**
 * asCreate: Allocates a new empty amount set.
 *
 * @param type- the numerical importance of the type of the amount set
 * @param copyElement - Function pointer to be used for copying elements into
 *     the set or when copying the set.
 * @param freeElement - Function pointer to be used for removing data elements from
 *     the set.
 * @param compareElements - Function pointer to be used for comparing elements
 *     inside the set. Used to check if new elements already exist in the set.
 * @return
 *     NULL - if one of the parameters is NULL or allocations failed.
 *     A new amount set in case of success.
 */
AmountSet asCreate(CopyASElement copyElement,
                   FreeASElement freeElement,
                   CompareASElements compareElements,
                   int type);

/**
 * asDestroy: Deallocates an existing amount set. Clears all elements by using
 * the stored free functions.
 *
 * @param set - Target set to be deallocated. If set is NULL nothing will be done.
 */
void asDestroy(AmountSet set);

/**
 * asCopy: Creates a copy of target set.
 *
 * Iterator values for both sets are undefined after this operation.
 *
 * @param set - Target set.
 * @return
 *     NULL if a NULL was sent or a memory allocation failed.
 *     An amount set containing the same elements (and amounts) as set, otherwise.
 */
AmountSet asCopy(AmountSet set);

/**
 * asGetSize: Returns the number of elements in a set.
 *
 * Iterator's state is unchanged after this operation.
 *
 * @param set - The set which size is requested.
 * @return
 *     -1 if a NULL pointer was sent.
 *     Otherwise the number of elements in the set.
 */
int asGetSize(AmountSet set);

/**
 * asContains: Checks if an element exists in the set.
 *
 * The element will be considered in the set if one of the elements in the set
 * it determined equal using the comparison function used to initialize the set.
 * Iterator's state is unchanged after this operation.
 *
 * @param set - The set to search in.
 * @param element - The element to look for. Will be compared using the
 *     comparison function.
 * @return
 *     false - if the input set is null, or if the element was not found.
 *     true - if the element was found in the set.
 */
bool asContains(AmountSet set, ASElement element);

/**
 * asRegister: Add a new element into the set.
 *
 * The element is added with an initial amount of 0.
 * Iterator's value is undefined after this operation.
 *
 * @param set - The target set to which the element is added.
 * @param element - The element to add.
 * @return
 *     AS_NULL_ARGUMENT - if a NULL argument was passed.
 *     AS_ITEM_ALREADY_EXISTS - if an equal element already exists in the set.
 *     AS_SUCCESS - if the element was added successfully.
 */
AmountSetResult asRegister(AmountSet set, ASElement element);

/**
 * asDelete: Delete an element completely from the set.
 *
 * This is the opposite of asRegister. The element is deallocated using the
 * stored free function.
 * Iterator's value is undefined after this operation.
 *
 * @param set - The target set from which the element is deleted.
 * @param element - The element to delete.
 * @return
 *     AS_NULL_ARGUMENT - if a NULL argument was passed.
 *     AS_ITEM_DOES_NOT_EXIST - if the element doesn't exist in the set.
 *     AS_SUCCESS - if the element was deleted successfully.
 */
AmountSetResult asDelete(AmountSet set, ASElement element);

/**
 * asClear: Deletes all elements from target set.
 *
 * The elements are deallocated using the stored free function.
 * Iterator's value is undefined after this operation.
 *
 * @param set - Target set to delete all elements from.
 * @return
 *     AS_NULL_ARGUMENT - if a NULL pointer was sent.
 *     AS_SUCCESS - Otherwise.
 */
AmountSetResult asClear(AmountSet set);

/**
 * asGetFirst: Sets the internal iterator (also called current element) to
 * the first  element in the set. The first element is the smallest element
 * of the set, according to the set's comparison function.
 * Use this to start iterating over the set.
 * To continue iteration use asGetNext.
 *
 * @param set - The set for which to set the iterator and return the first
 *     element.
 * @return
 *     NULL if a NULL pointer was sent or the set is empty.
 *     The first element of the set otherwise
 */
ASElement asGetFirst(AmountSet set);

/**
 * asGetNext: Advances the set iterator to the next element and returns it.
 * The iteration is in ascending order on the set's elements, according to the
 * set's comparison function.
 *
 * @param set - The set for which to advance the iterator
 * @return
 *     NULL if reached the end of the set, or the iterator is at an invalid state
 *     or a NULL sent as argument
 *     The next element on the set in case of success
 */
ASElement asGetNext(AmountSet set);

/**
 * asCompare- compares between sets
 * @param firstSet- amount set to cmpeare
 * @param secondSet- amount set to cmpeare
 *
 * @return three options:
 * positive- the first one is greater
 * negative- the second one is greater
 *
 */
int asCompare(AmountSet firstSet,AmountSet secondSet);

/**
 * asGetCurrent- gives the current element
 *
 * @param set- the set from which we take the current
 *
 * @return
 * NULL- IF THE SET IS PROBLEMATIC
 * pointer to the element othervise
 */
ASElement asGetCurrent(AmountSet set);

/**
 * asFilter- filters the amount set by given critiria
 *
 * @param set- the set we filter
 * @param filter- the filter function
 * @param key- the key we filter
 *
 * @return
 * NULL- failed allocation or null parameters
 * amount set otherwise
 */
AmountSet asFilter(AmountSet set, FilterASElement filter, AsFilterKey key);

/**
 *   asValid- checks the fact that the amount set is ok
 *   @param set- the set we need to check vlidity
 *
 *   @return
 *   true- valid
 *   false- otherwise
 */
bool asValid(AmountSet set);

/**
 * Macro for iterating over a set.
 * Declares a new iterator for the loop.
 */
#define AS_FOREACH(type, iterator, set)          \
    for(type iterator = (type) asGetFirst(set) ; \
        iterator ;                               \
        iterator = asGetNext(set))

#endif /* AMOUNT_SET_H_ */
