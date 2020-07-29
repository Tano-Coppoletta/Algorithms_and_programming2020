//
// Created by tanoc on 02/01/2020.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 100
#define DBG 0
#define DD 10
#define DP 20
#define maxe 5

typedef struct {
    char *nome;
    int tipo,dir_ingresso,dir_uscita,primo,finale,difficolta;
    float valore;
}Elemento;

typedef struct{
    int d[5];
}diagonale;

Elemento *alloca_e(int *N);
void scrivi_e(FILE *fp,int N,Elemento *e);
int comb_rip(int pos,Elemento *e,diagonale *diag,int *l,int i,int N,int k,int start);
int cerca(Elemento *e,int N,diagonale *diag,int l);
void disp_rip(int pos,Elemento *e,int *m,int *sol,int N,int k,int acrob,int due_acr,int difficolta,int maxpunti,int *bestsol);
diagonale *riallocad(diagonale *diag,int N);


int main(){
    int N;
    Elemento *e;
    diagonale *diag=malloc(sizeof(int));
    if(diag==NULL)
        exit(1);
    e=alloca_e(&N);
    if(e==NULL)
        exit(1);
#if DBG
    for(int i=0;i<N;i++)
        printf("%s %d %d %d %d %d %f %d\n",e[i].nome,e[i].tipo,e[i].dir_ingresso,e[i].dir_uscita,e[i].primo,
               e[i].finale,e[i].valore,e[i].difficolta);
#endif
    cerca(e,N,diag,1);
}

diagonale *riallocad(diagonale *diag,int N){
    diag=realloc(diag,N* sizeof(int));
    if(diag==NULL)
        exit(1);
    return diag;
}

Elemento *alloca_e(int *N){
    FILE *fp=fopen("elementi.txt","r");
    Elemento *e;
    if(fp==NULL)
        return NULL;
    fscanf(fp,"%d",N);
    e=malloc(*N* sizeof(Elemento));
    if(e==NULL)
        return NULL;
    scrivi_e(fp,*N,e);
    return e;
}

void scrivi_e(FILE *fp,int N,Elemento *e){
    int i;
    char stringa[max];
    for(i=0;i<N;i++){
        fscanf(fp,"%s %d %d %d %d %d %f %d",stringa,&e[i].tipo,&e[i].dir_ingresso,&e[i].dir_uscita,&e[i].primo,
                &e[i].finale,&e[i].valore,&e[i].difficolta);
        e[i].nome=strdup(stringa);
    }
}

int comb_rip(int pos,Elemento *e,diagonale *diag,int *l,int i,int N,int k,int start){
    int j;
    if(pos>=k){
        for(j=0;j<k;j++){
           // printf("%s",e[diag[i].d[j]].nome);
        }
        printf("\n");
        if(i+1>=(*l)){
          //  diag=riallocad(diag,2*(*l));
          diag=realloc(diag,2*(*l));
          *l=2*(*l);
        }
        return i+1;
    }
    for(j=start;j<N;j++){
        diag[i].d[pos]=j;
        i=comb_rip(pos+1,e,diag,l,i,N,k,start);
        start++;
    }
    return i;
}

int cerca(Elemento *e,int N,diagonale *diag,int l){
    int i,indice=0;
    //genero le combinazioni ripetute di N elementi su k posti con 1<k<5
    for(i=1;i<=maxe;i++){
       indice=comb_rip(0,e,diag,&l,indice,N,i,0);
        printf("%d %d\n",indice,l);
    }
    printf("%d",indice);
}


void disp_rip(int pos,Elemento *e,int *m,int *sol,int N,int k,int acrob,int due_acr,int difficolta,int maxpunti,int *bestsol){
    int i;

    if(pos>=k){

    }
    for(i=0;i<N;i++){
        sol[pos]=m[i];
        disp_rip(pos+1,e,m,sol,N,k,acrob,due_acr,difficolta,maxpunti,bestsol);
    }
}