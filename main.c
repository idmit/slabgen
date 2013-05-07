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
    
    g = InitLab(3);
    if (!g)
    {
        printf("\nMemory error\n");
        return 1;
    }
    
    SetOutStream(stdout);
    
    PrintLab(g);
    
    return 0;
}

