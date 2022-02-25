#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//teh files we are testing
#include "Kernel.h"
#include "Person.h"

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
bool greaterThanEpsilon(void* ras, void* key)
{
    Kernel epsilon=kernelEpsilonGetter();
    Kernel diff= kernelAddition(epsilon,(Kernel)ras);
    bool resalt=false;
    if(kernelCompeare((Kernel)key,diff))
    {
        resalt=true;
    }
    kernelDestroy(epsilon);
    kernelDestroy(diff);
    return resalt;
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
    char* names[]={"apple","banana","coconout","pinacolada","vine",
                   "laptop","tablet","screen","cigarets","tea"};
    kernelBeginner(intCopy,intDest,intAdvance,diffCulc,&j,refDate);
    Kernel t= kernelCreate(DATE,true,NULL,0,NULL,0,NULL,0,NULL);
    Person test=personCreate(1, kernelGetElement(t),"daniel",intCopy,
                             intDest,intCompare,4);
    if(!test)
    {
        return 0;
    }

    for (int k = 0; k < 10; ++k)
    {
        j=5;
        Kernel tmp= kernelCopy(t);
        int* id=&k;
        void* elements[]={id, kernelGetElement(tmp),names[k],"half integer",&k,
                          id,&k, "medicine"};
        CopyFunc copyArr[]={intCopy, intCopy};
        DestFunc dtours[]={intDest, intDest};
        Kernel product= kernelCreate(PRODUCT,true,elements,8,copyArr,
                                     2,dtours,2,intCompare);
        int den=k+1;
        int* pden=&den;

        void* elem[]={};
        Rational amount= rationalCreate(k+1,2);
        OrderUnit productunit= productUnitCreate(product,amount);
        if(!productunit)
        {
            rationalDestroy(amount);
            productDestroy(product);
            return 0;
        }
        productDestroy(product);
        rationalDestroy(amount);
        if(personAddToWishList(test,productunit)!=PERSON_SUCSESS)
        {
            return 0;
        }
        productUnitDestroy(productunit);
    }
    coreDestroyer();
    return 0;
}
