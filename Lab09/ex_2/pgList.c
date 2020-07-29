//
// Created by tanoc on 11/12/2019.
//
#include "pgList.h"

typedef struct node_t *link;

struct node_t{
    pg_t pg;
    link next;
};

struct pgList_s{
    link head;
    link tail;
    int N;
};

link new_node(pg_t pg,link next){
    link x=malloc(sizeof(*x));
    if(x==NULL)
        exit(1);
    x->pg=pg;
    x->next=next;
    return x;
}

pgList_t pgList_init(){
    pgList_t pg;
    pg=malloc(sizeof(struct pgList_s));
    if(pg==NULL)
        exit(1);
    pg->head=pg->tail=NULL;
    return pg;
}
/* lettura da file */
void pgList_read(FILE *fp, pgList_t pgList){
    pg_t pg;
    //tratto separatamente la testa, in seguito modifico solo tail
    pg_read(fp,&pg);
    pgList->N++;
    pgList->head=pgList->tail=new_node(pg,NULL);
    while(pg_read(fp,&pg)==1){
        pgList_insert(pgList,pg);
        pgList->N++;
    }
}
/*stampa su file */
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;
    for(x=pgList->head;x!=NULL;x=x->next){
        pg_print(fp,&(x->pg),invArray);
    }
}

void free_r(link h){
    if(h==NULL)
        return;
    free_r(h->next);
    pg_clean(&(h->pg));
    free(h);
}

void pgList_free(pgList_t pgList){
    free_r(pgList->head);
}

int KEYeq(char *c1,char *c2){
    if(strcmp(c1,c2)==0)
        return 1;
    return 0;
}

void pgList_insert(pgList_t pgList, pg_t pg){
    pgList->tail->next=new_node(pg,NULL);
    pgList->tail=pgList->tail->next;
}
/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod){
    link x,p;
    for(x=pgList->head,p=NULL;x!=NULL;p=x,x=x->next){
        if(KEYeq(x->pg.cod,cod)){
           if(x==pgList->head)
               pgList->head=x->next;
           else
               p->next=x->next;
           pg_clean(&(x->pg));
           free(x);
           break;
        }
    }
}
/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;
    for(x=pgList->head;x!=NULL;x=x->next){
        if(KEYeq(x->pg.cod,cod)){
            return &x->pg;
        }
    }
}