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

char*  stringCopy(char* org)
{
    return stringDup(org);
}

char*  casingFixer(bool upper, char* org)
{
    if(!org)
    {
        return NULL;
    }
    return casingFix(upper,org);
}

/**
 *   stringComp              -compare between strings
 * @param first
 * @param second
 * @return
 *   positive first> second
 *   negative second> first
 *   0 if they are equal
 */
int  stringComp(char* first, char* second);

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

void kernelEpsilonSetter(int base)
{
    Rational newEpsilon= doubleToRationalConvert(base);
    if(!newEpsilon)
    {
        return;
    }
    productSetEpsilon(newEpsilon);
    if(!productGetEpsilon())
    {
        productSetEpsilon(newEpsilon);
    }
    rationalDestroy(newEpsilon);
}

Kernel kernelCreate(CreatingType block,bool creOrCp, CreatorUnit* elements, int elementsSize,
                    CopyFunc* copyFunctions, int copyFuncAmount,DestFunc* destructors,
                    int destructorsAmount, CompFunc comparison)
{
    Kernel newKer= malloc(sizeof(struct Kernel_t));
    if(!newKer)
    {
        return NULL;
    }
    newKer->type=block;
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
                free(newKer);
                return NULL;
            }
            newKer->data= coreCreate(1,copyFunctions[0],destructors[0],
                                  comparison,*((int*)elements[0]));
        }
        else if (block==DATE)
        {
            newKer->data= coreCreate(2,NULL,NULL,NULL,-1);
        }
        else if (block==PRODUCT)
        {
            if(elementsSize!=6||!copyFunctions||copyFuncAmount!=2
                ||!destructors||destructorsAmount!=2||!comparison)
            {
                free(newKer);
                return NULL;
            }
            ProductAmountType type= converter((char*)elements[3]);
            if(type==ERROR)
            {
                free(newKer);
                return NULL;
            }
            newKer->data= productCreate(*((int*)elements[0]),(char*)elements[2],type,
                                     copyFunctions[0],destructors[0],elements[1],copyFunctions[1],destructors[1],
                                     comparison,elements[4],*((int*)elements[5]));
        }
        else if (block==RATIONAL)
        {
            if(elementsSize!=2||*((int*)elements[1])==0||copyFunctions||destructors||comparison)
            {
                free(newKer);
                return NULL;
            }
            newKer->data= rationalCreate(*((int*)elements[0]),*((int*)elements[1]));
        }
        else if (block==ORDER_PRODUCT)
        {
            if(elementsSize!=2||copyFunctions||destructors||comparison)
            {
                free(newKer);
                return NULL;
            }
            newKer->data= productUnitCreate((Product)elements[0],(Rational)elements[1]);
        }
        if(!newKer->data)
        {
            free(newKer);
            return NULL;
        }
    }
    return newKer;
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

bool kernelGreaterThan(void* kernel1, void* kernel2)
{
    if(kernelCompeare(kernel1,kernel2)>0)
    {
        return true;
    }
    return false;
}

bool kernelLesserThan(void* kernel1, void* kernel2)
{
    return kernelGreaterThan(kernel2,kernel1);
}

bool kernelEqual(void* kernel1, void* kernel2)
{
    return ((!kernelGreaterThan(kernel1,kernel2))&&(!kernelLesserThan(kernel1,kernel2)));
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

KernelErrors kernelInsert(Kernel kernel,int insertType, void* unit)
{
    if(!kernel||!unit)
    {
        return KERNEL_NULL_ARGUMENT;
    }
    if(insertType==0&&kernel->type==ORDER_PRODUCT)
    {
        if(productUnitChangeAmount(kernel->data,unit)==ORDER_UNIT_SUCSESS)
        {
            return KERNEL_SUCSESS;
        }
        return KERNEL_ERROR;
    }
    else
    {
        if(kernel->type==AMOUNT_SET)
        {
            OuterCoreErrors resalt=coreInsert(kernel->data,unit);
            if(resalt==CORE_ELEMENT_EXIST)
            {
                return KERNEL_ELEMENT_EXIST;
            }
            else if(resalt==CORE_SUCSESS)
            {
                return KERNEL_SUCSESS;
            }
            return KERNEL_ERROR;
        }
        else if(kernel->type==DATE)
        {
            return KERNEL_ERROR;
        }
        else if(kernel->type==PRODUCT)
        {
            ProductErrorCode resalt= productAddComponent(kernel->data,unit);
            if(resalt==PRODUCT_COMPONENT_ALREADY_EXIST)
            {
                return KERNEL_ELEMENT_EXIST;
            }
            else if(resalt==PRODUCT_SUCSESS)
            {
                return KERNEL_SUCSESS;
            }
            return KERNEL_ERROR;
        }
        else if(kernel->type==RATIONAL)
        {
            Kernel newElement=unit;
            if(kernel->type!=newElement->type)
            {
                return KERNEL_ERROR;
            }
            RtionalErrorCode resalt= rationalArithmeticChange(kernel->data,newElement->data);
            if(resalt==RATIONAL_ERROR)
            {
                return KERNEL_ERROR;
            }
            return KERNEL_SUCSESS;
        }
        return KERNEL_MEMORY_PROBLEM;
    }
}

KernelErrors kernelRemove(Kernel kernel,int insertType, void* unit)
{
    if(!kernel||!unit)
    {
        return KERNEL_NULL_ARGUMENT;
    }
    if(kernel->type==RATIONAL||kernel->type==DATE||kernel->type==ORDER_PRODUCT)
    {
        return KERNEL_ERROR;
    }
    else if (kernel->type==AMOUNT_SET)
    {
        OuterCoreErrors resalt=coreRemove(kernel->data,unit);
        if(resalt==CORE_SUCSESS)
        {
            return KERNEL_SUCSESS;
        }
        else if (resalt==CORE_ELEMENT_DOES_NOT_EXIST)
        {
            return KERNEL_ELEMENT_DOES_NOT_EXIST;
        }
        return KERNEL_ERROR;
    }
    else if(kernel->type==PRODUCT)
    {
        ProductErrorCode resalt= productRemoveComponent(kernel->data,unit);
        if(resalt==PRODUCT_COMPONENT_DOES_NOT_EXIST)
        {
            return KERNEL_ELEMENT_DOES_NOT_EXIST;
        }
        if(resalt==PRODUCT_SUCSESS)
        {
            return KERNEL_SUCSESS;
        }
        return KERNEL_ERROR;
    }
    return KERNEL_ERROR;
}


Kernel kernelFilter(Kernel kernel, KernelFilter filter, KerFilKey filKey)
{
    if(!kernel||!filter||!filKey)
    {
        return NULL;
    }
    if(kernel->type==RATIONAL||kernel->type==DATE||kernel->type==ORDER_PRODUCT)
    {
        return NULL;
    }
    Kernel filtered= kernelCreate(kernel->type,false,NULL,0,
                                  NULL,0,NULL,0,NULL);
    if(!filtered)
    {
        return NULL;
    }
    if(kernel->type==PRODUCT)
    {
        filtered->data=productComponentFilter(kernel->data,filter,filKey);
    }
    else if(kernel->type==AMOUNT_SET)
    {
        filtered->data=coreFilter(kernel->data,filter,filKey);
    }
    if(!filtered->data)
    {
        kernelDestroy(filtered);
        return NULL;
    }
    return filtered;
}

void* kernelFind(Kernel kernel, void* element)
{
    if(!kernel||!element)
    {
        return NULL;
    }
    CompFunc compFunc=NULL;
    if(kernel->type==AMOUNT_SET)
    {
        compFunc=coreGetCompare(kernel->data);
        if(!compFunc)
        {
            return NULL;
        }
        CORE_FOREACH(void*, iter, kernel->data)
        {
            if(compFunc(element,iter)==0)
            {
                return iter;
            }
        }
    }
    else if(kernel->type==PRODUCT)
    {
        compFunc= productGetCompDataFunc(kernel->data);
        if(!compFunc)
        {
            return NULL;
        }
        PRODUCT_FOREACH(iter,kernel->data)
        {
            if(compFunc(iter,element))
            {
                return iter;
            }
        }
    }
    return NULL;
}

int kernelSize(Kernel kernel)
{
    if(!kernel)
    {
        return -1;
    }
    if(kernel->type==AMOUNT_SET)
    {
        return coreSize(kernel->data);
    }
    else if(kernel->type==PRODUCT)
    {
        return productGetCompAmount(kernel->data);
    }
    return -1;
}

void* kernelGetElement(Kernel kernel)
{
    if(!kernel)
    {
        return NULL;
    }
    return kernel->data;
}

KernelErrors kernelSetElement(Kernel kernel,CreatingType type, void* element)
{
    if(!kernel)
    {
        return KERNEL_NULL_ARGUMENT;
    }
    CreatingType tmpType=kernel->type;
    void* tmpData= kernel->data;
    kernel->type=type;
    if (kernel->type==AMOUNT_SET||kernel->type==DATE)
    {
        kernel->data= coreCopy(element);
    }
    else if (kernel->type==PRODUCT)
    {
        kernel->data= productCopy(element);
    }
    else if (kernel->type==RATIONAL)
    {
        kernel->data= rationalCopy(kernel->data);
    }
    else if(kernel->type==ORDER_PRODUCT)
    {
        kernel->data= productUnitCopy(element);
    }
    if(!kernel->data)
    {
        kernel->type=tmpType;
        kernel->data=tmpData;
        return KERNEL_ERROR;
    }
    return KERNEL_SUCSESS;
}

void* kernelGetFirst(Kernel kernel)
{
    if(!kernel||!(kernel->data))
    {
        return NULL;
    }
    if(kernel->type==ORDER_PRODUCT||kernel->type==RATIONAL||kernel->type==DATE)
    {
        return NULL;
    }
    if(kernel->type==AMOUNT_SET)
    {
        return coreGetFirst(kernel->data);
    }
    else if(kernel->type==PRODUCT)
    {
        return productGetFirst(kernel->data);
    }
    return NULL;
}

void* kernelGetNext(Kernel kernel)
{
    if(!kernel||!(kernel->data))
    {
        return NULL;
    }
    if(kernel->type==DATE||kernel->type==RATIONAL||kernel->type==ORDER_PRODUCT)
    {
        return NULL;
    }
    if(kernel->type==AMOUNT_SET)
    {
        return coreGetNext(kernel->data);
    }
    else if(kernel->type==PRODUCT)
    {
        return productGetNext(kernel->data);
    }
    return NULL;
}

const void* kernelGetInternalData(Kernel kernel, InternalDataPart data)
{
    if(!kernel)
    {
        return NULL;
    }
    if(kernel->type==DATE)
    {
        return NULL;
    }
    else if(kernel->type==AMOUNT_SET)
    {
        if(data==ELEMENT)
        {
            return coreGetElement(kernel->data);
        }
        return NULL;
    }
    else if(kernel->type==PRODUCT)
    {
        if(data==ID)
        {
            int* toSend=malloc(sizeof(int));
            *toSend=productGetId(kernel->data);
            return  toSend;
        }
        else if(data==DATE_OF_CREATION)
        {
            return productGetDate(kernel->data);
        }
        else if (data==NAME)
        {
            return productGetName(kernel->data);
        }
        else if(data==COMPONENTS)
        {
            return productGetComponent(kernel->data);
        }
        else if(data==ADDITIONAL_DATA)
        {
            return productGetAdditionalData(kernel->data);
        }
        return NULL;
    }
    else if (kernel->type==ORDER_PRODUCT)
    {
        if(data==PRODUCT_PART)
        {
            return productUnitGetProduct(kernel->data);
        }
        else if(data==AMOUNT)
        {
            return productUnitGetAmount(kernel->data);
        }
        return NULL;
    }
    if(kernel->type==RATIONAL)
    {
        int* dataRas= malloc(sizeof(int));
        if(data==NUMERATOR)
        {
            *dataRas= rationalGetNumerator(kernel->data);
            return dataRas;
        }
        else if(data==DENUMERATOR)
        {
            *dataRas= rationalGetDenumerator(kernel->data);
            return dataRas;
        }
        else
        {
            free(dataRas);
            return NULL;
        }
    }
    return NULL;
}

KernelErrors kernelALU(Kernel kernel1, Kernel kernel2, int action)
{
    if(!kernel1||!kernel2)
    {
        return KERNEL_NULL_ARGUMENT;
    }
    if(kernel1->type!=RATIONAL||kernel2->type!=RATIONAL)
    {
        return KERNEL_ERROR;
    }
    RtionalErrorCode resalt=RATIONAL_ERROR;
    Rational* tmp=kernel1->data;
    if(action==0)
    {
        Kernel tmpKern=kernel1;
        kernel1=kernelAddition(kernel1, kernel2);
        if(!kernel1)
        {
            kernel1=tmpKern;
            return KERNEL_MEMORY_PROBLEM;
        }
        kernelDestroy(tmpKern);
        return KERNEL_SUCSESS;
    }
    else if(action==1)
    {
        resalt= rationalSubInto(tmp,kernel2->data);
    }
    else if(action==2)
    {
        resalt= rationalMultiplyInto(tmp,kernel2->data);
    }
    else if(action==3)
    {
        resalt= rationaldivideInto(tmp,kernel2->data);
    }
    else if(action==4)
    {
        resalt= rationalPowerInto(tmp,kernel2->data);
    }
    if(resalt==RATIONAL_NULL_ARGUMENT)
    {
        return KERNEL_NULL_ARGUMENT;
    }
    else if(resalt==RATIONAL_ERROR)
    {
        return KERNEL_ERROR;
    }
    else if(resalt==RATIONAL_DIVISION_BY_ZERO)
    {
        return KERNEL_MEMORY_PROBLEM;
    }
    else if(resalt==RATIONAL_SUCSESS)
    {
        return KERNEL_SUCSESS;
    }
    return KERNEL_ERROR;
}

CreatingType kernelGetType(Kernel kernel)
{
    if(!kernel)
    {
        return ERROR_TYPE;
    }
    return kernel->type;
}

Kernel kernelRound(Kernel kernel, int typeOfRound)
{
    if(!kernel||typeOfRound>1||kernel->type!=RATIONAL)
    {
        return NULL;
    }
    Kernel toSend= kernelCreate(RATIONAL,false,NULL,0,NULL,
                                0,NULL,0,NULL);
    if(!toSend)
    {
        return NULL;
    }
    toSend->data= rationalPureRound(kernel->data,typeOfRound);
    if(!toSend->data)
    {
        kernelDestroy(toSend);
        return NULL;
    }
    return toSend;
}

KernelErrors kernelSetter(Kernel kernel,InternalDataPart data, void* element)
{
    if(!kernel||!element)
    {
        return KERNEL_NULL_ARGUMENT;
    }
    if(kernel->type==RATIONAL||kernel->type==AMOUNT_SET)
    {
        return KERNEL_ERROR;
    }
    else if(kernel->type==DATE)
    {
        if(coreSetElement(kernel->data, element, convertTypeToInt(DATE))!=CORE_SUCSESS)
        {
            return KERNEL_ERROR;
        }
    }
    if(kernel->type==PRODUCT)
    {
        ProductErrorCode resalt=PRODUCT_ERROR;
        if(data==ADDITIONAL_DATA)
        {
            resalt= productSetAdditionalData(kernel->data,element);
        }
        if(resalt!=PRODUCT_SUCSESS)
        {
            return KERNEL_ERROR;
        }
    }
    else if(kernel->type==ORDER_PRODUCT)
    {
        OrderUnitErrors resalt=ORDER_UNIT_ERROR;
        if(data==AMOUNT)
        {
            Kernel amount=element;
            if(amount->type==RATIONAL)
            {
                resalt= productUnitChangeAmount(kernel->data,amount->data);
            }
        }
        if(resalt!=ORDER_UNIT_SUCSESS)
        {
            return KERNEL_ERROR;
        }
    }
    return KERNEL_ERROR;
}

/**
 *   kernelEpsilonDestroyer  -to destroy the epsilon
 */
void kernelEpsilonDestroyer()
{
    productDestroyEpsilon();
}

Kernel  kernelEpsilonGetter()
{
    Kernel toSend=kernelCreate(RATIONAL,false,NULL,0,NULL,
                               0,NULL,0,NULL);
    if(!toSend)
    {
        return NULL;
    }
    toSend->data= rationalCopy(productGetEpsilon());
    return toSend;
}


void kernelDestroyer()
{
    coreDestroyer();
}
