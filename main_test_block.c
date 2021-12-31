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
    coreBeginner(intCopy,intDest,intAdvance,diffCulc,&j,refDate);
    j=0;
    CoreUnit tmp= coreCreate(2,NULL,NULL,NULL,-1);
    Product product= productCreate(1,"apple",HALF_INTEGER_AMOUNT,
                                   intCopy,intDest, coreGetElement(tmp),
                                   rasCopy,rasDest,rasCompare,&j,3);
    coreDestroy(tmp);
    for(int i=0; i<10; i++)
    {
        Rational temp= rationalCreate(1,i+1);
        if(productAddComponent(product,temp)!=PRODUCT_SUCSESS)
        {
            return 0;
        }
        rationalDestroy(temp);
    }
    Product product2= productCopy(product);
    for(int i=0; i<10; i++)
    {
        Rational temp= rationalCreate(2,i+1);
        if(productAddComponent(product2,temp)!=PRODUCT_SUCSESS)
        {
            return 0;
        }
        rationalDestroy(temp);
    }
    Product product3= productUnite(product,product2);
    if(!product3)
    {
        printf("bad");
    }
    productDestroy(product);
    Rational k= rationalCreate(1,10);
    CoreUnit toFilter= coreCreate(1,NULL,NULL,NULL,0);
    if(coreSetElement(toFilter, productComponentFilter(product3,greaterThanEpsilon,k),1));
    rationalDestroy(k);
    productDestroy(product);
    productDestroy(product2);
    productDestroy(product3);
    coreDestroyer();
    return 0;
}
