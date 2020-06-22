//
// Created by tanoc on 13/11/2019.
//
#include <stdio.h>
#include <stdlib.h>

void malloc2dP(int ***mp,int nr,int nc,FILE *fp);
void freem(int **mp,int nr);
void separa(int **m,int nr,int nc,int *neri,int *bianchi);

int main(){
    FILE *fp;
    int nr,nc,**m,*neri,*bianchi;

    fp=fopen("mat.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
        return -1;
    }
    fscanf(fp,"%d%d",&nr,&nc);
    malloc2dP(&m,nr,nc,fp);
    neri=(int *)malloc(((nr*nc)/2)* sizeof(int));
    bianchi=(int *)malloc(((nr*nc)/2)* sizeof(int));
    separa(m,nr,nc,neri,bianchi);
    freem(m,nr);
}


void malloc2dP(int ***mp,int nr,int nc,FILE *fp){
    int **m;
    int i,j;
    m=(int**)malloc(nr*sizeof(int*));
    for(i=0;i<nr;i++){
        m[i]=(int*) malloc(nc* sizeof(int));
        for(j=0;j<nc;j++)
            fscanf(fp,"%d",&m[i][j]);
    }
    *mp=m;
}


void separa(int **m,int nr,int nc,int *neri,int *bianchi){
    int i,j,n=0,b=0;

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            if((i+j)%2==0)
                bianchi[b++]=m[i][j];
            else
                neri[n++]=m[i][j];
        }
    }
    printf("elementi neri: ");
    for(i=0;i<n;i++){
        printf("%d ",neri[i]);
    }
    printf("\nelementi bianchi: ");

    for(i=0;i<b;i++){
        printf("%d ",bianchi[i]);
    }
    free(bianchi);
    free(neri);
}

void freem(int **mp,int nr){
    int i;
    for(i=0;i<nr;i++)
        free(mp[i]);
    free(mp);
}
