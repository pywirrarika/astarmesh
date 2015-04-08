/*
 * pqueue.h 
 *
 * Description: Priority queue based on a double linked list. 
 *
 * Author: Manuel Mager <fongog@gmail.com> (C) 2013
 * Copyright: GPL v3 or later
 *
 */

#ifndef PQUEUE_H
#define PQUEUE_H

#include "queue.h"
#include "base.h"
#include "graphs.h"

typedef struct anode{
    char id[21];
    int index;
    int val;
    int deph;
    int g, h;
    int coord;
    int count;
    apoint point;
    int x,y,f;
    // The queue.h stores the next and prev pointers
    struct anode *parent;
    TAILQ_ENTRY(anode) pointers; 
}anode;

typedef struct skipnode{
    int f;
    int coord;
    int level;
    anode *node;
    struct skipnode *down;
    TAILQ_ENTRY(skipnode) pointers;
}skipnode;



int     openlist_init(void); 
int     openlist_insert(anode *); 
// Use -f if we don't know the value of f
int     openlist_remove(int x, int y, int f); 
anode   *openlist_search(int x, int y, int f); 
int     openlist_remove_node(anode *); 
anode   *openlist_getmin(void);
int     openlist_free(void); 
void    openlist_print(void); 
int     openlist_empty(void);

#endif
