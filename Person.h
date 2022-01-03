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
 *   personCreate              -Creates a new person
 *   personDestroy             -Deletes an existing person and frees all resources
 *   personCopy                -Copies an existing person
 *   personCompeare            -compares between people id's
 *   personAddToWishList      -adds the product to wish list. note that this would accept only the OrderType because
 *                              we need amount.
 *   personAddSkill            -this whould be a generic thing as we whould implement this later
 *   personRemoveFromWishList -removes the product from wish list
 *   personFilterSkills       -filters the skills according to a critiria
 *   personFilterWishList     -filters the skills according to a critiria
 *   personAddToCV            -adds a new element in the CV list of the person
 *   personFilterCV           -filtersCV according to a given criteria
 *   personFixSalary          -gives a person a salary
 *   personChangeBalance      -changes the person balance
 */

/**
 * the type we would use as a representive of our code
 */
typedef struct Person_t* Person;

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
typedef bool (*SkillComp)(Skill,Skill);

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


#endif //PERSON_H
