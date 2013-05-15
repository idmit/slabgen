//
//  labyrinth.h
//  Graph
//
//  Created by ivan on 07.05.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#ifndef Graph_labyrinth_c
#define Graph_labyrinth_c

// Pair of vertices
typedef struct Pair
{
    int f; // first vertice
    int s; // second vertice
} Pair;

typedef Pair * Edge;

// Graph is an array of edges (pairs)
typedef struct Graph
{
    int N; // side of the square
    int edgesNum; // number of edges
    Pair **edges; // array of pointers
} Graph;

Graph *InitLab(int N); // inits square labyrynth NxN cells
void ReleaseGraph(Graph *graph); // releases <graph>
void ShuffleEdges(Edge *edges, int edgesNum); // shuffles an <edges> array (<edgesNum> is its length)

void SetOutStream(FILE *stream); // sets out stream for PrintLab function
int SortToPrint(Graph *graph); // sorts edges in a <graph> for PrintLab correct work
void PrintLab(Graph *graph); // prints <graph> to <outStream> (stdout by default)

int Acyclic(Graph *graph); // checks if <graph> is acyclic
Graph *Kruskal(Graph *graph); // builds spanning tree of <graph>

#endif
