/*
 * astar.h 
 *
 * Description: Header of Astar algorithm. 
 *
 * Author: Manuel Mager <fongog@gmail.com> (C) 2013
 * Copyright: GPL v3 or later
 *
 */

#ifndef ASTAR_H
#define ASTAR_H

#include "base.h"
#include "skiplist.h"


int     ai_shortes_path(aobj *, int, apoint, apoint);
void    ai_free_aobj(aobj *);

#endif

