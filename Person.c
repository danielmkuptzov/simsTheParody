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
    return new;
}

static void* cVdataCopy(void* cvdata)
{

}

static void cvDataDestroy(void* cvdata);

static int cvDataComp(void* cvData1, void* cvData2);

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
    new->CV=coreCreate(1,,,,);
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

/**
 *   personAddToCV            -adds a new element in the CV list of the person
 * @param person
 * @param cvData
 * @return
 *   PERSON_NULL_ARGUMENT  -one of the argument was NULL
 *   PERSON_CV_EXIST       -the CV exists
 *   PERSON_ERROR          -the action failed
 *   PERSON_SUCSESS        -the addition was sucsessful
 */
PersonErrorCodes personAddToCV(Person person, CVData cvData,CVCopy cvCopy, CVDestroy cvDestroy, CVComp cvComp)
{
    if(!person||!cvData)
    {
        return PERSON_NULL_ARGUMENT;
    }
}

/**
 *   personFilterCV           -filtersCV according to a given criteria
 * @param person
 * @param cvFilter
 * @param keyCv
 * @return
 * NULL if one of the argument was null
 * OuterCore otherwise
 */
void* personFilterCV(Person person, CVFilter cvFilter, keyCV keyCv);

/**
 *   personFixSalary          -gives a person a salary
 * @param person
 * @param salary
 * @return
 *   PERSON_NULL_ARGUMENT -one of the arguments was NULL
 *   PERSON_WRONG_SALARY  -the salary is: negative, to much spesific (19.999 is not a salary)
 *   PERSON_ERROR         -the change failed
 *   PERSON_SUCSESS
 */
PersonErrorCodes personFixSalary(Person person, double salary);

/**
 *   personChangeBalance          -changes the person balance
 * @param person
 * @return
 *   PERSON_NULL_ARGUMENT  -the argument was NULL
 *   PERSON_ERROR          -the operation failed
 *   PERSON_SUCSESS        -the change sucseeded
 */
PersonErrorCodes personChangeBalance(Person person);

/**
 *   personChangeAmountINWIshList -changes the amount of the product in wish list
 * @param person
 * @param amount
 * @return
 *   PERSON_NULL_ARGUMENT -NULL argument was passed
 *   PERSON_WRONG_AMOUNT  -the amound don't match the critiria
 *   PERSON_ERROR         -the addition was wrong
 *   PERSON_SUCSESS       -the operation was sucsess
 */
PersonErrorCodes personChangeAmountINWIshList(Person person, void* amount);

/**
 *   personGetWishList            -getter
 * @param person
 * @return
 * NULL -if any problem accures
 * CoreUnit otherwise
 */
void* personGetWishList(Person person);

/**
 *   personGetSkills              -getter
 * @param person
 * @return
 * NULL if any problem accures
 * OuterCore otherwise
 */
void* personGetSkills(Person person);

/**
 *   personGetCv                  -getter
 * @param person
 * @return
 */
void* personGetCv(Person person);

/**
 *   personGetId                  -getter
 * @param person
 * @return
 * negative nuber if any problem accures
 * id otherwise
 */
int personGetId(Person person);

/**
 *   personGetName                -getter
 * @param person
 * @return
 * NULL if any problem accures
 * pointer to name otherwise
 */
char* personGetName(Person person);

/**
 *   personMakeDayCycle           -function that simulate a day
 */
CycleReturnCode personMakeDayCycle(CVData);
