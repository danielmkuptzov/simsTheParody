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
 *   apartmentCreate            - Creates a new apartment
 *   apartmentDestroy           - Deletes an existing apartment and frees all resources
 *   apartmentCopy              - Copies an existing apartment
 *   apartmentCompeare          -compares between apartments
 *   apartmentSetArnona         -change the arnona
 *   apartmentGetOwner          -get the owner
 *   apartmentSetOwner          -changes the owner
 *   apartmentAddResident       -adds new resident
 *   apartmentRemoveResident    -remove resident from the apartment
 *   apartmentGiveShoppingList  -gives the shopping list of the shopping list
 *   apartmentGetResidents      -gives the list of the residents
 *   apartmentAddFurniture      -adds furniture to the apartment
 *   appaertmentRemoveFurniture -removes furniture
 *   appartmentGetArnona        -gives the cost of the estate
 *   appartmentGetType          -gives the type of the appartment
 *   apartmentGetBills          -gives the bills of the apartment
 *   partmentMerge              -merges two same apartments
 *   apartmentGetfirst          -gives the first resident in the list
 *   apartmentGetNext           -the next one
 *   apartmentFilter            -filtersAccording to a crutiria
 *   APARTMENT_FOREACH          -iterator for passing on the residents or the furniture
 */

//the data type
typedef struct apartment_t* Apartment;

//error codes
typedef enum {
    APARTMENT_SUCSESS,
    APARTMENT_RESIDENT_EXIST,
    APARTMENT_RESIDENT_DOES_NOT_EXIST,
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

typedef Kernel(*AvarageSpending)(GetArnona,ElecBill,FoodBill);

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
                          GetArnona arnona,ElecBill electricity, FoodBill food);

/**
 *   apartmentDestroy           - Deletes an existing apartment and frees all resources
 * @param apartment
 */
void apartmentDestroy(Apartment apartment);

/**
 *   apartmentCopy              - Copies an existing apartment
 *   apartmentCompeare          -compares between apartments
 * @param apartment
 * @return
 *   NULL if there was any error
 *   apartment otherwise
 */
Apartment apartmentCopy(Apartment apartment);

/**
 *   apartmentSetArnona         -change the arnona
 *   apartmentGetOwner          -get the owner
 *   apartmentSetOwner          -changes the owner
 *   apartmentAddResident       -adds new resident
 *   apartmentRemoveResident    -remove resident from the apartment
 *   apartmentGiveShoppingList  -gives the shopping list of the shopping list
 *   apartmentGetResidents      -gives the list of the residents
 *   apartmentAddFurniture      -adds furniture to the apartment
 *   appaertmentRemoveFurniture -removes furniture
 *   appartmentGetArnona        -gives the cost of the estate
 *   appartmentGetType          -gives the type of the appartment
 *   apartmentGetBills          -gives the bills of the apartment
 *   partmentMerge              -merges two same apartments
 *   apartmentGetfirst          -gives the first resident in the list
 *   apartmentGetNext           -the next one
 *   apartmentFilter            -filtersAccording to a crutiria
 *   APARTMENT_FOREACH          -iterator for passing on the residents or the furniture
 * @param apartment1
 * @param apartment2
 * @return
 */
int apartmentCompeare(Apartment apartment1, Apartment apartment2);


#endif //APARTMENT_H
