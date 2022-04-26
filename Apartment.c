#include <stdlib.h>

#include "Apartment.h"

static void* residentCopy(void* resident)
{
    if(!resident)
    {
        return NULL;
    }
    return personCopy(resident);
}

static void residentDestroy(void* resident)
{
    if(!resident)
    {
        return;
    }
    personDestroy(resident);
}


static int residentcomp(void* resident1, void* resident2)
{
    return personCompeare(resident1,resident2);
}

static Kernel createSetOfPeople()
{
    int id=3;
    void* elem[1]={&id};
    CopyFunc copy[1]={residentCopy};
    DestFunc destruct[1]={residentDestroy};
    CompFunc compFunc[1]={residentcomp};
    return kernelCreate(AMOUNT_SET,true,elem,1,copy,1,
                                       destruct,1,compFunc,1);
}

typedef struct apar_elem_t{
    Kernel requestors;
    Kernel object;
}* ApapShoppingBlock;


static ApapShoppingBlock elementCreate(bool creorcp, Person first, Kernel product)
{
    ApapShoppingBlock new_elem= malloc(sizeof(struct apar_elem_t));
    if(!new_elem)
    {
        return NULL;
    }
    if(creorcp)
    {
        if(!first||!product)
        {
            free(new_elem);
            return NULL;
        }
        new_elem->requestors=createSetOfPeople();
        if (!new_elem->requestors)
        {
            free(new_elem);
            return NULL;
        }
        KernelErrors resalt= kernelInsert(new_elem->requestors,0,first);
        if(resalt!=KERNEL_SUCSESS)
        {
            kernelDestroy(new_elem->requestors);
            free(new_elem);
            return NULL;
        }
        new_elem->object= kernelCopy(product);
        if(!new_elem->object)
        {
            kernelDestroy(new_elem->requestors);
            free(new_elem);
            return NULL;
        }
    }
    return new_elem;
}

static void elemDestroy(void* elem)
{
    ApapShoppingBlock toDestroy=elem;
    kernelDestroy(toDestroy->requestors);
    kernelDestroy(toDestroy->object);
}

static void* elemCopy(void* original)
{
    ApapShoppingBlock org=original;
    ApapShoppingBlock copy= malloc(sizeof(struct apar_elem_t));
    if(!copy)
    {
        return NULL;
    }
    copy->requestors= kernelCopy(org->requestors);
    if(!copy->requestors)
    {
        free(copy);
        return NULL;
    }
    copy->object= kernelCopy(org->object);
    if(!copy->object)
    {
        kernelDestroy(copy->requestors);
        free(copy);
        return NULL;
    }
    return NULL;
}

static int elemComp(void* elem1, void* elem2)
{
    return(kernelCompeare(((ApapShoppingBlock)elem1)->object,((ApapShoppingBlock)elem2)->object));
}

struct apartment_t{
    ApartmentType typeofapar;
    PostalCode id;
    PostalCodeCopy postalCodeCopy;
    PostalCodeDestroy destroyer;
    PostalCodeCompear postComp;
    Person owner;
    Kernel residents;
    Kernel objects;
    Kernel food;
    GetArnona arnona;
    ElecBill elecBill;
    Gasbil gasbil;
    AvarageSpending avarageSpending;
    FoodBill foodBill;
    Kernel shoppingList;
};


Apartment apartmentCreate(bool creorcp,ApartmentType type, PostalCode postalCode,PostalCodeCopy postalCodeCopy,
                          PostalCodeDestroy destructor,PostalCodeCompear compare, Person owner,
                          GetArnona arnona,ElecBill electricity,AvarageSpending avgFunc,
                          Gasbil gasbil,FoodBill food)
{
    if(type==NONE||!postalCode||!postalCodeCopy||!destructor||!compare||
    !owner||!arnona||!electricity||!avgFunc||!gasbil||!food)
    {
        return NULL;
    }
    Apartment newapartment= malloc(sizeof(struct apartment_t));
    if(!newapartment)
    {
        return NULL;
    }
    newapartment->typeofapar=type;
    newapartment->postalCodeCopy=postalCodeCopy;
    newapartment->id=newapartment->postalCodeCopy(postalCode);
    if(!newapartment->id)
    {
        free(newapartment);
        return NULL;
    }
    newapartment->destroyer=destructor;
    newapartment->postComp=compare;
    newapartment->owner= personCopy(owner);
    if(!newapartment->owner)
    {
        apartmentDestroy(newapartment);
        return NULL;
    }
    newapartment->arnona=arnona;
    newapartment->elecBill=electricity;
    newapartment->avarageSpending=avgFunc;
    newapartment->gasbil=gasbil;
    newapartment->foodBill=food;
    if(creorcp)
    {
        int id=3;
        void* elem[1];
        CopyFunc copy[1];
        DestFunc destruct[1];
        CompFunc compFunc[1];
        newapartment->residents= createSetOfPeople();
        if(!newapartment->residents)
        {
            apartmentDestroy(newapartment);
            return NULL;
        }
        elem[0]=&id;
        copy[0]=kernelCopy;
        destruct[0]=kernelDestroy;
        compFunc[0]=kernelCompeare;
        newapartment->objects= kernelCreate(AMOUNT_SET,true,elem,1,copy,1,
                                            destruct,1,compFunc,1);
        if(!newapartment->objects)
        {
            free(newapartment);
            return NULL;
        }
        newapartment->food= kernelCreate(AMOUNT_SET,true,elem,1,copy,1,
                                            destruct,1,compFunc,1);
        if(!newapartment->food)
        {
            free(newapartment);
            return NULL;
        }
    }
    return newapartment;
}

void apartmentDestroy(Apartment apartment)
{
    if(!apartment)
    {
        return;
    }
    kernelDestroy(apartment->residents);
    kernelDestroy(apartment->food);
    kernelDestroy(apartment->objects);
    apartment->destroyer(apartment->id);
    personDestroy(apartment->owner);
    free(apartment);
}

Apartment apartmentCopy(Apartment apartment)
{
    if(!apartment)
    {
        return NULL;
    }
    Apartment copyApar= apartmentCreate(false,apartment->typeofapar,apartment->id,
                                        apartment->postalCodeCopy,apartment->destroyer,
                                        apartment->postComp,apartment->owner,apartment->arnona,
                                        apartment->elecBill,apartment->avarageSpending,
                                        apartment->gasbil,apartment->foodBill);
    if(!copyApar)
    {
        return NULL;
    }
    copyApar->residents= kernelCopy(apartment->residents);
    if(!copyApar->residents)
    {
        apartmentDestroy(copyApar);
        return NULL;
    }
    copyApar->objects= kernelCopy(apartment->objects);
    if(!copyApar->objects)
    {
        apartmentDestroy(copyApar);
        return NULL;
    }
    copyApar->food= kernelCopy(apartment->food);
    if(!copyApar->food)
    {
        apartmentDestroy(copyApar);
        return NULL;
    }
    return copyApar;
}

int apartmentCompeare(Apartment apartment1, Apartment apartment2)
{
    return apartment1->postComp(apartment1->id,apartment2->id);
}

Kernel apartmentGetArnona(Apartment apartment)
{
    return apartment->arnona(apartment);
}

Person apartmentGetOwner(Apartment apartment)
{
    return apartment->owner;
}

ApartmentErrorCodes apartmentSetOwner(Apartment apartment, Person newOwner)
{
    if(!apartment||!newOwner)
    {
        return APARTMENT_NULL_ARGUMENT;
    }
    personDestroy(apartment->owner);
    apartment->owner= personCopy(newOwner);
    if(!apartment->owner)
    {
        return APARTMENT_ERROR;
    }
    return APARTMENT_SUCSESS;
}

ApartmentErrorCodes apartmentAddResident(Apartment apartment,Person newResident) {
    if (!apartment || !apartment->residents || !newResident) {
        return APARTMENT_NULL_ARGUMENT;
    }
    KernelErrors resalt = kernelInsert(apartment->residents, 1, newResident);
    if (resalt == KERNEL_NULL_ARGUMENT)
    {
        return APARTMENT_NULL_ARGUMENT;
    }
    if(resalt==KERNEL_MEMORY_PROBLEM||resalt==KERNEL_ERROR)
    {
        return APARTMENT_ERROR;
    }
    if(resalt==KERNEL_ELEMENT_EXIST)
    {
        return APARTMENT_RESIDENT_EXIST;
    }
    return APARTMENT_SUCSESS;
}

ApartmentErrorCodes apartmentRemoveResident(Apartment apartment, Person resident)
{
    if(!apartment||!apartment->residents||!resident)
    {
        return APARTMENT_NULL_ARGUMENT;
    }
    KernelErrors resalt= kernelRemove(apartment->residents,1,resident);
    if(resalt==KERNEL_NULL_ARGUMENT)
    {
        return APARTMENT_NULL_ARGUMENT;
    }
    if(resalt==KERNEL_ELEMENT_DOES_NOT_EXIST)
    {
        return APARTMENT_RESIDENT_DOES_NOT_EXIST;
    }
    if(resalt==KERNEL_ERROR||resalt==KERNEL_MEMORY_PROBLEM)
    {
        return APARTMENT_ERROR;
    }
    return APARTMENT_SUCSESS;
}

Kernel apartmentGiveShoppingList(Apartment apartment)
{
    if(!apartment||!apartment->shoppingList)
    {
        return NULL;
    }
    int id=9;
    CreatorUnit unit[]={&id};
    CopyFunc ctours[]={elemCopy};
    DestFunc dtours[]={elemDestroy};
    CompFunc compFunc[]={elemComp};
    Kernel toSend= kernelCreate(AMOUNT_SET,true,unit,1,ctours,
                                1,dtours,1,compFunc,1);
    if(!toSend)
    {
        return NULL;
    }
    Kernel toSendtmp=NULL;
    KERNEL_FOREACH(Person,data,apartment->residents)
    {
        toSendtmp=kernelAddition(toSend, personGetWishList(data));
        kernelDestroy(toSend);
        if(!toSendtmp)
        {
            return NULL;
        }
        toSend=toSendtmp;
    }
    return toSend;
}

ApartmentErrorCodes apartmentCreateShoppingList(Apartment apartment)
{
    if(!apartment)
    {
        return APARTMENT_NULL_ARGUMENT;
    }
    if(apartment->shoppingList)
    {
        kernelDestroy(apartment->shoppingList);
    }
    apartment->shoppingList=apartmentGiveShoppingList(apartment);
    if(!apartment->shoppingList)
    {
        return APARTMENT_NO_SHOPPING_LIST;
    }
    return APARTMENT_SUCSESS;
}

Kernel apartmentGetResidents(Apartment apartment)
{
    if(!apartment)
    {
        return NULL;
    }
    return apartment->residents;
}

ApartmentErrorCodes apartmentAddFurniture(Apartment apartment, Kernel furniture)
{
    if(!apartment||!furniture)
    {
        return APARTMENT_NULL_ARGUMENT;
    }
    KernelErrors resalt= kernelInsert(apartment->objects,0,furniture);
    if(resalt==KERNEL_NULL_ARGUMENT)
    {
        return APARTMENT_NULL_ARGUMENT;
    }
    if(resalt==KERNEL_ELEMENT_EXIST)
    {
        return APARTMENT_FURNITURE_EXISTS;
    }
    if(resalt==KERNEL_ERROR||resalt==KERNEL_MEMORY_PROBLEM)
    {
        return APARTMENT_ERROR;
    }
    return APARTMENT_SUCSESS;
}

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
