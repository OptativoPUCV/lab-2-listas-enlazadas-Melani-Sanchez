#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

/*Funciones propias*/
List * createList() {
    List * newList = (List *)malloc(sizeof(List));
    if (newList == NULL) return NULL;
    newList->head = NULL;
    newList->tail = NULL;
    newList->current = NULL;
    return newList;
}

void * firstList(List * list) {
    list->current = list->head;
    if (list->current) return list->current->data;
    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL) list->current = list->current->next;
    if (list->current) return list->current->data;
    return NULL;
}

void * lastList(List * list) {
    list->current = list->tail;
    if (list->current) return list->current->data;
    
    return NULL;
}

void * prevList(List * list) {
    if (list->current == NULL) return NULL;
    list->current = list->current->prev;
    if (list->current) return list->current->data;
    return NULL;
}

void pushFront(List * list, void * data) { /* this*/
    Node * newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) { /* this*/
    Node * newNode = createNode(data);
    if (list->current == NULL){
        list->head = newNode;
        list->tail = newNode;
    }
    else{
        newNode->next = list->current->next;
        newNode->prev = list->current;
        if (list->current->next == NULL) list->tail = newNode;
        else list->current->next->prev = newNode;
        list->current->next = newNode;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) { /* this*/
    if (list == NULL || list->current == NULL) return NULL;

    void * aux = list->current;
    Node* izq = list->current->prev;
    Node* der = list->current->next;

    if (list->current == list->head) {
        free(list->current);
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
        return aux;
    }
    
    if (izq != NULL) izq->next = der;
    else list->head = der;

    if (der != NULL) der->prev = izq;
    else list->tail = izq;

    list->current = der;
    free(aux);
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}