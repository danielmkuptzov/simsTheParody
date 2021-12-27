#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//teh files we are testing
#include "AmountSet.h"
#include "Date.h"

void* dateCp(void *date)
{
    return dateCopy(date);
}

void freeDate(void* date)
{
    dateDestroy(date);
}

int datecomp(void* date1, void* date2)
{
    return dateCompeare(date1, date2);
}


void* intCopy(void* org)
{
    int *copy=(int*)org;
    return copy;
}

void intDest(void* org)
{
    org=NULL;
}

int intCompare(void* first, void* second)
{
    return *(int*)first-*(int*)second;
}

bool intFilter(void* data, void* limit)
{
    int* element=data;
    int* key=limit;
    if((*element)<(*key))
    {
        return true;
    }
    return false;
}

void intAdvance(void* org)
{
    (*(int*)org)++;
}

int diffCulc()
{
   return 3;
}



int main()
{
    int j=0;
    AmountSet dateSet= asCreate(dateCp,freeDate,datecomp,1);
    dateInitialiser(intCopy,intDest,intCompare,intAdvance,diffCulc,&j);
    for(int i=0; i<10; i++)
    {
        if(asRegister(dateSet, dateGenerate())!=AS_SUCCESS)
        {
            return 0;
        }
    }
    if(asCompare(dataSet,liscp)!=1)
    {
        return 0;
    }
    asDestroy(liscp);
    if(asClear(filtered)!=AS_SUCCESS)
    {
        printf("final test failed\n");
        asDestroy(filtered);
        return 0;
    }
    asDestroy(filtered);
    asDestroy(dataSet);
    return 0;
}
