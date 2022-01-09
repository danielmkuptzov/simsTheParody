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
void* rasCopy(void* org)
{
    return rationalCopy((Rational)org);
}
void rasDest(void* org)
{
    rationalDestroy((Rational)org);
}
int rasCompare(void* first, void* second)
{
    return rationalCompare((Rational)first,(Rational)second);
}
bool greaterThanEpsilon(void* ras, void* key)
{
    Rational epsilon= rationalCreate(0,1);
    Rational diff= rationalAddition(epsilon,(Rational)ras);
    bool resalt=false;
    if(rationalEqual((Rational)key,diff))
    {
        resalt=true;
    }
    rationalDestroy(epsilon);
    rationalDestroy(diff);
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
    coreBeginner(intCopy,intDest,intAdvance,diffCulc,&j,refDate);
    CoreUnit t=coreCreate(2,NULL,NULL,NULL,-1);
    Person test=personCreate(1,t,"daniel",intCopy,
                             intDest,intCompare,4);
    if(!test)
    {
        return 0;
    }
    for (int k = 0; k < 10; ++k)
    {
        j=0;
        CoreUnit tmp= coreCreate(2,NULL,NULL,NULL,-1);
        Product product= productCreate(k+1,names[k],HALF_INTEGER_AMOUNT,
                                       intCopy,intDest, coreGetElement(tmp),
                                       rasCopy,rasDest,rasCompare,&j,3);
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
