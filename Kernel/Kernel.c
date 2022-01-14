#include <stdlib.h>

#include "Rational.h"
#include "OrderProduct.h"
#include "outerCore.h"
#include "Product.h"
#include "../Kernel.h"

void kernelBeginner(CopyExternal copyFunc, DestExternal freeFunc,
                    AdvanceExternal advanceFunc,DifferenceForCync diffFunc,
                    ExternalDate date, CyncFunc firstDay)
{
    coreBeginner(copyFunc,freeFunc,advanceFunc,diffFunc,date,firstDay);
}

/**
 *   kernelCreate            -Creates a new kernel unit
 * @param block               -the type of the kernel we need
 * @param creOrCp             -for explaining purpose
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
Kernel kernelCreate(CreatingType block,bool creOrCp, CreatorUnit* elements, int elementsSize, CopyFunc* copyFunctions, int copyFuncAmount,
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
 * @param kernel
 * @param filter
 * @param filKey
 * @return
 */
Kernel kernelFilter(Kernel kernel, KernelFilter filter, KerFilKey filKey);

/**
 *   kernelFind              -finds specific element(works whith all accept for date)
 * @param kernel
 * @param type
 * @param element
 * @return
 * NULL -if the element doesn't exist
 * void* otherwise
 */
void* kernelFind(Kernel kernel,int type, void* element);

/**
 *   kernelSize              -returns the size of the element (for not amount set will return -1)
 * @param kernel
 * @param type
 * @return
 *  -1 wrong type or NULL argument
 *  size otherwise
 */
int kernelSize(Kernel kernel, int type);

/**
 *   kernelGetElement        -return the data of the element
 * @param kernel
 * @return
 * NULL if null argument was passed
 * void* otherwise
 */
void* kernelGetElement(Kernel kernel);

/**
 *   kernelSetElement        -changes the element
 * @param kernel
 * @param type
 * @param element
 * @return
 *  KERNEL_NULL_ARGUMENT   -gess what
 *  KERNEL_ERROR           -not memory related problems
 *  KERNEL_MEMORY_PROBLEM  -memory problems
 *  KERNEL_SUCSESS         -the change was sucsess
 */
KernelErrors kernelSetElement(Kernel kernel,int type, void* element);

/**
 *   kernelGetFirst          -the first element of the core
 * @param kernel
 * @param type
 * @return
 *  NULL if there was a problem with the input
 *  void* otherwise
 */
void* kernelGetFirst(Kernel kernel, int type);

/**
 *   kernelGetNext           -the next element
 * @param kernel
 * @param type
 * @return
 *  NULL if there was a problem with the input
 *  void* otherwise
 */
void* kernelGetNext(Kernel kernel,int type);

/**
 *   kernelGetInternalData   -gives the internal element requested
 * @param kernel
 * @param data -the data you need
 * @return
 */
void* kernelGetInternalData(Kernel kernel, int data);

/**
 *   kernelDestroyer         -use it to end the code
 */
void kernelDestroyer();
