//
// Created by tanoc on 14/10/2019.
//
#include <stdio.h>
#define max 50

typedef struct{
    int base;
    int h;
    int area;
    int coord[2];
}Max;

void acquisisci_m(int m[][max],int nr,int nc,FILE *fp);
void cerca_rettangoli(int m[max][max],int nr,int nc);
void scrivi_struct(int indice,Max m[],int base,int altezza,int coordx,int coordy);

int main(){
    FILE *fp;
    int matrice[max][max],nr,nc;
    Max ma[3];

    fp=fopen("mappa.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file mappa\n");
        return -1;
    }
    fscanf(fp,"%d %d",&nr,&nc);
    acquisisci_m(matrice,nr,nc,fp);
    fclose(fp);
    cerca_rettangoli(matrice,nr,nc);
    return 0;
}

void acquisisci_m(int m[][max],int nr,int nc,FILE *fp){
    int i,j;

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            fscanf(fp,"%d",&m[i][j]);
        }
    }
}

void cerca_rettangoli(int m[max][max],int nr,int nc){
    int i,j,I,cont=0,h=1,Area=0,b=0,n;
    Max s[3]={0,1,0,0,0};

    for(i=0;i<nr;i++){
        //j<(nc+1) così se sono sul bordo e l'ultima casella è 1 controllo la successiva che è vuota ed entro nell'else if
        for(j=0;j<(nc+1);j++){
            if(m[i][j]==1){
                cont++;
            }else if(cont!=0){
                b=cont;
                cont=0;
                I=i;
                while(m[I+1][j-1]==1){
                    h++; I++;
                }
                if((b*h)>Area){
                    Area=b*h;
                    n=2;
                    scrivi_struct(n,s,b,h,j,i);
                }
            }
            if(b>s[0].base){
                n=0;
                scrivi_struct(n,s,b,h,j,i);
            }
            if(h>s[1].h){
                n=1;
                scrivi_struct(n,s,b,h,j,i);
            }
        }
        b=0;
        cont=0;
        h=1;
    }
    printf("max base: estr sup %d %d, base %d h %d area %d\n",s[0].coord[0],s[0].coord[1],s[0].base,s[0].h,s[0].area);
    printf("max h: estr sup %d %d, base %d h %d area %d\n",s[1].coord[0],s[1].coord[1],s[1].base,s[1].h,s[1].area);
    printf("max area: estr sup %d %d, base %d h %d area %d\n",s[2].coord[0],s[2].coord[1],s[2].base,s[2].h,s[2].area);
}

void scrivi_struct(int indice,Max m[],int base,int altezza,int coordx,int coordy){

    m[indice].base=base;
    m[indice].h=altezza;
    m[indice].area=m[indice].base*m[indice].h;
    m[indice].coord[1]=coordx-m[indice].base;
    m[indice].coord[0]=coordy;
}
