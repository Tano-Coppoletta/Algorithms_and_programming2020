//
// Created by tanoc on 14/01/2020.
//
#include "collezione.h"

typedef struct node *link;

struct node{
    Titolo tit;
    link next;
};

struct collezione{
    link head;
    int N;
};

static link NEW(Titolo val,link next){
    link x=malloc(sizeof(*x));
    if(x==NULL)
        exit(1);
    x->tit=val;
    x->next=next;
    return x;
}

CT CTinit(){
    CT ct=malloc(sizeof(*ct));
    if(ct==NULL)
        exit(1);
    ct->N=0;
    ct->head=NULL;
    return ct;
}


CT CTscan(FILE *fp,CT ct){
    int N,i;
    fscanf(fp,"%d",&N);
    for(i=0;i<N;i++){
        insert(ct,Tscan(fp));
    }
}


static link insertOrd(link h,Titolo tit){
    link x,p;
    if(h==NULL || KEYgreater(KEYget(h->tit),KEYget(tit))==1)
        return NEW(tit,h);
    for(x=h->next, p=h; x!=NULL && KEYgreater(KEYget(tit),KEYget(x->tit))==1; p=x, x=x->next);
    if(KEYgreater(KEYget(tit),KEYget(p->tit))==0)
        return h;
    else
        p->next=NEW(tit,x);
    return h;
}

void insert(CT ct,Titolo tit){
    ct->head=insertOrd(ct->head,tit);
}

Titolo estraiTIT(CT ct,char *codice){
    link x;
    for(x=ct->head;x!=NULL;x=x->next){
        if(KEYcompare(codice,KEYget(x->tit))==0){
            return x->tit;
        }
    }
    return TsetNULL();
}

void cercaeBILANCIA(CT ct,char *nome){
    int S;
    printf("inserire S\n");
    scanf("%d",&S);
    bilancia(estraiTIT(ct,nome),S);
}

void ricercaTIT(CT ct,char *codice){
    link x;
    for(x=ct->head;x!=NULL;x=x->next){
        if(KEYcompare(codice,KEYget(x->tit))==0){
            Tprint(x->tit);
            return;
        }
    }
    printf("titolo non trovato\n");
}

static void ListfreeR(link h){
    if(h==NULL)
        return;
    ListfreeR(h->next);
    Tfree(h->tit);
    free(h);
}

void CTfree(CT ct){
    ListfreeR(ct->head);
    free(ct);
}