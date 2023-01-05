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
    dateInitialiser(copyFunc,freeFunc,advanceFunc,diffFunc,date,firstDay,ctour,dtour,zero,);
}


CoreUnit coreCreate(int type, CopyCOREElement copyfunc, FreeCOREElement freefunc,
                    CompareCOREElements compfunc, int asType)
{
    if(type<NAMOUNT_SET||type>NDATE)
    {
        return NULL;
    }
    CoreUnit newCore= malloc(sizeof(struct CoreUnit_t));
    if(!newCore)
    {
        return NULL;
    }

    switch (type)
    {
        case NAMOUNT_SET:
        {
            CopyASElement copy= copyfunc;
            FreeASElement freePointer=freefunc;
            CompareASElements comparison=compfunc;
            newCore->type=1;
            newCore->element= asCreate(copy,freePointer,comparison,asType);
            break;
        }
        case NDATE:
        {
            newCore->type=2;
            newCore->element= dateCopy(dateGenerate());
            break;
        }
    }
    return newCore;
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
    CoreUnit copy= coreCreate(NAMOUNT_SET,NULL,NULL,NULL,1);
    if(!copy)
    {
        return NULL;
    }
    copy->type=((CoreUnit)orgUnit)->type;
    asDestroy((AmountSet)copy->element);
    if(copy->type==NAMOUNT_SET)
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
        case NAMOUNT_SET:
        {
            return asCompare(((CoreUnit)first)->element,((CoreUnit)second)->element);
        }
        case NDATE:
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
    CoreUnit sum= coreCreate(NAMOUNT_SET, NULL,NULL,NULL,NAMOUNT_SET);
    if(!sum)
    {
        return NULL;
    }
    sum->type=((CoreUnit)unit1)->type;
    asDestroy((AmountSet)sum->element);
    if(sum->type==NAMOUNT_SET)
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

CoreUnit coreFilter(CoreUnit core, FilterCOREElement filter, CoreFilterKey key)
{
    if(!core||!filter||!key)
    {
        return NULL;
    }
    if(core->type!=NAMOUNT_SET)
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
    if(unit->type!=NAMOUNT_SET)
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
    if(unit->type!=NAMOUNT_SET)
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

OuterCoreErrors coreSetElement(CoreUnit unit, COREElement element, int type)
{
    if(!unit||!element)
    {
        return CORE_NULL_ARGUMENT;
    }
    switch (unit->type)
    {
        case NAMOUNT_SET:
        {
            asDestroy((AmountSet)unit->element);
            break;
        }
        case NDATE:
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
    if(unit->type!=NAMOUNT_SET)
    {
        return NULL;
    }
    return asGetFirst((AmountSet)unit->element);
}

void* coreGetNext(CoreUnit unit)
{
    if(!unit||unit->type!=NAMOUNT_SET)
    {
        return NULL;
    }
    return asGetNext((AmountSet)unit->element);
}

CompareCOREElements coreGetCompare(CoreUnit unit)
{
    if(!unit||unit->type!=DEFALT)
    {
        return NULL;
    }
    return asGetCompeare(unit->element);
}
