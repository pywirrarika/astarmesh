/*
 * closedlist.c 
 *
 * Description: Hashtable interface that uses the closed list for the
 *              A* Algorithm. 
 *
 * Author: Manuel Mager <fongog@gmail.com> (C) 2014
 * Copyright: GPL v3 or later
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "graphs.h"
#include "closedlist.h"

void print_closed_iter(char *key, void *value);

void 
print_closed_iter(char *key, void *value)
{

    printf("f=%d, x=%d, y=%d\n", \
            ((anode *)(value))->f, \
            ((anode *)(value))->x, \
            ((anode *)(value))->y  \
            );
}
 
int 
closedlist_init(aobj *astar)
{
    int x, y;
    if(!(astar->cache))
        return 0;
    for(x=0; x<x_tildes; x++)
    {
        for(y=0; y<y_tildes; y++)
        {
            astar->cache[x][y].inclosed = 0;
        }
    }
    astar->closed_empty = 0;
    return 1;
}

int
closedlist_insert(aobj *astar, anode *node)
{
    if(node == NULL)
        return 0;
    if(astar == NULL)
        return 0;
    astar->cache[node->x][node->y].inclosed = 1;
    astar->cache[node->x][node->y].pointer = node;
    astar->closed_empty++;
    return 1;
}

int
closedlist_remove(aobj *astar, anode *node)
{
    if(!astar)
        return 0;
    if(!node)
        return 0;
    astar->cache[node->x][node->y].inclosed = 0;
    FREE(astar->cache[node->x][node->y].pointer);

    astar->closed_empty--;

    return 1;
 }

anode *
closedlist_search(aobj *astar, anode *node)
{

    if(!astar)
        return NULL;
    if(!node)
        return NULL;

    if(astar->cache[node->x][node->y].inclosed)
        return astar->cache[node->x][node->y].pointer;
    return NULL;

}

void     
closedlist_free(aobj *astar) 
{
    int x, y;
    if(!(astar->cache))
        return;
    for(x=0; x<x_tildes; x++)
    {
        for(y=0; y<y_tildes; y++)
        {
            if(astar->cache[x][y].inclosed)
            {
               FREE(astar->cache[x][y].pointer); 
            }
            
        }
    }
    return;
}

void
closedlist_print(aobj *astar)
{
    int x, y;
    if(!(astar->cache))
        return;
    for(x=0; x<x_tildes; x++)
    {
        for(y=0; y<y_tildes; y++)
        {
            if(astar->cache[x][y].inclosed)
            {
                printf("x: %d y: %d f: %d\n", \
                        astar->cache[x][y].pointer->x, \
                        astar->cache[x][y].pointer->y, \
                        astar->cache[x][y].pointer->f);

            }
        }
    }
    return;
}

int 
closedlist_isempty(aobj *astar)
{
    if(astar->closed_empty)
        return 0;
    return 1;
}

