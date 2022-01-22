#include <stdlib.h>

#include "../outerCore.h"
#include "Date.h"
#include "AmountSet.h"

struct CoreUnit_t{
    int type;
    void* element;
};

void coreBeginner(CopyRefDate copyFunc, FreeRefDate freeFunc,
                  RefDateAdvance advanceFunc,DifferenceCalculator diffFunc,
                  ReferanceDate date, DayOne firstDay)
{
    dateInitialiser(copyFunc,freeFunc,advanceFunc,diffFunc,date,firstDay);
}


CoreUnit coreCreate(int type, CopyCOREElement copyfunc, FreeCOREElement freefunc,
                    CompareCOREElements compfunc, int asType)
{
    if(type<1||type>2)
    {
        return NULL;
    }
    CoreUnit new= malloc(sizeof(struct CoreUnit_t));
    if(!new)
    {
        return NULL;
    }

    switch (type)
    {
        case 1:
        {
            CopyASElement copy= copyfunc;
            FreeASElement freePointer=freefunc;
            CompareASElements comparison=compfunc;
            new->type=1;
            new->element= asCreate(copy,freePointer,comparison,asType);
            break;
        }
        case 2:
        {
            new->type=2;
            new->element= dateCopy(dateGenerate());
            break;
        }
    }
    return new;
}

void coreDestroy(void* unit)
{
    if(!unit)
    {
        return;
    }
    if(((CoreUnit)unit)->type==1)
    {
        asDestroy(((CoreUnit)unit)->element);
    }
    if(((CoreUnit)unit)->type==2)
    {
        dateDestroy(((CoreUnit)unit)->element);
    }
    free(unit);
}

void* coreCopy(void* orgUnit)
{
    if(!orgUnit)
    {
        return NULL;
    }
    CoreUnit copy= coreCreate(1,NULL,NULL,NULL,1);
    if(!copy)
    {
        return NULL;
    }
    copy->type=((CoreUnit)orgUnit)->type;
    asDestroy((AmountSet)copy->element);
    if(copy->type==1)
    {
        AmountSet toCopy=((CoreUnit)orgUnit)->element;
        copy->element= asCopy(toCopy);
    }
    else
    {
        Date dateCp=((CoreUnit)orgUnit)->element;
        copy->element=dateCopy(dateCp);
    }
    if(!copy->element)
    {
        coreDestroy(copy);
        return NULL;
    }
    return copy;
}

int coreCompeare(void* first, void* second)
{
    if(!first||!second||((CoreUnit)first)->type!=((CoreUnit)second)->type)
    {
        return -1024;
    }
    switch (((CoreUnit)first)->type) {
        case 1:
        {
            return asCompare(((CoreUnit)first)->element,((CoreUnit)second)->element);
        }
        case 2:
        {
            return dateCompeare(((CoreUnit)first)->element,((CoreUnit)second)->element);
        }
        default:
        {
            return -1345;
        }
    }
}

CoreUnit coreAddition(CoreUnit unit1, CoreUnit unit2)
{
    if(!unit1||!unit2||((CoreUnit)unit1)->type!=((CoreUnit)unit2)->type)
    {
        return NULL;
    }
    CoreUnit sum= coreCreate(1, NULL,NULL,NULL,1);
    if(!sum)
    {
        return NULL;
    }
    sum->type=((CoreUnit)unit1)->type;
    asDestroy((AmountSet)sum->element);
    if(sum->type==1)
    {
        sum->element= asUnite(((CoreUnit)unit1)->element,((CoreUnit)unit2)->element);
        if(!sum->element)
        {
            coreDestroy(sum);
            return NULL;
        }
    }
    else
    {
        sum->element= dateSum(((CoreUnit)unit1)->element,((CoreUnit)unit2)->element);
        if(!sum->element)
        {
            coreDestroy(sum);
            return NULL;
        }
    }
    return sum;
}

OuterCoreErrors coreInsert(CoreUnit core,COREElement element)
{
    if(!core||!element)
    {
        return CORE_NULL_ARGUMENT;
    }
    if(core->type!=1)
    {
        return CORE_ERROR;
    }
    AmountSetResult resalt= asRegister((AmountSet)(core->element),element);
    if(resalt==AS_ITEM_ALREADY_EXISTS)
    {
        return CORE_ELEMENT_EXIST;
    }
    if(resalt==AS_NULL_ARGUMENT)
    {
        return CORE_MEMORY_PROBLEM;
    }
    return CORE_SUCSESS;
}

OuterCoreErrors coreRemove(CoreUnit core, COREElement element)
{
    if(!core||!element)
    {
        return CORE_NULL_ARGUMENT;
    }
    if(core->type!=1)
    {
        return CORE_ERROR;
    }
    AmountSetResult resalt= asDelete((AmountSet)(core->element),element);
    if(resalt==AS_NULL_ARGUMENT)
    {
        return CORE_NULL_ARGUMENT;
    }
    if(resalt==AS_ITEM_DOES_NOT_EXIST)
    {
        return CORE_ELEMENT_DOES_NOT_EXIST;
    }
    return CORE_SUCSESS;
}

void* coreFilter(CoreUnit core, FilterCOREElement filter, CoreFilterKey key)
{
    if(!core||!filter||!key)
    {
        return NULL;
    }
    if(core->type!=1)
    {
        return NULL;
    }
    CoreUnit filtered= coreCreate(1,NULL,NULL,NULL,1);
    if(!filtered)
    {
        return NULL;
    }
    asDestroy((AmountSet)core->element);
    core->element= asFilter((AmountSet)core->element,filter,key);
    if(!filtered->element)
    {
        coreDestroy(filtered);
        return NULL;
    }
    return filtered;
}

COREElement coreFind(CoreUnit unit, COREElement element)
{
    if(!unit||!element)
    {
        return NULL;
    }
    if(unit->type!=1)
    {
        return NULL;
    }
    AS_FOREACH(COREElement,iter,(AmountSet)unit->element)
    {
        if((asGetCompeare((AmountSet)unit->element))(iter,element)==0)
        {
            return asGetCurrent((AmountSet)unit->element);
        }
    }
    return NULL;
}

int coreSize(CoreUnit unit)
{
    if(!unit)
    {
        return -2;
    }
    if(unit->type!=1)
    {
        return -1;
    }
    return asGetSize((AmountSet)unit->element);
}

void coreDestroyer()
{
    dateCleanInitializer();
}

COREElement coreGetElement(CoreUnit unit)
{
    if(!unit)
    {
        return NULL;
    }
    return unit->element;
}

/**
 * coreSetElement     -changes the element
 * @param unit
 * @param element
 * @return
 * CORE_ERROR -null or wrong type
 * CORE_SUCSESS -the operation was sucssesful
 */
OuterCoreErrors coreSetElement(CoreUnit unit, COREElement element, int type)
{
    if(!unit||!element)
    {
        return CORE_NULL_ARGUMENT;
    }
    switch (unit->type)
    {
        case 1:
        {
            asDestroy((AmountSet)unit->element);
            break;
        }
        case 2:
        {
            dateDestroy((Date)unit->element);
            break;
        }
    }
    switch (type)
    {
        case 1:
        {
            unit->type=1;
            unit->element= asCopy((AmountSet)element);
            if(!unit->element)
            {
                return CORE_ERROR;
            }
            return CORE_SUCSESS;
        }
        case 2:
        {
            unit->type=2;
            unit->element= dateCopy((Date)element);
            if(!unit->element)
            {
                return CORE_ERROR;
            }
            return CORE_SUCSESS;
        }
    }
    return CORE_ERROR;
}

void* coreGetFirst(CoreUnit unit)
{
    if(!unit)
    {
        return NULL;
    }
    if(unit->type!=1)
    {
        return NULL;
    }
    return asGetFirst((AmountSet)unit->element);
}

void* coreGetNext(CoreUnit unit)
{
    if(!unit||unit->type!=1)
    {
        return NULL;
    }
    return asGetNext((AmountSet)unit->element);
}

