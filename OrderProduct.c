//
// Created by danie on 31/12/2021.
//
#include <stdlib.h>

#include "OrderProduct.h"

struct OrderUnit_t{
    Product product;
    Rational amount;
};

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

/**
 *   productUnitRaiseAmount    -raise the amount of the product
 * @param unit
 * @param amount
 * @return
 *   ORDER_UNIT_NULL_ARGUMENT    -one of the argument was NULL
 *   ORDER_UNIT_ERROR            -for strange cases
 *   ORDER_UNIT_WRONG_AMOUNT     -the amount not match the product type
 *   ORDER_UNIT_SUCSESS          -sucsess
 */
OrderUnitErrors productUnitRaiseAmount(OrderUnit unit, Rational amount);

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
