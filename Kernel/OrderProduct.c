//
// Created by danie on 31/12/2021.
//
#include <stdlib.h>

#include "OrderProduct.h"

static Rational epsilon=NULL;

struct OrderUnit_t{
    Product product;
    Rational amount;
};

static bool checkAmount(const Rational amount, ProductAmountType type)
{
    if(!amount)
    {
        return false;
    }
    if(rationalIsHaveHalf(amount)&&type==INTEGER_AMOUNT)
    {
        return false;
    }
    Rational number= rationalround(amount);
    if(!number)
    {
        return false;
    }
    Rational resalt= rationalSubtruct(amount,number);
    rationalDestroy(number);
    if(!resalt)
    {
        return false;
    }
    bool answer=(rationalLesser(resalt,epsilon)&&type==HALF_INTEGER_AMOUNT);
    rationalDestroy(epsilon);
    rationalDestroy(resalt);
    return answer;
}

void  productSetEpsilon(Rational margin)
{
    if(!margin)
    {
        return;
    }
    if(rationalEqual(margin,epsilon))
    {
        return;
    }
    epsilon= rationalCopy(margin);
    if(!epsilon)
    {
        return;
    }
}

OrderUnit productUnitCreate(Product product, Rational initialAmount)
{
    if(!product||!initialAmount)
    {
        return NULL;
    }
    if(!checkAmount(initialAmount, productGetType(product)))
    {
        return NULL;
    }
    Rational zero= rationalCreate(0,1);
    if(rationalLesser(initialAmount,zero))
    {
        rationalDestroy(zero);
        return NULL;
    }
    rationalDestroy(zero);
    OrderUnit new= malloc(sizeof(struct OrderUnit_t));
    if(!new)
    {
        return NULL;
    }
    new->product= productCopy(product);
    if(!new->product)
    {
        free(new);
        return NULL;
    }
    new->amount= rationalCopy(initialAmount);
    if(!new->amount)
    {
        productDestroy(new->product);
        free(new);
        return NULL;
    }
    return new;
}

void productUnitDestroy(OrderUnit unit)
{
    if(!unit)
    {
        return;
    }
    productDestroy(unit->product);
    rationalDestroy(unit->amount);
    free(unit);
}

OrderUnit productUnitCopy(OrderUnit unit)
{
    if(!unit)
    {
        return NULL;
    }
    return productUnitCreate(unit->product,unit->amount);
}

int productUnitCompeare(OrderUnit unit1, OrderUnit unit2)
{
    return productCompeare(unit1->product,unit2->product);
}

OrderUnitErrors productUnitRaiseAmount(OrderUnit unit, Rational amount)
{
    if(!unit)
    {
        return ORDER_UNIT_NULL_ARGUMENT;
    }
    if(!checkAmount(amount, productGetType(unit->product)))
    {
        return ORDER_UNIT_WRONG_AMOUNT;
    }
    if(rationalAddInto(&unit->amount,amount)!=RATIONAL_SUCSESS)
    {
        return ORDER_UNIT_ERROR;
    }
    return ORDER_UNIT_SUCSESS;
}

OrderUnitErrors productUnitLowerAmount(OrderUnit unit, Rational amount)
{
    if(!unit)
    {
        return ORDER_UNIT_NULL_ARGUMENT;
    }
    Rational zero= rationalCreate(0,1);
    if(rationalGrater(amount,zero))
    {
        rationalDestroy(zero);
        return ORDER_UNIT_ERROR;
    }
    rationalDestroy(zero);
    if(!checkAmount(amount, productGetType(unit->product)))
    {
        return ORDER_UNIT_WRONG_AMOUNT;
    }
    Rational namount= rationalNegate(amount);
    if(rationalGrater(namount,unit->amount))
    {
        rationalDestroy(namount);
        return ORDER_UNIT_TOO_MUCH;
    }
    rationalDestroy(namount);
    if(rationalSubInto(&unit->amount,amount)!=RATIONAL_SUCSESS)
    {
        return ORDER_UNIT_ERROR;
    }
    return ORDER_UNIT_SUCSESS;
}

Product productUnitGetProduct(OrderUnit unit)
{
    if(!unit)
    {
        return NULL;
    }
    return unit->product;
}

Rational productUnitGetAmount(OrderUnit unit)
{
    if(!unit)
    {
        return NULL;
    }
    return unit->amount;
}

OrderUnitErrors productUnitChangeAmount(OrderUnit unit, Rational amount)
{
    if(!unit||!amount)
    {
        return ORDER_UNIT_NULL_ARGUMENT;
    }
    Rational zero= rationalCreate(0,1);
    if(rationalLesser(amount,zero))
    {
        rationalDestroy(zero);
        Rational fixAmount= rationalNegate(amount);
        if(!fixAmount)
        {
            return ORDER_UNIT_ERROR;
        }
        OrderUnitErrors resalt=productUnitLowerAmount(unit,fixAmount);
        rationalDestroy(fixAmount);
        return resalt;
    }
    rationalDestroy(zero);
    return productUnitRaiseAmount(unit,amount);
}

void  productDestroyEpsilon()
{
    rationalDestroy(epsilon);
}

Rational productGetEpsilon()
{
    return epsilon;
}
