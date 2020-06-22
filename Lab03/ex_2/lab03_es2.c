//
// Created by tanoc on 23/10/2019.
//
#include <stdio.h>

void stampaCodifica(void *p,int size,int bigEndian);
void codifica(unsigned char *p,int z,int *c);

int main(){
    float af;
    double ad;
    long double ald;
    int bigEndian=0,n=1;
    unsigned char *p;

    p=(char*)&n;
    if(p[0]==1){
        bigEndian=0;
        printf("Architettura little endian\n");
    }else{
        bigEndian=1;
        printf("Architettura big endian\n");
    }

    printf("inserisci un numero\n");
    //uso mingwscanf perchè la scanf di default non supporta i float di 80 bit
    __mingw_scanf("%Lf",&ald);
    ad=(double)ald;
    af=(float)ald;

    stampaCodifica((void *)&af,sizeof(af),bigEndian);
    printf("\n");

    stampaCodifica((void *)&ad,sizeof(ad),bigEndian);
    printf("\n");

    stampaCodifica((void *)&ald,sizeof(ald),bigEndian);
}


void stampaCodifica(void *p,int size,int bigEndian){
    unsigned char *u=p;
    int i=0,z,contatore=0,*cont=&contatore;
//in base al valore size capisco quando stampare lo spazio
    if(size==4)
        z=9;
    else if(size==8)
        z=12;
    else
        z=16;
//se big endian parto dal primo byte (MSB) altrimenti parto dall'ultimo così stampo per primo il MSB
    if(bigEndian){
        for(i=0;i<size-1;i++){
            codifica(&u[i],z,cont);
        }
    }else{
        for(i=size-1;i>=0;i--){
            codifica(&u[i],z,cont);

        }
    }
}

void codifica(unsigned char *p,int z,int *c){
    int j,bit[8]={0};
    j=0;
    //codifico il numero con l'operatore di resto
    do{
        bit[j++]=*p%2;
        *p=*p/2;
    }while(*p>0);
    j=7;
    while(j>=0) {
        //se *c è uno stampo spazio per separare segno da esponente
        if(*c==1){
            printf(" ");
            //se *c è z stampo spazio per separare esponente da mantissa
        }else if(*c==z){
            printf(" ");
        }
        printf("%d", bit[j--]);
        *c+=1;
    }
}
