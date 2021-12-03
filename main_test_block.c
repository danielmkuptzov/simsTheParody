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
    free((int*)org);
}

int intCompare(void* first, void* second)
{
    return *(int*)first-*(int*)second;
}
int main()
{
    List test= listCreate(intCopy,intDest);
    if(!test)
    {
        printf("test 1 failed\n");
        return 0;
    }
    for (int i = 0; i < 100; ++i)
    {
        int tmp= i;
        int* ptmp= &tmp;
        if(listInsertFirst(test,ptmp)==LIST_SUCCESS)
        {
            printf("failed at test 2\n");
            listDestroy(test);
            return 0;
        }
        tmp=i+1;
        if (listInsertLast(test,ptmp));
    }
    if(listSort(test,intCompare)!=LIST_SUCCESS)
    {
        printf("failed at test 3\n");
        listDestroy(test);
        return 0;
    }

}
