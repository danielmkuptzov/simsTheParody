#include <stdlib.h>
#include <string.h>

#include "Rational.h"
#include "OrderProduct.h"
#include "outerCore.h"
#include "Product.h"
#include "../Kernel.h"

#define CAP_MIN 'A'
#define CAP_MAX 'Z'
#define LOW_MIN 'a'
#define LOW_MAX 'z'

#define ERRORCOMP -1000000000;

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

static ProductAmountType converter(char* name)
{
    if(nameComparison(name,"int amount")==0)
    {
        return INTEGER_AMOUNT;
    }
    else if(nameComparison(name,"half int amount")==0)
    {
        return HALF_INTEGER_AMOUNT;
    }
    else if(nameComparison(name,"any amount")==0)
    {
        return ANY_AMOUNT;
    }
    else
    {
        return ERROR;
    }
}

static int convertTypeToInt(CreatingType type)
{
    if(type==AMOUNT_SET)
    {
        return 1;
    }
    else if(type==DATE)
    {
        return 2;
    }
    else if(type==PRODUCT)
    {
        return 3;
    }
    else if(type==RATIONAL)
    {
        return 4;
    }
    else if(type==ORDER_PRODUCT)
    {
        return 5;
    }
    return -1;
}

static int typeComparison(CreatingType type1, CreatingType type2)
{
    if(convertTypeToInt(type1)==-1|| convertTypeToInt(type2)==-1)
    {
        return ERRORCOMP;
    }
    return convertTypeToInt(type1)- convertTypeToInt(type2);
}

struct Kernel_t{
    CreatingType type;
    void* data;
};

void kernelBeginner(CopyExternal copyFunc, DestExternal freeFunc,
                    AdvanceExternal advanceFunc,DifferenceForCync diffFunc,
                    ExternalDate date, CyncFunc firstDay)
{
    coreBeginner(copyFunc,freeFunc,advanceFunc,diffFunc,date,firstDay);
}

Kernel kernelCreate(CreatingType block,bool creOrCp, CreatorUnit* elements, int elementsSize,
                    CopyFunc* copyFunctions, int copyFuncAmount,DestFunc* destructors,
                    int destructorsAmount, CompFunc comparison)
{
    Kernel new= malloc(sizeof(struct Kernel_t));
    if(!new)
    {
        return NULL;
    }
    new->type=block;
    if(creOrCp)
    {
        if(!elements)
        {
            return NULL;
        }
        if(block==AMOUNT_SET)
        {
            if(!copyFunctions||!destructors||!copyFunctions)
            {
                free(new);
                return NULL;
            }
            new->data= coreCreate(1,copyFunctions[0],destructors[0],
                                  comparison,*((int*)elements[0]));
        }
        else if (block==DATE)
        {
            new->data= coreCreate(2,NULL,NULL,NULL,-1);
        }
        else if (block==PRODUCT)
        {
            if(elementsSize!=6||!copyFunctions||copyFuncAmount!=2
                ||!destructors||destructorsAmount!=2||!comparison)
            {
                free(new);
                return NULL;
            }
            ProductAmountType type= converter((char*)elements[3]);
            if(type==ERROR)
            {
                free(new);
                return NULL;
            }
            new->data= productCreate(*((int*)elements[0]),(char*)elements[2],type,
                                     copyFunctions[0],destructors[0],elements[1],copyFunctions[1],destructors[1],
                                     comparison,elements[4],*((int*)elements[5]));
        }
        else if (block==RATIONAL)
        {
            if(elementsSize!=2||*((int*)elements[1])==0||copyFunctions||destructors||comparison)
            {
                free(new);
                return NULL;
            }
            new->data= rationalCreate(*((int*)elements[0]),*((int*)elements[1]));
        }
        else if (block==ORDER_PRODUCT)
        {
            if(elementsSize!=2||copyFunctions||destructors||comparison)
            {
                free(new);
                return NULL;
            }
            new->data= productUnitCreate((Product)elements[0],(Rational)elements[1]);
        }
        if(!new->data)
        {
            free(new);
            return NULL;
        }
    }
    return new;
}

void kernelDestroy(void* kernel)
{
    if(!kernel)
    {
        return;
    }
    if(((Kernel)kernel)->type==AMOUNT_SET||((Kernel)kernel)->type==DATE)
    {
        coreDestroy(((Kernel)kernel)->data);
    }
    else if(((Kernel)kernel)->type==PRODUCT)
    {
        productDestroy(((Kernel)kernel)->data);
    }
    else if(((Kernel)kernel)->type==RATIONAL)
    {
        rationalDestroy(((Kernel)kernel)->data);
    }
    else if(((Kernel)kernel)->type==ORDER_PRODUCT)
    {
        productUnitDestroy(((Kernel)kernel)->data);
    }
    free(kernel);
}

void* kernelCopy(void* kernel)
{
    if(!kernel||!((Kernel)kernel)->data)
    {
        return NULL;
    }
    Kernel copy= kernelCreate(AMOUNT_SET,false,NULL,
                              0,NULL,0,
                              NULL,0,NULL);
    if(!copy)
    {
        return NULL;
    }
    copy->type=((Kernel)kernel)->type;
    if(copy->type==AMOUNT_SET||copy->type==DATE)
    {
        copy->data= coreCopy(((Kernel)kernel)->data);
    }
    else if(copy->type==PRODUCT)
    {
        copy->data= productCopy(((Kernel)kernel)->data);
    }
    else if(copy->type==RATIONAL)
    {
        copy->data= rationalCopy(((Kernel)kernel)->data);
    }
    else if(copy->type==ORDER_PRODUCT)
    {
        copy->data= productUnitCopy(((Kernel)kernel)->data);
    }
    if(!copy->data)
    {
        free(copy);
        return NULL;
    }
    return copy;
}

int kernelCompeare(void* kernel1, void* kernel2)
{
    Kernel first=kernel1;
    Kernel second=kernel2;
    if(first->type!=second->type)
    {
        return typeComparison(first->type,second->type);
    }
    if(first->type==AMOUNT_SET||first->type==DATE)
    {
        return coreCompeare(first->data,second->data);
    }
    else if (first->type==PRODUCT)
    {
        return productCompeare(first->data,second->data);
    }
    else if (first->type==RATIONAL)
    {
        return rationalCompare(first->data,second->data);
    }
    else if(first->type==ORDER_PRODUCT)
    {
        return productUnitCompeare(first->data,second->data);
    }
    return ERRORCOMP;
}

Kernel kernelAddition(Kernel kernel1,Kernel kernel2)
{
    if(kernel1->type!=kernel2->type)
    {
        return NULL;
    }
    Kernel sum= kernelCreate(kernel1->type,false,NULL,0,
                             NULL,0,NULL,0,NULL);
    if(!sum)
    {
        return NULL;
    }
    sum->type=kernel1->type;
    if(!kernel1->data&&kernel2->data)
    {
        sum->data= kernelCopy(kernel2);
    }
    else if(!kernel2->data&&kernel1->data)
    {
        sum->data= kernelCopy(kernel1);
    }
    else if(kernel1->type==AMOUNT_SET||kernel1->type==DATE)
    {
        sum->data= coreAddition(kernel1->data,kernel2->data);
    }
    else if(kernel1->type==PRODUCT)
    {
        sum->data= productUnite(kernel1->data,kernel2->data);
    }
    else if(kernel1->type==RATIONAL)
    {
        sum->data= rationalAddition(kernel1->data,kernel2->data);
    }
    else if(kernel1->type==ORDER_PRODUCT)
    {
        if(productUnitCompeare(kernel1->data,kernel2->data)!=0)
        {
            free(sum);
            return NULL;
        }
        sum->data= productUnitCopy(kernel1->data);
        if(!sum->data)
        {
            free(sum);
            return NULL;
        }
        if(productUnitRaiseAmount(kernel1->data,
                                  productUnitGetAmount(kernel2->data))!=ORDER_UNIT_SUCSESS)
        {
            free(sum->data);
            free(sum);
            return NULL;
        }
    }
    if(!sum->data)
    {
        free(sum);
        return NULL;
    }
    return sum;
}

/**
 *   kernelInsert            -adds to the core (works whith all accept for date)
 * @param kernel
 * @param insertType -0 for addition
 *                    1 and onward depends if the adt have more than one area to add element
 * @param unit
 * @return
 *   KERNEL_NULL_ARGUMENT -NULL argument was passed
 *   KERNEL_ELEMENT_EXIST -the element we wish to add exist
 *   KERNEL_ERROR         -not memory related arror
 *   KERNEL_MEMORY_PROBLEM -memory problem or wrong type was passed
 *   KERNEL_SUCSESS        -the addition was sucsessful
 */
KernelErrors kernelInsert(Kernel kernel,int insertType, void* unit)
{
    if(!kernel||!unit)
    {
        return KERNEL_NULL_ARGUMENT;
    }
}

/**
 *   kernelRemove            -removes an element (works whith all accept for date)
 * @param kernel
 * @param insertType -for adt's that have more than one list
 * @param unit
 * @return
 *   KERNEL_NULL_ARGUMENT -NULL argument was passed
 *   KERNEL_ELEMENT_DOES_NOT_EXIST -the element we wish to destroy does not exist
 *   KERNEL_ERROR                  -not memory related problems
 *   KERNEL_MEMORY_PROBLEM -memory problem or wrong type was passed
 *   KERNEL_SUCSESS        -the removle was sucsessful
 */
KernelErrors kernelRemove(Kernel kernel,int insertType, void* unit);

/**
 *   kernelFilter            -filters core according to a criteria (works whith all accept for date)
 * @param kernel
 * @param filter
 * @param filKey
 * @return
 */
Kernel kernelFilter(Kernel kernel, KernelFilter filter, KerFilKey filKey);

/**
 *   kernelFind              -finds specific element(works whith all accept for date)
 * @param kernel
 * @param type
 * @param element
 * @return
 * NULL -if the element doesn't exist
 * void* otherwise
 */
void* kernelFind(Kernel kernel,int type, void* element);

/**
 *   kernelSize              -returns the size of the element (for not amount set will return -1)
 * @param kernel
 * @param type
 * @return
 *  -1 wrong type or NULL argument
 *  size otherwise
 */
int kernelSize(Kernel kernel, int type);

/**
 *   kernelGetElement        -return the data of the element
 * @param kernel
 * @return
 * NULL if null argument was passed
 * void* otherwise
 */
void* kernelGetElement(Kernel kernel);

/**
 *   kernelSetElement        -changes the element
 * @param kernel
 * @param type
 * @param element
 * @return
 *  KERNEL_NULL_ARGUMENT   -gess what
 *  KERNEL_ERROR           -not memory related problems
 *  KERNEL_MEMORY_PROBLEM  -memory problems
 *  KERNEL_SUCSESS         -the change was sucsess
 */
KernelErrors kernelSetElement(Kernel kernel,int type, void* element);

/**
 *   kernelGetFirst          -the first element of the core
 * @param kernel
 * @param type
 * @return
 *  NULL if there was a problem with the input
 *  void* otherwise
 */
void* kernelGetFirst(Kernel kernel, int type);

/**
 *   kernelGetNext           -the next element
 * @param kernel
 * @param type
 * @return
 *  NULL if there was a problem with the input
 *  void* otherwise
 */
void* kernelGetNext(Kernel kernel,int type);

/**
 *   kernelGetInternalData   -gives the internal element requested
 * @param kernel
 * @param data -the data you need
 * @return
 */
void* kernelGetInternalData(Kernel kernel, int data);

/**
 *   kernelDestroyer         -use it to end the code
 */
void kernelDestroyer();
