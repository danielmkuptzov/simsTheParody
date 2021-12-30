#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//teh files we are testing
#include "Rational.h"
#include "outerCore.h"
#include "Product.h"
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
    coreBeginner(intCopy,intDest,intAdvance,diffCulc,&j,refDate);
    j=0;
    CoreUnit tmp= coreCreate(2,NULL,NULL,NULL,-1);
    Product product= productCreate(1,"apple",HALF_INTEGER_AMOUNT,
                                   intCopy,intDest, coreGetElement(tmp),
                                   coreCopy,coreDestroy,coreCompeare,&j,2);
    coreDestroy(tmp);
    for(int i=0; i<10; i++)
    {
        CoreUnit unit=coreCreate(2,NULL,NULL,NULL,1);
        if(productAddComponent(product,unit)!=PRODUCT_SUCSESS)
        {
            return 0;
        }
        coreDestroy(unit);
    }
    Product product2= productCopy(product);
    for(int i=0; i<10; i++)
    {
        CoreUnit unit= coreCreate(2, NULL,NULL,NULL,-1);
        if(productAddComponent(product2,unit)!=PRODUCT_SUCSESS)
        {
            return 0;
        }
        coreDestroy(unit);
    }
    Product product3= productUnite(product,product2);
    if(!product3)
    {
        printf("bad");
    }
    productDestroy(product);
    productDestroy(product2);
    productDestroy(product3);
    coreDestroyer();
    return 0;
}
