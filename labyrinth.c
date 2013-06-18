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
#include "disjointset.h"

static FILE *outStream = NULL;

Graph *InitLab(int N)
{
    Graph *graph = NULL;
    int edgesNum = 0, i = 0, j = 0, addedPairs = 0;
    
    if (N < 2) // N = 1 doesn't make sense
    {
        return NULL;
    }
    
    edgesNum = 2 * N * (N - 1);
    
    graph = malloc(sizeof(Graph));
    if (!graph) { return NULL; }
    
    graph->N = N;
    graph->edgesNum = edgesNum;
    
    graph->edges = malloc(edgesNum * sizeof(Edge));
    if (!graph->edges) { free(graph); return NULL; }
    
    
    for (i = 0; i < edgesNum; i++)
    {
        graph->edges[i] = malloc(sizeof(Pair));
        if (!graph->edges[i]) { goto mem; }
    }
    
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N - 1; j++)
        {
            graph->edges[i * (N - 1) + j]->f = i * N + j;
            graph->edges[i * (N - 1) + j]->s = i * N + j + 1;
        }
    }
    
    addedPairs = N * (N - 1);
    
    for (i = 0; i < N - 1; i++)
    {
        for (j = 0; j < N; j++)
        {
            graph->edges[addedPairs + i * N + j]->f = i * N + j;
            graph->edges[addedPairs + i * N + j]->s = (i + 1) * N + j;
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
    int edgesNum = 0, N = 0, i = 0, j = 0,
        vertical = 0; // first index of horizontal edges
    
    if (!graph)
    {
        fprintf(outStream, "Empty graph");
        return;
    }
    
    edgesNum = graph->edgesNum;
    N = graph->N;
    
    vertical =  N * (N - 1);
    
    if (!outStream)
    {
        outStream = stdout;
    }
    
    fprintf(outStream, "\n");
    for (i = 0; i < N; i++)
    {
        fprintf(outStream, " _"); // upper bound of square
    }
    fprintf(outStream, " ");
    fprintf(outStream, "\n");
    
    i = j = 0;
    while (j < vertical)
    {
        if (i % N == 0)
        {
            fprintf(outStream, "|"); // first vertical edge in each row (part of left bound)
        }
        if (i < N * N - N)
        {
            fprintf(outStream, graph->edges[vertical + i] ? " " : "_");
        }
        else
        {
            fprintf(outStream, "_"); // printing bottom bound
        }
        
        if (i % N != N - 1)
        {
            fprintf(outStream, graph->edges[j] ? " " : "|");
        }
        if (i % N == N - 1)
        {
            fprintf(outStream, "|\n"); // last in a row (part of right bound)
            j--;
        }
        i++;
        j++;
    }
    fprintf(outStream, "_|\n\n"); // right bottom corner
}

void ShuffleEdges(Edge *edges, int edgesNum)
{
    int i;
    
    for (i = 0; i < edgesNum - 1; i++)
    {
        int j = i + rand() / (RAND_MAX / (edgesNum - i) + 1);
        Edge tmp = edges[j];
        edges[j] = edges[i];
        edges[i] = tmp;
    }
}

int SortToPrint(Graph *graph)
{
    int i = 0, f = 0, s = 0, a = 0, b = 0, N = 0, addedPairs = 0, edgesNum = 0;
    Edge *sorted = NULL, *edges = NULL;
    
    N = graph->N;
    
    edgesNum = 2 * N * (N - 1); // we are soring all, even if there are two edges, they can be from anywhere
    edges = graph->edges;
    addedPairs = N * (N - 1);
    
    sorted = malloc(edgesNum * sizeof(Edge));
    if (!sorted) { return 0; }
    
    for (i = 0; i < edgesNum; i++)
    {
        sorted[i] = NULL;
    }
    
    for (i = 0; i < edgesNum; i++)
    {
        if (!edges[i]) // all NULLs go to the end
        {
            continue;
        }
        
        f = edges[i]->f;
        s = edges[i]->s;
        
        a = f / N; b = f % N; // smth reverse to InitLab function
        
        if (f + 1 == s) // it's vertical edge
        {
            sorted[a * (N - 1) + b] = edges[i]; // goes to beginning
        }
        else
        {
            sorted[addedPairs + a * N + b] = edges[i]; // goes after the middle
        }
    }
    
    free(edges);
    graph->edges = sorted;
    
    return 1;
}

Graph *Kruskal(Graph *g)
{
    Graph *spt = NULL;
    int k = 0, edgesNum = 0, i = 0, verticesNum = 0, *djs = NULL, addedEdges = 0;
    
    spt = malloc(sizeof(Graph));
    if (!spt) { return NULL; }
    
    spt->N = g->N;
    spt->edgesNum = 0; // empty
    edgesNum = g->edgesNum;
    
    spt->edges = malloc(edgesNum * sizeof(Edge));
    if (!spt->edges) { free(spt); return NULL; }
    
    for (i = 0; i < edgesNum; i++)
    {
        spt->edges[i] = NULL; // for correct behaviour
    }
    
    verticesNum = g->N * g->N;
    
    djs = malloc(verticesNum * sizeof(int));
    for (i = 0; i < verticesNum; i++)
    {
        MakeSet(djs, i);
    }
    
    while (addedEdges < verticesNum - 1)
    {
        while (Find(djs, g->edges[k]->f) != Find(djs, g->edges[k]->s))
        {
            Unite(djs, g->edges[k]->f, g->edges[k]->s);
            spt->edges[k] = g->edges[k];
            k++;
            addedEdges++;
        }
        k++;
    }
    
    free(djs);
    return spt;
}

void ReleaseGraph(Graph *graph)
{
    int edgesNum = 0, i = 0;
    
    if (!graph)
    {
        return;
    }
    if (!graph->edges)
    {
        free(graph);
    }
    
    edgesNum = graph->edgesNum;
    
    for (i = 0; i < edgesNum; i++)
    {
        if (graph->edges[i])
        {
            free(graph->edges[i]);
        }
    }
    
    free(graph->edges);
    free(graph);
}

