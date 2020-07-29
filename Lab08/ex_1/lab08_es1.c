//
// Created by tanoc on 03/12/2019.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int si;
    int fi;
}att;

att *v;
void attSel(int N);
void powerset_r(int *val,int k,int *sol,int n,int pos,int start,int curr_d,int *best_d,int *best_sol);
void alloca_att(int N);
void acquisisci_file(int *N);
void scrivi_indici(int N,int *val);
int incrementad(int i,int dist);
int decrementad(int i,int dist);
int promising(int *sol,int pos);
int not_ok(int a1,int a2);

int main(){
    int N;
    acquisisci_file(&N);
  /*  for(int i=0;i<N;i++)
        printf("%d %d\n",v[i].si,v[i].fi);*/
    attSel(N);
    free(v);
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



void attSel(int N){
    int i,*sol,*val=(int*)malloc(N* sizeof(int));
    scrivi_indici(N,val);
    int best_d=0,*best_sol;
    sol=(int*)malloc(N* sizeof(int));
    best_sol=(int*)malloc(N* sizeof(int));
    if(val==NULL || sol==NULL || best_sol==NULL)
        exit(1);
    for(i=1;i<=N;i++){
        powerset_r(val,N,sol,i,0,0,0,&best_d,best_sol);
    }

    printf("%d\n",best_d);
    free(sol);
    free(val);
    free(best_sol);
}

void powerset_r(int *val,int k,int *sol,int n,int pos,int start,int curr_d,int *best_d,int *best_sol){
    int i;
    if(pos>=n){
        if(*best_d<curr_d){
            for(i=0;i<n;i++)
                best_sol[i]=sol[i];
            *best_d=curr_d;
            return;
        }
        return;
    }
    for(i=start;i<k;i++){
        sol[pos]=val[i];
        if(pos==0 || promising(sol,pos)){
            curr_d=incrementad(i,curr_d);
            powerset_r(val,k,sol,n,pos+1,i+1,curr_d,best_d,best_sol);
            curr_d=decrementad(i,curr_d);
        }
    }
    return;
}

void scrivi_indici(int N,int *val){
    int i;

    for(i=0;i<N;i++)
        val[i]=i;
}

int incrementad(int i,int dist){
    return dist+(v[i].fi-v[i].si);
}

int decrementad(int i,int dist){
    return dist-(v[i].fi-v[i].si);
}

int promising(int *sol,int pos){
    int j=0;
//sol[pos] e' quello da controllare
    for(j=0;j<pos;j++){
        if(not_ok(sol[j],sol[pos]))
            return 0;
    }
    return 1;
}

int not_ok(int a1,int a2){
    if(v[a1].si<v[a2].fi && v[a2].si<v[a1].fi)
        return 1;
    return 0;
}