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
 *   stringCopy              -to copy strings
 *   stringDestroy           -to destroy strings
 *   casingFixer             -to lower or upper the word
 *   stringComp              -compare between strings
 *   kernelBeginner          -the function that you use to begin the date function
 *   kernelEpsilonSetter     -to set the epsilon we would work on
 *   kernelCreate            -Creates a new kernel unit
 *   kernelDestroy           -Deletes an existing kernel unit and frees all resources
 *   kernelCopy              -Copies an existing kernel unit
 *   kernelCompeare          -compares between kernel units
 *   kernelGreaterThan       -the > opreration
 *   kernelLesserThan       -the < operation
 *   kernelEqual             -uses the operator ==
 *   kernelAddition          -adds two units together
 *   kernelInsert            -adds to the core (works whith all accept for date)
 *   kernelRemove            -removes an element (works whith all accept for date)
 *   kernelFilter            -filters core according to a criteria (works whith all accept for date)
 *   kernelFind              -finds specific element(works whith all accept for date)
 *   kernelSize              -returns the size of the element (for not amount set will return -1)
 *   kernelGetElement        -return the data of the element
 *   kernelSetElement        -changes the element
 *   kernelGetInternalData   -gives the internal element requested
 *   kernelGetFirst          -the first element of the core
 *   kernelGetNext           -the next element
 *   kernelALU               -aritmetical functions to rational and to orderProduct
 *   kernelGetType           -gives to the user the type of the kernel
 *   kernel foreach          -the amount set foreach
 *   kernelRound             -function for rounding the rational
 *   kernelSetter            -for changing things in the element
 *   kernelEpsilonDestroyer  -to destroy the epsilon
 *   kernelEpsilonGetter     -gives the epsilon
 *   kernelDestroyer         -use it to end the code
 *   kernelCheckType         -for elements that has type
 *   kernel_foreach          -iterator
 */

//the external libreries we are working with
#include <stdio.h>
#include <stdbool.h>

//internal libreries
#include "consrtants.h"

/**
 * functions for years
 */
//still a problem?
typedef void* Yearnumexter;
//change names
typedef Yearnumexter(*YearCp)(Yearnumexter);//why?
typedef void (*YearDest)(Yearnumexter);
typedef void(*YearAdv)(Yearnumexter);
typedef Yearnumexter(*MaxYear)(void);
typedef int (*YearCmp)(Yearnumexter,Yearnumexter);
//fix overriding and find doubles
typedef void(*Yearinitexter)(Yearnumexter);
//typedef struct counter_t* Counterex;
typedef Yearnumexter (*YearZeroexter)(void);
typedef void (*Yearbackadvanceexter)(Yearnumexter);
typedef Yearnumexter(*Yearlowestpossexter)(void);
typedef int (*Diffcalcexer)(Yearnumexter,Yearnumexter);
//is there no doubles? i think not

//the enums to the creator
typedef enum {
    AMOUNT_SET,
    DATE,
    PRODUCT,
    RATIONAL,
    ORDER_PRODUCT,
    ERROR_TYPE
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

//enum for internal data
typedef enum {
    ID,
    DATE_OF_CREATION,
    NAME,
    AMOUNT,
    PRODUCT_PART,
    COMPONENTS,
    ELEMENT,
    NUMERATOR,
    DENUMERATOR,
    CATEGORY,
    ADDITIONAL_DATA
} InternalDataPart;


//this definition is for the date
typedef void* ExternalDate;

//this is for coping the external date
typedef ExternalDate (*CopyExternal)(ExternalDate);

//this is for destroing the date
typedef void (*DestExternal)(ExternalDate);

//this is for date advancment
typedef void (*AdvanceExternal)(ExternalDate);

//this is for giving the difference between the calendars
typedef int(*DifferenceForCync)(void);


//this is for the begining date
typedef int (*CyncFunc)(void);

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
 *   stringCopy              -to copy strings
 * @param org
 * @return
 *   NULL if any error accures
 *   char* otherwise
 */
char*  stringCopy(char* org);

/**
 *   stringDestroy              -to destroy strings
 * @param str
 */
void stringDestroy(char* str);

/**
 *   casingFixer             -to lower or upper the word
 * @param upper
 *      true for upper
 *      false for lowercase
 * @param org
 * @return
 *      NULL if any error accures
 *      char* otherwise
 */
char*  casingFixer(bool upper, char* org);

/**
 *   stringComp              -compare between strings
 * @param first
 * @param second
 * @return
 *   positive first> second
 *   negative second> first
 *   0 if they are equal
 */
int  stringComp(char* first, char* second);

/**
 *   kernelBeginner          -the function that you use to begin the date function
 * @param copyFunc
 * @param freeFunc
 * @param advanceFunc
 * @param diffFunc
 * @param date
 * @param firstDay
 */
 //dont forget to write why? why intresting why? realy? why?
void kernelBeginner(CopyExternal copyFunc, DestExternal freeFunc,
                    AdvanceExternal advanceFunc,DifferenceForCync diffFunc,
                    ExternalDate date, CyncFunc firstDay,YearCp ctour,YearDest dtour,YearZeroexter zero,
                    Yearlowestpossexter lowest,YearAdv advance,MaxYear max,YearCmp compeare,
                    Yearinitexter init, Yearbackadvanceexter backadv, Diffcalcex diffcalc);

/**
 *   kernelEpsilonSetter     -to set the epsilon we would work on
 * @param base the power of 10 we want
 */
void kernelEpsilonSetter(int base);


/**
 *   kernelCreate            -Creates a new kernel unit
 * @param block               -the type of the kernel we need
 * @param creOrCp             -for explaining purpose
 * @param elements            -the simple  elements we pass
 * @important the order is this
 *           0- the id of the item or the element type if the type is amount set
 *           1- the date
 *           2- the name
 *           3- for product the type in char ("integer amount", "half integer amount", "any amount")
 *           4-additional data
 *           5-component data
 *           6-component type
 *           7-main category of the product
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

Kernel kernelCreate(CreatingType block,bool creOrCp,
                    CreatorUnit* elements, int elementsSize, CopyFunc* copyFunctions, int copyFuncAmount,
                    DestFunc* destructors, int destructorsAmount, CompFunc* comparison, int compAmount);

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
 *   kernelGreaterThan       -the > opreration
 *   kernelLesserThan       -the < operation
 * @param kernel1
 * @param kernel2
 * @return
 * @note if the types are different the hirarcy is-
 *  1 amount set
 *  2 date
 *  3 product
 *  4 rational
 *  5 order product
 *
 * 0- equal
 * positive kernel1> kernel2
 * negative kernel1< kernel2
 */
int kernelCompeare(void* kernel1, void* kernel2);

/**
 *   kernelGreaterThan       -the > opreration
 * @param kernel1
 * @param kernel2
 * @return
 *  true if kernel1> kernel2
 *  false otherwise
 */
bool kernelGreaterThan(void* kernel1, void* kernel2);

/**
 *   kernelLesserThan       -the < operation
 * @param kernel1
 * @param kernel2
 * @return
 *  true if kernel1< kernel2
 *  false otherwise
 */
bool kernelLesserThan(void* kernel1, void* kernel2);

/**
 *   kernelEqual             -uses the operator ==
 * @param kernel1
 * @param kernel2
 * @return
 *  true equal
 *  false non equal
 */
bool kernelEqual(void* kernel1, void* kernel2);

/**
 *   kernelAddition          -adds two units together
 * @param kernel1
 * @param kernel2
 * @return
 * NULL -wrong addition or corrupter input
 * kernel otherwise
 */
Kernel kernelAddition(Kernel kernel1,Kernel kernel2);

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
 * @param element
 * @return
 * NULL -if the element doesn't exist
 * void* otherwise
 */
void* kernelFind(Kernel kernel, void* element);

/**
 *   kernelSize              -returns the size of the element (for not amount set will return -1)
 * @param kernel
 * @param type
 * @return
 *  -1 wrong type or NULL argument
 *  size otherwise
 */
int kernelSize(Kernel kernel);

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
KernelErrors kernelSetElement(Kernel kernel,CreatingType type, void* element);

/**
 *   kernelGetFirst          -the first element of the core
 * @param kernel
 * @param type
 * @return
 *  NULL if there was a problem with the input
 *  void* otherwise
 */
void* kernelGetFirst(Kernel kernel);

/**
 *   kernelGetNext           -the next element
 * @param kernel
 * @param type
 * @return
 *  NULL if there was a problem with the input
 *  void* otherwise
 */
void* kernelGetNext(Kernel kernel);

/**
 *   kernelGetInternalData   -gives the internal element requested
 * @param kernel
 * @param data -
 *  ID
 *  DATE_OF_CREATION
 *  NAME
 *  AMOUNT
 *  PRODUCT_PART
 *  COMPONENTS
 *  ELEMENT
 *  ADDITIONAL_DATA
 * @return
 *  NULL if there was any error
 *  data otherwise
 */
const void* kernelGetInternalData(Kernel kernel, InternalDataPart data);

void* kernelGetInternalDataNonConst(Kernel kernel, InternalDataPart data);

/**
 *   kernelALU               -aritmetical functions to rational and to orderProduct
 * @param kernel1
 * @param kernel2
 * @param action
 *                0- for addition
 *                1- to substruct
 *                2- multiply
 *                3- divide
 *                4- power by integer
 * @return
 *  KERNEL_NULL_ARGUMENT   one of the arguments was NULL
 *  KERNEL_ERROR           error not related to the memory
 *  KERNEL_MEMORY_PROBLEM  the operation failed or was iligal
 *  KERNEL_SUCSESS         the operation was a sucsess
 */
KernelErrors kernelALU(Kernel kernel1, Kernel kernel2, int action);

/**
 *  kernelGetType           -gives to the user the type of the kernel
 * @param kernel
 * @return
 */
CreatingType kernelGetType(Kernel kernel);

/**
 *   kernelRound             -function for rounding the rational
 * @param kernel
 * @param typeOfRound
 *          0 -for the product round
 *          1- for the standart round
 * @return
 *      NULL if there is any error
 *      kernel elsewise
 */
Kernel kernelRound(Kernel kernel, int typeOfRound);

/**
 *   kernelSetter            -for changing things in the element
 * @param kernel
 * @param data -
 *  ID
 *  DATE_OF_CREATION
 *  NAME
 *  AMOUNT
 *  PRODUCT_PART
 *  COMPONENTS
 *  ADDITIONAL_DATA
 * @return
 *  KERNEL_NULL_ARGUMENT   one of the arguments was NULL
 *  KERNEL_ERROR           error not related to the memory
 *  KERNEL_MEMORY_PROBLEM  the element was wrong
 *  KERNEL_SUCSESS         the operation was a sucsess
 */
KernelErrors kernelSetter(Kernel kernel,InternalDataPart data, void* element);

/**
 *   kernelEpsilonDestroyer  -to destroy the epsilon
 */
void kernelEpsilonDestroyer(void);

/**
 *   kernelEpsilonGetter     -gives the epsilon
 * @return
 */
Kernel  kernelEpsilonGetter(void);

/**
 *   kernelDestroyer         -use it to end the code
 */
void kernelDestroyer(void);

/**
 *   kernelCheckType         -for elements that has type
 * @param kernel
 * @param type
 * @param name
 * @return
 *   false for any error or wrong type
 *   true otherwise
 */
bool kernelCheckType(Kernel kernel,char* name);

/**
 *   kernel foreach          -the amount set foreach
 */
#define KERNEL_FOREACH(type, iterator,kernel)          \
    for(type iterator =kernelGetFirst(kernel) ; \
        iterator ;                               \
        iterator = kernelGetNext(kernel))
#endif //KERNEL_H
