//
// Created by danie on 08/03/2022.
//

#ifndef APARTMENT_H
#define APARTMENT_H

//external libreries
#include <stdio.h>
#include <stdbool.h>

//internal libreries
#include "Kernel.h"
#include "Person.h"

/**
 * apartment  adt
 *
 * Implements an apartment data type. in this data type the apartment is a general termen for living unit,
 * meaning that the apartment could be one of the foloing categories: standart apartment, vila,
 * semi house (a living unit that is half of the house), panthouse.
 * also, the postal code could be any type you desire (recomended somthing that could be compeared and copied).
 * and please don't use float in the bills
 *
 * The following functions are available:
 *   apartmentCreate             - Creates a new apartment
 *   apartmentDestroy            - Deletes an existing apartment and frees all resources
 *   apartmentCopy               - Copies an existing apartment
 *   apartmentCompeare           -compares between apartments
 *   apartmentSetArnona          -change the arnona
 *   apartmentGetArnona          -gives back the arnona calculation
 *   apartmentGetOwner           -get the owner
 *   apartmentSetOwner           -changes the owner
 *   apartmentAddResident        -adds new resident
 *   apartmentRemoveResident     -remove resident from the apartment
 *   apartmentGiveShoppingList   -gives the shopping list of the shopping list
 *   apartmentCreateShoppingList -creates the shopping list of the residents
 *   apartmentGetResidents       -gives the list of the residents
 *   apartmentAddFurniture       -adds furniture to the apartment
 *   appaertmentRemoveFurniture  -removes furniture
 *   appartmentGetArnona         -gives the cost of the estate
 *   apartmentGetGasBill         -gives the gas bill
 *   appartmentGetType           -gives the type of the appartment
 *   apartmentGetBills           -gives the bills of the apartment
 *   partmentMerge               -merges two same apartments
 *   apartmentGetfirst           -gives the first resident in the list
 *   apartmentGetNext            -the next one
 *   apartmentFilter             -filtersAccording to a crutiria
 *   apartmentDayCycle           -for cycle work
 *   apartmentLogManager         -for log managment
 *   APARTMENT_FOREACH           -iterator for passing on the residents or the furniture
 */

//the data type
typedef struct apartment_t* Apartment;

//error codes
typedef enum {
    APARTMENT_SUCSESS,
    APARTMENT_RESIDENT_EXIST,
    APARTMENT_RESIDENT_DOES_NOT_EXIST,
    APARTMENT_NULL_ARGUMENT,
    APATMENT_NON_EXISTING_PERSON,
    APARTMENT_NO_SHOPPING_LIST,
    APARTMENT_ERROR
} ApartmentErrorCodes;

//apartment type
typedef enum {
    FLAT,
    VILA,
    SEMI_HOUSE,
    PANTHOUSE
} ApartmentType;

typedef void* PostalCode;

typedef PostalCode(*PostalCodeCopy)(PostalCode);

typedef void(*PostalCodeDestroy)(PostalCode);

typedef int(*PostalCodeCompear)(PostalCode,PostalCode);

typedef Kernel(*GetArnona)(Apartment);

typedef Kernel(*ElecBill)(Apartment);

typedef Kernel(*FoodBill)(Kernel);

typedef Kernel(*Gasbil)(Apartment);

typedef Kernel(*AvarageSpending)(GetArnona,ElecBill,FoodBill,Gasbil);

typedef Kernel(*BillFilter)(AvarageSpending);

typedef Kernel(*generalFilter)();

/**
 *   apartmentCreate            - Creates a new apartment
 * @param type
 * @param postalCode
 * @param owner
 * @return
 *   NULL for any error
 *   Apartment otherwise
 */
Apartment apartmentCreate(ApartmentType type, PostalCode postalCode,PostalCodeCopy postalCodeCopy,
                          PostalCodeDestroy destructor,PostalCodeCompear compare, Person owner,
                          GetArnona arnona,ElecBill electricity,AvarageSpending avgFunc,
                          Gasbil gasbil,FoodBill food);

/**
 *   apartmentDestroy           - Deletes an existing apartment and frees all resources
 * @param apartment
 */
void apartmentDestroy(Apartment apartment);

/**
 *   apartmentCopy              - Copies an existing apartment
 * @param apartment
 * @return
 *   NULL if there was any error
 *   apartment otherwise
 */
Apartment apartmentCopy(Apartment apartment);

/**
 *   apartmentCompeare          -compares between apartments
 * @param apartment1
 * @param apartment2
 * @
 *  positive if apartment1> apartment2
 *  negative if apartment1< apartment2
 *  0 if they are equal
 */
int apartmentCompeare(Apartment apartment1, Apartment apartment2);

/**
 *   apartmentSetArnona         -change the arnona
 * @param apartment
 * @param arnona
 * @return
 *      APARTMENT_SUCSESS -the change was sucsessful
 *      APARTMENT_NULL_ARGUMENT -a NULL argument was passed
 *      APARTMENT_ERROR
 */
ApartmentErrorCodes apartmentSetArnona(Apartment apartment, GetArnona arnona);

/**
 *   apartmentGetArnona         -gives back the arnona calculation
 * @param apartment
 * @return
 *      NULL- for any error
 *      Kernel otherwise
 */
Kernel apartmentGetArnona(Apartment apartment);

/**
 *   apartmentGetOwner          -get the owner
 * @param apartment
 * @return
 *      NULL for any error
 *      Person otherwise
 */
Person apartmentGetOwner(Apartment apartment);

/**
 *   apartmentSetOwner          -changes the owner
 * @param apartment
 * @param newOwner
 * @return
 *      APARTMENT_SUCSESS -the owner has changed
 *      APARTMENT_NULL_ARGUMENT -a NULL argument was passed
 *      APARTMENT_ERROR -any error not related to the previous one
 *      APATMENT_NON_EXISTING_PERSON -the person doesn't exist
 */
ApartmentErrorCodes apartmentSetOwner(Apartment apartment, Person newOwner);

/**
 *   apartmentAddResident       -adds new resident
 * @param apartment
 * @param newResident
 * @return
 *      APARTMENT_SUCSESS -the resident was added sucsessfuly
 *      APARTMENT_RESIDENT_EXIST -the resident already exist
 *      APARTMENT_NULL_ARGUMENT - a NULL argument was passed
 *      APARTMENT_ERROR  -any error not listed above
 */
ApartmentErrorCodes apartmentAddResident(Apartment apartment,Person newResident);

/**
 *   apartmentRemoveResident     -remove resident from the apartment
 * @param apartment
 * @param resident
 * @return
 * APARTMENT_SUCSESS -the resident was removed
 * APARTMENT_RESIDENT_DOES_NOT_EXIST -the resident you requested does'nt exist
 * APARTMENT_NULL_ARGUMENT -a NULL argument was passed
 * APARTMENT_ERROR  -any error not listed above
 */
ApartmentErrorCodes apartmentRemoveResident(Apartment apartment, Person resident);

/**
 *   apartmentGiveShoppingList   -gives the shopping list of the shopping list
 * @param apartment
 * @return
 *      NULL -for any error that might accure
 *      Kernel -otherwise
 */
Kernel apartmentGiveShoppingList(Apartment apartment);

/**
 *   apartmentCreateShoppingList -creates the shopping list of the residents
 *   apartmentGetResidents       -gives the list of the residents
 *   apartmentAddFurniture       -adds furniture to the apartment
 *   appaertmentRemoveFurniture  -removes furniture
 *   appartmentGetArnona         -gives the cost of the estate
 *   apartmentGetGasBill         -gives the gas bill
 *   appartmentGetType           -gives the type of the appartment
 *   apartmentGetBills           -gives the bills of the apartment
 *   partmentMerge               -merges two same apartments
 *   apartmentGetfirst           -gives the first resident in the list
 *   apartmentGetNext            -the next one
 *   apartmentFilter             -filtersAccording to a crutiria
 *   apartmentDayCycle           -for cycle work
 *   apartmentLogManager         -for log managment
 *   APARTMENT_FOREACH           -iterator for passing on the residents or the furniture
 * @param apartment
 * @return
 *      APARTMENT_SUCSESS -the creation was sucsessful
 *      APARTMENT_NULL_ARGUMENT -a NULL argument was passed
 *      APARTMENT_NO_SHOPPING_LIST -there was an error in the process
 *      APARTMENT_ERROR -other errors
 */
ApartmentErrorCodes apartmentCreateShoppingList(Apartment apartment);

#endif //APARTMENT_H
