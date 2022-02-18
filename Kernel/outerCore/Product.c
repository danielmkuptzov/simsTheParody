#include <stdlib.h>
#include <string.h>

#include "../Product.h"
#include "AmountSet.h"
#include "Date.h"

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
        secondName= casingFix(true,stringDup(second));
    }
    else
    {
        mainName=   casingFix(false,stringDup(first));
        secondName= casingFix(false,stringDup(second));
    }
    int diff= strcmp(mainName,secondName);
    free(mainName);
    free(secondName);
    return diff;
}

static char* typeToStringConvert(TypeOfProduct typeOfProduct)
{
    if(typeOfProduct==FURNITURE)
    {
        return "furniture";
    }
    else if(typeOfProduct==ELECTRONICS)
    {
        return "electronic";
    }
    else if(typeOfProduct==FOOD)
    {
        return "food";
    }
    else if(typeOfProduct==BOOK)
    {
        return "book";
    }
    else
    {
        return "medicine";
    }
}

static void* typeOfProdCopy(void* type)
{
    if(!type)
    {
        return NULL;
    }
    TypeOfProduct* toSend= malloc(sizeof(TypeOfProduct));
    if(!toSend)
    {
        return NULL;
    }
    *toSend=*((TypeOfProduct*)type);
    return toSend;
}

static void typeOfProdDestroy(void* type)
{
    free(type);
}

static int typeOfProdCompare(void* type1, void* type2)
{
    TypeOfProduct* tmp1= type1;
    TypeOfProduct* tmp2= type2;
    return nameComparison(typeToStringConvert(*tmp1), typeToStringConvert(*tmp2));
}

// Product struct - represents a product in MatamIkya
struct product_t {
    AmountSet classifications;
    Date creationDate;
    int id;
    char* name;
    ProductData data;
    ProductAmountType amount_type;
    CopyProductData copyData;
    FreeData freeData;
    AmountSet components;
};

Product productCreate(int id, char* name, ProductAmountType type,
                      CopyProductData copyData, FreeData freeFunc,void* dateCre,
                      CopyProductComponent copyComp, FreeProductComponent freeComp,
                      ProductCompCmp compCmp, ProductData data,int  CompType, TypeOfProduct typeOfProduct)
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
    new->creationDate= dateCopy((Date)dateCre);
    if(!new->creationDate)
    {
        asDestroy(new->components);
        freeFunc(new->data);
        free(new);
        return NULL;
    }
    new->freeData=freeFunc;
    if(!name||name[0]==' ')
    {
        productDestroy(new);
        return NULL;
    }
    new->name= stringDup(name);
    if(!new->name)
    {
        productDestroy(new);
        return NULL;
    }
    new->id=id;
    new->amount_type= type;
    new->classifications= asCreate(typeOfProdCopy,typeOfProdDestroy,typeOfProdCompare
                              ,7);
    if(!new->classifications)
    {
        productDestroy(new);
        return NULL;
    }
    if(asRegister(new->classifications,&typeOfProduct)!=AS_SUCCESS)
    {
        productDestroy(new);
        return NULL;
    }
    return new;
}

void productDestroy(Product product)
{
    product->freeData(product->data);
    asDestroy(product->components);
    free(product->name);
    dateDestroy(product->creationDate);
    asDestroy(product->classifications);
    free(product);
}

Product productCopy(Product product)
{
    if(!product)
    {
        return NULL;
    }
    TypeOfProduct* mainClass= asGetFirst(product->classifications);
    Product copy=productCreate(product->id,product->name,product->amount_type,
                         product->copyData,product->freeData,product->creationDate,
                         NULL,NULL,NULL,product->data,
                         asGetType(product->components),*mainClass);
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
    asDestroy(copy->classifications);
    copy->classifications= asCopy(product->classifications);
    if(!copy->classifications)
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

const void* productGetComponent(Product product)
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

void* productComponentFilter(Product product, FilterComponent filterFunc, ComponentFilterKey key)
{
   if(!product||!product->components||!filterFunc||!key)
   {
       return NULL;
   }
   return asFilter(product->components,filterFunc, key);
}

Product productUnite(Product product1, Product product2)
{
    if(!product1||!product2|| productEquals(product1,product2)!=0)
    {
        return NULL;
    }
    TypeOfProduct* mainClassification= asGetFirst(product1->classifications);
    Product sum= productCreate(product1->id,product1->name,product1->amount_type,product1->copyData,
                               product1->freeData,product1->creationDate,asGetCopy(product1->components),
                               asGetFree(product1->components),asGetCompeare(product1->components),product1->data,
                               asGetType(product1->components),*mainClassification);
    if(!sum)
    {
        return NULL;
    }
    asDestroy(sum->components);
    sum->components= asUnite(product1->components,product2->components);
    if(!sum->components)
    {
        productDestroy(sum);
        return NULL;
    }
    asDestroy(sum->classifications);
    sum->classifications= asUnite(product1->classifications,product2->classifications);
    if(!sum->classifications)
    {
        productDestroy(sum);
        return NULL;
    }
    return sum;
}

ProductComp productGetFirst(Product product)
{
    if(!product)
    {
        return NULL;
    }
    return asGetFirst(product->components);
}

ProductComp productGetNext(Product product)
{
    if(!product)
    {
        return NULL;
    }
    return asGetNext(product->components);
}

int productCompeare(Product product1, Product product2)
{
    if(productEquals(product1,product2)==0)
    {
        return 0;
    }
    return product1->id-product2->id;
}

ProductCompCmp productGetCompDataFunc(Product product)
{
    if(!product)
    {
        return NULL;
    }
    return asGetCompeare(product->components);
}

int productGetCompAmount(Product product)
{
    if(!product)
    {
        return -1;
    }
    return asGetSize(product->components);
}

void* productGetDate(Product product)
{
    if(!product)
    {
        return NULL;
    }
    return product->creationDate;
}

ProductErrorCode productSetType(Product product, TypeOfProduct typeOfProduct)
{
    if(!product)
    {
        return PRODUCT_ERROR;
    }
    AmountSetResult resalt= asRegister(product->classifications,&typeOfProduct);
    if(resalt==AS_NULL_ARGUMENT)
    {
        return PRODUCT_ERROR;
    }
    else if(resalt==AS_ITEM_ALREADY_EXISTS)
    {
        return PRODUCT_COMPONENT_ALREADY_EXIST;
    }
    return PRODUCT_SUCSESS;
}

CoreUnit productGetTypeOfProd(Product product)
{
    if(!product)
    {
        return NULL;
    }
    CoreUnit toSend= coreCreate(1,asGetCopy(product->classifications),
                                asGetFree(product->classifications),
                                asGetCompeare(product->classifications),
                                asGetType(product->classifications));
    if(!toSend)
    {
        return NULL;
    }
    AS_FOREACH(TypeOfProduct*,iter,product->classifications)
    {
        if(coreInsert(toSend,iter)!=CORE_SUCSESS)
        {
            coreDestroy(toSend);
            return NULL;
        }
    }
    return toSend;
}

/**
 *   isProductAType           -boolean function to find if the type matches
 * @param product
 * @param typeOfProduct
 * @return
 *  true if the type is one of the products classsificatin
 *  false otherwise
 */
bool isProductAType(Product product, TypeOfProduct typeOfProduct);

/**
 *   productRemoveType        -to remove a undesireble type
 * @param product
 * @param typeOfProduct
 * @return
 *  PRODUCT_ERROR         this type already exist
 *  PRODUCT_WRONG_FORMAT  NULL arguments
 *  PRODUCT_COMPONENT_DOES_NOT_EXIST
 *  PRODUCT_SUCSESS       the operation was sucssesful
 */
ProductErrorCode  productRemoveType(Product product,TypeOfProduct typeOfProduct);
