/*
 * openlist.h 
 *
 * Description: The open list is stored in a hashtable and in a proprity 
 *              queue that use a skiplist to do its job. 
 *
 * Author: Manuel Mager <fongog@gmail.com> (C) 2014
 * Copyright: GPL v3 or later
 *
 * The list:    This is a interface to the skiplist implementarion
 *              written by Theo Schlossnagle, commplemented with a
 *              hashtable, that was written by Robbert Haarman, and 
 *              has the next rules:
 *
 *              + The skip list is ordered by the F variable and in 
 *                a desdentant way. The top of it is MIN(f) and is the 
 *                used function by POP().
 *              + We can also make a search of (x,y) values using 
 *                the hastable to avoid O(n).
 *              + We can also remove elementes, those elements will
 *                be removed in the hastable and in the skiplist
 *              + For the addition operation we have the same 
 *                beavor.
 *              + All elementes are anode pointers defined in 
 *                base.h
 */

#ifndef OPENLIST_H
#define OPENLIST_H

#include "base.h"
#include "graphs.h"

int     openlist_init(aobj *); 
int     openlist_insert(aobj *, anode *); 
int     openlist_remove(aobj *, anode *); 
anode   *openlist_search(aobj *, anode *); 
int     openlist_remove_node(aobj *, anode *); 
anode   *openlist_getmin(aobj *);
void    openlist_free(aobj *);
void    openlist_print(aobj *); 
int     openlist_isempty(aobj *);
int     openlist_rm(aobj *astar, anode *node);
#endif
