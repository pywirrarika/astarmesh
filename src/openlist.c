/*
 * openlist.c 
 *
 * Description: This implements the functions of the open list, we
 *              use a hashtable and a skiplist. 
 *
 * Author: Manuel Mager <fongog@gmail.com> (C) 2014
 * Copyright: GPL v3 or later
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "openlist.h"
#include "base.h"
#include "graphs.h"
#include "skiplist.h"

int comparador1(void *, void *);
int comparador2(void *, void *);
int comparador3(void *, void *);
void *print_open_iter(char *key, void *value);

void *
print_open_iter(char *key, void *value)
{

    printf("%s: f=%d, x=%d, y=%d\n", \
            key,
            ((anode *)(value))->f, \
            ((anode *)(value))->x, \
            ((anode *)(value))->y  \
            );
    return NULL;
}

int 
comparador1(void *node1, void *node2)
{
    anode   *n1 = (anode *)node1;
    anode   *n2 = (anode *)node2;
    int     diff;

    diff = n1->f - n2->f;
    if (diff == 0)
    {
        if ((n1->x == n2->x) && (n1->y == n2->y))
        {
            COMMENT
                printf("Comp1: (%d,%d)) == (%d,%d)\n", n1->x, n1->y, n2->x, n2->y);
            COMMENTEND
            return 0; 
        }
        else
        {
            COMMENT
                printf("Comp1: (%d,%d)) != (%d,%d)\n", n1->x, n1->y, n2->x, n2->y);
            COMMENTEND
            return 1;
        }
    }
    else
    {
        return diff;
    }

};

int 
comparador2(void *node1, void *node2)
{
    anode   *n1 = (anode *)node1;
    anode   *n2 = (anode *)node2;


    if ((n1->x == n2->x) && (n1->y == n2->y))
    {
        COMMENT
            printf("Comp2: (%d,%d)) == (%d,%d)\n", n1->x, n1->y, n2->x, n2->y);
        COMMENTEND
        return 0; 
    }
    else
    {
        COMMENT
            printf("Comp2: (%d,%d)) != (%d,%d)\n", n1->x, n1->y, n2->x, n2->y);
        COMMENTEND
        return 1;
    }
};

void openlist_print(aobj *astar)
{
    struct skiplistnode *item;
    int i;

    printf("Printing skiplist!\n");

    item = astar->openlist->bottom;
    item = item->next;
    i = 0;
    while(item != NULL)
    {
        printf("Elemento nº %d: %d, (%d,%d))\n", i, ((anode *)(item->data))->f,
                ((anode *)(item->data))->x,
                ((anode *)(item->data))->y);
        i++;
        item = item->next;
    }
}

int openlist_isempty(aobj *astar)
{
    if(astar->openlist->bottom == NULL)
        return 1;
    else
        return 0;
}

int openlist_init(aobj *astar)
{
    int x, y;

    if(astar == NULL)
    {
        COMMENT
        printf("The astar pointer is NULL\n");
        COMMENTEND
        return 0;
    }
    if((astar->openlist = malloc(sizeof(Skiplist))) == NULL)
        return 0;
    
    //Initizalizing the skiplist.
    COMMENT
        printf("* Iniciando skiplist\n");
    COMMENTEND

    skiplist_init(astar->openlist);

    COMMENT
        printf("* Definiendo comparadores\n");
    COMMENTEND

    skiplist_set_compare(astar->openlist, comparador1, comparador2);

    //Initizalizing the array
    astar->open_empty = 0;
    for(x=0; x<x_tildes; x++)
    {
        for(y=0; y<y_tildes; y++)
        {
            astar->cache[x][y].inopen = 0;
            astar->cache[x][y].skip = NULL;
        }
    }
    return 1;
}

int openlist_insert(aobj *astar, anode *node)
{

    struct skiplistnode *skip;

    if(node == NULL)
        return 0;
    if(astar == NULL)
        return 0;
    COMMENT
        printf("Inserting: (%d,%d) f:%d\n", node->x, node->y, node->f);
    COMMENTEND

    skip = skiplist_insert(astar->openlist, node);
    if(!skip)
    {
        fprintf(stderr, "Error adding to open skiplist\n");
        return 0;
    }
    
    astar->cache[node->x][node->y].inopen= 1;
    astar->cache[node->x][node->y].pointer = node;
    astar->cache[node->x][node->y].skip = skip;
    astar->open_empty++;

    COMMENT
        printf("Succsesful: (%d,%d) f:%d\n", node->x, node->y, node->f);
    COMMENTEND
    return 1;
}

anode *
openlist_getmin(aobj *astar)
{
    anode *item;
    item = (anode *)skiplist_pop(astar->openlist, NULL);
    astar->cache[item->x][item->y].inopen = 0;
    astar->cache[item->x][item->y].pointer = NULL;
    astar->open_empty--;
    return item;
}
     
void 
openlist_free(aobj *astar)
{
    int x, y;

    if(astar == NULL)
    {
        COMMENT
        printf("The astar pointer is NULL\n");
        COMMENTEND
    }

    skiplist_remove_all(astar->openlist, NULL );
    for(x=0; x<x_tildes; x++)
    {
        for(y=0; y<y_tildes; y++)
        {
            if(astar->cache[x][y].inopen && astar->cache[x][y].pointer)
            {
                FREE(astar->cache[x][y].pointer);
            }
            astar->cache[x][y].inopen = 0;
            astar->cache[x][y].skip = NULL;
        }
    }

    COMMENT
        printf("Done with the Hashtable freeing\n");
    COMMENTEND

}

anode *
openlist_search(aobj *astar, anode *node)
{
    anode   *item;

    if(astar->cache[node->x][node->y].inopen)
    {
    COMMENT
        printf("Should be in open\n");
    COMMENTEND
        item = astar->cache[node->x][node->y].pointer;
        if(!item)
    COMMENT
            printf("Error: the pointer is null!\n");
    COMMENTEND

        return item;
    }
    else
    {
    COMMENT
        printf("Shouldn't be in open\n");
    COMMENTEND
        ;
    }
    return NULL;
}
    

int 
openlist_remove(aobj *astar, anode *node)
{
    anode   *item;

    if(skiplist_remove(astar->openlist, node, NULL))
    {
        astar->cache[node->x][node->y].inopen = 0;
        item = astar->cache[node->x][node->y].pointer;
        astar->cache[node->x][node->y].pointer = NULL;
        astar->cache[node->x][node->y].skip = NULL;
        astar->open_empty--;
        FREE(item);
        return 1;
    }
    COMMENT
        printf("Error removing element from open list\n");
    COMMENTEND
    return 0;
}

int 
openlist_rm(aobj *astar, anode *node)
{
    anode   *item;
    struct skiplistnode *bottom;
    
    bottom = astar->cache[node->x][node->y].skip;
    if(!bottom)
    {
    COMMENT
        printf("Node is not in Open List!\n");
    COMMENTEND
        return 0;
    }

    if(skiplisti_remove(astar->openlist, bottom, NULL))
    {
        astar->cache[node->x][node->y].inopen = 0;
        item = astar->cache[node->x][node->y].pointer;
        astar->cache[node->x][node->y].pointer = NULL;
        astar->cache[node->x][node->y].skip = NULL;
        astar->open_empty--;
        FREE(item);
    COMMENT
        printf("Sucessful.\n");
    COMMENTEND
        return 1;
    }
    COMMENT
        printf("Error removing element from open list\n");
    COMMENTEND
    return 0;
}

