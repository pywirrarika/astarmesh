/* bheap.c
 *
 * Description: Skip list implementarion.
 * 
 * Author: Jesús Manuel Mager Hois (fongog@gmail.com) 2013
 * Copyright: GPL v3 or later
 *
 */




#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "queue.h"

#define MAX_LEVEL   3
#define MAX_PROB    3

typedef struct anode{
    char id[21];
    int index;
    int deph;
    int g, h, f;
    int count;
    int x,y;
    TAILQ_ENTRY(anode) level1; 
    TAILQ_ENTRY(anode) level2;
    TAILQ_ENTRY(anode) level3;
}anode;

typedef struct skipinit{
    anode **level[2];
}skipinit;

TAILQ_HEAD(open_list, anode) openlist;
anode *skipindex[MAX_LEVEL];

int random_func(int);
int skip_init(void);
int skip_insert(anode *);
void skip_print(void);

// Debug function
void
print_indextable(void)
{
    if(!TAILQ_EMPTY(&openlist))
    {
        printf(" First list element:%d\n", 
                TAILQ_FIRST(&openlist)->f);
        printf(" Last list element:%d\n", 
                TAILQ_LAST(&openlist, open_list)->f);
        printf("   Index 3-> %d\n", skipindex[2]->f);
        printf("   Index 2-> %d\n", skipindex[1]->f);
        printf("   Index 1-> %d\n", skipindex[0]->f);
    }
};


/*
 * Function name: random_func(int max)
 * Description:
 *      Returns a random value, not grather than the max argument. 
 */
int 
random_func(int max) 
{
    return ((rand()%max));
}

/*
 * Function name: skip_init(anode *node)
 * Description:
 *      This functions provides the initial values in for the skiplist and the
 *      initial values in the start array. 
 */

int 
skip_init(void)
{
    int i;

    TAILQ_INIT(&openlist);
    for(i=0; i<MAX_LEVEL; i++)
    {
        skipindex[i] = NULL;
    }

    return 1;
}

/*
 * Function name: skip_insert(anode *node)
 * Description:
 *      This function inserts a node that was previusly allocated in memory 
 *      into the skiplist, itering the entire list to insert it under a min()
 *      criteria.
 * Return values:
 *   0: An error ocurred during the insertion.
 *   1: The node was inserted
 */

int 
skip_insert(anode *node)
{
    int     i,
            level = 0,
            daze,
            first_element = 1;
    anode   *item,
            *next,
            *level3 = NULL,
            *level2 = NULL;
    anode   **prev   = NULL;
    
    level = -1;

    printf("---- Inizalizing the insertion of %d\n", node->f);

    // We use a random mothod to determine if the level of the new node
    do
    {
        daze = random_func(MAX_PROB);
        level++;
        printf("Random number: %d. The actual level is: %d\n", daze, level);
    } while((daze == MAX_PROB-1));
    puts("Selecting level fo node finished!");
    
    if (skipindex[0] == NULL)
    {
        // If the list is empy then we enter to this section.
        
        puts("**** This list is empty!");
        TAILQ_INSERT_HEAD(&openlist, node, level1);
        for(i=0; i<MAX_LEVEL; i++)  
            skipindex[i] = node;

        node->level3.tqe_next = NULL;
        node->level2.tqe_next = NULL;
        node->level3.tqe_prev = NULL;
        node->level2.tqe_prev = NULL;
      
        return 1;
    }
    else
    {

        // The list is not empty!

        puts("The list is't empty!");
        print_indextable();
        item = skipindex[MAX_LEVEL-1];

        for (i=(MAX_LEVEL-1); i>=0; i--)
        {
            while (item != NULL)
            {
                printf("Searching in level %d\n", i);
                if (item->f == node->f && i != 0)
                {
                    printf("%d = %d\n", item->f, node->f);
                    break;
                }
                
                // We insert the new node in front of the closest greater
                // element in the list.
                if (item->f > node->f)
                {
                    if (i == 0) 
                    {
                        puts("Level 0");
                        puts(" + **** Addning node.");
                
                // We insert the new node in front of the first reference node
                // of the list defined in skipidex. 

                        if (TAILQ_FIRST(&openlist)->f > node->f)
                        {
                            TAILQ_INSERT_HEAD(&openlist, node, level1);
                            skipindex[0] = node;
                            print_indextable();
                            printf("The level of the node we are adding is: %d\n",\
                                    level);
                            if(level >= 2)
                            {
                                puts("Confirmed: node has level 3");
                                node->level3.tqe_next = level3;
                                node->level3.tqe_prev = NULL;
                                level3->level3.tqe_prev = &node;
                                skipindex[2] = node;
                            }
                            if(level >= 1)
                            {
                                puts("Confirmed: node has level 2");
                                printf("nivel2 era %d\n", level2->f);
                                node->level2.tqe_next = level2;
                                node->level2.tqe_prev = NULL;
                                printf(" In the node %d, the prev node value is: %d\n",\
                                    level2->f,
                                    node->f);               
                                level2->level2.tqe_prev = &node;

                                printf(" In the node %d, the prev node value is: %d\n",\
                                        level2->f,
                                        node->f);

                                print_indextable();

                                skipindex[1] = node;

                            }


                            print_indextable();
                            return 1;
                        }
                        else
                        {
                            item = TAILQ_PREV(item, open_list, level1);
                            continue;
                        }
                    }
                    else
                    {
                        if (i == 2)
                        {
                            printf("Going down one livel!\n");
                            level3 = item;

                            break;
                        }
                        if (i == 1)
                        {
                            printf("Searching for a smaller node%d!\n",
                                    item->f);
                            prev = item->level2.tqe_prev; 
                            printf("Analizing...\n");
                            if (prev == NULL)
                            {
                                puts("Saving the actual position to nivel2");
                                level2 = item;
                                break;
                            }
                            else
                            {
                                printf("Going back one node in level 2!\n");
                                item = *(prev);
                                printf("The new searched node value is: %d!\n",
                                        item->f);
                                continue;
                            }                            
                        }
                        break;
                    }
                }

                if(item->f <= node->f)
                {
                    printf("The seach node %d is smaller than ", \
                            item->f);
                    printf("the new node %d\n",  node->f);
                    if(i == 2)
                    {
                        puts("Estamos en el nivel 2");
                        next = TAILQ_NEXT(item, level3);
                        if(next == NULL){
                            printf("El elemento siguiente del nivel 1 en ");
                            printf("%d está vacio.\n", item->f);
                            level3 = item;
                            break;
                        }
                        if(next->f > node->f){
                            printf("El siguiento nodo %d es mayor que %d\n",\
                                    next->f,
                                    node->f);
                            printf("Bajamos de nivel!\n");
                            level3 = item;
                            break;
                        }
                        else if(next->f <= node->f)
                        {
                            item = next;
                            printf("Continuar el siguiente en el nivel 2\n");
                            first_element = 0;
                            continue;
                        }
                    }
                    if (i == 1) 
                    {
                        puts("Estamos en el nivel 1");
                        next = TAILQ_NEXT(item, level2);
                        if (next == NULL){
                            printf("El elemento siguiente del nivel 1 en ");
                            printf("%d está vacio.\n", item->f);
                            level2 = item;
                            break;
                        }
                        if (next->f > node->f){
                            level2 = item;
                            printf("El siguiento nodo %d es menor que %d\n",\
                                    next->f,
                                    node->f);
                            printf("Bajamos de nivel!\n");
                            break;
                        }
                        else if (next->f <= node->f)
                        {
                            item = next;
                            printf("Continuar el siguiente en el nivel 2\n");
                            first_element = 0;
                            continue;
                        }
                    }
                    if(i == 0) 
                    {
                        puts(" + Estamos en el nivel 0");
                        next = TAILQ_NEXT(item, level1);
                        if(next == NULL)
                        {
                            printf(" + ****Incertado %d al final de la lista\n",
                                    node->f);
                            TAILQ_INSERT_TAIL(&openlist, node, level1);
                            if(level>=1)
                            {
                                if((node->level2.tqe_next = \
                                            level2->level2.tqe_next) != NULL)
                                    node->level2.tqe_next->level2.tqe_prev =\
                                        &node->level2.tqe_next;
                                else
                                    openlist.tqh_last = &node->level2.tqe_next;
                                item->level2.tqe_next = node;
                                node->level2.tqe_prev = &item->level2.tqe_next;
                                if(skipindex[1] == NULL)
                                    skipindex[1] = node;
                            }
                            if(level>=2)
                            {
                                if((node->level3.tqe_next = \
                                            level3->level3.tqe_next) != NULL)
                                    node->level3.tqe_next->level3.tqe_prev =\
                                        &node->level3.tqe_next;
                                else
                                    openlist.tqh_last = &node->level3.tqe_next;
                                item->level3.tqe_next = node;
                                node->level3.tqe_prev = &item->level3.tqe_next;
                                if(skipindex[2] == NULL)
                                    skipindex[2] = node;
                            }
                            return 1;
                        }
                        if(next->f > node->f)
                        {
                            printf(" + **** Incertando %d adelante de %d\n", \
                                    node->f, next->f);
                            TAILQ_INSERT_BEFORE(next, node, level1);
                            printf("Exito!\n");
                            if(level>=1)
                            {
                                printf("El f anterior n3:%d, n2:%d\n",\
                                        level3->f, level2->f);
                                puts("Arreglando para nivel 2");
                                if((node->level2.tqe_next = \
                                            level2->level2.tqe_next) != NULL){
                                    printf("Siguiente nodo es NULL\n");
                                    node->level2.tqe_next->level2.tqe_prev =\
                                        &node->level2.tqe_next;
                                }
                                else
                                {
                                    printf("Siguiente nodo es %d",\
                                            node->level2.tqe_next->f);
                                    openlist.tqh_last = &node->level2.tqe_next;
                                }
                                item->level2.tqe_next = node;
                                node->level2.tqe_prev = &item->level2.tqe_next;
                                if(skipindex[1] == NULL)
                                    skipindex[1] = node;
                                printf("Listo acomodado nivel 2");
                            }
                            if(level>=2)
                            {
                                if ((node->level3.tqe_next = \
                                            level3->level3.tqe_next) != NULL)
                                    node->level3.tqe_next->level3.tqe_prev =\
                                        &node->level3.tqe_next;
                                else
                                    openlist.tqh_last = &node->level3.tqe_next;
                                item->level3.tqe_next = node;
                                node->level3.tqe_prev = &item->level3.tqe_next;
                                if (skipindex[2] == NULL)
                                    skipindex[2] = node;
                                printf("Listo acomodado nivel 2");
                            }
                            return 1;
                        }

                     printf(" + Avanzamos al siguiente nodo para buscar %d\n",\
                        next->f);
                        item = next;
                    }
                }
            }
            printf("Si terminamos el ciclo %d\n", i);
        }
    }

    return 0;
}

void 
skip_print(void)
{
    anode *item;
    int i = 0;
    TAILQ_FOREACH(item, &openlist, level1)
    {
        printf("%d: Nodo f=%d\n", i, item->f);
        i++;
    }
}

void 
skip_free(void)
{
    anode *item;
    TAILQ_FOREACH(item, &openlist, level1)
    {
        free(item);
        item = NULL;
    }
}

int 
main()
{
    anode   *item;
    int     i;
    printf("*****************************************************\n");
    printf("                Iniciando Skiplist \n");
    printf("*****************************************************\n");
    skip_init();

    for(i=0; i<100; i++)
    {
        print_indextable();
        item = malloc(sizeof(anode));
        item->f = random_func(100);
        item->x = 5;
        item->y = 10;
        skip_insert(item);
        skip_print();
        print_indextable();
    } 
    return 0;
}


