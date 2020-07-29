//
// Created by tanoc on 13/01/2020.
//

#ifndef PROGETTO_GRAPH_H
#define PROGETTO_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

typedef struct graph *Graph;

typedef struct{
    int v;
    int w;
    int wt;
}Edge;

Graph Graphinit(int V);
Graph Graphload(Graph G,FILE *fp);
void GraphinsertEM(Graph G,int v,int w,int wt);
int numeroArchi(FILE *fp);
void Graphprint(Graph G);
void adiacenzaM(Graph G);
void GRAPHfree(Graph G);
void GRAPHlist(Graph G);
void adiacenzaList(Graph G);

#endif //PROGETTO_GRAPH_H
