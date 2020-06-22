//
// Created by tanoc on 19/11/2019.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int v1;
    int v2;
}Archi;
//puntatore a struct globale
Archi *archi;

Archi *scrivi_struct(int E,FILE *fp);
void powerset(int e,int n);
void powerset_r(int *vertici,int v,int e,int *sol,int n,int pos,int start);
int check(int *sol,int n,int e);

int main(){
    int N,E;
    FILE *fp;

    fp=fopen("grafi.txt","r");
    if(fp==NULL){
        printf("errore nel file\n");
        return -1;
    }
    fscanf(fp,"%d %d",&N,&E);
    archi=scrivi_struct(E,fp);
    powerset(E,N);
    free(archi);
}


Archi *scrivi_struct(int E,FILE *fp){
    int i;
    Archi *a;

    //allocazione e scrittura di struct archi
    a=(Archi *)malloc(E* sizeof(*a));
    if(a==NULL)
        exit(1);
    for(i=0;i<E;i++)
        fscanf(fp,"%d %d",&a[i].v1,&a[i].v2);
    return a;
}

void powerset(int e,int n){
    int num,*sol,*vertici;

    //vertici viene inizializzato con numeri da 0 al numero di archi
    vertici=(int*)malloc(n* sizeof(int));
    for(num=0;num<n;num++)
        vertici[num]=num;
    //modello delle combinazioni semplici
    for(num=1;num<=n;num++){
        //vettore sol che aumenta di grandezza ad ogni passo del for
        sol=(int*)malloc(num* sizeof(int));
        powerset_r(vertici,n,e,sol,num,0,0);
        free(sol);
    }
    free(vertici);
}
void powerset_r(int *vertici,int v,int e,int *sol,int n,int pos,int start){
    int i;

    if(pos>=n){
        if(check(sol,n,e)) {
            printf("{");
            for (i = 0; i < n; i++)
                printf("%d ", sol[i]);
            printf("}\n");
        }
        return ;
    }
    for(i=start;i<v;i++){
        sol[pos]=vertici[i];
        powerset_r(vertici,v,e,sol,n,pos+1,i+1);
    }
}


int check(int *sol,int n,int e){
    int i,j,flag;

    for(i=0;i<e ;i++){
        flag=1;
        for(j=0;j<n && flag==1;j++){
            if(archi[i].v1==sol[j] || archi[i].v2==sol[j])
                flag=0;
    }
        if(flag==1){
            return 0;
        }
    }
   return 1;
}