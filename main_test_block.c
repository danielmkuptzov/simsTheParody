#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

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
    Set test= setCreate(intCopy,intDest, intCompare);
    if(!test)
    {
        printf("test 1 failed\n");
        return 0;
    }
    int testarr[10]={2,4,3,5,8,7,6,1,9,10};
    for (int i=0; i < 10; ++i)
    {
        if (setAdd(test, &testarr[i]) != SET_SUCCESS)
        {
            printf("failed at test 2\n");
            setDestroy(test);
            return 0;
        }
    }
    int i=0;
    SET_FOREACH(int*,iter,test)
    {
        int* elemTest=setGetCurrent(test);
        if(*elemTest!=testarr[i])
        {
            printf("whyyyyyyyyyyyyyyyyyyyyy");
            setDestroy(test);
        }
        i++;
    }
    int j=5;
    if(setAdd(test,&j)!=SET_ITEM_ALREADY_EXISTS)
    {
        printf("noooooooooooooooo");
        setDestroy(test);
        return 0;
    }
    if(setGetSize(test)!=10)
    {
        printf("test 3 failed\n");
        setDestroy(test);
        return 0;
    }
    if(setOrder(test)!=SET_SUCCESS)
    {
        printf("failed at test 4\n");
        setDestroy(test);
        return 0;
    }
    i=0;
    SET_FOREACH(int*,order,test)
    {
        if(*order!=(i+1))
        {
            setDestroy(test);
            return 0;
        }
        i++;
    }
    Set liscp= setCopy(test);
    if(!liscp)
    {
        printf("test 8 failed\n");
        setDestroy(test);
        return 0;
    }
    int k=9;
    SET_FOREACH(int*,iter,test)
    {
        if(*iter==k)
        {
            if(setRemove(test,&k)!=SET_SUCCESS)
            {
                printf("fail");
                setDestroy(test);
                return 0;
            }
        }
    }
    if(setClear(test)!=SET_SUCCESS)
    {
        printf("test 7 failed\n");
        setDestroy(test);
        return 0;
    }
    setDestroy(test);
    int key=5;
    Set filtered= setFilter(liscp,intFilter,&key);
    if(!filtered)
    {
        printf("test 9 failed\n");
        setDestroy(liscp);
        return 0;
    }
    setDestroy(liscp);
    if(setClear(filtered)!=SET_SUCCESS)
    {
        printf("final test failed\n");
        setDestroy(filtered);
        return 0;
    }
    setDestroy(filtered);
    return 0;
}
