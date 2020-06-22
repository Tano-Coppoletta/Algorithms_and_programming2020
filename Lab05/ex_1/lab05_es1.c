//
// Created by tanoc on 13/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 256

typedef struct {
    int l;
    char *c[5];
}canzoni;

//struct globale
canzoni *c;

void leggi_canzoni(FILE *fp,int A);
int princ_molt(int pos,int *sol,int n,int count);

int main(){
    int A,i,j,*sol,cont;
    FILE *fp;

    fp=fopen("brani.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
        return -1;
    }
    fscanf(fp,"%d",&A);
    c=(canzoni *)malloc(A* sizeof(canzoni));
    leggi_canzoni(fp,A);
    //sol vettore che contiene la soluzione
    sol=(int *)malloc(A* sizeof(int));
    cont=princ_molt(0,sol,A,0);
    free(sol);
    printf("%d",cont);
    //free di stringhe e struct
    for(i=0;i<A;i++){
        for(j=0;j<c[i].l;j++){
            free(c[i].c[j]);
        }
    }
    free(c);

}


void leggi_canzoni(FILE *fp,int A){
    int i,j;
    char stringa[max];
//per ogni gruppo di canzioni leggo il numero di canzoni proposte dall'amico
    for(i=0;i<A;i++){
        fscanf(fp,"%d",&c[i].l);
        for(j=0;j<c[i].l;j++){
            fscanf(fp,"%s",stringa);
            c[i].c[j]=strdup(stringa);
        }
    }
}


int princ_molt(int pos,int *sol,int n,int count){
    int i;

    if(pos>=n){
        //se la soluzione e' completa la stampo
        for(i=0;i<n;i++)
            printf("%s ",c[i].c[sol[i]]);
        printf("\n");
        return count+1;
    }
    for(i=0;i<c[pos].l;i++){
        sol[pos]=i;
        count=princ_molt(pos+1,sol,n,count);
    }
    return count;
}