//
// Created by tanoc on 14/01/2020.
//
#include "titolo.h"
#include <string.h>
#define max 20


struct titolo{
    char nome[max];
    BST quotaz;
    int N;
};

static void TRANSAZIONIscan(Titolo tit,FILE *fp,int N){
    int i,num;
    float val;
    Data d;
    Ora ora;
    for(i=0;i<N;i++){
        d=Datascan(fp);
        ora=Orascan(fp);
        fscanf(fp,"%f %d\n",&val,&num);
        BSTinsert(tit->quotaz,d,val,num);
    }
}

void Tprint(Titolo t){
    printf("%s %d\n",t->nome,t->N);
}

Titolo Tscan(FILE *fp){
    Titolo tit=Tinit();
    fscanf(fp,"%s %d\n",tit->nome,&(tit->N));
    TRANSAZIONIscan(tit,fp,tit->N);
    return tit;
}

Titolo Tinit(){
    Titolo tit=malloc(sizeof(*tit));
    tit->N=0;
    strcpy(tit->nome,"\0");
    tit->quotaz=BSTinit();
    return tit;
}

int KEYcompare(key k1,key k2){
   return strcmp(k1,k2);
}

key KEYget(Titolo tit){
    return (tit->nome);
}

int KEYgreater(key k1,key k2){
    if(strcmp(k1,k2)>0)
        return 1;
    if(strcmp(k1,k2)==0)
        return 0;
    return -1;
}

void bilancia(Titolo tit,int S){
    int q=rapportoCAMMINI(tit->quotaz);
    if(q>S){
        BSTbalance(tit->quotaz);
        printf("albero bilanciato\nStampa inorder\n");
        BSTprintINORDER(tit->quotaz);
    } else
        printf("rapporto max/min < S\n non e' possibile bilanciare l'albero\n");
}

BST estraiBST(Titolo tit){
    return tit->quotaz;
}

Titolo TsetNULL(){
    Titolo tit=malloc(sizeof(*tit));
    if(tit==NULL)
        exit(1);
    tit->N=-1;
    strcpy(tit->nome,"\0");
    tit->quotaz=BSTinit();
    return tit;
}

void Tfree(Titolo tit){
    BSTfree(tit->quotaz);
    free(tit);
}