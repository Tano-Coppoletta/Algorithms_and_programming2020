//
// Created by tanoc on 04/12/2019.
//
#include "personaggi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 50

link new_node(Pg_t val,link next){
    link x=malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    x->pg=val;
    x->next=next;
    return x;
}


void aggiungi_ogg(link h,tabInv inv){
    int i;
    char personaggio[7],oggetto[max];
    link x;
    printf("inserire codice personaggio a cui aggiungere oggetto\n");
    scanf("%s",personaggio);
    //cerca_pers torna il link che punta al personaggio
    x=cerca_pers(h,personaggio);
    if(x->pg.equip.n==0){
        //se il pers non ha neanche un ogg alloco un vett di puntatori di 1
        x->pg.equip.inUso=(Inv_t**)malloc(sizeof(Inv_t*));
        x->pg.equip.n++;
    }else if(x->pg.equip.n>=8){
        printf("il personaggio %s possiede già il max numero di oggetti\n",x->pg.nome);
    }else{
        x->pg.equip.n++;
        x->pg.equip.inUso=(Inv_t**)realloc(x->pg.equip.inUso,x->pg.equip.n* sizeof(Inv_t*));
    }
    printf("inserire nome oggetto da aggiungere a %s",x->pg.nome);
    scanf("%s",oggetto);
    for(i=0;i<(inv->n_inv);i++){
        //appena trovo l'oggetto esco in modo non strutturato,i sara' l'indice dove si trova l'oggetto
        if(strcmp(inv->vettinv[i].nome,oggetto)==0){
            break;
        }
    }
    x->pg.equip.inUso[(x->pg.equip.n-1)]=&inv->vettinv[i];
    aggiorna_stat(1,x,inv->vettinv[i]);
    //  printf("personaggio %s %s oggetto: %s %d\n",x->pg.nome,x->pg.codice,x->pg.equip.inUso[(x->pg.equip.n-1)]->nome,x->pg.equip.inUso[0]->stat_ogg.hp);
}

void inizializza_ogg(Pg_t *p){
    p->equip.n=0;
}

void cancella_ogg(link h){
    int i;
    Inv_t **nuovo;
    char personaggio[7],oggetto[max];
    link x;
    printf("inserire codice personaggio a cui togliere oggetto\n");
    scanf("%s",personaggio);
    x=cerca_pers(h,personaggio);
    x->pg.equip.n--;
    //alloco un vett di punt con lunghezza n-1 in cui scrivo tutti gli oggetti tranne quello da cancellare
    nuovo=(Inv_t**)malloc(x->pg.equip.n* sizeof(Inv_t*));
    printf("inserire nome oggetto da togliere\n");
    scanf("%s",oggetto);
    for(i=0;i<x->pg.equip.n;i++){
        if(strcmp(oggetto,x->pg.equip.inUso[i]->nome)!=0){
            nuovo[i]=(x->pg.equip.inUso[i]);
        }
    }
    //aggiorno statistiche giocatore
    aggiorna_stat(0,x,*x->pg.equip.inUso[i]);
    //libero vettore precedente e ne alloco un altro con lunghezza n-1 in cui copio nuovo
    free(x->pg.equip.inUso);
    x->pg.equip.inUso=(Inv_t**)malloc(x->pg.equip.n* sizeof(Inv_t*));
    for(i=0;i<x->pg.equip.n;i++){
        x->pg.equip.inUso[i]=nuovo[i];
    }
    free(nuovo);
}

int carica_p(tabPg tab){
    FILE *fp;
    Pg_t p;
    int l=0;
    char nome[max],classe[max];

    fp=fopen("pg.txt","r");
    if(fp==NULL)
        printf("errore file\n");
    while(fscanf(fp,"%s %s %s %d %d %d %d %d %d",p.codice,nome,classe,&p.stat.hp
            ,&p.stat.mp,&p.stat.atk,&p.stat.def,&p.stat.mag,&p.stat.spr)>=0){
        p.nome=strdup(nome);
        p.classe=strdup(classe);
        //copio le statistiche in statistiche effettive, serve per i casi in cui stat<1
        p.eff_stat=p.stat;
        inizializza_ogg(&p);
        //inserisco in coda
        listInstail(tab,p);
        l++;
    }
    return l;
}

void listInstail(tabPg tab,Pg_t val){
    if(tab->headPg==NULL){
        tab->headPg=tab->tailPg=new_node(val,NULL);
    }else{
        tab->tailPg->next=new_node(val,NULL);
        tab->tailPg=tab->tailPg->next;
    }
}

void aggiungi_p(tabPg tab){
    Pg_t p;
    char nome[max],classe[max];

    printf("inserire codice,nome,classe,hp,mp,atk,def,mag,spr\n");
    scanf("%s %s %s %d %d %d %d %d %d",p.codice,nome,classe,&p.stat.hp,&p.stat.mp,&p.stat.atk,&p.stat.def,
          &p.stat.mag,&p.stat.spr);
    p.nome=strdup(nome);
    p.classe=strdup(classe);
    p.eff_stat=p.stat;
    inizializza_ogg(&p);
    listInstail(tab,p);
}

void cancella_P(tabPg tab){
    char delcodice[7];
    link x,p;
    printf("inserire codice da eliminare\n");
    scanf("%s",delcodice);
    for(p=NULL,x=tab->headPg;x!=NULL;p=x,x=x->next){
        if(strcmp(x->pg.codice,delcodice)==0){
            //caso testa
            if(x==tab->headPg)
                tab->headPg=x->next;
                //caso in cui devo cancellare coda
            else if(x->next==NULL){
                tab->tailPg=p;
                tab->tailPg->next=NULL;
            }else
                p->next=x->next;
            freeP(x);
            free(x);
        }
    }
}

void freeP(link x){
    free(x->pg.nome);
    free(x->pg.classe);
}

link cerca_pers(link h,char *codice){
    link x;
    for(x=h;x!=NULL;x=x->next){
        if(strcmp(x->pg.codice,codice)==0){
            return x;
        }
    }
    return NULL;
}
void stampa_stat(char *p,link h){
    link x;
    x=cerca_pers(h,p);
    printf("statistiche giocatore %s :%d %d %d %d %d %d\n",x->pg.nome,x->pg.eff_stat.hp,x->pg.eff_stat.mp,x->pg.eff_stat.atk,
           x->pg.eff_stat.def,x->pg.eff_stat.mag,x->pg.eff_stat.spr);
}


void aggiorna_stat(int scelta,link x,Inv_t ogg){
    if(scelta==1){
        x->pg.stat.hp+=ogg.stat_ogg.hp; if(x->pg.stat.hp<1) x->pg.eff_stat.hp=1; else x->pg.eff_stat.hp=x->pg.stat.hp;
        x->pg.stat.mp+=ogg.stat_ogg.mp; if(x->pg.stat.mp<1) x->pg.eff_stat.mp=1; else x->pg.eff_stat.mp=x->pg.stat.mp;
        x->pg.stat.atk+=ogg.stat_ogg.atk; if(x->pg.stat.atk<1) x->pg.eff_stat.atk=1; else x->pg.eff_stat.atk=x->pg.stat.atk;
        x->pg.stat.def+=ogg.stat_ogg.def; if(x->pg.stat.def<1) x->pg.eff_stat.def=1; else x->pg.eff_stat.def=x->pg.stat.def;
        x->pg.stat.mag+=ogg.stat_ogg.mag; if(x->pg.stat.mag<1) x->pg.eff_stat.mag=1; else x->pg.eff_stat.mag=x->pg.stat.mag;
        x->pg.stat.spr+=ogg.stat_ogg.spr; if(x->pg.stat.spr<1) x->pg.eff_stat.spr=1; else x->pg.eff_stat.spr=x->pg.stat.spr;
    }else{
        x->pg.stat.hp-=ogg.stat_ogg.hp;if(x->pg.stat.hp<1) x->pg.eff_stat.hp=1;else x->pg.eff_stat.hp=x->pg.stat.hp;
        x->pg.stat.mp-=ogg.stat_ogg.mp; if(x->pg.stat.mp<1) x->pg.eff_stat.mp=1; else x->pg.eff_stat.mp=x->pg.stat.mp;
        x->pg.stat.atk-=ogg.stat_ogg.atk; if(x->pg.stat.atk<1) x->pg.eff_stat.atk=1; else x->pg.eff_stat.atk=x->pg.stat.atk;
        x->pg.stat.def-=ogg.stat_ogg.def; if(x->pg.stat.def<1) x->pg.eff_stat.def=1; else x->pg.eff_stat.def=x->pg.stat.def;
        x->pg.stat.mag-=ogg.stat_ogg.mag; if(x->pg.stat.mag<1) x->pg.eff_stat.mag=1; else x->pg.eff_stat.mag=x->pg.stat.mag;
        x->pg.stat.spr-=ogg.stat_ogg.spr; if(x->pg.stat.spr<1) x->pg.eff_stat.spr=1; else x->pg.eff_stat.spr=x->pg.stat.spr;
    }
}
void dealloca_lista(link h){
    if(h==NULL)
        return;
    dealloca_lista(h->next);
    freeP(h);
    free(h);
}
