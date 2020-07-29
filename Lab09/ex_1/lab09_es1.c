//
// Created by tanoc on 11/12/2019.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int si;
    int fi;
}att;

att *v;

void alloca_att(int N);
void acquisisci_file(int *N);
void quicksort(int l,int r);
int partition(int l,int r);
void swap(int n1,int n2);
void optD(int N);
void printbest(int *P,int i);

int main(){
    int N;

    acquisisci_file(&N);
    quicksort(0,N-1);
    optD(N);
}


void alloca_att(int N){

    v=(att*)malloc(N* sizeof(att));
    if(v==NULL)
        exit(1);
}

void acquisisci_file(int *N){
    int i;
    FILE *fp=fopen("attivita.txt","r");

    if(fp==NULL)
        printf("errore file\n");
    fscanf(fp,"%d",N);
    alloca_att(*N);
    for(i=0;i<*N;i++){
        fscanf(fp,"%d %d",&v[i].si,&v[i].fi);
    }
}

void quicksort(int l,int r){
    int q;
    if(r>=l)
        return;
    q=partition(l,r);
    quicksort(l,q-1);
    quicksort(q+1,r);
    return;
}

int partition(int l,int r){
    int i=l-1,j=r;
    int x=v[r].si;
    for(;;){
        while(v[++i].si<x);
        while(v[--j].si>x)
            if(j==l)
                break;
        if(i>=j)
            break;
        swap(i,j);
    }
    swap(i,r);
    return i;
}

void swap(int n1,int n2){
    int tmp;
    tmp=v[n1].si;
    v[n1].si=v[n2].si;
    v[n2].si=tmp;
}

void optD(int N){
    int L[N],P[N],last,i,j,ris=0;

    for(i=0;i<N;i++){
        L[i]=v[i].fi-v[i].si;
        P[i]=-1;
        for(j=0;j<i;j++){
            if(v[j].fi<v[i].si){
                L[i]+=L[j];
                P[i]=j;
            }
        }
        if(ris<L[i]){
            ris=L[i];
            last=i;
        }
    }
    printf("soluzione:\n");
    printbest(P,last);
}

void printbest(int *P,int i){
    if(P[i]==-1){
        printf("%d %d\n",v[i].si, v[i].fi);
        return;
    }
    printbest(P,P[i]);
    printf("%d %d\n",v[i].si,v[i].fi);
}
