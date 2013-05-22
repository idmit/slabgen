//
//  disjointset.h
//  Graph
//
//  Created by ivan on 22.05.13.
//  Copyright (c) 2013 dmitrievsky. All rights reserved.
//

#ifndef Graph_disjointset_c
#define Graph_disjointset_c

void MakeSet(int *p, int x);
int Find(int *p, int x);
void Unite(int *p, int x, int y);

#endif
