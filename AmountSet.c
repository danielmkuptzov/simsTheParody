#include <stdlib.h>

#include "AmountSet.h"
#include "set.h"

struct AmountSet_t{
    int type;
    Set components;
};

AmountSet asCreate(CopyASElement copyElement,
                   FreeASElement freeElement,
                   CompareASElements compareElements,
                   int type)
{
    AmountSet new= malloc(sizeof (struct AmountSet_t));
    if(!new)
    {
        return NULL;
    }
    new->components= setCreate(copyElement, freeElement, compareElements);
    if(!(new->components))
    {
        free(new);
        return NULL;
    }
    new->type=type;
    return new;
}

void asDestroy(AmountSet set)
{
    if(!set)
    {
        return;
    }
    asClear(set);
    free(set);
}

AmountSet asCopy(AmountSet set)
{
    if(!set)
    {
        return NULL;
    }
    AmountSet copy= asCreate(NULL,NULL,NULL,set->type);
    setDestroy(copy->components);
    copy->components= setCopy(set->components);
    if(!(copy->components))
    {
        asDestroy(copy);
        return NULL;
    }
    return copy;
}

int asGetSize(AmountSet set)
{
    if(!set)
    {
        return -1;
    }
    return setGetSize(set->components);
}

bool asContains(AmountSet set, ASElement element)
{
    return setIsIn(set->components,element);
}

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
AmountSetResult asRegister(AmountSet set, ASElement element)
{
    if(!)
}

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
 * resalt- standart comparison
 */
int asCompare(AmountSet firstSet,AmountSet secondSet);
