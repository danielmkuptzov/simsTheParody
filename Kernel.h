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
 *   kernelGetFirst          -the first element of the core
 *   kernelGetNext           -the next element
 *   kernel foreach          -the amount set foreach
 *   kernelGetInternalData   -gives the internal element requested
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

//for generic copy function

//for generic destroy

//for generic compare function


typedef struct Kernel_t* Kernel;



#endif //KERNEL_H
