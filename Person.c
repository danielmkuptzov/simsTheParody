#include <stdlib.h>

#include "Person.h"
#include "OrderProduct.h"
#include "Rational.h"
#include "outerCore.h"
#include "Product.h"

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
                    SkillComp skillComp, CVCopy cvCopy, CVDestroy cvDestroy, CVComp cvComp);

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
PersonErrorCodes personAddToCV(Person person, CVData cvData);

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
void personMakeDayCycle();
