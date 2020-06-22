//
// Created by tanoc on 05/11/2019.
//
#include <stdio.h>
#include <stdlib.h>

int majority( int *a, int N);
int majorityR(int *a,int l,int r);

int main(){
    int N,i,mag;
    int *vett;

    printf("inserire dimensione vettore\n");
    scanf("%d",&N);
    vett=(int*)malloc(N*sizeof(int));
    if(vett==NULL){
        printf("errore nell'allocazione\n");
        exit(1);
    }
    printf("inserire elementi vettore\n");
    for(i=0;i<N;i++){
        scanf("%d",&vett[i]);
    }
    mag=majority(vett,N);
    if(mag==-1){
        printf("il maggioritario non esiste\n");
    }else{
        printf("il maggioritario e' %d",mag);
    }

}


int majority( int *a, int N){
    int l=0,r=N-1;
    int mag;
    mag=majorityR(a,l,r);
    return mag;
}


int majorityR(int *a,int l,int r){
    int mag_sx,mag_dx,cont_sx=0,cont_dx=0,q,i;
    //caso terminale ho una sola cella, il maggioritario e' quell'elemento
    if(l>=r){
        return *(a+r);
    }
    //divido in due in vettore e ricorro a sx e dx
    q=(l+r)/2;
    mag_sx=majorityR(a,l,q);
    mag_dx=majorityR(a,q+1,r);
    //controllo quante volte e' presente il maggioritario nel sottovettore
    for(i=l;i<=r;i++){
        if(mag_dx==a[i]){
            cont_dx++;
        }
        if(mag_sx==a[i]){
            cont_sx++;
        }
    }
    //se ho trovato il maggioritario un numero sufficiente di volte lo ritorno
    if(cont_sx>((r-l)+1)/2){
        return mag_sx;
    }
    if(cont_dx>((r-l)+1)/2){
        return mag_dx;
    }
    return -1;
}



