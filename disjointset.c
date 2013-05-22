//
//  disjointset.c
//  Graph
//
//  Created by ivan on 22.05.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#include <stdlib.h>
#include "disjointset.h"

void MakeSet(int *p, int x)
{
    p[x] = x;
}

int Find(int *p, int x)
{
    return x == p[x] ? x : (p[x] = Find(p, p[x]));
}

void Unite(int *p, int x, int y)
{
    x = Find(p, x);
    y = Find(p, y);
    
    if (rand() % 2)
    {
        y = (x + y) - (x = y);
    }
    p[x] = y;
}