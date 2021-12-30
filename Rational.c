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

static double rationalToDoubleConverter(Rational rational)
{
    return rational->numerator/rational->denumerator;
}

static bool doublePositive(double number)
{
    if(number>0)
    {
        return 1;
    }
    if(number<0)
    {
        return -1;
    }
    return 0;
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
    bool negative=(denumerator<0);
    denumerator= negative*denumerator;
    int gcd=rationalGcd(numerator,denumerator);
    new->numerator=negative*numerator/gcd;
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
    Rational nrational= rationalNegate(rational2);
    Rational resalt= rationalAddition(rational1,nrational);
    rationalDestroy(nrational);
    int tosend=doublePositive(rationalToDoubleConverter(resalt));
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
