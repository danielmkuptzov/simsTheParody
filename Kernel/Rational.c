#include <stdlib.h>

#include "Rational.h"

struct Rational_t {
    int numerator;
    int denumerator;
};

static int rationalGcd(int a, int b)
{
    int gcd =1;
    for(int i=1; i <= a && i <=b; ++i)
    {
        if(a%i==0 && b%i==0)
        {
            gcd=i;
        }
    }
    return gcd;
}

static int rationalToDoubleConverter(Rational rational)
{
    if(rational->numerator==0)
    {
        return 0;
    }
    if(rational->numerator>0)
    {
        return 1;
    }
    return -1;
}

static int powerInt(int base, int power)
{
    int resalt=1;
    for(int i=0; i<power; i++)
    {
        resalt=resalt*base;
    }
    return resalt;
}

Rational rationalCreate(int numerator,int denumerator)
{
    if(denumerator==0)
    {
        return NULL;
    }
    Rational new= malloc(sizeof(struct Rational_t));
    if(!new)
    {
        return NULL;
    }
    if(denumerator<0)
    {
        numerator=-1*numerator;
        denumerator=-1*denumerator;
    }
    int gcd=rationalGcd(numerator,denumerator);
    new->numerator=numerator/gcd;
    new->denumerator=denumerator/gcd;
    return new;
}

void rationalDestroy(Rational rational)
{
    if(!rational)
    {
        return;
    }
    free(rational);
}

Rational rationalCopy(Rational rational)
{
    Rational copy= rationalCreate(rational->numerator,rational->denumerator);
    if(!copy)
    {
        return NULL;
    }
    return copy;
}

int rationalCompare(Rational rational1, Rational rational2)
{
    Rational resalt= rationalSubtruct(rational1,rational2);
    int tosend=rationalToDoubleConverter(resalt);
    rationalDestroy(resalt);
    return tosend;
}

Rational rationalAddition(Rational rational1, Rational rational2)
{
    if(!rational1||!rational2)
    {
        return NULL;
    }
    int sumNumerator=rational1->numerator*rational2->denumerator+rational2->numerator*rational1->denumerator;
    int sumDenumerator=rational1->denumerator*rational2->denumerator;
    return rationalCreate(sumNumerator,sumDenumerator);
}

Rational rationalNegate(Rational rational)
{
    if(!rational)
    {
        return NULL;
    }
    return rationalCreate(-rational->numerator,rational->denumerator);
}

Rational rationalMultiply(Rational rational1, Rational rational2)
{
    if(!rational1||!rational2)
    {
        return NULL;
    }
    return rationalCreate(rational1->numerator*rational2->numerator,rational1->denumerator*rational2->denumerator);
}

Rational rationalPower(Rational base, int power)
{
    if(!base)
    {
        return NULL;
    }
    return rationalCreate(powerInt(base->numerator,power), powerInt(base->denumerator,power));
}

Rational rationalTransform(Rational rational)
{
    if(!rational||rational->numerator==0)
    {
        return NULL;
    }
    return rationalCreate(rational->denumerator,rational->numerator);
}

bool rationalEqual(Rational rational1,Rational rational2)
{
    if((!rationalGrater(rational1,rational2))&&(!rationalLesser(rational1,rational2)))
    {
        return true;
    }
    return false;
}

bool rationalGrater(Rational rational1, Rational rational2)
{
    if(rationalCompare(rational1,rational2)>0)
    {
        return true;
    }
    return false;
}

bool rationalLesser(Rational rational1, Rational rational2)
{
    return rationalGrater(rational2,rational1);
}

RtionalErrorCode rationalAddInto(Rational* rational1, Rational rational2)
{
    if(!rational1||!rational2)
    {
        return RATIONAL_NULL_ARGUMENT;
    }
    Rational tmp= *rational1;
    *rational1= rationalAddition(tmp,rational2);
    if(!*rational1)
    {
        *rational1=tmp;
        return RATIONAL_ERROR;
    }
    rationalDestroy(tmp);
    return RATIONAL_SUCSESS;
}

Rational rationalSubtruct(Rational rational1, Rational rational2)
{
    if(!rational1||!rational2)
    {
        return NULL;
    }
    Rational nrational2= rationalNegate(rational2);
    Rational resalt= rationalAddition(rational1,nrational2);
    rationalDestroy(nrational2);
    if(!resalt)
    {
        return NULL;
    }
    return resalt;
}

RtionalErrorCode rationalSubInto(Rational* rational1, Rational rational2)
{
    if(!rational1||!rational2)
    {
        return RATIONAL_NULL_ARGUMENT;
    }
    Rational tmp=*rational1;
    *rational1= rationalSubtruct(tmp,rational2);
    if(!*rational1)
    {
        *rational1=tmp;
        return RATIONAL_ERROR;
    }
    rationalDestroy(tmp);
    return RATIONAL_SUCSESS;
}

Rational rationalDivide(Rational rational1, Rational rational2)
{
    if(!rational1||!rational2)
    {
        return NULL;
    }
    Rational revrational2= rationalTransform(rational2);
    if(!revrational2)
    {
        return NULL;
    }
    Rational resalt= rationalMultiply(rational1, revrational2);
    rationalDestroy(revrational2);
    return resalt;
}

Rational rationalround(Rational rational)
{
    if(rational->denumerator==1)
    {
        return rationalCopy(rational);
    }
    int left=rational->numerator%rational->denumerator;
    int full=rational->numerator/rational->denumerator;
    int newdenu=full;
    if(left>=rational->denumerator/2)
    {
        newdenu=newdenu*rational->denumerator+rational->denumerator/2;
    }
    return rationalCreate(newdenu,rational->denumerator);
}

bool rationalIsHaveHalf(Rational rational)
{
    int left= rational->numerator%rational->denumerator;
    if(left>rational->denumerator/2)
    {
        return true;
    }
    return false;
}
