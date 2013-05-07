//
//  labyrinth.h
//  Graph
//
//  Created by ivan on 07.05.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#ifndef Graph_labyrinth_c
#define Graph_labyrinth_c

typedef struct Pair
{
    int f;
    int s;
} Pair;

typedef struct Graph
{
    int _n;
    int n;
    Pair **edges;
} Graph;

Graph *InitLab(int _n);
void SetOutStream(FILE *stream);
void PrintLab(Graph *graph);

#endif
