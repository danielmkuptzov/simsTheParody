//
// Created by danie on 31/12/2021.
//
#include <stdlib.h>

#include "OrderProduct.h"

struct OrderUnit_t{
    Product product;
    Rational amount;
};

static bool checkAmount(Rational amount, ProductAmountType type)
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
    Rational epsilon= rationalCreate(1,1000);
    if(!epsilon)
    {
        rationalDestroy(resalt);
        return false;
    }
    bool answer=rationalGrater(resalt,epsilon);
    rationalDestroy(epsilon);
    rationalDestroy(resalt);
    return answer;
}

OrderUnit productUnitCreate(Product product, Rational initialAmount)
{
    if(!product||!initialAmount)
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
    if(rationalAddInto(unit->amount,amount)!=RATIONAL_SUCSESS)
    {
        return ORDER_UNIT_ERROR;
    }
    return ORDER_UNIT_SUCSESS;
}

/**
 *   productUnitLowerAmount    -lowers the amount of the product
 * @param unit
 * @param amount
 * @return
 *   ORDER_UNIT_NULL_ARGUMENT  -aNULL argument was passed
 *   ORDER_UNIT_ERROR          -strange casess
 *   ORDER_UNIT_WRONG_AMOUNT   -amount don't match the decription
 *   ORDER_UNIT_TOO_MUCH       -the amount is too much
 *   ORDER_UNIT_SUCSESS        -sucsess
 */
OrderUnitErrors productUnitLowerAmount(OrderUnit unit, Rational amount);

/**
 *   productUnitGetProduct     -to see the product
 * @param unit
 * @return
 * NULL -corrupted argument
 * product otherwise
 */
Product productUnitGetProduct(OrderUnit unit);

/**
 *   productUnitGetAmount      -to get the amount of the product
 * @param unit
 * @return
 * NULL for corrupted product
 * rational otherwise
 */
Rational productUnitGetAmount(OrderUnit unit);
