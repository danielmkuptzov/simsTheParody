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

Kernel appartmentGetArnona(Apartment apartment)
{
    if(!apartment||!apartment->arnona)
    {
        return NULL;
    }
    return apartment->arnona(apartment);
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

ApartmentErrorCodes appaertmentRemoveFurniture(Apartment apartment, Kernel removedFurniture)
{
    if(!apartment||!apartment->objects||removedFurniture)
    {
        return APARTMENT_NULL_ARGUMENT;
    }
    KernelErrors resalt= kernelRemove(apartment->objects,0,removedFurniture);
    if(resalt==KERNEL_NULL_ARGUMENT)
    {
        return APARTMENT_NULL_ARGUMENT;
    }
    if(resalt==KERNEL_ELEMENT_DOES_NOT_EXIST)
    {
        return APARTMENT_FURNITURE_DOES_NOT_EXIST;
    }
    if(resalt==KERNEL_MEMORY_PROBLEM||resalt==KERNEL_ERROR)
    {
        return APARTMENT_ERROR;
    }
    return APARTMENT_SUCSESS;
}

ApartmentErrorCodes appartmentSetArnona(Apartment apartment, GetArnona newArnona)
{
    if(!apartment||!newArnona)
    {
        return APARTMENT_NULL_ARGUMENT;
    }
    apartment->arnona=newArnona;
    return APARTMENT_SUCSESS;
}

Kernel apartmentGetGasBill(Apartment apartment)
{
    if(!apartment||!apartment->gasbil)
    {
        return NULL;
    }
    return apartment->gasbil(apartment);
}

ApartmentErrorCodes appartmentSetGasBill(Apartment apartment, Gasbil newgas)
{
    if(!apartment||!newgas)
    {
        return APARTMENT_NULL_ARGUMENT;
    }
    apartment->gasbil=newgas;
    return APARTMENT_SUCSESS;
}

ApartmentType appartmentGetType(Apartment apartment)
{
    if(!apartment)
    {
        return NONE;
    }
    return (apartment->typeofapar);
}

Kernel apartmentGetBills(Apartment apartment)
{
    if(!apartment)
    {
        return NULL;
    }
    return apartment->avarageSpending(apartment->arnona,apartment->elecBill,apartment->foodBill,apartment->gasbil);
}

Apartment partmentMerge(Apartment apartment1, Apartment apartment2)
{
    if((!apartment1)&&(!apartment2))
    {
        return NULL;
    }
    if(!apartment1)
    {
        return apartmentCopy(apartment2);
    }
    if(!apartment2)
    {
        return apartmentCopy(apartment1);
    }
    if(apartment1->typeofapar!=apartment2->typeofapar)
    {
        return NULL;
    }
    Apartment uniapar= apartmentCopy(apartment1);
    if(!uniapar)
    {
        return NULL;
    }
    KernelErrors resalt=KERNEL_SUCSESS;
    KERNEL_FOREACH(Person,iter,apartment2->residents)
    {
        resalt= kernelInsert(uniapar->residents,0,iter);
        if(resalt!=KERNEL_SUCSESS)
        {
            apartmentCopy(uniapar);
            return NULL;
        }
    }
    KERNEL_FOREACH(Kernel ,iter,apartment2->objects)
    {
        resalt= kernelInsert(uniapar->objects,0,iter);
        if(resalt!=KERNEL_SUCSESS)
        {
            apartmentDestroy(uniapar);
            return NULL;
        }
    }
    KERNEL_FOREACH(Kernel,iter,apartment2->food)
    {
        resalt= kernelInsert(uniapar->food,0,iter);
        if(resalt!=KERNEL_SUCSESS)
        {
            apartmentDestroy(uniapar);
            return NULL;
        }
    }
    return uniapar;
}

Data apartmentGetfirst(Apartment apartment, DataType type)
{
    if(!apartment)
    {
        return NULL;
    }
    if(type==RESIDENT)
    {
        return kernelGetFirst(apartment->residents);
    }
    else if(type==FURNITURE)
    {
        return kernelGetFirst(apartment->objects);
    }
    else if(type==FOOD)
    {
        return kernelGetFirst(apartment->food);
    }
    return NULL;
}

Data apartmentGetNext(Apartment apartment, DataType type)
{
    if(!apartment)
    {
        return NULL;
    }
    if(type==RESIDENT)
    {
        return kernelGetNext(apartment->residents);
    }
    else if(type==FURNITURE)
    {
        return kernelGetNext(apartment->objects);
    }
    else if(type==FOOD)
    {
        return kernelGetNext(apartment->food);
    }
    return NULL;
}

/**
 *   apartmentFilter             -filters According to a crutiria
 * @param apartment
 * @param filterFunc
 * @return
 *   NULL if any problem accured
 *   Kernel otherwise
 */
Kernel apartmentFilter(Apartment apartment, GeneralFilter filterFunc, DataType type)
{
    if(!apartment||!filterFunc)
    {
        return NULL;
    }
    if(type==RESIDENT)
    {
        Kernel tosend=createSetOfPeople();
        KERNEL_FOREACH(Person,iter,apartment->residents)
        {
            //filterFunc(apartment->residents);
        }
    }
    else
    {
        int id=8;
        CreatorUnit elem[]={&id};
        CopyFunc copyFunc[1];
        DestFunc destFunc[1];
        CompFunc compFunc[1];
        Kernel tosend= kernelCreate(AMOUNT_SET,true,elem,1,copyFunc
                ,1,destFunc,1,compFunc,1);
        if()
    }
}

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
