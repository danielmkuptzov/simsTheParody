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
        printf("test 1 failed");
        return 0;
    }

}
