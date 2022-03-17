#include "Apartment.h"

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
 * @param apartment
 * @return
 *      APARTMENT_SUCSESS -the creation was sucsessful
 *      APARTMENT_NULL_ARGUMENT -a NULL argument was passed
 *      APARTMENT_NO_SHOPPING_LIST -there was an error in the process
 *      APARTMENT_ERROR -other errors
 */
ApartmentErrorCodes apartmentCreateShoppingList(Apartment apartment);

/**
 *   apartmentGetResidents       -gives the list of the residents
 * @param apartment
 * @return
 */
Kernel apartmentGetResidents(Apartment apartment);

/**
 *   apartmentAddFurniture       -adds furniture to the apartment
 * @param apartment
 * @param furniture
 * @return
 *      APARTMENT_SUCSESS -the opreration terminated with sucsess
 *      APARTMENT_NULL_ARGUMENT -a NULL argument was passed
 *      APARTMENT_NOT_ENOTH_SPACE -we can't add this
 *      APARTMENT_ERROR -any error not listed above
 */
ApartmentErrorCodes apartmentAddFurniture(Apartment apartment, Kernel furniture);

/**
 *   appaertmentRemoveFurniture  -removes furniture
 * @param apartment
 * @param removedFurniture
 * @return
 * APARTMENT_SUCSESS -the removle was sucsessful
 * APARTMENT_NULL_ARGUMENT -a NULL argument was passed
 * APARTMENT_FURNITURE_DOES_NOT_EXIST -the object you requested does not exist
 * APARTMENT_ERROR -any error not listed above
 */
ApartmentErrorCodes appaertmentRemoveFurniture(Apartment apartment, Kernel removedFurniture);

/**
 *   appartmentGetArnona         -gives the cost of the estate
 * @param apartment
 * @return
 *  NULL if any error acures
 *  Kernel otherwise
 */
Kernel appartmentGetArnona(Apartment apartment);

/**
 *   apartmentGetGasBill         -gives the gas bill
 * @param apartment
 * @return
 *  NULL for any error
 *  Kernel otherwise
 */
Kernel apartmentGetGasBill(Apartment apartment);

/**
 *   appartmentGetType           -gives the type of the appartment
 * @param apartment
 * @return
 *   NONE -if there is any error
 *   type otherwise
 */
ApartmentType appartmentGetType(Apartment apartment);

/**
 *   apartmentGetBills           -gives the bills of the apartment
 * @param apartment
 * @return
 *   NULL if any error acures
 *   Kernel otherwise
 */
Kernel apartmentGetBills(Apartment apartment);

/**
 *   partmentMerge               -merges two same apartments
 * @param apartment1
 * @param apartment2
 * @return
 *   NULL for any error
 *   Apartment otherwise
 */
Apartment partmentMerge(Apartment apartment1, Apartment apartment2);

/**
 *   apartmentGetfirst           -gives the first resident in the list
 * @param apartment
 * @param type
 * @return
 *   NULL if there was any error or shor list
 *   Data otherwise
 */
Data apartmentGetfirst(Apartment apartment, DataType type);

/**
 *   apartmentGetNext            -the next one
 * @param apartment
 * @param type
 * @return
 *   NULL any problem or we reached the end of the list
 *   Data otherwise
 */
Data apartmentGetNext(Apartment apartment, DataType type);

/**
 *   apartmentFilter             -filters According to a crutiria
 * @param apartment
 * @param filterFunc
 * @return
 *   NULL if any problem accured
 *   Kernel otherwise
 */
Kernel apartmentFilter(Apartment apartment, GeneralFilter filterFunc);

/**
 *   apartmentDayCycle           -for cycle work
 * @param apartment
 * @param action
 * @param object
 * @return
 *    the standart one
 */
ApartmentErrorCodes apartmentDayCycle(Apartment apartment, ApartmentCycleErrorCodes action, Data object);

/**
 *   apartmentLogManager         -for log managment
 *   APARTMENT_FOREACH           -iterator for passing on the residents or the furniture
 * @param apartment
 * @return
 *    the standat one
 */
ApartmentErrorCodes apartmentLogManager(Apartment apartment, ApartmentLogActions action);
