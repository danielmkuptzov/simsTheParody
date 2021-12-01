//
// Created by danie on 01/12/2021.
//

#include "List.h"
#include <stdlib.h>

typedef struct node_t{
    ListElement element;
    struct node_t* next;
}Node;

struct List_t{
    Node *head;
    Node *current;
    int size;
    CopyListElement cpElement;
    FreeListElement destElement;
};

List listCreate(CopyListElement copyElement, FreeListElement freeElement)
{
    List new_list= malloc(sizeof(List));
    if(!new_list)
    {
        return NULL;
    }
    new_list->cpElement=copyElement;
    new_list->destElement=freeElement;
    return new_list;
}

/**
* Creates a copy of target list.
*
* The new copy will contain all the elements from the source list in the same
* order and will use the same functions as the original list for copying and
* freeing elements.
*
* @param list The target list to copy
* @return
* NULL if a NULL was sent or a memory allocation failed.
* A List containing the same elements with same order as list otherwise.
*/
List listCopy(List list)
{
    List cpList= malloc(sizeof(List));

}

/**
* Returns the number of elements in a list
*
* @param list The target list which size is requested.
* @return
* -1 if a NULL pointer was sent.
* Otherwise the number of elements in the list.
*/
int listGetSize(List list);

/**
* Sets the internal iterator to the first element and retrieves it.
*
* The list has an internal iterator (also called current element) to allow
* iteration over the list's elements. This function sets the iterator to point
* to the first element in the list and return it.
* Use this to start iteraing over the list, searching from the beginning of
* the list and/or get the first element in the list.
* (To continue iteration use listGetNext)
* @code
* void f(List list) {
*   ListElement first = listGetFirst(list);
*   printf("The first element is at address %x\n", first);
* }
* @endcode
*
* @param list The list for which to set the iterator and return the first
* element.
* @return
* NULL is a NULL pointer was sent or the list is empty.
* The first element of the list otherwise
*/
ListElement listGetFirst(List list);

/**
* Advances the list's iterator to the next element and return it
*
* @param list The list for which to advance the iterator
* @return
* NULL if reached the end of the list, the iterator is at an invalid state or
* a NULL sent as argument
* The next element on the list in case of success
*/
ListElement listGetNext(List list);

/**
* Returns the current element (pointed by the iterator)
*
* @param list The list for which to get the iterator
* @return
* NULL if the iterator is at an invalid state or a NULL sent as argument
* The current element on the list in case of success
*/
ListElement listGetCurrent(List list);

/**
* Adds a new element to the list, the new element will be the first element.
*
* @param list The list for which to add an element in its start
* @param element The element to insert. A copy of the element will be
* inserted as supplied by the copying function which is stored in the list
* @return
* LIST_NULL_ARGUMENT if a NULL was sent as list
* LIST_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* an element failed)
* LIST_SUCCESS the element has been inserted successfully
*/
ListResult listInsertFirst(List list, ListElement element);

/**
* Adds a new element to the list, the new element will be the last element
*
* @param list The list for which to add an element in its end
* @param element The element to insert. A copy of the element will be
* inserted as supplied by the copying function which is stored in the list
* @return
* LIST_NULL_ARGUMENT if a NULL was sent as list
* LIST_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* an element failed)
* LIST_SUCCESS the element has been inserted successfully
*/
ListResult listInsertLast(List list, ListElement element);

/**
* Adds a new element to the list, the new element will be place right before
* the current element (As pointed by the inner iterator of the list)
*
* @param list The list for which to add an element before its current element
* @param element The element to insert. A copy of the element will be
* inserted as supplied by the copying function which is stored in the list
* @return
* LIST_NULL_ARGUMENT if a NULL was sent as list
* LIST_INVALID_CURRENT if the list's iterator is in an invalid state (Does
* not point to a legal element in the list)
* LIST_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* an element failed)
* LIST_SUCCESS the element has been inserted successfully
*/
ListResult listInsertBeforeCurrent(List list, ListElement element);

/**
* Adds a new element to the list, the new element will be place right after
* the current element (As pointed by the inner iterator be of the list)
*
* @param list The list for which to add an element after its current element
* @param element The element to insert. A copy of the element will be
* inserted as supplied by the copying function which is stored in the list
* @return
* LIST_NULL_ARGUMENT if a NULL was sent as list
* LIST_INVALID_CURRENT if the list's iterator is in an invalid state (Does
* not point to a legal element in the list)
* LIST_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* an element failed)
* LIST_SUCCESS the element has been inserted successfully
*/
ListResult listInsertAfterCurrent(List list, ListElement element);

/**
* Removes the currently pointed element of the list using the stored freeing
* function
*
* @param list The list for which the current element will be removed
* @return
* LIST_NULL_ARGUMENT if list is NULL
* LIST_INVALID_CURRENT if the current pointer of the list is in invalid state
* LIST_SUCCESS the current element was removed successfully
*/
ListResult listRemoveCurrent(List list);

/**
* Sorts the list according to the given function.
*
* For example, the following code will sort a list of integers according to
* their distance from 0.
* @code
* int closerToZero(ListElement num1, ListElement num2) {
*   int distance1 = abs(*(int*)num1);
*   int distance2 = abs(*(int*)num2);
*   return distance1 - distance2;
* }
*
* void sortInts(List listOfInts) {
*   listSort(listOfInts, closerToZero);
* }
* @endcode
*
* @param list the target list to sort
* @param compareElement A comparison function as defined in the type
* CompareListElements. This function should return an integer indicating the
* relation between two elements in the list
*
* @return
* LIST_NULL_ARGUMENT if list or compareElement are NULL
* LIST_OUT_OF_MEMORY if a memory allocation failed, the list will be intact
* in this case.
* LIST_SUCCESS if sorting completed successfully.
*/
ListResult listSort(List list, CompareListElements compareElement);

/**
* Creates a new filtered copy of a list.
*
* This creates a new list with only the elements for which the filtering
* function returned true.
*
* For example, the following code creates a new list, given a list of strings
* containing only the strings which are longer than 10 characters.
* @code
*
* bool isLongerThan(ListElement string, ListFilterKey key) {
*   return strlen(string) > *(int*)key;
* }
*
* List createFilteredList(List listOfStrings) {
*   int key = 10;
*   return listFilter(listOfStrings, isLongerThan, &key);
* }
* @endcode
*
* @param list The list for which a filtered copy will be made
* @param filterElement The function used for determining whether a given
* element should be in the resulting list or not.
* @param key Any extra values that need to be sent to the filtering function
* when called
* @return
* NULL if list or filterElement are NULL or a memory allocation failed.
* A List containing only elements from list which filterElement returned true
* for.
*/
List listFilter(List list, FilterListElement filterElement, ListFilterKey key);

/**
* Removes all elements from target list.
*
* The elements are deallocated using the stored freeing function
* @param list Target list to remove all element from
* @return
* LIST_NULL_ARGUMENT - if a NULL pointer was sent.
* LIST_SUCCESS - Otherwise.
*/
ListResult listClear(List list);

/**
* listDestroy: Deallocates an existing list. Clears all elements by using the
* stored free function.
*
* @param list Target list to be deallocated. If list is NULL nothing will be
* done
*/
void listDestroy(List list);
