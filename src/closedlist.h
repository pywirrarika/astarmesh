/*
 * closedlist.h 
 *
 * Description: Hashtable interface to store the data in the closed list
 *              for the astar algorithm. 
 *
 * Author: Manuel Mager <fongog@gmail.com> (C) 2013
 * Copyright: GPL v3 or later
 *
 */

#ifndef CLOSEDLIST_H
#define CLOSEDLIST_H

#include "base.h"
#include "graphs.h"
#include "skiplist.h"

int     closedlist_init(aobj *); 
int     closedlist_insert(aobj *, anode *); 
int     closedlist_remove(aobj *, anode *); 
anode   *closedlist_search(aobj *, anode *); 
anode   *closedlist_getmin(aobj *);
void    closedlist_free(aobj *); 
void    closedlist_print(aobj *); 
int     closedlist_isempty(aobj *);

#endif
