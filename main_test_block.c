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

int main()
{
    AmountSet test= asCreate(intCopy,intDest, intCompare, 1);
    if(!test)
    {
        printf("test 1 failed\n");
        return 0;
    }
    int testarr[10]={2,4,3,5,8,7,6,1,9,10};
    for (int i=0; i < 10; ++i)
    {
        if (asRegister(test, &testarr[i]) != AS_SUCCESS)
        {
            printf("failed at test 2\n");
            asDestroy(test);
            return 0;
        }
    }
    int i=0;
    AS_FOREACH(int*,order,test)
    {
        if(*order!=(i+1))
        {
            asDestroy(test);
            return 0;
        }
        i++;
    }
    int j=5;
    if(asRegister(test,&j)!=AS_ITEM_ALREADY_EXISTS)
    {
        printf("noooooooooooooooo");
        asDestroy(test);
        return 0;
    }
    if(asGetSize(test)!=10)
    {
        printf("test 3 failed\n");
        asDestroy(test);
        return 0;
    }
    AmountSet liscp= asCopy(test);
    if(!liscp)
    {
        printf("test 8 failed\n");
        asDestroy(test);
        return 0;
    }
    if(asCompare(test,liscp)!=0)
    {
        asDestroy(test);
        asDestroy(liscp);
        return 0;
    }
    int k=9;
    AS_FOREACH(int*,iter,test)
    {
        if(*iter==k)
        {
            if(asDelete(test,&k)!=AS_SUCCESS)
            {
                asDestroy(test);
                asDestroy(liscp);
                return 0;
            }
        }
    }
    if(asClear(test)!=AS_SUCCESS)
    {
        asDestroy(test);
        asDestroy(liscp);
        return 0;
    }
    asDestroy(test);
    int key=5;
    AmountSet filtered= asFilter(liscp,intFilter,&key);
    if(!filtered)
    {
        printf("test 9 failed\n");
        asDestroy(liscp);
        return 0;
    }
    AmountSet dataSet= asCreate(dateCp,freeDate,datecomp,2);
    dateInitialiser();
    for(i=0; i<10; i++)
    {
        if(asRegister(dataSet, dateGenerate())!=AS_SUCCESS)
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
