#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//teh files we are testing
#include "AmountSet.h"
#include "Date.h"
#include "Product.h"
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
   return -2;
}
int refDate()
{
    return 3;
}
void* pseudoCopy(void* pseudoObject)
{
    Product product=pseudoObject;
    return productCopy(product);
}
void pseudoDestroy(void* pseudoObject)
{
    productDestroy(pseudoObject);
}
int pseudoComp(void *first, void* second)
{
    return productEquals(first,second);
}

int main()
{
    int j=7;
    dateInitialiser(intCopy,intDest,intAdvance,diffCulc,&j,refDate);
    j=0;
    Date tmp=dateGenerate();
    Product product= productCreate(1,"apple",HALF_INTEGER_AMOUNT,
                                   intCopy,intDest,tmp,
                                   intCopy,intDest,intCompare,&j,2);
    for(int i=0; i<10; i++)
    {
        if(productAddComponent(product,))
        {
            return 0;
        }
        productDestroy(product);
    }

    return 0;
}
