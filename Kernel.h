//
// Created by danie on 08/01/2022.
//

#ifndef KERNEL_H
#define KERNEL_H

/**
 * kernel  adt
 *
 * Implements a functions that are inside the kernel
 *
 *
 *
 * The following functions are available:
 *   kernelBeginner          -the function that you use to begin the date function
 *   kernelCreate            -Creates a new kernel unit
 *   kernelDestroy           -Deletes an existing kernel unit and frees all resources
 *   kernelCopy              -Copies an existing kernel unit
 *   kernelCompeare          -compares between kernel units
 *   kernelAddition          -adds two units together
 *   kernelInsert            -adds to the core (works whith all accept for date)
 *   kernelRemove            -removes an element (works whith all accept for date)
 *   kernelFilter            -filters core according to a criteria (works whith all accept for date)
 *   kernelFind              -finds specific element(works whith all accept for date)
 *   kernelSize              -returns the size of the element (for not amount set will return -1)
 *   kernelDestroyer         -use it to end the code
 *   kernelGetElement        -return the data of the element
 *   kernelSetElement        -changes the element
 *   kernelGetInternalData   -gives the internal element requested
 *   kernelGetFirst          -the first element of the core
 *   kernelGetNext           -the next element
 *   kernel foreach          -the amount set foreach
 */

//the external libreries we are working with
#include <stdio.h>
#include <stdbool.h>

//the enums to the creator
typedef enum {
    AMOUNT_SET,
    DATE,
    PRODUCT,
    RATIONAL,
    ORDER_PRODUCT
} CreatingType;

//error enum
typedef enum{
    KERNEL_NULL_ARGUMENT,
    KERNEL_ELEMENT_EXIST,
    KERNEL_ELEMENT_DOES_NOT_EXIST,
    KERNEL_ERROR,
    KERNEL_MEMORY_PROBLEM,
    KERNEL_SUCSESS
} KernelErrors;

//this definition is for the date
typedef void* ExternalDate;

//this is for coping the external date
typedef ExternalDate (*CopyExternal)(ExternalDate);

//this is for destroing the date
typedef void (*DestExternal)(ExternalDate);

//this is for date advancment
typedef void (*AdvanceExternal)(ExternalDate);

//this is for giving the difference between the calendars
typedef int(*DifferenceForCync)();


//this is for the begining date
typedef int (*CyncFunc)();

//our base element
typedef void* CreatorUnit;

//for generic copy function
typedef CreatorUnit (*CopyFunc)(CreatorUnit);

//for generic destroy
typedef void (*DestFunc)(CreatorUnit);

//for generic compare function
typedef int(*CompFunc)(CreatorUnit,CreatorUnit);

//filtering key
typedef void* KerFilKey;

//filtering func
typedef bool (*KernelFilter)(void*, KerFilKey);

typedef struct Kernel_t* Kernel;

/**
 *   kernelBeginner          -the function that you use to begin the date function
 * @param copyFunc
 * @param freeFunc
 * @param advanceFunc
 * @param diffFunc
 * @param date
 * @param firstDay
 */
void kernelBeginner(CopyExternal copyFunc, DestExternal freeFunc,
                    AdvanceExternal advanceFunc,DifferenceForCync diffFunc,
                    ExternalDate date, CyncFunc firstDay);

/**
 *   kernelCreate            -Creates a new kernel unit
 * @param block               -the type of the kernel we need
 * @param elements            -the simple  elements we pass
 * @param elementsSize        -the elements array size
 * @param copyFunctions       -the copy functions we need
 * @param copyFuncAmount      -the size of the copy functions array
 * @param destructors         -the destructors we need
 * @param destructorsAmount   -the size of the destructors array
 * @param comparison          -the comparison functions
 * @return
 *  NULL -if one of the critiria didn't passed
 *  kernel -otherwise
 */
Kernel kernelCreate(CreatingType block, CreatorUnit* elements, int elementsSize, CopyFunc* copyFunctions, int copyFuncAmount,
                    DestFunc* destructors, int destructorsAmount, CompFunc comparison);

/**
 *   kernelDestroy           -Deletes an existing kernel unit and frees all resources
 * @param kernel
 */
void kernelDestroy(void* kernel);

/**
 *   kernelCopy              -Copies an existing kernel unit
 * @param kernel
 * @return
 * NULL -problem with the element
 * kernel -otherwise
 */
void* kernelCopy(void* kernel);

/**
 *   kernelCompeare          -compares between kernel units
 * @param kernel1
 * @param kernel2
 * @return
 * 0- equal
 * positive kernel1> kernel2
 * negative kernel1< kernel2
 */
int kernelCompeare(void* kernel1, void* kernel2);

/**
 *   kernelAddition          -adds two units together
 * @param kernel1
 * @param kernel2
 * @return
 * NULL -wrong addition or corrupter input
 * kernel otherwise
 */
Kernel kernelAddition(void* kernel1, void* kernel2);

/**
 *   kernelInsert            -adds to the core (works whith all accept for date)
 * @param kernel
 * @param insertType -for adt's that have more than one list
 * @param unit
 * @return
 *   KERNEL_NULL_ARGUMENT -NULL argument was passed
 *   KERNEL_ELEMENT_EXIST -the element we wish to add exist
 *   KERNEL_ERROR         -not memory related arror
 *   KERNEL_MEMORY_PROBLEM -memory problem or wrong type was passed
 *   KERNEL_SUCSESS        -the addition was sucsessful
 */
KernelErrors kernelInsert(Kernel kernel,int insertType, void* unit);

/**
 *   kernelRemove            -removes an element (works whith all accept for date)
 * @param kernel
 * @param insertType -for adt's that have more than one list
 * @param unit
 * @return
 *   KERNEL_NULL_ARGUMENT -NULL argument was passed
 *   KERNEL_ELEMENT_DOES_NOT_EXIST -the element we wish to destroy does not exist
 *   KERNEL_ERROR                  -not memory related problems
 *   KERNEL_MEMORY_PROBLEM -memory problem or wrong type was passed
 *   KERNEL_SUCSESS        -the removle was sucsessful
 */
KernelErrors kernelRemove(Kernel kernel,int insertType, void* unit);

/**
 *   kernelFilter            -filters core according to a criteria (works whith all accept for date)
 *   kernelFind              -finds specific element(works whith all accept for date)
 *   kernelSize              -returns the size of the element (for not amount set will return -1)
 *   kernelDestroyer         -use it to end the code
 *   kernelGetElement        -return the data of the element
 *   kernelSetElement        -changes the element
 *   kernelGetFirst          -the first element of the core
 *   kernelGetNext           -the next element
 *   kernelGetInternalData   -gives the internal element requested
 *   kernel foreach          -the amount set foreach
 * @param kernel
 * @param filter
 * @param filKey
 * @return
 */
Kernel kernelFilter(Kernel kernel, KernelFilter filter, KerFilKey filKey);


#endif //KERNEL_H