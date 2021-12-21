//
// Created by danie on 01/12/2021.
//
#include <stdlib.h>

#include "set.h"
#include "list.h"

struct Set_t{
    List  elements;
    compareSetElements setcomp;
};


Set setCreate(copySetElements copyElement, freeSetElements freeElement, compareSetElements compareElements)
{
    Set new= malloc(sizeof(struct Set_t));
    if(!new)
    {
        return NULL;
    }
    new->elements= listCreate(copyElement, freeElement);
    if(!(new->elements))
    {
        free(new);
        return NULL;
    }
    new->setcomp=compareElements;
    return new;
}

Set setCopy(Set set)
{
    if(set)
    {
        return NULL;
    }
    Set copy= setCreate(NULL,
                        NULL,set->setcomp);
    if(!copy)
    {
        return NULL;
    }
    listDestroy(copy->elements);
    copy->elements= listCopy(set->elements);
    if(!(copy->elements))
    {
        setDestroy(copy);
        return NULL;
    }
    copy->setcomp=set->setcomp;
    return copy;
}

void setDestroy(Set set)
{
    if(!set)
    {
        return;
    }
    if(set->elements)
    {
        listDestroy(set->elements);
    }
    free(set);
}

int setGetSize(Set set)
{
    return listGetSize(set->elements);
}

bool setIsIn(Set set, SetElement element)
{
    if((!set)||(!set->elements)||(!element))
    {
        return false;
    }
    LIST_FOREACH(SetElement,iter,set->elements)
    {
        if(set->setcomp(iter,element)==0)
        {
            return true;
        }
    }
    return false;
}

SetElement setGetFirst(Set set)
{
    if(!set)
    {
        return NULL;
    }
    return listGetFirst(set->elements);
}

SetElement setGetNext(Set set)
{
    if(!set)
    {
        return NULL;
    }
    return listGetNext(set->elements);
}

SetResult setAdd(Set set, SetElement element)
{
    if(!set||!set->elements||!element)
    {
        return SET_NULL_ARGUMENT;
    }
    if(setIsIn(set,element))
    {
        return SET_ITEM_ALREADY_EXISTS;
    }
    ListResult resalt=listInsertLast(set->elements,element);
    if(resalt==LIST_SUCCESS)
    {
        return SET_SUCCESS;
    }
    return SET_OUT_OF_MEMORY;
}

SetResult setOrder(Set set)
{
    if(!set||!set->elements)
    {
        return SET_NULL_ARGUMENT;
    }
    if(listSort(set->elements,set->setcomp)==LIST_SUCCESS)
    {
        return SET_SUCCESS;
    }
    return SET_OUT_OF_MEMORY;
}

Set setFilter(Set set, FilterSetElement filterElement, SetFilterKey key)
{
    if(!set||!filterElement||!key)
    {
        return NULL;
    }
    Set filtered= setCreate(NULL,NULL,set->setcomp);
    if(!filtered)
    {
        return NULL;
    }
    listDestroy(filtered->elements);
    filtered->elements= listFilter(set->elements,filterElement,key);
    if(!filtered->elements)
    {
        setDestroy(filtered);
        return NULL;
    }
    return filtered;
}


/**
* 	setRemove: Removes an element from the set. The element is found using the
* 	comparison function given at initialization. Once found, the element is
* 	removed and deallocated using the free function supplied at initialzation.
*  Iterator's value is undefined after this operation.
*
* @param set -
* 	The set to remove the element from.
* @param element
* 	The element to remove from the set. The element will be freed using the
* 	free function given at initialization.
* @return
* 	SET_NULL_ARGUMENT if a NULL was sent as set
* 	SET_ITEM_DOES_NOT_EXIST if the element doesn't exist in the set
* 	SET_SUCCESS if the element was successfully removed.
*/
SetResult setRemove(Set set, SetElement element);

/**
* setClear: Removes all elements from target set.
* The elements are deallocated using the stored free function
* @param set
* 	Target set to remove all element from
* @return
* 	SET_NULL_ARGUMENT - if a NULL pointer was sent.
* 	SET_SUCCESS - Otherwise.
*/
SetResult setClear(Set);
