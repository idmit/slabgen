//
//  labyrinth.c
//  Graph
//
//  Created by ivan on 07.05.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "labyrinth.h"

static FILE *outStream;

Graph *InitLab(int _n)
{
    Graph *graph = NULL;
    int n = 0, i = 0, j = 0, addedPairs = 0;
    
    n = 2 * _n * (_n - 1);
    
    graph = malloc(sizeof(Graph));
    if (!graph) { return NULL; }
    
    graph->_n = _n;
    graph->n = n;
    
    graph->edges = malloc(n * sizeof(Pair *));
    if (!graph->edges) { free(graph); return NULL; }
    
    
    for (i = 0; i < n; i++)
    {
        graph->edges[i] = malloc(sizeof(Pair));
        if (!graph->edges[i]) { goto mem; }
    }
    
    for (i = 0; i < _n; i++)
    {
        for (j = 0; j < _n - 1; j++)
        {
            graph->edges[i * (_n - 1) + j]->f = i * _n + j;
            graph->edges[i * (_n - 1) + j]->s = i * _n + j + 1;
        }
    }
    
    addedPairs = _n * (_n - 1);
    
    for (i = 0; i < _n - 1; i++)
    {
        for (j = 0; j < _n; j++)
        {
            graph->edges[addedPairs + i * _n + j]->f = i * _n + j;
            graph->edges[addedPairs + i * _n + j]->s = (i + 1) * _n + j;
        }
    }
    
    return graph;
    
    mem:
    for (j = 0; j < i + 1; j++)
    {
        free(graph->edges[j]);
    }
    free(graph->edges);
    free(graph);
    return NULL;
}

void SetOutStream(FILE *stream)
{
    outStream = stream;
}

void PrintLab(Graph *graph)
{
    int n = 0, _n = 0, i = 0, j = 0, vertical = 0;
    
    n = graph->n;
    _n = graph->_n;
    
    vertical =  _n * (_n - 1);
    
    for (i = 0; i < _n; i++)
    {
        printf(" _");
    }
    printf(" ");
    printf("\n");
    
    i = j = 0;
    while (j < vertical)
    {
        if (i % _n == 0)
        {
            printf("|");
        }
        if (i < _n * _n - _n)
        {
            printf(graph->edges[vertical + i] ? " " : "_");
        }
        else
            printf("_");
        
        if (i % _n != _n - 1)
        {
            printf(graph->edges[j] ? " " : "|");
        }
        if (i % _n == _n - 1)
        {
            printf("|\n");
            j--;
        }
        i++;
        j++;
    }
    printf("_|\n\n");
}

Graph *Kruskal()
{
    
}





