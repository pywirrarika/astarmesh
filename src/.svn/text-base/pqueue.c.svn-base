/*
 * pqueue.c 
 *
 * Description: Priority queue based on a double linked list. 
 *
 * Author: Manuel Mager <fongog@gmail.com> (C) 2013
 * Copyright: GPL v3 or later
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "base.h"
#include "pqueue.h"
#include "graphs.h"


void openlist_print(void)
{
    anode *item;
    TAILQ_FOREACH(item, &openlist, pointers){
        printf("x = %d; y = %d; f = %d\n", item->x, item->y, item->f);
    }
}

int openlist_empty(void)
{
    return TAILQ_EMPTY(&openlist);
}

int openlist_init(void)
{
    if(!TAILQ_EMPTY(&openlist))
        return 0;
    TAILQ_INIT(&openlist);
    return 1;
}

int openlist_insert(anode *elm)
{
    anode *item;
    elm->coord = elm->x * 10000 + elm->y;
    
    if(TAILQ_EMPTY(&openlist)){
        TAILQ_INSERT_HEAD(&openlist, elm, pointers);
        return 1;
    }

    TAILQ_FOREACH(item, &openlist, pointers){
        if(item->f > elm->f){
            TAILQ_INSERT_BEFORE(item, elm, pointers);
            return 1;
        }
    }
    if(item == NULL){
            TAILQ_INSERT_TAIL(&openlist, elm, pointers);
            return 1;
    }
    return 0;
}

anode *openlist_search(int x, int y, int f)
{
    anode *item;
    if(f != -1)
    {
        TAILQ_FOREACH(item, &openlist, pointers){
            if(item == NULL)
                return NULL;

            if(item->f == f)
                return item;
        }
        return NULL;
    }
    
    TAILQ_FOREACH(item, &openlist, pointers){
        if(item == NULL)
            return NULL;

        if(item->x == x && item->y == y)
            return item;
    }
    return NULL;
}

anode *openlist_getmin(void)
{
    anode *item;
    if(TAILQ_EMPTY(&openlist))
        return NULL;
    item = TAILQ_FIRST(&openlist);
    TAILQ_REMOVE(&openlist, item, pointers);
    return item;
}
     
int openlist_remove_node(anode *elm)
{
    if(elm != NULL){
        TAILQ_REMOVE(&openlist, elm, pointers);
        return 1;
    }
    return 0;
}

int openlist_free(void)
{
    anode *item;
    while(!TAILQ_EMPTY(&openlist))
    {
        item = TAILQ_FIRST(&openlist);
        TAILQ_REMOVE(&openlist, item, pointers);
        free(item);
        item = NULL;
    }
    return 1;
}

int openlist_remove(x, y, f)
{
    anode *item;
    if(f <= -1)
        return 0;
    item = openlist_search(x,y,f);
    if(item != NULL){
        TAILQ_REMOVE(&openlist, item, pointers);
        return 1;
    }
    return 0;
}

