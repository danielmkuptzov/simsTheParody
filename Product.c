
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Product.h"

#define CAP_MIN 'A'
#define CAP_MAX 'Z'
#define LOW_MIN 'a'
#define LOW_MAX 'z'
#define DECA 10

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
    char* mainName=NULL;
    char* secondName=NULL;
    if(((first[0]>=CAP_MIN)&&(first[0]<=CAP_MAX))||((second[0]>=CAP_MIN)&&(second[0]<=CAP_MAX)))
    {
        mainName=   casingFix(true,stringDup(first));
        secondName= casingFix(true,stringDup(first));
    }
    else
    {
        mainName=   casingFix(false,stringDup(first));
        secondName= casingFix(false,stringDup(first));
    }
    int diff= strcmp(mainName,secondName);
    free(mainName);
    free(secondName);
    return diff;
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

int productEquals(Product first, Product secont)
{
    if(nameComparison(first->name,secont->name)==0)
    {
        return 0;
    }
    return first->id-secont->id;
}

const int productGetId(Product product)
{
    if(!product)
    {
        return -1;
    }
    return product->id;
}

const ProductAmountType productGetType(Product product)
{
    return product->amount_type;
}

const AmountSet productGetComponent(Product product)
{
    if(!product)
    {
        return NULL;
    }
    return product->components;
}

ProductErrorCode productAddComponent(Product product, ProductComp component)
{
    if(!product||!component)
    {
        return PRODUCT_WRONG_FORMAT;
    }
    AmountSetResult resalt=asRegister(product->components,component);
    if(resalt==AS_ITEM_ALREADY_EXISTS)
    {
        return PRODUCT_COMPONENT_ALREADY_EXIST;
    }
    if(resalt==AS_SUCCESS)
    {
        return PRODUCT_SUCSESS;
    }
    return PRODUCT_ERROR;
}

ProductErrorCode productRemoveComponent(Product product, ProductComp component)
{
    if(!product||!component)
    {
        return PRODUCT_WRONG_FORMAT;
    }
    AmountSetResult resalt= asDelete(product->components,component);
    if(resalt==AS_ITEM_DOES_NOT_EXIST)
    {
        return PRODUCT_COMPONENT_DOES_NOT_EXIST;
    }
    if(resalt==AS_SUCCESS)
    {
        return PRODUCT_SUCSESS;
    }
    return PRODUCT_ERROR;
}

const ProductData productGetAdditionalData(Product product)
{
    if(!product)
    {
        return NULL;
    }
    return product->data;
}

ProductErrorCode productSetAdditionalData(Product product, ProductData data)
{
    if(!product||!data||product->copyData)
    {
        return PRODUCT_WRONG_FORMAT;
    }
    ProductData tmpData=product->copyData(data);
    if(!tmpData)
    {
        return PRODUCT_ERROR;
    }
    product->data=tmpData;
    return PRODUCT_SUCSESS;
}

const char*  productGetName(Product product)
{
    if(!product)
    {
        return NULL;
    }
    return product->name;
}

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
ProductErrorCode productAmountChecker(ProductAmountType type, double amount)
{
    double left=DECA*amount - ((int)(DECA*amount);
    if((left>0.0&&left<0.9&&((type==INTEGER_AMOUNT)||(left>0.5&&left<0.4&&type==HALF_INTEGER_AMOUNT))))
    {
        return PRODUCT_WRONG_AMOUNT;
    }

}


/**
 * productComponentFilter   -for filtering purposes
 * @param filterFunc
 * @param key
 * @return
 *   NULL- if the filtering or the component were problematic
 *   amountset elsewise
 */
AmountSet productComponentFilter(FilterComponent filterFunc, ComponentFilterKey key);
