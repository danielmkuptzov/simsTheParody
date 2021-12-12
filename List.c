//
// Created by danie on 01/12/2021.
//

#include "List.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node_t{
    ListElement element;
    struct node_t* next;
}* Node;

struct List_t{
    Node head;
    Node current;
    int size;
    CopyListElement cpElement;
    FreeListElement destElement;
};

//elemnt destruction
static void nodeDestroy(FreeListElement destFunc,Node Elem)
{
    if(!Elem)
    {
        return;
    }
    destFunc(Elem->element);
    nodeDestroy(destFunc,Elem->next);
    free(Elem);
}

static Node createNode(CopyListElement copyElem,ListElement element)
{
    Node newElem=malloc(sizeof(struct node_t));
    if(!newElem)
    {
        return NULL;
    }
    newElem->element=copyElem(element);
    if(!(newElem->element))
    {
        free(newElem);
        return NULL;
    }
    return newElem;
}

//recursive copy of element
static Node nodeCopy(List list, Node node,int size)
{
    if(node==NULL)
    {
        return NULL;
    }
    Node newElem= createNode(list->cpElement,node->element);
    newElem->next= nodeCopy(list, node->next,size+1);
    if((!newElem->next)&&(size==list->size))
    {
        nodeDestroy(list->destElement,newElem);
        return NULL;
    }
    return newElem;
}

//swapping nodes
static void nodeSwap(Node first, CompareListElements comparison)
{
    if(comparison(first,first->next)<0)
    {
        Node tmp=first->next;
        first->next=tmp->next;
        tmp->next=first;
        first=tmp;
    }
    return;
}

List listCreate(CopyListElement copyElement, FreeListElement freeElement)
{
    List new_list= malloc(sizeof(struct List_t));
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
    List cpList= malloc(sizeof(struct List_t));
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
    if(!(list->current))
    {
        return NULL;
    }
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

ListResult listInsertLast(List list, ListElement element)
{
    if(!list||!element)
    {
        return LIST_NULL_ARGUMENT;
    }
    Node newElem= createNode(list->cpElement,element);
    if(!newElem)
    {
        return LIST_OUT_OF_MEMORY;
    }
    if(!(list->head))
    {
        list->head=newElem;
        list->size++;
        return LIST_SUCCESS;
    }
    Node tmp=list->head;
    while (tmp->next)
    {
        tmp=tmp->next;
    }
    tmp->next=newElem;
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
    Node tmp=list->head;
    while (tmp->next==list->current)
    {
        tmp=tmp->next;
    }
    Node toDestroy=list->current;
    tmp->next=list->current->next;
    list->current->next=NULL;
    nodeDestroy(list->destElement,toDestroy);
    list->size--;
    return LIST_SUCCESS;
}


ListResult listSort(List list, CompareListElements compareElement)
{
    if (!list||!compareElement)
    {
        return LIST_NULL_ARGUMENT;
    }
    for(int i=0; i<list->size-1;i++)
    {
        Node tmp=list->head;
        for (int j =0; j<list->size-i; j++)
        {
            while(tmp->next->next)
            {
                nodeSwap(tmp->next,compareElement);
                tmp=tmp->next;
            }
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
    Node tmp=list->head;
    while (!tmp)
    {
        if(filterElement(tmp->element, &key))
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

ListResult listClear(List list)
{
    if(!list)
    {
        return LIST_NULL_ARGUMENT;
    }
    Node tmp=list->head;
    nodeDestroy(list->destElement,tmp);
    return LIST_SUCCESS;
}

void listDestroy(List list)
{
    if(!list)
    {
        return;
    }
    if(listClear(list)==LIST_SUCCESS)
    {
        free(list);
        return;
    }
    printf("operation failed");
}
