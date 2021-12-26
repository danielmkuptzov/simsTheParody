//
// Created by danie on 26/12/2021.
//

#ifndef PRODUCT_H
#define PRODUCT_H

#include "outerCore.h"

/**
 * Product adt
 *
 * Implements a product variable type.
 * our product would be sorted by the id given by the user.
 * The names would be checked by the string standart.
 *
 * @important be shure what type of product you want. we wonwt tolerate expiriment of changing to wrong type.
 *
 *
 * The following functions are available:
 *   productCreate            - Creates a new product
 *   productDestroy           - Deletes an existing product and frees all resources
 *   productCopy              - Copies an existing product
 *   productEquals            -checks if the products are the same
 *   productGetId             -for serching purposes
 *   productGetType           -gives the type of the product
 *   productGetComponent      -givesThe components of the product
 *   productAddComponent      -for adding to components
 *   productRemoveComponent   -for removing component
 *   productGetAdditionalData -for seeing the additional data
 *   productSetAdditionalData -for changing the additional data
 *   productGetName           -for getting the name of the product
 *   productSetName           -for name change
 */

/** Type for additional custom data of a product */
typedef void *ProductData;

/**
 * Type of function for copying a product's custom data.
 *
 * Such a function receives a ProductData, creates a new ProductData
 * object, and returns a pointer to the new object. If the function fails for
 * any reason, it returns NULL.
 */
typedef ProductData (*CopyProductData)(ProductData);

/**
 * Type of function for freeing a product's custom data.
 *
 * Such a function receives a MtmProductData object and frees it. The
 * MtmProductData can be NULL, in which case the function does nothing.
 */
typedef void (*FreeData)(ProductData);

/**
 * type of function to compeare data
 *
 * Such a function receives two ProductData objects and compeares between them. The
 * ProductData can't be NULL, we cant compeare whith NULL.
 */
typedef int (*ProductDataCmp)(ProductData,ProductData);

/** Type for specifying what is a valid amount for a product.
 * For a INTEGER_AMOUNT product, a valid amount is an amount which is
 * within 0.001 of an integer. For example, 8.001 or 7.999 are considered a valid amount
 * for INTEGER_AMOUNT, but 8.0011 or 7.9989 are not.
 *
 * For a HALF_INTEGER_AMOUNT product, a valid amount is an amount which is
 * within 0.001 of a half-integer. For example, 8.001 is valid and 8.0011 is not valid,
 * but also 8.501 is valid and 8.5011 is not valid.
 *
 * For ANY_AMOUNT, any amount is valid. For example, this is suitable for
 * products which are measured by weight.
 */
typedef enum ProductAmountType_t {
    INTEGER_AMOUNT,
    HALF_INTEGER_AMOUNT,
    ANY_AMOUNT,
} ProductAmountType;

/**
 * the product type, use whith care
 */
typedef struct product_t *Product;

/**
 *   productCreate            - Creates a new product
 * @param id non negative number
 * @param name empty manes or NULL wouldn't be tolareted. for simple use use "john dou", "nanashi", "ploni".
 *            Also, we don't differ from capital letters to non-capital
 * @param type  -see the explenation above
 * @param copyData -see the explenation above
 * @param freeFunc -see the explenation above
 * @return
 *         Null- if the requirement don't match
 *         product othrwise
 */
Product productCreate(int id, char* name, ProductAmountType type,
                      CopyProductData copyData, FreeData freeFunc, Date dateCre);

/**
 *   productDestroy           - Deletes an existing product and frees all resources
 * @param product the product we wish to destroy
 */
void productDestroy(Product product);

/**
 *   productCopy              - Copies an existing product
 * @param product the product we need to copy
 * @return
 *  NULL- if there is a problem in the product
 *  product otherwise
 */
Product productCopy(Product product);

/**
 *   productEquals            -checks if the products are the same
 *   productGetId             -for serching purposes
 *   productGetType           -gives the type of the product
 *   productGetComponent      -givesThe components of the product
 *   productAddComponent      -for adding to components
 *   productRemoveComponent   -for removing component
 *   productGetAdditionalData -for seeing the additional data
 *   productSetAdditionalData -for changing the additional data
 *   productGetName           -for getting the name of the product
 *   productSetName           -for name change
 * @param first
 * @param secont
 * @return
 */
bool productEquals(Product first, Product secont);


#endif //DANIELCITY_PRODUCT_H
