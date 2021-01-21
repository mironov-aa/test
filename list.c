#include <stdlib.h>
#include <string.h>
#include "list.h"

static node_t* listCreateNode(void* data, const size_t sizeElement, node_t* prev, node_t* next);

static node_t* listCreateNode(void* data, const size_t sizeElement, node_t* prev, node_t* next)
{
    node_t* node = (node_t*)(malloc(sizeof(node_t)));
    if(!node)
        return NULL;

    node->data = (void*)(malloc(sizeElement));
    if(!node->data)
    {
        free(node);
        return NULL;
    }

    memcpy(node->data, data, sizeElement);
    node->prev = prev;
    node->next = next;

    return node;
}

bool listInit(list_t** list, void* data, const size_t sizeElement) 
{
    *list = (list_t*)(malloc(sizeof(list_t)));
    if(!*list)
        return false;
    
    node_t* begin = listCreateNode(data, sizeElement, NULL, NULL);
    if(!begin)
    {
        free(*list);
        return false;
    }

    list_t initList = { sizeElement, 1, begin, begin };    
    memcpy(*list, &initList, sizeof(initList));

    return true;
}

void listFree(list_t* list)
{
    listTruncate(list, (node_t*)(list->front));
    free(list->front->data);
    free((node_t*)list->front);
    free(list);
}

void listTruncate(list_t* list, node_t* pos)
{
    node_t* iter = list->back;  
    while(iter != pos)
    {
        free(iter->data);
        node_t* prev = iter->prev;
        free(iter);
        iter = prev;
        list->countElements--;
    }
    list->back = pos;
}

void listRemoveNode(list_t* list, node_t* pos)
{
    if(pos->prev)
        pos->prev->next = pos->next;
    else
        list->front = pos->next;

    if(pos->next)
        pos->next->prev = pos->prev;
    else
        list->back = pos->prev;

    list->countElements--;
    free(pos->data);
    free(pos);
}

void listPopBack(list_t* list, void* data)
{
    memcpy(data, list->back->data, list->sizeElement);
    listRemoveNode(list, list->back);
}

void listPopFront(list_t* list, void* data)
{
    memcpy(data, list->front->data, list->sizeElement);
    listRemoveNode(list, list->front);
}

node_t* listMoveIter(node_t* iter, size_t count, bool toFront)
{
    if(toFront)
    {
        for(size_t counter = 0; counter < count; counter++)
        {
            if(!iter->prev)
                break;

            iter = iter->prev;
        }
    }
    else
    {
        for(size_t counter = 0; counter < count; counter++)
        {
            if(!iter->next)
                break;

            iter = iter->next;               
        }
    }
    return iter;
}

node_t* listPushBack(list_t* list, void* data)
{
    node_t* node = listCreateNode(data, list->sizeElement, (node_t*)list->back, NULL);
    if(!node)
        return NULL;

    list->back->next = node;
    list->back = node;
    list->countElements++;
    return node;
}

node_t* listPushFront(list_t* list, void* data)
{
    node_t* node = listCreateNode(data, list->sizeElement, NULL, (node_t*)list->front);
    if(!node)
        return NULL;

    list->front->prev = node;
    list->front = node;
    list->countElements++;
    return node;
}

node_t* listInsert(list_t* list, node_t* pos, void* data)
{
    if(pos == list->back)
    {
        return listPushBack(list, data);
    }

    node_t* node = listCreateNode(data, list->sizeElement, pos, pos->next);
    pos->next->prev = node;
    pos->next = node;    

    list->countElements++;
    return node;
}

void listPrintAll(list_t* list, void (*printData)(const void*))
{
    const node_t* iter = list->front;
    while(iter != list->back)
    {
        printData(iter->data);
        iter = iter->next;
    }
    printData(list->back->data); 
}
