#include <stdlib.h>
#include <string.h>

#include "Person.h"
#include "OrderProduct.h"
#include "Rational.h"
#include "outerCore.h"

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
    DEAD
} Acupation;

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

typedef struct CVData_t{
    CoreUnit dateStart;
    CoreUnit dateStop;
    char* cvName;
    CVData description;
    CVCopy copy;
    CVDestroy erazor;
    CVComp comp;
}*CVdata;

static CVData cvDataCreate(CoreUnit dateStart, CVData element, CVCopy copy,CVDestroy erazor,CVComp comp,
                           char* cvName)
{
    if(!element||!copy||!dateStart||!erazor||!comp)
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
    CVdata copy= cvDataCreate(org->dateStart,org->description,org->copy,org->erazor,org->comp,org->cvName);
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
    int id;
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

Person personCreate(int id, void* dateOfBirth,char* name, SkillCopy copySkill, SkillDestroy skillDestroy,
                    SkillComp skillComp, int SkillType)
{
    if(!name||strcmp(name," "))
    {
        return NULL;
    }
    Person new= malloc(sizeof(struct Person_t));
    if(!new)
    {
        return NULL;
    }
    new->id=id;
    new->name= stringDup(name);
    if(!new->name)
    {
        personDestroy(new);
        return NULL;
    }
    new->wishList= coreCreate(1,orderUnitCopy,orderunitdestroy,orderunitcomp,5);
    if(!new->wishList)
    {
        personDestroy(new);
        return NULL;
    }
    new->salary=0.0;
    new->balance= rationalCreate(0,1);
    if(!new->salary)
    {
        personDestroy(new);
        return NULL;
    }
    new->dateOfBirth= coreCopy((CoreUnit)dateOfBirth);
    if(!new->dateOfBirth)
    {
        personDestroy(new);
        return NULL;
    }
    new->CV=coreCreate(1,cVdataCopy,cvDataDestroy,cvDataComp,5);
    if(!new->CV)
    {
        personDestroy(new);
        return NULL;
    }
    new->skills= coreCreate(1,copySkill,skillDestroy,skillComp,SkillType);
    if(!new->skills)
    {
        personDestroy(new);
        return NULL;
    }
    new->age=0;
    new->accupation=BABY;
    return new;
}

void personDestroy(Person person)
{
    if(!person)
    {
        return;
    }
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
    Person copy= personCreate(person->id,person->dateOfBirth,person->name,NULL,NULL,NULL,1);
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
    return person1->id-person2->id;
}

PersonErrorCodes personAddToWishList(Person person, void* product)
{
    if(!person||!product)
    {
        return PERSON_NULL_ARGUMENT;
    }
    OuterCoreErrors resalt= coreInsert(person->wishList,product);
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

PersonErrorCodes personRemoveFromWishList(Person person, void* product)
{
    if(!person||!product)
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
                               void* dateStart, char* name);
{
    if(!person||!cvData||!cvCopy||!cvDestroy||!cvComp)
    {
        return PERSON_NULL_ARGUMENT;
    }
    CVdata new= cvDataCreate((CoreUnit)dateStart,cvData,cvCopy,cvDestroy,cvComp,name);
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

int personGetId(Person person)
{
    if(!person)
    {
        return -1;
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

CycleReturnCode personMakeDayCycle(Person person,void* date, CVData newData,
                                   CVCopy copyData, CVDestroy dataDest,char* dataName,
                                   bool serviceFlag)
{
    if(!person||!date)
    {
        return CYCLE_ERROR;
    }
    if(coreCompeare(date,person->dateOfBirth)%365!=0)
    {
        return CYCLE_SUCSESS;
    }
    person->age++;
    if(person->age==6)
    {
        person->accupation=STUDENT;
        if(!newData&&!copyData&&!dataDest)
        {
            return REQUEST_SCHOOL;
        }
        if(nameComparison("school",dataName)==0&&
            personAddToCV(person,newData,copyData,
                          dataDest,date,dataName)==PERSON_SUCSESS)
        {
            return CYCLE_SUCSESS;
        }
        return CYCLE_ERROR;
    }
    if(person->age==18&&!serviceFlag)
    {
        person->accupation=SOLDIER;
        if(!newData&&!copyData&&!dataDest)
        {
            return REQUEST_MILITARY_BACKROUND;
        }
        if(nameComparison("service",dataName)==0&&
           personAddToCV(person,newData,copyData,
                         dataDest,date,dataName)==PERSON_SUCSESS)
        {
            return CYCLE_SUCSESS;
        }
        return CYCLE_ERROR;
    }
    if(serviceFlag&&person->age==21)
    {
        person->accupation=UNIVERCITY_STUDENT;
        if(!newData&&!copyData&&!dataDest)
        {
            return REQUEST_UNIVERSITY;
        }
        if(nameComparison("university",dataName)==0&&
           personAddToCV(person,newData,copyData,
                         dataDest,date,dataName)==PERSON_SUCSESS)
        {
            return CYCLE_SUCSESS;
        }
        return CYCLE_ERROR;
    }
    if(person->age==24)
    {
        person->accupation=CIVILIAN_JOB;
        if(!newData&&!copyData&&!dataDest)
        {
            return REQUEST_JOB;
        }
        if(nameComparison("job",dataName)==0&&
           personAddToCV(person,newData,copyData,
                         dataDest,date,dataName)==PERSON_SUCSESS)
        {
            return CYCLE_SUCSESS;
        }
        return CYCLE_ERROR;
    }
    if(person->age==80)
    {
        person->accupation=CIVILIAN_JOB;
        if(!newData&&!copyData&&!dataDest)
        {
            return REQUEST_HOSPITAL;
        }
        if(nameComparison("hospital",dataName)==0&&
           personAddToCV(person,newData,copyData,
                         dataDest,date,dataName)==PERSON_SUCSESS)
        {
            return CYCLE_SUCSESS;
        }
        return CYCLE_ERROR;
    }
    if(person->age==120)
    {
        person->accupation=DEAD;
        if(!newData&&!copyData&&!dataDest)
        {
            return REQUEST_CEMETERY;
        }
        if(nameComparison("cemetery",dataName)==0&&
           personAddToCV(person,newData,copyData,
                         dataDest,date,dataName)==PERSON_SUCSESS)
        {
            return CYCLE_SUCSESS;
        }
        return CYCLE_ERROR;
    }
    return CYCLE_SUCSESS;
}
