//
//  main.c
//  Graph
//
//  Created by ivan on 07.05.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include <stdio.h>
#include "labyrinth.h"

// В  квадрате  NxN  клеток  требуется  построить  случайный  лабиринт из
// вертикальных  и  горизонтальных  перегородок  между клетками. При этом
// любая  клетка  должна  быть  достижима из любой другой, но общее число
// перегородок должно быть максимальным.

int main(int argc, const char * argv[])
{
    Graph *g = NULL;
    FILE *out = NULL;
    int _n = 0;
    
    //out = fopen("out.txt", "w");
    SetOutStream(stdout);
    
    scanf("%d", &_n);
    
    g = InitLab(_n);
    if (!g)
    {
        printf("\nMemory error\n");
        return 1;
    }
    
    Acyclic(g);
    PrintLab(g);
    
    //fclose(out);
    return 0;
}

