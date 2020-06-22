//
// Created by tanoc on 12/10/2019.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define max 30
#define max_s 100

void ruota(int m[][max],char scelta,int nr,int nc,int P,int N,char direzione);
void acquisisci_m(int m[][max],FILE *fp,int nr,int nc);


int main() {
    int i, j, nr, nc,N,P, matrice[max][max];
    char scelta[max_s], nome_file[20],direzione[max];
    FILE *fp;

    printf("inserire nome file\n");
    //scanf("%s",nome_file);
    fp = fopen("matrice_es3", "r");
    if (fp == NULL) {
        printf("errore nell'apertura del file\n");
    }
    fscanf(fp, "%d %d", &nr, &nc);
    acquisisci_m(matrice, fp, nr, nc);

    printf("scrivere su cosa si vuole operare o fine\n");
    scanf("%s",scelta);

    while(toupper(scelta[0])!='F'){
        printf("inserire numero di %s su cui si vuole operare\n",scelta);
        scanf("%d",&N);
        printf("inserire direzione\n");
        scanf("%s",direzione);
        printf("inserire numero posizioni\n");
        scanf("%d",&P);
        ruota(matrice,scelta[0],nr,nc,P,N,direzione[0]);
        for(i=0;i<nr;i++){
            for(j=0;j<nc;j++){
                printf("%d ",matrice[i][j]);
            }
            printf("\n");
        }
        printf("scrivere su cosa si vuole operare o fine\n");
        scanf("%s",scelta);
    }
}

void acquisisci_m(int m[][max],FILE *fp,int nr,int nc) {
    int i, j;
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            fscanf(fp, "%d", &m[i][j]);
        }
    }
}

void ruota(int m[][max],char scelta,int nr,int nc,int P,int N,char direzione){
    int i,j=0,v[(nc-1)];
    N=N-1;

    if(toupper(scelta)=='R'){
        if(toupper(direzione)=='D'){
            for(i=0;i<nc;i++){
                v[i]=m[N][(i+P)%nc];
            }
            for(i=0;i<nc;i++){
                m[N][i]=v[i];
            }
        }else if(toupper(direzione)=='S'){
            for(i=P;i<nc;i++){
                v[j]=m[N][i];
                j++;
            }
            for(i=0;i<P;i++){
                v[j]=m[N][i];
                j++;
            }
            for(i=0;i<nc;i++){
                m[N][i]=v[i];
            }
        }else{
            printf("inserire direzione valida\n");
        }
    }else if(toupper(scelta)=='C'){
        if(toupper(direzione)=='S'){
            for(i=P;i<nr;i++){
                v[j]=m[i][N];
                j++;
            }
            for(i=0;i<P;i++){
                v[j]=m[i][N];
                j++;
            }
            for(i=0;i<nr;i++){
                m[i][N]=v[i];
            }
        }else if(toupper(scelta)=='G'){
            for(i=0;i<nr;i++){
                v[i]=m[(i+P)%nr][N];
            }
            for(i=0;i<nr;i++){
                m[i][N]=v[i];
            }
        }
    }
}
