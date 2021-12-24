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
    if(!set||!element)
    {
        return false;
    }
    return setIsIn(set->components,element);
}

AmountSetResult asRegister(AmountSet set, ASElement element)
{
    if(!set||!element)
    {
        return AS_NULL_ARGUMENT;
    }
    if(setAdd(set->components,element)!=SET_SUCCESS)
    {
        return AS_ERROR;
    }
    if(asGetSize(set)>1)
    {
        if(setOrder(set->components)!=SET_SUCCESS)
        {
            return AS_ERROR;
        }
    }
    return AS_SUCCESS;
}

AmountSetResult asDelete(AmountSet set, ASElement element)
{
    if(!set||!element)
    {
        return AS_NULL_ARGUMENT;
    }
    if(setIsIn(set->components,element))
    {
        return AS_ITEM_DOES_NOT_EXIST;
    }
    if(setRemove(set->components,element)!=SET_SUCCESS)
    {
        return AS_ERROR;
    }
    return AS_SUCCESS;
}

AmountSetResult asClear(AmountSet set)
{
    if(!set||!(set->components))
    {
        return AS_NULL_ARGUMENT;
    }
    setDestroy(set->components);
    return AS_SUCCESS;
}

ASElement asGetFirst(AmountSet set)
{
    if(!set)
    {
        return NULL;
    }
    return setGetFirst(set->components);
}

ASElement asGetNext(AmountSet set)
{
    if(!set)
    {
        return NULL;
    }
    return setGetNext(set->components);
}

int asCompare(AmountSet firstSet,AmountSet secondSet)
{
    if(!firstSet||!secondSet)
    {
        return 0;
    }
    if(firstSet->type!=secondSet->type)
    {
        return firstSet->type-secondSet->type;
    }
    if(asGetSize(firstSet)!= asGetSize(secondSet))
    {
        return asGetSize(firstSet)- asGetSize(secondSet);
    }
    ASElement iterfir= setGetFirst(firstSet->components);
    SET_FOREACH(ASElement, itersec, secondSet->components)
    {
        int diff=(setGetComp(firstSet->components))(iterfir,itersec);
        if(diff!=0)
        {
            return diff;
        }
        iterfir= setGetNext(firstSet->components);
    }
    return 0;
}

