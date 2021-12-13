#include <stdio.h>
#include <stdlib.h>
#include "List.h"

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

bool intFilter(void* data, void* power)
{
    if(*(int*)data/10<=*(int*)power)
    {
        return true;
    }
    return false;
}


int main()
{
    List test= listCreate(intCopy,intDest);
    if(!test)
    {
        printf("test 1 failed\n");
        return 0;
    }
    int testarr[10]={2,4,3,5,8,7,6,1,9,10};
    for (int i=0; i < 10; ++i)
    {
        if (listInsertLast(test, &testarr[i]) != LIST_SUCCESS)
        {
            printf("failed at test 2\n");
            listDestroy(test);
            return 0;
        }
    }
    int i=0;
    LIST_FOREACH(int*,iter,test)
    {
        int* elemTest=listGetCurrent(test);
        if(*elemTest!=testarr[i])
        {
            printf("whyyyyyyyyyyyyyyyyyyyyy");
            listDestroy(test);
        }
        i++;
    }
    if(listGetSize(test)!=10)
    {
        printf("test 3 failed\n");
        listDestroy(test);
        return 0;
    }
    if(listSort(test,intCompare)!=LIST_SUCCESS)
    {
        printf("failed at test 4\n");
        listDestroy(test);
        return 0;
    }
    i=0;
    LIST_FOREACH(int*,order,test)
    {
        if(*order!=(i+1))
        {
            listDestroy(test);
            return 0;
        }
        i++;
    }
    List liscp= listCopy(test);
    if(!liscp)
    {
        printf("test 8 failed\n");
        listDestroy(test);
        return 0;
    }
    if(listClear(test)!=LIST_SUCCESS)
    {
        printf("test 7 failed\n");
        listDestroy(test);
        return 0;
    }
    listDestroy(test);
    int key=5;
    List filtered= listFilter(liscp,intFilter,&key);
    if(!filtered)
    {
        printf("test 9 failed\n");
        listDestroy(liscp);
        return 0;
    }
    listDestroy(liscp);
    if(listClear(filtered)!=LIST_SUCCESS)
    {
        printf("final test failed\n");
        listDestroy(filtered);
        return 0;
    }
    listDestroy(filtered);
    return 0;
}
