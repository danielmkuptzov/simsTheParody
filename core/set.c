#include <stdlib.h>
#include <stdio.h>

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
    if(!set)
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
    if(setClear(set)!=SET_SUCCESS)
    {
        printf("error\n");
    }
    free(set);
}

int setGetSize(Set set)
{
    if(!set)
    {
        return -1;
    }
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
    return SET_ERROR;
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

SetResult setRemove(Set set, SetElement element)
{
    if(!set||!element||!set->elements)
    {
        return SET_NULL_ARGUMENT;
    }
    if(!setIsIn(set,element))
    {
        return SET_ITEM_DOES_NOT_EXIST;
    }
    LIST_FOREACH(SetElement,iter,set->elements)
    {
        if(set->setcomp(iter,element)==0)
        {
            if(listRemoveCurrent(set->elements)==LIST_SUCCESS)
            {
                return SET_SUCCESS;
            }
            return SET_ERROR;
        }
    }
    return SET_ERROR;
}

SetResult setClear(Set set)
{
    if(!set)
    {
        return SET_NULL_ARGUMENT;
    }
    List toDestroy=set->elements;
    set->elements=NULL;
    listDestroy(toDestroy);
    return SET_SUCCESS;
}

SetElement setGetCurrent(Set set)
{
    if(!set)
    {
        return NULL;
    }
    return listGetCurrent(set->elements);
}

copySetElements setGetCopy(Set set)
{
    if(!set)
    {
        return NULL;
    }
    return listGetCopy(set->elements);
}

freeSetElements setGetFree(Set set)
{
    if(!set)
    {
        return NULL;
    }
    return listGetFree(set->elements);
}

compareSetElements setGetComp(Set set)
{
    if(!set)
    {
        return NULL;
    }
    return set->setcomp;
}
