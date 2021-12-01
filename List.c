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

//elemnt destruction
static void nodeDestroy(List list,Node* Elem)
{
    if(!Elem)
    {
        return;
    }
    list->destElement(Elem->element);
    free(Elem);
}

static Node *createNode(CopyListElement copyElem,ListElement element)
{
    Node *newElem= malloc(sizeof(Node));
    if(!newElem)
    {
        return NULL;
    }
    newElem->element=copyElem(element);
    return newElem;
}

//recursive copy of element
static Node* nodeCopy(List list, Node* node,int size)
{
    if(node==NULL)
    {
        return NULL;
    }
    Node *newElem= createNode(list->cpElement,node->element);
    if((!newElem->next)&&(size==list->size))
    {
        nodeDestroy(list,newElem);
        return NULL;
    }
    return newElem;
}

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

List listCopy(List list)
{
    if(!list)
    {
        return NULL;
    }
    List cpList= malloc(sizeof(List));
    if(!cpList)
    {
        return NULL;
    }
    cpList->destElement=list->destElement;
    cpList->cpElement=list->cpElement;
    cpList->head= nodeCopy(list,list->head,1);
    if(!cpList->head)
    {
        listDestroy(cpList);
        return NULL;
    }
    return cpList;
}

int listGetSize(List list)
{
    if(!list)
    {
        return -1;
    }
    return list->size;
}

ListElement listGetFirst(List list)
{
    if(!list)
    {
        return NULL;
    }
    list->current=list->head;
    return list->current->element;
}

ListElement listGetNext(List list)
{
    if(!list)
    {
        return NULL;
    }
    list->current=list->current->next;
    return list->current->element;
}

ListElement listGetCurrent(List list)
{
    if(!list)
    {
        return NULL;
    }
    return list->current->element;
}

ListResult listInsertFirst(List list, ListElement element)
{
    if(!list||!element)
    {
        return LIST_NULL_ARGUMENT;
    }
    Node *newElem=createNode(list->cpElement,element);
    if(!newElem)
    {
        return LIST_OUT_OF_MEMORY;
    }
    newElem->next=list->head;
    list->head=newElem;
    return LIST_SUCCESS;
}

ListResult listInsertLast(List list, ListElement element)
{
    if(!list||!element)
    {
        return LIST_NULL_ARGUMENT;
    }
    Node * newElem= createNode(list->cpElement,element);
    if(!newElem)
    {
        return LIST_OUT_OF_MEMORY;
    }
    Node *tmp=list->head;
    while (!tmp->next)
    {
        tmp=tmp->next;
    }
    tmp->next=newElem;
    return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element)
{
    if(!list||!element)
    {
        return LIST_NULL_ARGUMENT;
    }
    if(!list->current)
    {
        return LIST_INVALID_CURRENT;
    }
    Node *newElem= createNode(list->cpElement,element);
    if(!newElem)
    {
        return LIST_OUT_OF_MEMORY;
    }
    Node *tmp=list->head;
    while (tmp->next==list->current)
    {
        tmp=tmp->next;
    }
    newElem->next=list->current;
    tmp->next=newElem;
    return LIST_SUCCESS;
}

ListResult listInsertAfterCurrent(List list, ListElement element)
{
    if(!list||!element)
    {
        return LIST_NULL_ARGUMENT;
    }
    if(!list->current)
    {
        return LIST_INVALID_CURRENT;
    }
    Node *newElem= createNode(list->cpElement,element);
    if(!newElem)
    {
        return LIST_OUT_OF_MEMORY;
    }
    newElem->next=list->current->next;
    list->current->next=newElem;
    return LIST_SUCCESS;
}

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
