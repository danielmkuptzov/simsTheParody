
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Product.h"

#define CAP_MIN 'A'
#define CAP_MAX 'Z'
#define LOW_MIN 'a'
#define LOW_MAX 'z'

static char* stringDup(char* str)
{
    char* copy = malloc(strlen(str) + 1);
    return copy ? strcpy(copy, str) : NULL;
}

static char *casingFix(bool upperCase, char *fixstring)
{
    if(!(upperCase)&&((fixstring[0]>=CAP_MIN)&&(fixstring[0]<=CAP_MAX)))
    {
        fixstring[0]=fixstring[0]-CAP_MIN+LOW_MIN;
    }
    if(upperCase&&((fixstring[0]>=LOW_MIN)&&(fixstring[0]<=LOW_MAX)))
    {
        fixstring[0]=fixstring[0]-LOW_MIN+CAP_MIN;
    }
    return fixstring;
}

static int nameComparison(char* first, char*second)
{
    if(((first[0]>=CAP_MIN)&&(first[0]<=CAP_MAX))||((second[0]>=CAP_MIN)&&(second[0]<=CAP_MAX)))
    {
        char* mainName=   casingFix(true,stringDup(first));
        char* secondName= casingFix(true,stringDup(first));
    }

}

// Product struct - represents a product in MatamIkya
struct product_t {
    Date creationDate;
    int id;
    char* name;
    double amount;
    ProductData data;
    ProductAmountType amount_type;
    CopyProductData copyData;
    FreeData freeData;
    AmountSet components;
};

Product productCreate(int id, char* name, ProductAmountType type,
                      CopyProductData copyData, FreeData freeFunc, Date dateCre,
                      CopyProductComponent copyComp, FreeProductComponent freeComp,
                      ProductCompCmp compCmp, ProductData data, int CompType)
{
    Product new= malloc(sizeof(struct product_t));
    if(!new)
    {
        return NULL;
    }
    new->copyData=copyData;
    new->data=new->copyData(data);
    if(!new->data)
    {
        free(new);
        return NULL;
    }
    new->components= asCreate(copyComp,freeComp, compCmp,CompType);
    if(!new->components)
    {
        freeFunc(new->data);
        free(new);
        return NULL;
    }
    new->creationDate= dateCopy(dateCre);
    if(!new->creationDate)
    {
        asDestroy(new->components);
        freeFunc(new->data);
        free(new);
        return NULL;
    }
    new->freeData=freeFunc;
    return new;
}

void productDestroy(Product product)
{
    product->freeData(product->data);
    asDestroy(product->components);
    free(product->name);
    dateDestroy(product->creationDate);
    free(product);
}

Product productCopy(Product product)
{
    if(!product)
    {
        return NULL;
    }
    Product copy=productCreate(product->id,product->name,product->amount_type,
                         product->copyData,product->freeData,product->creationDate,
                         NULL,NULL,NULL,product->data,
                         asGetType(product->components));
    if(!copy)
    {
        return NULL;
    }
    asDestroy(copy->components);
    copy->components= asCopy(product->components);
    if(!copy->components)
    {
        productDestroy(copy);
        return NULL;
    }
    return copy;
}

/**
 *   productEquals            -checks if the products are the same
 * @param first
 * @param secont
 * @return
 * 0- same
 * positive-  first> second
 * negative-  second> first
 */
int productEquals(Product first, Product secont)
{
}

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
AmountSet productGetComponent(Product product);

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
 *   productAmountChecker     -testing function to determine if the amount is legal to the product
 * @param type -the type of the product
 * @param amount -the amount in question
 * @return
 *   PRODUCT_ERROR -problems that didn't covered in the description
 *   PRODUCT_WRONG_AMOUNT -the amount was wrong
 *   PRODUCT_WRONG_FORMAT -the type or the amount was illegal
 *   PRODUCT_SUCSESS -the amount is ok
 *
 */
ProductErrorCode productAmountChecker(ProductAmountType type, double amount);


