//
// Created by tanoc on 13/01/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef enum{c_stampa,c_adiacenzam,c_adiacenzal,c_lista,fine}comando_e;

comando_e leggicomando(char *cmd);

int main(int argc,char *argv[]){
    Graph G;
    FILE *fp;
    comando_e cmd;
    int continua=1,lista=0;
    char comando[max],v1[max],v2[max],v3[max];

    if(argc!=2)
        exit(1);
    fp=fopen(argv[1],"r");
    if(fp==NULL)
        printf("errore file\n");
    int V=numeroArchi(fp);
    G=Graphinit(V);
    fclose(fp);
    fp=fopen(argv[1],"r");
    G=Graphload(G,fp);
    fclose(fp);
    while(continua){
        printf("inserire comando tra: stampa, adiacenzaM, adiacenzaL, lista, fine\n");
        scanf("%s",comando);
        cmd=leggicomando(comando);
        switch(cmd){
            case c_stampa:
                Graphprint(G);
                break;
            case c_adiacenzam:
                adiacenzaM(G);
                break;
            case c_adiacenzal:
                if(lista){
                    adiacenzaList(G);
                }else{
                    printf("lista ancora non generata\n");
                }
                break;
            case c_lista:
                GRAPHlist(G);
                lista=1;
                break;
            case fine:
                continua=0;
            default:
                printf("comando errato\n");
        }
    }
    GRAPHfree(G);
}


comando_e leggicomando(char *cmd){
    char *scelte[fine+1]={"stampa","adiacenzaM","adiacenzaL","lista","fine"};
    comando_e c=c_stampa;
    while(c<=fine && strcmp(scelte[c],cmd)!=0)
        c++;
    return c;
}
