//
// Created by tanoc on 04/12/2019.
//

#ifndef PROGETTO_PERSONAGGI_H
#define PROGETTO_PERSONAGGI_H

#include "inventario.h"

typedef struct tabPg_t *tabPg;

typedef struct nodoPg_t *link;

typedef struct{
    char codice[7];
    char *nome;
    char *classe;
    Equip equip;
    Stat stat;
    Stat eff_stat;
}Pg_t;

struct tabPg_t{
    link headPg;
    link tailPg;
    int nPg;
};

struct nodoPg_t{
    Pg_t pg;
    link next;
};

link new_node(Pg_t val,link next);
void listInstail(tabPg tab,Pg_t val);
int carica_p(tabPg tab);
void aggiungi_p(tabPg tab);
void cancella_P(tabPg tab);
void freeP(link x);
link cerca_pers(link h,char *codice);
void stampa_stat(char *p,link h);
void aggiorna_stat(int scelta,link x,Inv_t ogg);
void dealloca_lista(link h);
void aggiungi_ogg(link h,tabInv inv);
void inizializza_ogg(Pg_t *p);
void cancella_ogg(link h);

#endif //PROGETTO_PERSONAGGI_H
