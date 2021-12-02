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
static void nodeDestroy(FreeListElement destFunc,Node* Elem)
{
    if(!Elem)
    {
        return;
    }
    destFunc(Elem->element);
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
        nodeDestroy(list->destElement,newElem);
        return NULL;
    }
    return newElem;
}

//swapping nodes
static Node *nodeSwap(Node *first,Node *second,CompareListElements comparison)
{
    if(comparison(first,second)<0)
    {
        Node* tmp=second;
        first->next=tmp->next;
        tmp->next=first;
        first=tmp;
    }
    return first;
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
    new_list->size=0;
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
    cpList->size=list->size;
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
    list->size++;
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
    list->size++;
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
    list->size++;
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
    list->size++;
    return LIST_SUCCESS;
}

ListResult listRemoveCurrent(List list)
{
    if(!list)
    {
        return LIST_NULL_ARGUMENT;
    }
    if(!list->current)
    {
        return LIST_INVALID_CURRENT;
    }
    Node *tmp=list->head;
    while (tmp->next==list->current)
    {
        tmp=tmp->next;
    }
    Node *toDestroy=list->current;
    tmp->next=list->current->next;
    nodeDestroy(list->destElement,list->current);
    list->size--;
    return LIST_SUCCESS;
}


ListResult listSort(List list, CompareListElements compareElement)
{
    if (!list||!compareElement)
    {
        return LIST_NULL_ARGUMENT;
    }
    list->head=nodeSwap(list->head,list->head->next,compareElement);
    Node *tmp=list->head;
    for (int i =list->size; i >0; ++i)
    {
        int j=0;
        while(!tmp->next->next&&j!=i)
        {
            tmp->next=nodeSwap(tmp->next,tmp->next->next,compareElement);
            tmp=tmp->next;
        }
    }
    return LIST_SUCCESS;
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key)
{
    if(!list||!filterElement)
    {
        return NULL;
    }
    List filList= listCreate(list->cpElement,list->destElement);
    if(!filList)
    {
        return NULL;
    }
    Node *tmp=list->head;
    while (!tmp)
    {
        if(filterElement(tmp->element)==&key)
        {
            if(listInsertLast(filList,tmp->element)!=LIST_SUCCESS)
            {
                listDestroy(filList);
                return NULL;
            }
        }
    }
    return filList;
}

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
