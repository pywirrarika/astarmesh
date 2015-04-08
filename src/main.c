/*
 * main.c
 *
 * Description: Source file containing the main function. 
 *
 * Author: Manuel Mager <fongog@gmail.com> (C) 2013
 * Copyright: GPL v3 or later
 *
 */

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "base.h"
#include "data.h"
#include "graphs.h"
#include "astar.h"

void 
init_error(void)
{
    printf("El programa astar es una aplicación del algoritmo de búsqueda de mejor camino, utilizando A*. ");
    printf("Para utilizar correctamente esta aplicación introduzca:");
    printf("\n\n\tastar X Y X2 Y2 imagen.bmp salida.bmp DEBUG\n\n");
    printf("Donde X y Y son las coordenadas de punto de partida, y ");
    printf("X2 y Y2 es la coordenada de destino. imagen.bmp es el mapa");
    printf(" sobre el cual se trabajará. Tiene que ser BMP, sin compresión, de preferencia de 24bits. \n");
}


int main (int argc, char **argv)
{

    apoint      source, goal;
    aobj        *astar;
    int         i, x, y;
    char        *output = "astar.bmp";
    
    if (argc != 8)
    {
        init_error();
        return 0;
    }
    
    source.x = atoi(argv[1]);
    source.y = atoi(argv[2]);

    goal.x = atoi(argv[3]);
    goal.y = atoi(argv[4]);

    debug = atoi(argv[7]);
    
    astar = malloc(sizeof(aobj));
    if(astar == NULL)
        return 0;
    astar->path.size = 0;
    astar->path.path = NULL;
    astar->output = malloc(20*sizeof(char));
    sprintf(astar->output, "%s", argv[6]);
    //printf("Archivo de salida: %s\n", argv[6]);

    if(!read_map(argv[5]))
    {
        printf("Error al cargar %s. Debe ser una imagen ", argv[5]);
        printf("BMP sin compresión de 24 bits.\n");
        return 0;
    }
    //maps_init(map1);

    astar->cache = malloc(x_tildes *  sizeof(anode *));
    if(!(astar->cache))
        return 0;
    for(i=0; i < x_tildes; i++)
    {
        astar->cache[i] = malloc(y_tildes * sizeof(anode));
        if(!(astar->cache[i]))
            return 0;
    }
    for(x=0; x<x_tildes; x++)
        for(y=0; y<y_tildes; y++)
            astar->cache[x][y].pointer = NULL;

    astar->open_empty = 0;
    astar->closed_empty = 0;

    if(!ai_shortes_path(astar, 0, source, goal))
    {
        printf("We couldn't find any path to the goal!\n");
    }

    if( astar->path.size == 0)
    {
        printf("Error: Couldnt find a path!\n");
        clean_gmaps();
        return 0;
    }

    data_store(astar);
    
    ai_free_aobj(astar);
    clean_gmaps();

    return 0;
}
