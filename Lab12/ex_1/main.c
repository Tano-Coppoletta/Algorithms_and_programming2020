//
// Created by tanoc on 21/01/2020.
//
#include "Graph.h"
#define max 30

int main(){
    Graph G,DAG;
    FILE *fp;
    Edge e;
    char nome[max];
    e.v=-1;e.w=-1;e.wt=-1;

    printf("inserire nome file\n");
    scanf("%s",nome);
    fp=fopen(nome,"r");
    if(fp==NULL)
        return -1;
    G=Graphload(fp);
    fclose(fp);
    if(CHECKcicli(G,&e,0)==0){
        printf("il grafo e' un DAG\n");
        DAGmax(G);
        Graphfree(G);
    }else{
        DAG=GraphtoDAG(G);
        printf("grafo:\n");
        Graphprint(G);
        printf("DAG:\n");
        Graphprint(DAG);
        DAGmax(DAG);
        Graphfree(G);
        Graphfree(DAG);
    }
}
