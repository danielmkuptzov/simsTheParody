#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//teh files we are testing
#include "Kernel.h"
#include "Person.h"
#include "Apartment.h"
#include "consrtants.h"

Kernel prodarr=NULL;
int max=INTMAX;
int zero=0;
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
        if(kernelInsert(prodarr,0,productunit)!=KERNEL_SUCSESS)
        {
            kernelDestroy(product);
            personDestroy(test);
            return NULL;
        }
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
Kernel foodCheck(Kernel shoppingList)
{
    if(shoppingList==NULL)
    {
        return NULL;
    }
    int nom=1000;
    int denom=1;
    void* elem[]={&nom,&denom};
    CopyFunc ctours[]={intCopy};
    DestFunc dtours[]={intDest};
    CompFunc compare[]={intCompare};
    return kernelCreate(RATIONAL,true,elem,2,ctours,1,
                        dtours,1,compare,1);
}
void* maximum(void)
{
    return &max;
}
void init(void* year)
{
    int* yearto=year;
    *yearto=0;
}
void back(void* year)
{
    int* yearba=year;
    (*yearba)--;
}
int difference(void* a, void* b)
{
    int* first=a;
    int* second=b;
    return (*first-*second);
}
void* zerofunk(void)
{
    return &zero;
}

int main(void)
{
    int j=7;
    prodarr= kernelCreate(AMOUNT_SET,true,NULL,0,NULL,0,
                          NULL,0,NULL,0);
    if(prodarr==NULL)
    {
        return 0;
    }
    kernelEpsilonSetter(3);
    char* resNames[]={"alexander","betty","charly","daniel","evgeny",
                      "fridrich","guliver","hilbert","isic","jonatan",
                      "kolin"};
    char* names[]={"apple","ananas","aricaltural waste","banana","burger","bill",
                   "coconout","calaulator","cartoon","desk","drawer","donut",
                   "elicsir","elefant statue","epsilon","figure","frog purse","frigate",
                   "globus","glasses","g-watch","horn","horoscope","hospital","ink",
                   "india's map","insignia","jumpsuit","jewelry","jewish hat","kola",
                   "korkinet","killometraz","lamburgini","lada","lepricon","mazda",
                   "mazeraty","muzarella","neckless","norigian hat","number","organ",
                   "onion","oreo","penut","popcorn","peperoni","quest","quens crown",
                   "que","rog","rogatka","rorshach","sugar","salt","sodium",
                   "tungsten","table","teabag","terra","unicorn","union jack",
                   "uormsvikings","violin","vog","viking","wolkswagen","wave",
                   "victory sight","pepsi","pinacolada","popes hat","pineapple",
                   "x-ray bag","xcalibur","x-transmittion","yolk","yetti","yaga",
                   "zeppelin","zoom","zen","vine","vodka","logarithm","laptop",
                   "longtitude","tablet","tea- table","tablet","screen","sulfar",
                   "sun","cigarets","cherchils statu","cisco","tea","tank","tork"};
    char* prodamount[]={"any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount",
                        "any amount","any amount","any amount","any amount","any amount"};
    char* prodtypes[]={"FURNITURE","FURNITURE","FURNITURE","FURNITURE","FURNITURE",
                       "FURNITURE","FURNITURE","FURNITURE","FURNITURE","FURNITURE",
                       "FURNITURE","FURNITURE","FURNITURE","FURNITURE","FURNITURE",
                       "FURNITURE","FURNITURE","FURNITURE","FURNITURE","FURNITURE","FOOD",
                       "FOOD","FOOD","FOOD","FOOD","FOOD","FOOD",
                       "FOOD","FOOD","FOOD","FOOD","FOOD","FOOD",
                       "FOOD","FOOD","FOOD","FOOD","FOOD","FOOD","FOOD","BOOK",
                       "BOOK","BOOK","BOOK","BOOK","BOOK",
                       "BOOK","BOOK","BOOK","BOOK","BOOK",
                       "BOOK","BOOK","BOOK","BOOK","BOOK",
                       "BOOK","BOOK","BOOK","BOOK","MEDICINE","MEDICINE",
                       "MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE",
                       "MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE",
                       "MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE",
                       "MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE",
                       "MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE",
                       "MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE","MEDICINE",
                       "MEDICINE","MEDICINE"};
    kernelBeginner(intCopy,intDest,intAdvance,diffCulc,&j,refDate,
                   intCopy,intDest,zerofunk,zerofunk,intAdvance,maximum,
                   intCompare,init,back, difference);
    Kernel t= kernelCreate(DATE,true,NULL,0,NULL,
                           0,NULL,0,NULL,0);
    int* idp=&j;
    Person owner= createPerson(resNames[0],t,names,idp,j,prodamount,prodtypes);
    kernelDestroy(t);
    Kernel time=kernelCreate(DATE,true,NULL,0,NULL,
                          0,NULL,0,NULL,0);
    Apartment test= apartmentCreate(true,time,VILA,idp,intCopy,
                                    intDest,intCompare,owner,arnonaCalc,calcElec,
                                    avgSpend, calcElec,foodCheck);
    for (int i = 0; i < 10; ++i)
    {
        j++;
        int k= i*10* sizeof(char*);
        Person resident= createPerson(resNames[i],t,names+k,idp,j,prodamount+k,
                                      prodtypes+k);
        ApartmentErrorCodes resalt= apartmentAddResident(test,resident);
        if(resalt!=APARTMENT_SUCSESS)
        {
            personDestroy(resident);
            apartmentDestroy(test);
            return 0;
        }
        bool exist=false;
        APARTMENT_FOREACH(Person,iter,test,RESIDENT)
        {
            if(personCompeare(iter,resident)==0)
            {
                exist=true;
                break;
            }
        }
        personDestroy(resident);
        if(exist==false)
        {
            apartmentDestroy(test);
        }
    }
    Apartment tounite= apartmentCopy(test);
    if(tounite==NULL)
    {
        apartmentDestroy(test);
    }
    Person newres= personCopy(owner);
    if(personCompeare(newres,owner)!=0)
    {
        personDestroy(newres);
        personDestroy(owner);
        apartmentDestroy(tounite);
        apartmentDestroy(test);
    }
    Kernel tmp= kernelCopy(t);
    j=5;
    int* idpt=&j;
    void* elements[]={idpt, kernelGetElement(tmp),"yossi","any amount",idpt,
                      idpt,idpt, "MEDICINE"};
    CopyFunc copyArr[]={intCopy, intCopy, intCopy};
    DestFunc dtours[]={intDest, intDest, intDest};
    CompFunc compFunc[]={intCompare, intCompare};
    Kernel product= kernelCreate(PRODUCT,true,elements,8,copyArr,
                                 2,dtours,2,compFunc,2);
    int id=1;
    Kernel creDate= kernelCreate(DATE,true,NULL,0,NULL,0,
                                 NULL,0,NULL,0);
    char* type="any amount";
    void* elem[]={&id,creDate,"temp"};
    CopyFunc ctours[]={intCopy};
    dtours[0]=intDest;
    CompFunc compeare[]={intCompare};
    Kernel tempProd= kernelCreate(PRODUCT,true,elem,3,ctours,
                                  1,dtours,1,compeare,1);
    if(tempProd==NULL)
    {
        apartmentDestroy(tounite);
    }
    PersonErrorCodes resalt= personAddToWishList(newres,tempProd);
    kernelDestroy(tempProd);
    if(resalt!=PERSON_SUCSESS)
    {
        personDestroy(newres);
        apartmentDestroy(tounite);
        apartmentDestroy(test);
        return 0;
    }
    int res= apartmentCompeare(test,tounite);
    if(res!=0)
    {
        apartmentDestroy(tounite);
        apartmentDestroy(test);
        return 0;
    }
    ApartmentErrorCodes resaltApar= apartmentAddResident(tounite,newres);
    personDestroy(newres);
    if(resaltApar!=APARTMENT_SUCSESS)
    {
        apartmentDestroy(tounite);
        apartmentDestroy(test);
        return 0;
    }
    Apartment aparuni = partmentMerge(test,tounite);
    apartmentDestroy(test);
    apartmentDestroy(tounite);
    if(aparuni==NULL)
    {
        return 0;
    }
    //find use for Person apartmentGetOwner(Apartment apartment); but stil dont know how, maybe to  just test
    Kernel date= kernelCreate(DATE,true,NULL,0,NULL,
                              0,NULL,0,NULL,0);
    int* idq;
    id=7;
    idq=&id;
    Person newowner= personCreate(idq,intCopy,intDest,intCompare,date,"yossi",
                                  intCopy,intDest,intCompare, 1);
    if(apartmentSetOwner(tounite,newowner)!=APARTMENT_SUCSESS)
    {
        personDestroy(newowner);
        apartmentDestroy(tounite);
        return 0;
    }
    if(personCompeare(apartmentGetOwner(tounite),newowner)!=0)
    {
        personDestroy(newowner);
        apartmentDestroy(tounite);
        return 0;
    }
    if(apartmentCreateShoppingList(tounite)!=APARTMENT_SUCSESS)
    {
        personDestroy(newowner);
        apartmentDestroy(tounite);
    }
    APARTMENT_FOREACH(Kernel,iter,tounite,FURNITURE)
    {
        if(!kernelFind(prodarr,iter))
        {
            personDestroy(newowner);
            apartmentDestroy(tounite);
            kernelDestroy(prodarr);
            kernelDestroyer();
            return 0;
        }
    }
    //check if ezerithing is tested
    apartmentDestroy(aparuni);
    kernelDestroyer();
    kernelEpsilonDestroyer();
    return 0;
}
