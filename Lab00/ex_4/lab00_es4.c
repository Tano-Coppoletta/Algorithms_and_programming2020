//
// Created by tanoc on 05/10/2019.
//
#include <stdio.h>
#define maxN 20

void stampa(int m[maxN][maxN],int dim,int nr,int nc);

int main(){
    int m[maxN][maxN],i,j,max;
    int dim=1,nr,nc;
    FILE *fp;

    do{
        printf("inserire dimensione\n");
        scanf("%d",&dim);
        fp=fopen("testo_es2.txt","r");
        fscanf(fp,"%d %d",&nr ,&nc);
        for(i=0;i<nr;i++){
            for(j=0;j<nc;j++){
                fscanf(fp,"%d",&m[i][j]);
            }
        }
        stampa(m,dim,nr,nc);
        fclose(fp);
    }while(dim>=0 && dim<=maxN);
}

void stampa(int m[maxN][maxN],int dim,int nr,int nc){
    int r=-1,c=-1,i,j,z,h;

    for(i=0;i<(nr-dim);i++){
        r++;
        for(j=0;j<(nc-dim);j++){
            c++;
            for(z=r;z<(dim+r);z++){
                for(h=c;h<(dim+c);h++){
                    printf("%d ",m[z][h]);
                }printf("\n");
            }
            printf("\n");
        }
    }
}


