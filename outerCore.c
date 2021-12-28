#include <stdlib.h>

#include "outerCore.h"

struct CoreUnit_t{
    int type;
    void* element;
};

CoreUnit coreCreate(int type, void* element)
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
            AmountSet set=element;
            new->type=1;
            new->element= asCopy(set);
            break;
        }
        case 2:
        {
            Date tmpDate=element;
            new->type=2;
            new->element= dateCopy(tmpDate);
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
    CoreUnit copy= coreCreate(((CoreUnit)orgUnit)->type,((CoreUnit)orgUnit)->element);
    if(!copy)
    {
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
