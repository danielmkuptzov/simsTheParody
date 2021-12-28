#include <stdlib.h>

#include "../outerCore.h"
#include "Date.h"
#include "AmountSet.h"

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

bool coreValid(void* unit)
{
    if(!unit)
    {
        return false;
    }
    if(((CoreUnit)unit)->type==1&& asValid(((CoreUnit)unit)->element)==false)
    {
        return false;
    }
    if(((CoreUnit)unit)->type==2&& dateValid(((CoreUnit)unit)->element))
    {
        return false;
    }
    return true;
}

CoreUnit coreAddition(CoreUnit unit1, CoreUnit unit2)
{
    if(!unit1||!unit2||((CoreUnit)unit1)->type!=((CoreUnit)unit2)->type)
    {
        return NULL;
    }
    CoreUnit sum= coreCreate(((CoreUnit)unit1)->type,NULL);
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
