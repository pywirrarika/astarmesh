/*
 * astar.c
 *
 * Description: The A* algorithm implementation. 
 *
 * Author: Manuel Mager <fongog@gmail.com> (C) 2013
 * Copyright: GPL v3 or later
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

#include "base.h"
#include "graphs.h"
#include "astar.h"

#include "openlist.h"
#include "closedlist.h"

// Defining local macros

// Absolute value of a diference of two numbers
#define ABSD(a, b) (a<b) ? (b-a) : (b-a)

// Hueristic distance between to points

// Manahttan distance
#define HDIST(x1, y1, x2, y2) (((x1<x2)?(x2-x1):(x1-x2) + \
            ((y1<y2)?(y2-y1):(y1-y2)))*10)

// Chebyshev distance 
#define HDISTC(x1, y1, x2, y2) 10*(abs(x2-x1) + abs(y2-y1))+\
    (13-2*10)+(abs(x2-x1)<abs(y2-y1))?(abs(x2-x1))*10:(abs(y2-y1))*10 

// Euclidean distance
#define HDISTE(x1, y1, x2, y2) (int)(sqrt(((x2-x1) * (x2-x1)) + \
            ((y2-y1) * (y2-y1)))*10) 

// No Hueristic function
#define HDISTN(x1, y1, x2, y2) 10



#define G 10

// Local Function definitions
void    ai_free_path(apath path);
int     hdist(int p1x, int p1y, int p2x, int p2y);
int     ai_valid_tile(int unit, apoint coords);


// Local function implementations

// Modified Chebyshev distance to get a precise distance 
// for NW, NE, SW and SE direccions. 
int hdist(int p1x, int p1y, int p2x, int p2y)
{
    int xDistance = abs(p1x-p2x);
    int yDistance = abs(p1y-p2y);
    
    if (xDistance > yDistance)
    {
        return 14*yDistance + 10*(xDistance-yDistance);
    }
    else
    {
        return 14*xDistance + 10*(yDistance-xDistance);
    }
}

// Returns 1 if the tile is valid to use for a player, and unit
// and 0 if not.
int ai_valid_tile(int unit, apoint coords)
{

    if(coords.x < 0 || coords.x >= x_tildes)
        return 0;
    if(coords.y < 0 || coords.y >= y_tildes)
        return 0;
   
    //unit_p = list_search(list_nodes, unit);
    
    if(gmaps[coords.x][coords.y].terrain == WALL)
    {
        return 0;
    }
    
     
    return 1; 
}

// This is the main A* algorithm function. Unit parameter is not
// jet implemented, so it should be 0. TODO
int ai_shortes_path(aobj *astar, int unit, apoint source, apoint goal)
{
    int                 i, a;
    int                 closed_flag, open_flag;

    avector             vector;
    apoint              pt;
    apoint              **solution;
    anode               *item;
    anode               *next;
    anode               *old;
    anode               *tmp_item;
  
    //printf("Initializing the A* algorithm!\n");
    printf("Our source point is: %d, %d \n", source.x, source.y);
    printf("Our goal point is: %d, %d\n", goal.x, goal.y);


    // Are the source and goal point valid?
    if(!ai_valid_tile(unit, source))
    {
        fprintf(stderr, "Invalid source point! %d \n", ai_valid_tile(unit, \
                    source));
        return 0;    
    }
    if(!ai_valid_tile(unit, goal))
    {
        fprintf(stderr, "Invalid goal point! %d \n", ai_valid_tile(unit, goal));
        return 0;    
    }
        
    i = 0;

    // Creating open and closed lists
    if (!openlist_init(astar))
    {
        fprintf(stderr, "Error initializing the open list\n");
        return 0;
    }
    if(!closedlist_init(astar))
    {
        fprintf(stderr, "Error initializing the closed list\n");
        return 0;
    }


    // Defining the initial node 
    printf("================= A* ==================\n");
    
    item = malloc(sizeof(anode));
    if(item == NULL)
    {
        return 0; 
    }  
    item->deph = 0;
    item->point = source;
    item->x = source.x;
    item->y = source.y;
    item->h = hdist(item->x, item->y, goal.x, goal.y);
    item->g = 0;
    item->f = item->g + item->h;
    item->parent = NULL;

    // Insert the initial node to the open list
    if(!openlist_insert(astar, item))
    {
        fprintf(stderr, "Coudn't add element to the open list!\n");
        return 0;
    }

    while(!openlist_isempty(astar))
    {
        ////////////////////////////////////////////
        // Remove the lowest element in open list
        // and add it to the closed list
        ////////////////////////////////////////////

        COMMENT
            printf("********** New Loop Cycle\n");
            puts("Open List:\n");
            openlist_print(astar);
            puts("Closed List:\n");
            closedlist_print(astar);
        COMMENTEND

        item = openlist_getmin(astar);
        if(item == NULL)
        {
            fprintf(stderr, "Error deleting the priority element from open list!\n");
            return 0;
        }
        if(!closedlist_insert(astar, item))
        {
            fprintf(stderr, "Error adding to hashtable!\n");
            return 0;
        }


        /////////////////////////////////////////////
        // Is this element the goal?
        /////////////////////////////////////////////

        if(item->x == goal.x && item->y == goal.y)
        {
            //printf("Solution deph is %d\n", item->deph);
            solution = malloc(item->deph * sizeof(apoint *));

            if(!solution)
            {
                astar->item = NULL;
                return 0;
            }

            i=0;

            while(item->parent)
            {
                //printf("(%d,%d)\n",item->point.x, item->point.y);
                solution[i] = &(item->point);
                item = item->parent;
                i++;
            } 
            
            
            astar->path.size = i - 1;
            astar->path.path = solution;
            astar->item = item;

            // Time routines for gather the needed data for 
            // our analysis.

            return 1;
        }

        COMMENT
            printf("This element is not the goal!.. Trying...\n");
        COMMENTEND
        
        ///////////////////////////////////////////////////////////
        // For each valid move for n, also known as the neigbhors 
        // of the current node.
        // ///////////////////////////////////////////////////////

        for(a = 0; a < NUM_DIRS; a++)
        {
            vector = get_vector(item->point, a);
            if(vector.x != -2 && vector.y != -2)
            {
                COMMENT
                    printf("For %d direction tile in (%d,%d) is valid?\n", \
                            a, item->point.x, item->point.y);
                    printf("Vector is valid...\n");
                COMMENTEND

                pt.x = vector.x + item->point.x;
                pt.y = vector.y + item->point.y;
                if(ai_valid_tile(unit, pt))
                {
                    //New valid element
                    next = malloc(sizeof(anode));
                    next->deph = item->deph + 1;
                    next->point = pt;
                    next->h = hdist(next->point.x, next->point.y, goal.x, \
                            goal.y);
                    next->x = next->point.x;
                    next->y = next->point.y;
                    if( a == ISO_N || 
                        a == ISO_S ||
                        a == ISO_W ||
                        a == ISO_E)
                        next->g = item->g + G; 
                    else
                        next->g = item->g + G+4;
                    next->f = next->g + next->h; // F = G + H
                    next->parent = item;

                    COMMENT
                        printf("Adding direction %d to open list!\n", a);
                        printf("Actual H: %d G:%d F:%d Deph:%d\n", \
                               next->h, next->g, next->f, \
                               next->deph);
                    COMMENTEND

                    open_flag = 0;
                    closed_flag = 0;
                    ///////////////////////////////////////////////
                    // Is this element in closed list?
                    // If the neigbhor is in closed list and 
                    // cost less than g(neigbhor) then remove neighbor
                    // from closed list.
                    //////////////////////////////////////////////
                    if((old = closedlist_search(astar, next)) != NULL)
                    {
                        COMMENT
                            puts("The element is in the closed list!\n");
                        COMMENTEND
                        if(next->f < old->f)
                        {
                            COMMENT
                                printf("Prior element from closed list is greater than the next value!\n");
                            COMMENTEND
                            
                            if(!closedlist_remove(astar, old))
                            {
                                printf("Error ocurred while trying to remove \
                                        key in hashtable!\n");
                                COMMENT
                                    closedlist_print(astar);
                                    openlist_print(astar);
                                COMMENTEND
                                astar->item = NULL;
                                return 0;
                            }
                            closed_flag = 0;
                            COMMENT
                                printf("Succesfully removed from closed list\n");
                            COMMENTEND
                        }
                        else
                        {
                            closed_flag = 1;
                        }
                    }
                    /////////////////////////////////////////////////
                    // Is this element in open list?
                    // If the neigbhor is in openlist and
                    // cost less than g(neighbor) then remove 
                    // neighbor from open list.
                    /////////////////////////////////////////////////
                    if((tmp_item = openlist_search(astar,next))!=NULL)
                    {
                        COMMENT
                            printf("Node exists in openlist!\n");
                                openlist_print(astar); 
                                closedlist_print(astar);
                        COMMENTEND
                        if(tmp_item->f > next->f && closed_flag == 0)
                        {
                            open_flag = 0;
                            if(!openlist_rm(astar, tmp_item))
                            {
                        COMMENT
                                printf("The node is in the open list, but we couldn't remove it\n");
                                printf("(%d,%d)\n", tmp_item->x, tmp_item->y);
                                openlist_print(astar); 
                                closedlist_print(astar);
                        COMMENTEND
                                return 0;
                            }

                            COMMENT
                                printf("The new path is better: removing and adding the new one!\n");
                                openlist_print(astar); 
                                closedlist_print(astar);
                            COMMENTEND
                        }
                        else
                        {
                            open_flag = 1;
                        }
                    }
                    ////////////////////////////////////////////////////////////
                    // If the element is not in the open list nor in the closed
                    // we can add the new node to the open list
                    //////////////////////////////////////////////////////////

                    if(open_flag == 0 && closed_flag == 0)
                    {
                        COMMENT
                            printf("Node doesn't exist in closed list or in open\
                                    list!\n");
                        COMMENTEND
                        if(!openlist_insert(astar, next))
                        {
                            printf("Error ocurred while adding a new element to \
                                    open list\n");
                            astar->item = NULL;
                            return 0;
                        }
                    }
                    else
                    {
                        if(next != NULL)
                        {
                            free(next);
                            next = NULL;
                        }
                    }
                }
            }
        }
    }
    astar->item = NULL;
    return 0;
}

void ai_free_path(apath path)
{
    if(path.size)
    {
        FREE(path.path);
    }
}

void ai_free_aobj(aobj *astar)
{
    int i;
    ai_free_path(astar->path);
    //printf("Path is FREE\n");
    //closedlist_print(astar);
    closedlist_free(astar);
    //printf("Closed list is FREE\n");
    //openlist_print(astar);
    openlist_free(astar);
    //printf("Open list is FREE\n");
    FREE(astar->output);
    for(i=0; i<x_tildes; i++)
        FREE(astar->cache[i]);
    FREE(astar->cache);

}
