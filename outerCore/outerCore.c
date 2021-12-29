#include <stdlib.h>

#include "../outerCore.h"
#include "Date.h"
#include "AmountSet.h"

struct CoreUnit_t{
    int type;
    void* element;
};

/**
 * coreBeginner       -the function that you use to begin the date function
 */
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
    CoreUnit copy= malloc(sizeof(struct CoreUnit_t));
    if(!copy)
    {
        return NULL;
    }
    copy->type=((CoreUnit)orgUnit)->type;
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
    CoreUnit sum= coreCreate(((CoreUnit)unit1)->type,NULL,NULL,);
    if(!sum)
    {
        return NULL;
    }
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

/**
 *   coreInsert         -adds to the core (only works with set)
 * @param core
 * @param element
 * @return
 * CORE_ERROR          -the operation failed
 * CORE_MEMORY_PROBLEM -memory acsess problems
 * CORE_NULL_ARGUMENT  -the arguments were nulll
 * CORE_ELEMENT_EXIST  -the addition is impossible
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
CoreUnit coreFilter(void* core, FilterCOREElement filter, CoreFilterKey key);

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
