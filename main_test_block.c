#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//teh files we are testing
#include "Kernel.h"
#include "Person.h"
#include "Apartment.h"

void* intCopy(void* org)
{
    int *copy= malloc(sizeof (int*));
    *copy=*(int*)org;
    return copy;
}
void intDest(void* org)
{
    org=NULL;
}
int intCompare(void* first, void* second)
{
    int* one=first;
    int* two=second;
    return one-two;
}
bool greaterThanEpsilon(void* ras, void* key)
{
    Kernel epsilon=kernelEpsilonGetter();
    Kernel diff= kernelAddition(epsilon,(Kernel)ras);
    bool resalt=false;
    if(kernelCompeare((Kernel)key,diff))
    {
        resalt=true;
    }
    kernelDestroy(epsilon);
    kernelDestroy(diff);
    return resalt;
}
void intAdvance(void* org)
{
    (*(int*)org)++;
}
int diffCulc(void)
{
   return -2;
}
int refDate(void)
{
    return 3;
}

Person createPerson(char* name, Kernel t, char** names,Id idp,int j, char** prodamount, char** type)
{
    Person test=personCreate(idp,intCopy,intDest,intCompare, kernelGetElement(t),"daniel",intCopy,
                             intDest,intCompare,4);
    if(!test)
    {
        return 0;
    }
    for (int k = 0; k < 10; ++k)
    {
        j=5;
        Kernel tmp= kernelCopy(t);
        int* id=&k;
        void* elements[]={id, kernelGetElement(tmp),names[k],prodamount[k],&k,
                          id,&k, type[k]};
        CopyFunc copyArr[]={intCopy, intCopy, intCopy};
        DestFunc dtours[]={intDest, intDest, intDest};
        CompFunc compFunc[]={intCompare, intCompare};
        Kernel product= kernelCreate(PRODUCT,true,elements,8,copyArr,
                                     2,dtours,2,compFunc,2);
        int den=k+1;
        int* pden=&den;
        int o=k+1;
        void* elem[]={&o,pden};
        Kernel amount= kernelCreate(RATIONAL,true,elem,2,NULL,0
                ,NULL,0,NULL,0);
        void* prodUniElem[]={kernelGetElement(product), kernelGetElement(amount)};
        Kernel productunit= kernelCreate(ORDER_PRODUCT,true,prodUniElem,2,
                                         NULL,0,NULL,
                                         0,NULL,0);
        if(!productunit)
        {
            kernelDestroy(amount);
            kernelDestroy(product);
            return 0;
        }
        kernelDestroy(product);
        kernelDestroy(amount);
        if(personAddToWishList(test,productunit)!=PERSON_SUCSESS)
        {
            return 0;
        }
        kernelDestroy(productunit);
    }
    return test;
}

Kernel arnonaCalc(Apartment theEstate)
{
    if(!theEstate)
    {
        return NULL;
    }
    ApartmentType type= appartmentGetType(theEstate);
    int nominator=1;
    int denominator=1;
    if(type==VILA)
    {
        nominator=1000;
    }
    if(type==FLAT)
    {
        nominator=70000;
    }
    if(type==SEMI_HOUSE)
    {
        nominator=9000;
    }
    void* elem[]={&nominator,&denominator};
    return kernelCreate(RATIONAL,true,elem,2,NULL,0,
                        NULL,0,NULL,0);
}

Kernel calcElec(Apartment apartment)
{
    int nominator=32;
    int denominator=1;
    void* elem[]={&nominator,&denominator};
    return kernelCreate(RATIONAL,true,elem,2,NULL,0,
                        NULL,0,NULL,0);
}

Kernel avgSpend(Apartment apartment) {
    Kernel avg = apartmentGetArnona(apartment);
    if (kernelALU(avg, apartmentGetArnona(apartment), 0) != KERNEL_SUCSESS)
    {
        kernelDestroy(avg);
        return NULL;
    }
    int amount=3;
    int base=1;
    void* element[]={&amount,&base};
    CopyFunc ctours[]={intCopy};
    DestFunc dtours[]={intDest};
    CompFunc comp[]={intCompare};
    Kernel div= kernelCreate(RATIONAL,true,element,2,ctours,1,
                             dtours,1,comp,1);
    if(div==NULL)
    {
        kernelDestroy(avg);
        return NULL;
    }
    KernelErrors res=kernelALU(avg,div,3);
    kernelDestroy(div);
    if(res!=KERNEL_SUCSESS)
    {
        kernelDestroy(avg);
        return NULL;
    }
    return avg;
}

int main(void)
{
    int j=7;
    kernelEpsilonSetter(3);
    char* resNames[]={"alexander","betty","charly","daniel","evgeny",
                      "fridrich","guliver","hilbert","isic","jonatan",
                      "kolin"};
    char* names[]={"apple","banana","coconout","desk","elicsir","figure","globus",
                   "horn","ink","jumpsuit","kola","lamburgini","mazda","neckless",
                   "organ","penut","quest","rog","salt","table","unicorn",
                   "vog","wave","pinacolada","vine","laptop","tablet","screen",
                   "cigarets","tea"};
    char* prodamount[]={"any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount"};
    char* prodtypes[]={"FURNITURE","FURNITURE","FURNITURE","FURNITURE","FURNITURE",
                       "FURNITURE","FOOD","FOOD","FOOD","FOOD","FOOD","FOOD","BOOK",
                       "BOOK","BOOK","BOOK","BOOK","BOOK","MEDICINE","MEDICINE",
                       "MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE",
                       "MEDICINE","MEDICINE","MEDICINE","MEDICINE"};
    kernelBeginner(intCopy,intDest,intAdvance,diffCulc,&j,refDate);
    Kernel t= kernelCreate(DATE,true,NULL,0,NULL,
                           0,NULL,0,NULL,0);
    int* idp=&j;
    Person owner= createPerson(resNames[0],t,names,idp,j,);
    kernelDestroy(t);
    Kernel time=kernelCreate(DATE,true,NULL,0,NULL,
                          0,NULL,0,NULL,0);
    Apartment test= apartmentCreate(true,time,VILA,idp,intCopy,intDest,intCompare,owner,arnonaCalc,
                                    calcElec,avgSpend,);
    kernelDestroyer();
    kernelEpsilonDestroyer();
    return 0;
}
