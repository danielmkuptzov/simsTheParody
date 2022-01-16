//
// Created by danie on 26/12/2021.
//

#ifndef PRODUCT_H
#define PRODUCT_H
#include <stdbool.h>

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
 *   productComponentFilter   -for filtering purposes
 *   productUnite             -if the products have the same caracteristics but different components unites them
 *   productGetFirst          -gives the first component in the list
 *   productGetNext           -brings the next one
 *   productCompeare          -compares between products
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

/**
 * for easy addition of new components we have this
 */
typedef void* ProductComp;

/**
 * Type of function for copying a product's components.
 *
 * Such a function receives a ProductComp, creates a new ProductComp
 * object, and returns a pointer to the new object. If the function fails for
 * any reason, it returns NULL.
 */
typedef ProductData (*CopyProductComponent)(ProductComp);

/**
 * Type of function for freeing a product's components.
 *
 * Such a function receives a ProductComp object and frees it. The
 * ProductComp can be NULL, in which case the function does nothing.
 */
typedef void (*FreeProductComponent)(ProductComp);

/**
 * type of function to compeare ProductComp
 *
 * Such a function receives two ProductComp objects and compeares between them. The
 * ProductComp can't be NULL, we cant compeare whith NULL.
 */
typedef int (*ProductCompCmp)(ProductComp,ProductComp);

/**
* Use this type to pass extra information needed by the filtering function
* when calling listFilter. (See the example for a FilterListElement function)
*/
typedef void* ComponentFilterKey;

/**
* Function used for creating a filtered copy of a set.
* A element is said to pass filtering if the function returns true
* For example, the following function can be used to filter a list of strings
* from short strings:
* @code
* bool isShorterThan(SetElement str, SetFilterKey length) {
*   return strlen(str) < *(int*) length;
* }
* @endcode
*/
typedef bool (*FilterComponent) (ProductComp,ComponentFilterKey);

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
    ERROR
} ProductAmountType;

/**
 * product error codes
 */
typedef enum ProductErrorCode_t{
    PRODUCT_ERROR,
    PRODUCT_COMPONENT_ALREADY_EXIST,
    PRODUCT_COMPONENT_DOES_NOT_EXIST,
    PRODUCT_WRONG_FORMAT,
    PRODUCT_SUCSESS
} ProductErrorCode;

/**
 * the product type, use whith care
 */
typedef struct product_t *Product;

/**
 *   productCreate            - Creates a new product
 * @param id non negative number
 * @param name empty manes or NULL wouldn't be tolareted. for simple use use "john dou", "nanashi", "ploni".
 *            Also, we don't differ from capital letters to non-capital
 * @return
 *         Null- if the requirement don't match
 *         product othrwise
 */
Product productCreate(int id, char* name, ProductAmountType type,
                      CopyProductData copyData, FreeData freeFunc,void* dateCre,
                      CopyProductComponent copyComp, FreeProductComponent freeComp,
                      ProductCompCmp compCmp, ProductData data,int  CompType);

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
 * @param first
 * @param secont
 * @return
 * 0- same
 * positive-  first> second
 * negative-  second> first
 */
int productEquals(Product first, Product secont);

/**
 *   productGetId             -for serching purposes
 * @param product
 * @return
 * -1 if the imput is problematic
 * id otherwise
 */
const int productGetId(Product product);

/**
 *   productGetType           -gives the type of the product
 * @param product
 * @return
 * the amount type
 */
const ProductAmountType productGetType(Product product);

/**
 *   productGetComponent      -givesThe components of the product
 * @param product   -the place where we serch
 * @return
 * NULL- if the product doesn't have a components or wrong format
 * amount set othewise
 */
const void* productGetComponent(Product product);

/**
 *   productAddComponent      -for adding to components
 * @param product -the place we wish to add to
 * @param component -the component we want to add
 * @return
 *   PRODUCT_ERROR -  unknown error
 *   PRODUCT_COMPONENT_ALREADY_EXIST -the component already exist
 *   PRODUCT_WRONG_FORMAT -wrong arguments entered
 *   PRODUCT_SUCSESS -the addition was sucssesful
 */
ProductErrorCode productAddComponent(Product product, ProductComp component);

/**
 *   productRemoveComponent   -for removing component
 * @param product -the place we need to clean
 * @param component -the element we remove
 * @return
 *   PRODUCT_ERROR -unknown error
 *   PRODUCT_COMPONENT_DOES_NOT_EXIST -the element wasn't found
 *   PRODUCT_WRONG_FORMAT- wrong inpud data
 *   PRODUCT_SUCSESS- the process was sucssesful
 */
ProductErrorCode productRemoveComponent(Product product, ProductComp component);

/**
 *   productGetAdditionalData -for seeing the additional data
 * @param product -the product we want to get the additional information
 * @return
 */
const ProductData productGetAdditionalData(Product product);

/**
 *   productSetAdditionalData -for changing the additional data
 * @param product -the product we want to change
 * @param data - the data we want to enter
 * @return
 *   PRODUCT_ERROR -for every error
 *   PRODUCT_WRONG_FORMAT- null arguments
 *   PRODUCT_SUCSESS -the process was sucssesful
 */
ProductErrorCode productSetAdditionalData(Product product, ProductData data);

/**
 *   productGetName           -for getting the name of the product
 * @param product- the product we need the name of
 * @return
 * NULL -wrong format or problems
 * name otherwise
 */
const char*  productGetName(Product product);

/**
 * productComponentFilter   -for filtering purposes
 * @param filterFunc
 * @param key
 * @return
 *   NULL- if the filtering or the component were problematic
 *   amountset elsewise
 */
void* productComponentFilter(Product product, FilterComponent filterFunc, ComponentFilterKey key);

/**
 *  productUnite             -if the products have the same caracteristics but different components unites them
 * @param product1
 * @param product2
 * @return
 * NULL -null arguments or different products
 * product- elsewise
 */
Product productUnite(Product product1, Product product2);

/**
 *    productGetFirst          -gives the first component in the list
 * @param product
 * @return
 * NULL -for any problem that might accure
 * product component otherwise
 */
ProductComp productGetFirst(Product product);

/**
 *    productGetNext           -brings the next one
 * @param product
 * @return
 * NULL -end of elements or other problems
 * product component otherwise
 */
ProductComp productGetNext(Product product);

/**
 *   productCompeare          -compares between products
 * @param product1
 * @param product2
 * @return
 */
int productCompeare(Product product1, Product product2);

/**
 * Macro for iterating over a product.
 * Declares a new iterator for the loop.
 */
#define PRODUCT_FOREACH(iterator, product)          \
    for(ProductComp iterator = productGetFirst(product) ; \
        iterator ;                               \
        iterator = productGetNext(product))

#endif //DANIELCITY_PRODUCT_H
