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
 * Implements an apartment data type
 *
 *
 *
 * The following functions are available:
 *   apartmentCreate            - Creates a new apartment
 *   apartmentDestroy           - Deletes an existing apartment and frees all resources
 *   apartmentCopy              - Copies an existing apartment
 *   apartmentCompeare          -compares between
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
 */

typedef struct apartment_t* Apartment;

typedef enum {} ApartmentErrorCodes;

typedef enum {} ApartmentType;

typedef Kernel(*GetArnona)();


#endif //APARTMENT_H
