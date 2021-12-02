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

int main()
{
    List test= listCreate(intCopy,intDest);
    if(!test)
    {
        printf("test 1 failed\n");
        return 0;
    }
    int tmp= 7;
    int* ptmp= &tmp;
    if(listInsertFirst(test,ptmp)==LIST_SUCCESS)
    {
        printf("failed at test 2\n");
        listDestroy(test);
        return 0;
    }

}
