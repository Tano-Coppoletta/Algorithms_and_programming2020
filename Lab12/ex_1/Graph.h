//
// Created by tanoc on 21/01/2020.
//

#ifndef PROGETTO_GRAPH_H
#define PROGETTO_GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct graph *Graph;

typedef struct{
    int v,w,wt;
}Edge;

Graph Graphinit(int V);
Graph Graphload(FILE *fp);
void GRAPHinsertE(Graph G,int v,int w,int wt);
int CHECKcicli(Graph G,Edge *escludi,int E);
void GraphEDGE(Graph G,Edge *e);
Graph GraphtoDAG(Graph G);
void Graphprint(Graph G);
void DAGmax(Graph D);
void Graphfree(Graph G);

#endif //PROGETTO_GRAPH_H
