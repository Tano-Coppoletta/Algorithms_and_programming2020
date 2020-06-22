//
// Created by tanoc on 07/10/2019.
//
#define N 20
#define M 20

#include <stdio.h>


int main(){
    int calendario[20]={0},punt,p=0;
    int i,j;
    FILE *fp;

    fp=fopen("calendario_es1.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
        return -1;
    }
    for(i=0;i<N;i++){
        p=0;
        for(j=0;j<M && p!=-1;j++){
            fscanf(fp,"%d",&punt);
            if(punt==-1){
                p=-1;
            }else
                calendario[j]+=punt;
        }
    }
   // for(j=0;j<M;j++){
     //       printf("%d",calendario[j]);
       // }

    punt=0;
    for(i=0;i<N;i++){
        if(calendario[i]>punt){
            punt=calendario[i];
            p=i;
        }
    }
   printf("%d",(p+1));

    return 0;
}
