#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//teh files we are testing
#include "outerCore.h"
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
    int *copy= malloc(sizeof (int*));
    *copy=*(int*)org;
    return copy;
}
void intDest(void* org)
{
    org=NULL;
}
int intCompare(void* first, void* second)
{
    int* one=first;
    int* two=second;
    return one-two;
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

int main()
{
    int j=7;
    dateInitialiser(intCopy,intDest,intAdvance,diffCulc,&j,refDate);
    j=0;
    Date tmp=dateGenerate();
    Product product= productCreate(1,"apple",HALF_INTEGER_AMOUNT,
                                   intCopy,intDest,tmp,
                                   intCopy,intDest,intCompare,&j,2);
    dateDestroy(tmp);
    for(int i=0; i<10; i++)
    {
        Date tmpDate=dateGenerate();
        CoreUnit unit=coreCreate(2,tmpDate);
        if(productAddComponent(product,unit)!=PRODUCT_SUCSESS)
        {
            return 0;
        }
        coreDestroy(unit);
    }
    Date tmp2=dateGenerate();
    Product product2= productCreate(1,"apple",HALF_INTEGER_AMOUNT,
                                   intCopy,intDest,tmp2,
                                   intCopy,intDest,intCompare,&j,2);
    dateDestroy(tmp);
    for(int i=0; i<10; i++)
    {
        Date tmpDate=dateGenerate();
        CoreUnit unit=coreCreate(2,tmpDate);
        if(productAddComponent(product2,unit)!=PRODUCT_SUCSESS)
        {
            return 0;
        }
        coreDestroy(unit);
    }
    productDestroy(product);
    dateCleanInitializer();
    return 0;
}
