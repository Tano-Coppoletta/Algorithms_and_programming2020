//
// Created by tanoc on 01/10/2019.
//
#include <stdio.h>
#define MaxN 30

void ruota(int v[MaxN],int N,int P,int dir);

int main(){
    int i,N,P=1,dir,vettore[MaxN]={0};
    do {
        printf("inserire lunghezza vettore\n");
        scanf("%d", &N);

        if (MaxN < N) {
            printf("errore 1\n");
        }
    }while(MaxN<N);
    printf("inserire %d elementi vettore\n",N);
    for(i=0;i<N;i++){
        scanf("%d",&vettore[i]);
    }
    while(P!=0) {
        printf("inserire P\n");
        scanf("%d", &P);
        printf("inserire -1 per ruotare a destra o 1 per sinistra\n");
        scanf("%d",&dir);
        ruota(vettore,N,P,dir);
    }
    }

    void ruota(int v[MaxN],int N,int P,int dir){
    int i,flag=0;

    if(dir==-1){
        for(i=(N-P);i<N;i++){
            printf("%d",v[i]);
        }
        for(i=0;i<(N-P);i++){
            printf("%d",v[i]);
        }

    }else if(dir==1){
        for(i=P;i<N;i++){
            printf("%d",v[i]);
        }
        for(i=0;i<P;i++){
            printf("%d",v[i]);
        }

    }else{
        printf("errore 2\n");
    }
}