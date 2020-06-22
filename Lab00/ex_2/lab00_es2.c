//
// Created by tanoc on 01/10/2019.
//
#include <stdio.h>
#include <string.h>
#define vocali 2

int conta(char S[20],int n);

int main(){
    int N=0,n,i,trovate=0;
    char parola[20],nomefile[200];
    FILE *fp;

  //  printf("inserire nome file\n");
    //scanf("%s",nomefile);
    printf("inserire lunghezza sottostringa\n");
    scanf("%d",&n);
    fp=fopen("C:\\Users\\tanoc\\Desktop\\Algoritmi e programmazione\\progetto\\lab00_es2\\testo_es2.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
    }
    fscanf(fp,"%d",&N);
    for(i=0;i<N;i++){
        fscanf(fp,"%s",parola);
        trovate=conta(parola,n);
        printf("%d",trovate);
    }
    fclose(fp);
}

int conta(char S[20],int n){
    char v[10]={'a','e','i','o','u','A','E','I','O','U'};
    int  voc=0,t=0,i,j,z;

    for(i=0;i<(strlen(S)-n);i++){
        for(j=i;j<(n+i-1);j++){
            for(z=0;z<10;z++){
            if(S[j]==v[z]){
                voc++;
                if(voc==2){

                    t++;
                    voc=0;
                }
            }
            }
        }

    }
    return t;
}
