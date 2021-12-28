#include <stdlib.h>
#include <string.h>

#include "../Product.h"

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

AmountSet productComponentFilter(Product product, FilterComponent filterFunc, ComponentFilterKey key)
{
   if(!product||!product->components||!filterFunc||!key)
   {
       return NULL;
   }
   return asFilter(product->components,filterFunc, key);
}

/**
 *  productUnite             -if the products have the same caracteristics but different components unites them
 * @param product1
 * @param product2
 * @return
 * NULL -null arguments of different products
 * product- elsewise
 */
Product productUnite(Product product1, Product product2)
{
    if(!product1||!product2|| productEquals(product1,product2)!=0)
    {
        return NULL;
    }
    Product sum= productCreate(product1->id,product1->name,product1->amount_type,product1->copyData,
                               product1->freeData,product1->creationDate,asGetCopy(product1->components),
                               asGetFree(product1->components),asGetCompeare(product1->components),product1->data,
                               asGetType(product1->components));
    if(!sum)
    {
        return NULL;
    }
    sum->components= asUnite(product1->components,product2->components);
    if(!sum->components)
    {
        productDestroy(sum);
        return NULL;
    }
    return sum;
}

