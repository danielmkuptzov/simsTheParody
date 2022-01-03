#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//teh files we are testing
#include "Rational.h"
#include "outerCore.h"
#include "Product.h"
#include "OrderProduct.h"
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
        Rational temp= rationalCreate(1,10*(i+2));
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
    void * toCore=productComponentFilter(product3,greaterThanEpsilon,k);
    if(coreSetElement(toFilter,toCore,1)!=CORE_SUCSESS)
    {
        printf("why");
    }
    rationalDestroy(k);
    productDestroy(product2);
    Rational amount= rationalCreate(1,2);
    OrderUnit productunit= productUnitCreate(product3,amount);
    if(!productunit)
    {
        rationalDestroy(amount);
        productDestroy(product3);
        return 0;
    }
    productDestroy(product3);
    rationalDestroy(amount);
    for(int i=0;i<10;i++)
    {
        Rational toAdd= rationalCreate(i,1);
        if(productUnitRaiseAmount(productunit,toAdd)!=ORDER_UNIT_SUCSESS)
        {
            return 0;
        }
        rationalDestroy(toAdd);
    }
    productUnitDestroy(productunit);
    coreDestroyer();
    return 0;
}
