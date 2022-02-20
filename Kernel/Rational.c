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

int powerInt(int base, int power)
{
    int resalt=1;
    for(int i=0; i<power; i++)
    {
        resalt=resalt*base;
    }
    return resalt;
}

Rational doubleToRationalConvert(int base)
{
    if(base<=1)
    {
        return NULL;
    }
    return rationalCreate(1, powerInt(10,base));
}

Rational rationalCreate(int numerator,int denumerator)
{
    if(denumerator==0||numerator==-999999999||denumerator==-999999999)
    {
        return NULL;
    }
    Rational newRas= malloc(sizeof(struct Rational_t));
    if(!newRas)
    {
        return NULL;
    }
    if(denumerator<0)
    {
        numerator=-1*numerator;
        denumerator=-1*denumerator;
    }
    int gcd=rationalGcd(numerator,denumerator);
    newRas->numerator=numerator/gcd;
    newRas->denumerator=denumerator/gcd;
    return newRas;
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
    if(power<0)
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

RtionalErrorCode rationalArithmeticChange(Rational rational1, Rational rational2)
{
    if(!rational1||!rational2)
    {
        return RATIONAL_NULL_ARGUMENT;
    }
    Rational zero= rationalCreate(0,1);
    if(!zero)
    {
        return RATIONAL_ERROR;
    }
    RtionalErrorCode resalt=RATIONAL_ERROR;
    if(rationalLesser(rational2,zero))
    {
        resalt= rationalSubInto(&rational1,rational2);
    }
    else
    {
        resalt= rationalAddInto(&rational1,rational2);
    }
    rationalDestroy(zero);
    return resalt;
}

RtionalErrorCode rationalMultiplyInto(Rational* rational1, Rational rational2)
{
    if(!rational1||!rational2)
    {
        return RATIONAL_NULL_ARGUMENT;
    }
    Rational tmp=*rational1;
    *rational1= rationalMultiply(tmp,rational2);
    if(!*rational1)
    {
        *rational1=tmp;
        return RATIONAL_ERROR;
    }
    rationalDestroy(tmp);
    return RATIONAL_SUCSESS;
}

RtionalErrorCode rationaldivideInto(Rational* rational1, Rational rational2)
{
    if(!rational1||!rational2)
    {
        return RATIONAL_NULL_ARGUMENT;
    }
    Rational zero= rationalCreate(0,1);
    if(rationalCompare(*rational1,zero)||rationalCompare(rational2,zero))
    {
        rationalDestroy(zero);
        return RATIONAL_DIVISION_BY_ZERO;
    }
    rationalDestroy(zero);
    Rational tmp=*rational1;
    *rational1= rationalDivide(tmp,rational2);
    if(!*rational1)
    {
        *rational1=tmp;
        return RATIONAL_ERROR;
    }
    rationalDestroy(tmp);
    return RATIONAL_SUCSESS;
}

RtionalErrorCode rationalPowerInto(Rational* rational1, Rational rational2)
{
    if(!rational1||!rational2)
    {
        return RATIONAL_NULL_ARGUMENT;
    }
    Rational tmp=*rational1;
    if(rational2->denumerator!=1)
    {
        return RATIONAL_ERROR;
    }
    *rational1= rationalPower(tmp,rational2->numerator);
    if(!*rational1)
    {
        *rational1=tmp;
        return RATIONAL_ERROR;
    }
    rationalDestroy(tmp);
    return RATIONAL_SUCSESS;
}

Rational rationalPureRound(Rational rational, int typeOfRound)
{
    if(!rational||typeOfRound>1)
    {
        return NULL;
    }
    if(typeOfRound==0)
    {
        return rationalround(rational);
    }
    Rational lowerValue=rationalCreate(rational->numerator/rational->denumerator,1);
    if(!lowerValue)
    {
        return NULL;
    }
    Rational left= rationalSubtruct(rational,lowerValue);
    if(!left)
    {
        rationalDestroy(lowerValue);
        return NULL;
    }
    Rational half= rationalCreate(0,5);
    if(!half)
    {
        rationalDestroy(left);
        rationalDestroy(lowerValue);
        return NULL;
    }
    bool resalt= rationalLesser(left,half);
    rationalDestroy(half);
    rationalDestroy(left);
    if(resalt)
    {
        return lowerValue;
    }
    if(rationalGetNumerator(lowerValue)==-999999999)
    {
        rationalDestroy(lowerValue);
        return NULL;
    }
    Rational toSend= rationalCreate(rationalGetNumerator(lowerValue)+1,
                                    rationalGetDenumerator(lowerValue));
    rationalDestroy(lowerValue);
    if(!toSend)
    {
        return NULL;
    }
    return toSend;
}

int rationalGetNumerator(Rational rational)
{
    if(!rational)
    {
        return -999999999;
    }
    return rational->numerator;
}

int rationalGetDenumerator(Rational rational)
{
    if(!rational)
    {
        return -999999999;
    }
    return rational->denumerator;
}
