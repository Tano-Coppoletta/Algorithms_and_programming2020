//
// Created by tanoc on 04/12/2019.
//
#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 50

tabInv carica_oggetti(tabInv inv){
    int i;
    char nome[max],tipo[max];
    inv=malloc(sizeof(*inv));

    FILE *fp=fopen("C:\\Users\\tanoc\\Desktop\\Algoritmi e programmazione\\progetto\\lab07\\inventario.txt","r");
    if(fp==NULL)
        printf("errore file oggetti\n");
    fscanf(fp,"%d",&inv->n_inv);
    inv->vettinv=(Inv_t*)malloc(inv->n_inv*sizeof(Inv_t));
    for(i=0;i<inv->n_inv;i++){
        fscanf(fp,"%s %s %d %d %d %d %d %d",nome,tipo,&inv->vettinv[i].stat_ogg.hp,&inv->vettinv[i].stat_ogg.mp,
               &inv->vettinv[i].stat_ogg.atk,&inv->vettinv[i].stat_ogg.def,&inv->vettinv[i].stat_ogg.mag,
               &inv->vettinv[i].stat_ogg.spr);
        inv->vettinv[i].nome=strdup(nome);
        inv->vettinv[i].tipo=strdup(tipo);
    }
    return inv;
}




void dealloca_inv(tabInv inv){
    int i;
    for(i=0;i<inv->n_inv;i++){
        free(inv->vettinv[i].nome);
        free(inv->vettinv[i].tipo);
    }
    free(inv);
}