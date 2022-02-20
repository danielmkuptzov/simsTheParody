#ifndef ORDERPRODUCT_H
#define ORDERPRODUCT_H

#include <stdio.h>
#include "Rational.h"
#include "Product.h"

/**
 *  order product adt
 *
 * this header implements the second basic thing in this project, the trasporting unit of the product.
 *
 * The following functions are available:
 *   productSetEpsilon         -sets the epsilon of the margin
 *   productUnitAddCategory    -adds new category for the product
 *   productUnitIsACategory    -checks if the product is in a specific category
 *   productUnitRemoveCategory -removes a category by users request
 *   productUnitGetCategories  -returns the categories the product have
 *   productUnitCreate         -Creates the order product.
 *   productUnitDestroy        -Deletes an existing order product and frees all resources
 *   productUnitCopy           -Copies an existing order product
 *   productUnitCompeare       -compares between order products
 *   productUnitRaiseAmount    -raise the amount of the product
 *   productUnitLowerAmount    -lowers the amount of the product
 *   productUnitGetProduct     -to see the product
 *   productUnitGetAmount      -to get the amount of the product
 *   productUnitChangeAmount   -for general amount change
 *   productDestroyEpsilon     -destroys the epsilon
 *   productGetEpsilon         -gives the epsilon
 */

typedef enum {
    ORDER_UNIT_NULL_ARGUMENT,
    ORDER_UNIT_ERROR,
    ORDER_UNIT_WRONG_AMOUNT,
    ORDER_UNIT_TOO_MUCH,
    ORDER_UNIT_CATEGORY_DOES_NOT_EXIST,
    ORDRE_UNIT_CATEGORY_EXIST,
    ORDER_UNIT_SUCSESS
} OrderUnitErrors;

typedef struct OrderUnit_t* OrderUnit;

/**
 *   productSetEpsilon         -sets the epsilon of the margin
 * @param margin- the margin should be less than 1
 */
void  productSetEpsilon(Rational margin);

/**
 *   productUnitAddCategory    -adds new category for the product
 * @param unit
 * @param typeOfProduct
 * @return
 *   ORDER_UNIT_NULL_ARGUMENT -a NULL argument was passed
 *   ORDRE_UNIT_CATEGORY_EXIST -the category we want to add exist
 *   ORDER_UNIT_ERROR          -any error not directly related to the previous codes
 *   ORDER_UNIT_SUCSESS        - sucsess
 */
OrderUnitErrors productUnitAddCategory(OrderUnit unit,TypeOfProduct typeOfProduct);

/**
 *   productUnitIsACategory    -checks if the product is in a specific category
 * @param unit
 * @param typeOfProduct
 * @return
 *   true if exist
 *   false if not
 */
bool productUnitIsACategory(OrderUnit unit,TypeOfProduct typeOfProduct);

/**
 *   productUnitRemoveCategory -removes a category by users request
 * @param unit
 * @param typeOfProduct
 * @return
 *   ORDER_UNIT_NULL_ARGUMENT  -a NULL was passed
 *   ORDER_UNIT_ERROR          -new unknown error
 *   ORDER_UNIT_CATEGORY_DOES_NOT_EXIST  -the product didn't existed
 *   ORDER_UNIT_SUCSESS  -sucsess
 */
OrderUnitErrors productUnitRemoveCategory(OrderUnit unit,TypeOfProduct typeOfProduct);

/**
 *   productUnitGetCategories  -returns the categories the product have
 * @param unit
 * @return
 *  NULL for any error
 *  coreunit otherwise
 */
CoreUnit productUnitGetCategories(OrderUnit unit);

/**
 *   productUnitCreate         -Creates the order product.
 * @param product
 * @param initialAmount
 * @return
 * NULL -if there was a NULL argument or memory problem
 */
OrderUnit productUnitCreate(Product product, Rational initialAmount);

/**
 *   productUnitDestroy        -Deletes an existing order product and frees all resources
 * @param unit
 */
void productUnitDestroy(OrderUnit unit);

/**
 *   productUnitCopy           -Copies an existing order product
 * @return
 * NULL if any problem accurs
 * order unit otherwise
 */
OrderUnit productUnitCopy(OrderUnit unit);

/**
 *   productUnitCompeare       -compares between order products
 * @param unit1
 * @param unit2
 * @return
 */
int productUnitCompeare(OrderUnit unit1, OrderUnit unit2);

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

/**
 *   productUnitChangeAmount   -for general amount change
 * @param unit
 * @param amount
 * @return
 * ORDER_UNIT_NULL_ARGUMENT
 * ORDER_UNIT_ERROR
 * ORDER_UNIT_WRONG_AMOUNT
 * ORDER_UNIT_TOO_MUCH
 * ORDER_UNIT_SUCSESS
 */
OrderUnitErrors productUnitChangeAmount(OrderUnit unit, Rational amount);

/**
 *   productDestroyEpsilon     -destroys the epsilon
 */
void  productDestroyEpsilon();

/**
 *   productGetEpsilon         -gives the epsilon
 * @return
 */
Rational productGetEpsilon();

#endif //ORDERPRODUCT_H
