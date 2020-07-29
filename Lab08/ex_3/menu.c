//
// Created by tanoc on 04/12/2019.
//
#include "personaggi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 50

typedef enum{personaggi,oggetti,aggiungiP,cancellaP,aggiungiO,cancellaO,statistiche,fine}comando_e;

comando_e leggicomando(char *comando);

int main(){
    link x;
    int continua=1;
    char comando[max],codice[max];
    comando_e cmd;
    tabPg tab=malloc(sizeof(*tab));
    tabInv inventario=malloc(sizeof(*inventario));

    if(tab==NULL)
        exit(1);
    tab->headPg=tab->tailPg=NULL;
    if(inventario==NULL)
        exit(1);

    while(continua){
        printf("comando tra:personaggi,oggetti,aggiungiP,cancellaP,aggiungiO,cancellaO,statistiche,fine\n");
        scanf("%s",comando);
        cmd=leggicomando(comando);
        switch(cmd){
            case personaggi:
                //la funzione carica_p legge i personaggi crea la lista e torna il numero di personaggi
                tab->nPg=carica_p(tab);
                for(x=tab->headPg;x!=NULL;x=x->next){
                      printf("%s %s %s %d %d %d %d %d %d\n",x->pg.codice,x->pg.nome,x->pg.classe,x->pg.stat.hp
                             ,x->pg.stat.mp,x->pg.stat.atk,x->pg.stat.def,x->pg.stat.mag,x->pg.stat.spr);
                   }
                break;
            case oggetti:
                //alloco e scrivo inventario
                inventario=carica_oggetti(inventario);
                /*stampa per controllo   for(int i=0;i<inventario->n_inv;i++){
                     printf("%s %s %d %d %d %d %d %d\n",inventario->vettinv[i].nome,inventario->vettinv[i].tipo,inventario->vettinv[i].stat_ogg.hp
                              ,inventario->vettinv[i].stat_ogg.mp,
                           inventario->vettinv[i].stat_ogg.atk,inventario->vettinv[i].stat_ogg.def,inventario->vettinv[i].stat_ogg.mag,
                              inventario->vettinv->stat_ogg.spr);
                   }*/
                break;
            case aggiungiP:
                //incremento numero personaggi e aggiungo in testa, aggiorno testa
                tab->nPg++;
                aggiungi_p(tab);
                break;
            case cancellaP:
                if(tab->headPg==NULL)
                    printf("lista vuota\n");
                else {
                    cancella_P(tab);
                    tab->nPg--;
                    for (x = tab->headPg; x != NULL; x = x->next)
                           printf("%s %s %s %d %d %d %d %d %d\n", x->pg.codice, x->pg.nome, x->pg.classe, x->pg.stat.hp,
                                  x->pg.stat.mp, x->pg.stat.atk, x->pg.stat.def, x->pg.stat.mag, x->pg.stat.spr);
                }
                break;
            case aggiungiO:
                aggiungi_ogg(tab->headPg,inventario);
                break;
            case cancellaO:
                cancella_ogg(tab->headPg);
                break;
            case statistiche:
                printf("inserire codice personaggio\n");
                scanf("%s",codice);
                stampa_stat(codice,tab->headPg);
                break;
            case fine:
                continua=0;
                if(tab->headPg!=NULL)
                    dealloca_lista(tab->headPg);
                if(inventario!=NULL)
                    dealloca_inv(inventario);
                break;
            default:printf("comando non valido\n");
        }
    }
}


comando_e leggicomando(char *comando){
    char *scelte[fine+1]={"personaggi","oggetti","aggiungiP","cancellaP","aggiungiO",
                          "cancellaO","statistiche","fine"};
    comando_e c=personaggi;
    while(c<=fine && strcmp(scelte[c],comando)!=0)
        c++;
    return c;
}