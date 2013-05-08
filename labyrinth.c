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
    
    if (!graph)
    {
        fprintf(outStream, "Empty graph");
        return;
    }
    
    n = graph->n;
    _n = graph->_n;
    
    vertical =  _n * (_n - 1);
    
    fprintf(outStream, "\n");
    for (i = 0; i < _n; i++)
    {
        fprintf(outStream, " _");
    }
    fprintf(outStream, " ");
    fprintf(outStream, "\n");
    
    i = j = 0;
    while (j < vertical)
    {
        if (i % _n == 0)
        {
            fprintf(outStream, "|");
        }
        if (i < _n * _n - _n)
        {
            fprintf(outStream, graph->edges[vertical + i] ? " " : "_");
        }
        else
            fprintf(outStream, "_");
        
        if (i % _n != _n - 1)
        {
            fprintf(outStream, graph->edges[j] ? " " : "|");
        }
        if (i % _n == _n - 1)
        {
            fprintf(outStream, "|\n");
            j--;
        }
        i++;
        j++;
    }
    fprintf(outStream, "_|\n\n");
}

void GetU(Graph *graph, int v, int *u, int from)
{
    int i = 0, _n = 0, curr = 0, vertical = 0;
    
    _n = graph->_n;
    vertical =  _n * (_n - 1);
    for (i = 0; i < 4; u[i] = -1, i++);
    
    if (v - _n >= 0)
        if (graph->edges[vertical + v - _n])
            if (v - _n != from)
                u[curr] = v - _n, curr++;
    if (v % _n != 0)
        if (graph->edges[v - (v / _n + 1)])
            if (v - 1 != from)
                u[curr] = v - 1, curr++;
    if (v % _n != _n - 1)
        if (graph->edges[v - (v / _n + 1) + 1])
            if (v + 1 != from)
                u[curr] = v + 1, curr++;
    if (v + _n < _n * _n)
        if (graph->edges[vertical + v])
            if (v + _n != from)
                u[curr] = v + _n, curr++;
}

int Len(int *u)
{
    int i = 0;;
    
    for (i = 0; i < 4; i++)
    {
        if (u[i] == -1)
            return i;
    }
    return 4;
}

int _dfs(Graph *graph, int *x, int v, int from)
{
    int i = 0, num = 0, u[4] = {0}, lenU = 0, to = 0;
    
    num = graph->_n * graph->_n;
    
    //printf("%d ", v);
    x[v] = 1;
    
    GetU(graph, v, u, from);
    lenU = Len(u);
    for (i = 0; i < lenU; i++)
    {
        to = u[i];
        if (x[to] == 0)
        {
            if (_dfs(graph, x, to, v))
                return 1;
        }
        else if (x[to] == 1)
        {
            return 1;
        }
    }
    
    x[v] = 2;
    return 0;
}

int Dfs(Graph *graph, int v)
{
    int num = 0, *x = NULL, i = 0;
    
    num = graph->_n * graph->_n;
    
    x = malloc(num * sizeof(int));
    if (!x)
    {
        return -1;
    }
    
    for (i = 0; i < num; x[i] = 0, i++);
    
    return _dfs(graph, x, v, v);
}

int Acyclic(Graph *graph)
{
    int i = 0, num = 0;
    
    num = graph->_n * graph->_n;
    
    for (i = 0; i < num; i++)
        if (Dfs(graph, i))
        {
            return 0;
        }
    
    return 1;
}

Graph *Kruskal(Graph *g)
{
    Graph *spt = NULL;
    int k = 0, n = 0, i = 0;
    
    spt = malloc(sizeof(Graph));
    if (!spt) { return NULL; }
    
    spt->_n = g->_n;
    spt->n = g->n;
    
    spt->edges = malloc(spt->n * sizeof(Pair *));
    if (!spt->edges) { free(spt); return NULL; }
    
    n = g->n;
    
    for (i = 0; i < n; i++)
    {
        while (!Acyclic((spt->edges[k] = g->edges[k], spt)))
        {
            spt->edges[k] = NULL;
            k++;
        }
        k++;
    }
    return spt;
}



