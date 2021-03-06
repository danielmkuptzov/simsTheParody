#include <stdlib.h>
#include <string.h>

#include "../Person.h"
#include "OrderProduct.h"
#include "Rational.h"
#include "outerCore.h"

#define SCHOOLAGE 6
#define SERVICEAGE 18
#define UNIVERCITYAGE 21
#define JOBAGE 24
#define OLDAGE 80
#define DEADAGE 120

#define WORKDAY 7
#define MEGA 100

#define CAP_MIN 'A'
#define CAP_MAX 'Z'
#define LOW_MIN 'a'
#define LOW_MAX 'z'

typedef enum {
    BABY,
    STUDENT,
    UNIVERCITY_STUDENT,
    SOLDIER,
    CIVILIAN_JOB,
    VERY_OLD,
    DEAD
} Acupation;

typedef struct CVData_t{
    CoreUnit dateStart;
    CoreUnit dateStop;
    char* cvName;
    CVData description;
    CVCopy copy;
    CVDestroy erazor;
}*CVdata;

static CVData cvDataCreate(CoreUnit dateStart, CVData element, CVCopy copy,CVDestroy erazor,
                           char* cvName)
{
    if(!element||!copy||!dateStart||!erazor)
    {
        return NULL;
    }
    CVdata new= malloc(sizeof(struct CVData_t));
    if(!new)
    {
        return NULL;
    }
    new->dateStart= coreCopy(dateStart);
    if(!new->dateStart)
    {
        free(new);
        return NULL;
    }
    new->copy=copy;
    new->description=new->copy(element);
    if(!new->description)
    {
        coreDestroy(dateStart);
        free(new);
    }
    new->erazor=erazor;
    new->cvName= stringDup(cvName);
    if(!new->cvName)
    {
        new->erazor(new->description);
        coreDestroy(dateStart);
        free(new);
    }
    new->dateStop=NULL;
    return new;
}

static void* cVdataCopy(void* cvdata)
{
    if(!cvdata)
    {
        return NULL;
    }
    CVdata org= cvdata;
    CVdata copy= cvDataCreate(org->dateStart,org->description,
                              org->copy,org->erazor,org->cvName);
    if(!copy)
    {
        return NULL;
    }
    if(org->dateStop)
    {
        copy->dateStop= coreCopy(org->dateStop);
        if(!copy->dateStop)
        {
            return NULL;
        }
    }
    return copy;
}

static void cvDataDestroy(void* cvdata)
{
    if(!cvdata)
    {
        return;
    }
    coreDestroy(((CVdata)cvdata)->dateStart);
    coreDestroy(((CVdata)cvdata)->dateStop);
    free(((CVdata)cvdata)->cvName);
    ((CVdata)cvdata)->erazor(((CVdata)cvdata)->description);
    free(cvdata);
}

static int cvDataComp(void* cvData1, void* cvData2)
{
    if(nameComparison(((CVdata)cvData1)->cvName,((CVdata)cvData2)->cvName)==0)
    {
        return 0;
    }
    return coreCompeare(((CVdata)cvData1)->dateStart,((CVdata)cvData2)->dateStart);
}

struct Person_t
{
    void* id;
    IdCopy copyId;
    IdDestroy destroyId;
    IdComp idComp;
    int age;
    Acupation accupation;
    char* name;
    CoreUnit dateOfBirth;
    CoreUnit skills;
    CoreUnit wishList;
    CoreUnit CV;
    double salary;
    Rational balance;
};

static void* orderUnitCopy(void* orderUnit)
{
    return productUnitCopy((OrderUnit)orderUnit);
}

static void orderunitdestroy(void* orderUnit)
{
    productUnitDestroy((OrderUnit)orderUnit);
}

static int orderunitcomp(void* unit1, void* unit2)
{
    return productUnitCompeare((OrderUnit)unit1,(OrderUnit)unit2);
}

Person personCreate(void* id, IdCopy copyId, IdDestroy destroyId, IdComp idComp,
                    void* dateOfBirth,char* name, SkillCopy copySkill, SkillDestroy skillDestroy,
                    SkillComp skillComp, int SkillType)
{
    if(!name||name[0]==' '||!idComp||!destroyId||!idComp)
    {
        return NULL;
    }
    Person newPer= malloc(sizeof(struct Person_t));
    if(!newPer)
    {
        return NULL;
    }
    newPer->copyId=copyId;
    if(!newPer->copyId)
    {
        free(newPer);
        return NULL;
    }
    newPer->destroyId=destroyId;
    newPer->idComp=idComp;
    newPer->id=newPer->copyId(id);
    newPer->name= stringDup(name);
    if(!newPer->name)
    {
        personDestroy(newPer);
        return NULL;
    }
    newPer->wishList= coreCreate(1,orderUnitCopy,
                              orderunitdestroy,orderunitcomp,5);
    if(!newPer->wishList)
    {
        personDestroy(newPer);
        return NULL;
    }
    newPer->salary=0.0;
    newPer->balance= rationalCreate(0,1);
    if(!newPer->balance)
    {
        personDestroy(newPer);
        return NULL;
    }
    if(dateOfBirth)
    {
        newPer->dateOfBirth= coreCopy((CoreUnit)dateOfBirth);
        if(!newPer->dateOfBirth)
        {
            personDestroy(newPer);
            return NULL;
        }
    }
    newPer->CV=coreCreate(1,cVdataCopy,cvDataDestroy,cvDataComp,5);
    if(!newPer->CV)
    {
        personDestroy(newPer);
        return NULL;
    }
    newPer->skills= coreCreate(1,copySkill,skillDestroy,skillComp,SkillType);
    if(!newPer->skills)
    {
        personDestroy(newPer);
        return NULL;
    }
    newPer->age=0;
    newPer->accupation=BABY;
    return newPer;
}

void personDestroy(Person person)
{
    if(!person)
    {
        return;
    }
    person->destroyId(person->id);
    coreDestroy(person->dateOfBirth);
    coreDestroy(person->wishList);
    coreDestroy(person->skills);
    coreDestroy(person->CV);
    rationalDestroy(person->balance);
    free(person->name);
    free(person);
}

Person personCopy(Person person)
{
    if(!person)
    {
        return NULL;
    }
    Person copy= personCreate(person->id,person->copyId,person->destroyId, person->idComp,
                              person->dateOfBirth,person->name,NULL,
                              NULL,NULL,1);
    if(!copy)
    {
        return NULL;
    }
    coreDestroy(copy->wishList);
    coreDestroy(copy->CV);
    coreDestroy(copy->skills);
    copy->wishList= coreCopy(person->wishList);
    if(!copy->wishList)
    {
        personDestroy(copy);
        return NULL;
    }
    copy->skills= coreCopy(person->skills);
    if(!copy->skills)
    {
        personDestroy(copy);
        return NULL;
    }
    copy->CV= coreCopy(person->CV);
    if(!copy->CV)
    {
        personDestroy(copy);
        return NULL;
    }
    copy->balance= coreCopy(person->balance);
    if(!copy->balance)
    {
        personDestroy(copy);
        return NULL;
    }
    copy->salary=person->salary;
    copy->age=person->age;
    copy->accupation=person->accupation;
    return copy;
}

int personCompeare(Person person1, Person person2)
{
    return person1->idComp(person1->id,person2->id);
}

PersonErrorCodes personAddToWishList(Person person, Kernel product)
{
    if(!person||!product|| kernelGetType(product)!=ORDER_PRODUCT)
    {
        return PERSON_NULL_ARGUMENT;
    }
    OuterCoreErrors resalt= coreInsert(person->wishList,kernelGetElement(product));
    if(resalt==CORE_ELEMENT_EXIST)
    {
        return PERSON_PRODUCT_EXIST;
    }
    if(resalt!=CORE_SUCSESS)
    {
        return PERSON_ERROR;
    }
    return PERSON_SUCSESS;
}

PersonErrorCodes personAddSkill(Person person, Skill skill)
{
    if(!person||!skill)
    {
        return PERSON_NULL_ARGUMENT;
    }
    OuterCoreErrors resalt= coreInsert(person->skills,skill);
    if(resalt==CORE_ELEMENT_EXIST)
    {
        return PERSON_SKILL_EXIST;
    }
    if(resalt!=CORE_SUCSESS)
    {
        return PERSON_ERROR;
    }
    return PERSON_SUCSESS;
}

PersonErrorCodes personRemoveFromWishList(Person person, Kernel product)
{
    if(!person||!product|| kernelGetType(product)!=ORDER_PRODUCT)
    {
        return PERSON_NULL_ARGUMENT;
    }
    OuterCoreErrors resalt= coreRemove(person->wishList,product);
    if(resalt==CORE_ELEMENT_DOES_NOT_EXIST)
    {
        return PERSON_PRODUCT_DOES_NOT_EXIST;
    }
    if(resalt!=CORE_SUCSESS)
    {
        return PERSON_ERROR;
    }
    return PERSON_SUCSESS;
}

void* personFilterSkills(Person person, SkillFilter filterFunc, keySkill keyValue)
{
    if(!person||!filterFunc||!keyValue)
    {
        return NULL;
    }
    return coreFilter(person->skills,filterFunc,keyValue);
}

void* personFilterWishList(Person person, WishlistFilter wishlistFilter,keyProduct product)
{
    if(!person||!wishlistFilter||!product)
    {
        return NULL;
    }
    return coreFilter(person->wishList,wishlistFilter,product);
}

PersonErrorCodes personAddToCV(Person person, CVData cvData,CVCopy cvCopy, CVDestroy cvDestroy,
                               void* dateStart, char* name)
{
    if(!person||!cvData||!cvCopy||!cvDestroy)
    {
        return PERSON_NULL_ARGUMENT;
    }
    CVdata new= cvDataCreate((CoreUnit)dateStart,cvData,cvCopy,cvDestroy,name);
    if(!new)
    {
        return PERSON_ERROR;
    }
    OuterCoreErrors resalt= coreInsert(person->CV,new);
    cvDataDestroy(new);
    if(resalt==CORE_ELEMENT_EXIST)
    {
        return PERSON_CV_EXIST;
    }
    if(resalt!=CORE_SUCSESS)
    {
        return PERSON_ERROR;
    }
    return PERSON_SUCSESS;
}

void* personFilterCV(Person person, CVFilter cvFilter, keyCV keyCv)
{
    if(!person||!cvFilter||!keyCv)
    {
        return NULL;
    }
    return coreFilter(person->CV,cvFilter,keyCv);
}

PersonErrorCodes personFixSalary(Person person, double salary)
{
    if(!person)
    {
        return PERSON_NULL_ARGUMENT;
    }
    if(salary<0.0||(salary*1000)-((int)(salary*100)*10))
    {
        return PERSON_WRONG_SALARY;
    }
    person->salary+=salary;
    return PERSON_SUCSESS;
}

PersonErrorCodes personChangeBalance(Person person, void* amount)
{
    if(!person||!amount)
    {
        return PERSON_NULL_ARGUMENT;
    }
    Rational zero= rationalCreate(0,1);
    RtionalErrorCode resalt;
    if(rationalLesser((Rational)amount,zero))
    {
        Rational fixedAmount= rationalNegate(amount);
        resalt= rationalSubInto(&person->balance,fixedAmount);
        rationalDestroy(fixedAmount);
    }
    else
    {
        resalt= rationalAddInto(&person->balance,amount);
    }
    rationalDestroy(zero);
    if(resalt!=RATIONAL_SUCSESS)
    {
        return PERSON_ERROR;
    }
    return PERSON_SUCSESS;
}

PersonErrorCodes personChangeAmountINWIshList(Person person,void* amount, void* product)
{
    if(!person||!amount)
    {
        return PERSON_NULL_ARGUMENT;
    }
    Rational zero= rationalCreate(0,1);
    OrderUnit toComp=productUnitCreate((Product)product,zero);
    OrderUnit toChange= coreFind(person->wishList,toComp);
    orderunitdestroy(toComp);
    Rational changAmount=amount;
    OrderUnitErrors resalt;
    if(rationalLesser(changAmount,zero))
    {
        Rational fixedAmount= rationalNegate(changAmount);
        resalt=productUnitLowerAmount(toChange,fixedAmount);
        rationalDestroy(fixedAmount);
    }
    else
    {
        resalt= productUnitLowerAmount(toChange,changAmount);
    }
    if(resalt!=ORDER_UNIT_SUCSESS)
    {
        return PERSON_ERROR;
    }
    return PERSON_SUCSESS;
}

void* personGetWishList(Person person)
{
    if(!person)
    {
        return NULL;
    }
    return person->wishList;
}

void* personGetSkills(Person person)
{
    if(!person)
    {
        return NULL;
    }
    return person->skills;
}

void* personGetCv(Person person)
{
    if(!person)
    {
        return NULL;
    }
    return person->CV;
}

void* personGetId(Person person)
{
    if(!person)
    {
        return NULL;
    }
    return person->id;
}

char* personGetName(Person person)
{
    if(!person)
    {
        return NULL;
    }
    return person->name;
}

IdCopy personGetCopyId(Person person)
{
    if(!person)
    {
        return NULL;
    }
    return person->copyId;
}

IdDestroy personGetDestroyId(Person person)
{
    if(!person)
    {
        return NULL;
    }
    return person->destroyId;
}

IdComp personGetComp(Person person)
{
    if(!person)
    {
        return NULL;
    }
    return person->idComp;
}

static bool cvFilter(void* cvunit, void* key)
{
    if(nameComparison(((CVdata)cvunit)->cvName,(char*)key)==0)
    {
        return true;
    }
    return false;
}

static CycleReturnCode cycleChanger(Person person,void* date, CVData newData,
                                    CVCopy copyData, CVDestroy dataDest,char* dataName,
                                    Acupation newAccupation, char* accupationPlace,
                                    CycleReturnCode matchingError)
{
    person->accupation=newAccupation;
    CoreUnit filter= personFilterCV(person,cvFilter,accupationPlace);
    if(!filter)
    {
        coreDestroy(filter);
        if (!newData && !copyData && !dataDest) {
            return matchingError;
        }
        if (nameComparison(accupationPlace, dataName) == 0 &&
            personAddToCV(person, newData, copyData,
                          dataDest, date, dataName) == PERSON_SUCSESS) {
            return CYCLE_SUCSESS;
        }
        return CYCLE_ERROR;
    }
    coreDestroy(filter);
    return CYCLE_SUCSESS;
}

static CycleReturnCode moneyCycle(Person person)
{
    if(person->salary==0.0)
    {
        return CYCLE_ERROR;
    }
    Rational money= rationalCreate(person->salary*WORKDAY*MEGA,MEGA);
    if(personChangeBalance(person,money)!=PERSON_SUCSESS)
    {
        return CYCLE_ERROR;
    }
    return CYCLE_SUCSESS;
}

CycleReturnCode personMakeDayCycle(Person person,CycleReturnCode code,bool toAddToWishList,
                                   Kernel product,void* date, CVData newData,
                                   CVCopy copyData, CVDestroy dataDest,char* dataName,
                                   bool serviceFlag)
{
    if(!person||!date)
    {
        return CYCLE_ERROR;
    }
    if(person->accupation==CIVILIAN_JOB||person->accupation==SOLDIER)
    {
        return moneyCycle(person);
    }
    if(person->accupation==DEAD)
    {
        return CYCLE_ERROR;
    }
    person->age++;
    if(toAddToWishList)
    {
        if(kernelGetType(product)!=PRODUCT)
        {
            return CYCLE_ERROR;
        }
        PersonErrorCodes resalt= personAddToWishList(person, kernelGetElement(product));
        if(resalt==PERSON_SUCSESS&&code==CYCLE_SUCSESS)
        {
            return CYCLE_SUCSESS;
        }
        else if(resalt!=PERSON_SUCSESS)
        {
            return CYCLE_ERROR;
        }
    }
    if(coreCompeare(date,person->dateOfBirth)%365!=0&&code==CYCLE_SUCSESS)
    {
        return CYCLE_SUCSESS;
    }
    if((person->age>=SCHOOLAGE&&person->age<SERVICEAGE)||code==REQUEST_SCHOOL)
    {
        return cycleChanger(person,date, newData,copyData,dataDest,dataName,
        STUDENT,"school",REQUEST_SCHOOL);
    }
    if((person->age>=SERVICEAGE&&person->age<UNIVERCITYAGE&&!serviceFlag)||code==REQUEST_MILITARY_BACKROUND)
    {
        return cycleChanger(person,date, newData,copyData,dataDest,dataName,
                            SOLDIER,"service",REQUEST_MILITARY_BACKROUND);
    }
    if((serviceFlag&&person->age>=UNIVERCITYAGE&&person->age<JOBAGE)||code==REQUEST_UNIVERSITY)
    {
        return cycleChanger(person,date, newData,copyData,dataDest,dataName,
                            UNIVERCITY_STUDENT,"univercity",
                            REQUEST_UNIVERSITY);
    }
    if((person->age>=JOBAGE&&person->age<OLDAGE)||code==REQUEST_JOB)
    {
        return cycleChanger(person,date, newData,copyData,dataDest,dataName,
                            CIVILIAN_JOB,"job",
                            REQUEST_JOB);
    }
    if((person->age>=OLDAGE&&person->age<DEADAGE)||code==REQUEST_HOSPITAL)
    {
        return cycleChanger(person,date, newData,copyData,dataDest,dataName,
                            VERY_OLD,"hospital",
                            REQUEST_HOSPITAL);
    }
    if(person->age>=DEADAGE||code==REQUEST_CEMETERY)
    {
        return cycleChanger(person,date, newData,copyData,dataDest,dataName,
                            DEAD,"cemetery",
                            REQUEST_CEMETERY);
    }
    return CYCLE_SUCSESS;
}
