//
// Created by tanoc on 19/10/2019.
//
#include <stdio.h>

void copia(int v[],int temp[],int N);
void stampa(int v[],int N);
void selectionsort(int v[],int N);
void insertionsort(int v[],int N);
void shellsort(int v[],int N);

int main(){
    FILE *fp;
    int S,l,i=0,j,v[20],temp[20];

    fp=fopen("C:\\Users\\tanoc\\Desktop\\Algoritmi e programmazione\\progetto\\lab02\\sort.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
        return -1;
    }
    fscanf(fp,"%d",&S);
    while(i<=S){
        i++;
        fscanf(fp,"%d",&l);
        for(j=0;j<l;j++){
            fscanf(fp,"%d",&v[j]);
        }
        copia(v,temp,l);
        insertionsort(temp,l);
        stampa(temp,l);
        copia(v,temp,l);
        shellsort(temp,l);
        stampa(temp,l);
        copia(v,temp,l);
        selectionsort(temp,l);
        stampa(temp,l);
    }
}


void copia(int v[],int temp[],int N){
    int i;
    for(i=0;i<N;i++){
        temp[i]=v[i];
    }
}

void stampa(int v[],int N){

    for(int i=0;i<N;i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}

void selectionsort(int v[],int N){
    int i,j,min,temp,scambi=0,iterazioni_e=0,iterazioni_i=0;

    for(i=0;i<N;i++,iterazioni_e++){
        min=i;
        for(j=i+1;j<N;j++,iterazioni_i++){
            if(v[j]<v[min]){
                min=j;
            }
            if(min!=i){
                scambi++;
                temp=v[i];
                v[i]=v[min];
                v[min]=temp;
            }
        }
    }
    printf("selectionsort: numero iterazioni esterne %d\nnumero iterazioni interne %d\nnumero scambi %d\niterazioni totali %d\n",iterazioni_e,iterazioni_i,scambi,iterazioni_e+iterazioni_i);
}


void insertionsort(int v[],int N){
    int i,j,x,scambi=0,iterazioni_i=0,iterazioni_e=0;

    for(i=1;i<N;i++,iterazioni_e++){
        x=v[i];
        j=i-1;
        while(j>=0 && x<v[j]){
            scambi++;
            v[j+1]=v[j];
            j--;
            iterazioni_i++;
        }
        v[j+1]=x;
    }
    printf("insertionsort: numero iterazioni esterne %d\nnumero iterazioni interne %d\nnumero scambi %d\niterazioni totali %d\n",iterazioni_e,iterazioni_i,scambi,iterazioni_e+iterazioni_i);
}


void shellsort(int v[],int N){
    int i,j,x,h=1,scambi=0,iterazioni_e=0,iterazioni_i=0;

    while(h<(N/3))
        h=3*h+1;
    while(h>=1){
        for(i=h;i<N;i++,iterazioni_e++){
            j=i;
            x=v[i];
            while(j>=h && x<v[j-h]){
                scambi++;
                v[j]=v[j-h];
                j-=h;
            }
            v[j]=x;
        }
        h=h/3;
    }
    printf("shellsort: numero iterazioni esterne %d\nnumero iterazioni interne %d\nnumero scambi %d\niterazioni totali %d\n",iterazioni_e,iterazioni_i,scambi,iterazioni_e+iterazioni_i);

}