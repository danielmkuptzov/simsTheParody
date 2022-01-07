#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>
#include <stdbool.h>

/**
 *Preson  adt
 *
 * Implements a person type. this would be outside of the kernel and would get most of the kernel adt threw the
 * void* formula, meaning that we would check the elments before doing somthing. for the name fild, please give
 * a butiful name, "ana aref" ia a bad name
 *
 *
 *
 * The following functions are available:
 *   personCreate                  -Creates a new person
 *   personDestroy                 -Deletes an existing person and frees all resources
 *   personCopy                    -Copies an existing person
 *   personCompeare                -compares between people id's
 *   personAddToWishList           -adds the product to wish list. note that this would accept only the OrderType because
 *                                   we need amount.
 *   personAddSkill                -this whould be a generic thing as we whould implement this later
 *   personRemoveFromWishList      -removes the product from wish list
 *   personFilterSkills            -filters the skills according to a critiria
 *   personFilterWishList          -filters the skills according to a critiria
 *   personAddToCV                 -adds a new element in the CV list of the person
 *   personFilterCV                -filtersCV according to a given criteria
 *   personFixSalary               -gives a person a salary
 *   personChangeBalance           -changes the person balance
 *   personChangeAmountINWIshList  -changes the amount of the product in wish list
 *   personGetWishList             -getter
 *   personGetSkills               -getter
 *   personGetCv                   -getter
 *   personGetId                   -getter
 *   personGetName                 -getter
 *   personMakeDayCycle            -function that simulate a day
 */

/**
 * the type we would use as a representive of our code
 */
typedef struct Person_t* Person;

/**
 * error codes for person
 */
 typedef enum{
     PERSON_NULL_ARGUMENT,
     PERSON_SKILL_EXIST,
     PERSON_PRODUCT_EXIST,
     PERSON_PRODUCT_DOES_NOT_EXIST,
     PERSON_CV_EXIST,
     PERSON_TOO_MUCH_TO_ADD,
     PERSON_WRONG_AMOUNT,
     PERSON_WRONG_SALARY,
     PERSON_ERROR,
     PERSON_SUCSESS
 } PersonErrorCodes;

typedef enum{
    REQUEST_SCHOOL,
    REQUEST_UNIVERSITY,
    REQUEST_MILITARY_BACKROUND,
    REQUEST_JOB,
    REQUEST_HOSPITAL,
    REQUEST_CEMETERY,
    CYCLE_ERROR
} CycleReturnCode;
/**
 *  the skill generic type
 */
 typedef void* Skill;

 /**
  * the generic copy
  */
typedef Skill (*SkillCopy)(Skill);

/**
 * the skill destroy
 */
typedef void (*SkillDestroy)(Skill);

/**
 * the skill comparison
 */
typedef int (*SkillComp)(Skill,Skill);

/**
 * the CV unit block
 */
typedef void* CVData;

/**
 * the CV copy function
 */
typedef CVData (*CVCopy)(CVData);

/**
 * the CV destroy function
 */
typedef void (*CVDestroy)(CVData);

/**
 * comparison between CV's
 */
typedef int (*CVComp)(CVData,CVData);

/**
 * key component for filtering skills
 */
 typedef void* keySkill;

/**
 * function for filtering the skills
 */
typedef bool (*SkillFilter)(Skill,keySkill);

/**
 * key component for filtering the wishlist
 */
 typedef void* keyProduct;

 /**
 * function for filtering the wishlist
 */
typedef bool (*WishlistFilter)(void*,keyProduct);

/**
* key component for filtering CV
*/
typedef void* keyCV;

/**
 * function for filtering the CV
 */
typedef bool (*CVFilter)(CVData,keyCV);

/**
 *   personCreate              -Creates a new person
 * @param id            -the id of the person
 * @param dateOfBirth   -outerCore type by number 2
 * @param name          -name is a string
 * @return
 * NULL if one of the critiria don't match
 * person otherwise
 */
Person personCreate(int id, void* dateOfBirth,char* name, SkillCopy copySkill, SkillDestroy skillDestroy,
                    SkillComp skillComp, int SkillType);

/**
 *   personDestroy             -Deletes an existing person and frees all resources
 * @param person
 */
void personDestroy(Person person);

/**
 *   personCopy                -Copies an existing person
 * @param person
 * @return
 * NULL for NULL argument or other errors
 * person otherwise
 */
Person personCopy(Person person);

/**
 *   personCompeare            -compares between people id's
 * @param person1
 * @param person2
 * @return
 * 0 -if equal
 * positive- person1 > person2
 * negative -person1< person2
 */
int personCompeare(Person person1, Person person2);

/**
 *   personAddToWishList      -adds the product to wish list. note that this would accept only the OrderType because
 *                              we need amount.
 * @param person
 * @param product
 * @return
 *   PERSON_NULL_ARGUMENT  -one of the arguments was NULL
 *   PERSON_PRODUCT_EXIST  -the product exist
 *   PERSON_ERROR          -the action failed
 *   PERSON_SUCSESS        -the addition was a sucsess
 */
PersonErrorCodes personAddToWishList(Person person, void* product);

/**
 *   personAddSkill            -this whould be a generic thing as we whould implement this later
 * @param person
 * @param skill
 * @return
 *   PERSON_NULL_ARGUMENT  -one  of the arguments was NULL
 *   PERSON_SKILL_EXIST    -the skill exist
 *   PERSON_ERROR          -the action failed
 *   PERSON_SUCSESS        -the skill was added
 */
PersonErrorCodes personAddSkill(Person person, Skill skill);

/**
 *   personRemoveFromWishList -removes the product from wish list
 * @param person
 * @param product
 * @return
 *   PERSON_NULL_ARGUMENT           -one of the arguments was NULL
 *   PERSON_PRODUCT_DOES_NOT_EXIST  -the product wasn't found
 *   PERSON_ERROR                   -the action failed
 *   PERSON_SUCSESS                 -the removle was sucsessful
 */
PersonErrorCodes personRemoveFromWishList(Person person, void* product);

/**
 *   personFilterSkills       -filters the skills according to a critiria
 * @param person
 * @param filterFunc
 * @param keyValue
 * @return
 * NULL if one of the argument was null
 * OuterCore otherwise
 */
void* personFilterSkills(Person person, SkillFilter filterFunc, keySkill keyValue);

/**
 *   personFilterWishList     -filters the skills according to a critiria
 * @param person
 * @param wishlistFilter
 * @param product
 * @return
 * NULL if one of the argument was null
 * OuterCore otherwise
 */
void* personFilterWishList(Person person, WishlistFilter wishlistFilter,keyProduct product);

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
PersonErrorCodes personAddToCV(Person person, CVData cvData,CVCopy cvCopy, CVDestroy cvDestroy,
                               void* dateStart, char* name);

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
 * @param amount
 * @return
 *   PERSON_NULL_ARGUMENT  -the argument was NULL
 *   PERSON_ERROR          -the operation failed
 *   PERSON_SUCSESS        -the change sucseeded
 */
PersonErrorCodes personChangeBalance(Person person, void* amount);

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
PersonErrorCodes personChangeAmountINWIshList(Person person, void* amount, void* product);

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
 *   @param date
 *   @param newData
 *   @return
 *       REQUEST_SCHOOL
 *       REQUEST_UNIVERSITY
 *       REQUEST_MILITARY_BACKROUND
 *       REQUEST_JOB,REQUEST_HOSPITAL
 *       REQUEST_CEMETERY
 *       CYCLE_ERROR
 */
CycleReturnCode personMakeDayCycle(Person person,void* date, void* newData);

#endif //PERSON_H
