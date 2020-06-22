//
// Created by tanoc on 23/10/2019.
//
#include <stdio.h>
#define MAXR 50

typedef struct{
    int base;
    int h;
    int area;
    int coord[2];
}Max;

void leggimatrice(int M[][MAXR],int *nr,int *nc);
int riconosciRegione(int M[][MAXR],int nr,int nc,int r,int c,int *b,int *h);
void scrivi_struct(int indice,Max m[],int base,int altezza,int coordx,int coordy);

int main(){
    int nr,nc,M[MAXR][MAXR]={0},n,i,j,b,h;
    Max max[3]={0,0,0,0,0};
    //nella struttura in 0 scrivo dati max base,1 dati max h,2 dati max area

    leggimatrice(M,&nr,&nc);
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            //riconosciRegione torna 1 se l'elemento considerato è estremo sup sinistro del rettangolo
            if(riconosciRegione(M,nr,nc,i,j,&b,&h)){
                if((b*h)>max[2].area){
                    n=2;
                    scrivi_struct(n,max,b,h,j,i);
                }
                if(b>max[0].base){
                    n=0;
                    scrivi_struct(n,max,b,h,j,i);
                    b=0;
                }
                if(h>max[1].h){
                    n=1;
                    scrivi_struct(n,max,b,h,j,i);
                    h=0;
                }
            }
        }
    }
    printf("max base: estr sup %d %d, base %d h %d area %d\n",max[0].coord[0],max[0].coord[1],max[0].base,max[0].h,max[0].area);
    printf("max h: estr sup %d %d, base %d h %d area %d\n",max[1].coord[0],max[1].coord[1],max[1].base,max[1].h,max[1].area);
    printf("max area: estr sup %d %d, base %d h %d area %d\n",max[2].coord[0],max[2].coord[1],max[2].base,max[2].h,max[2].area);

}


void leggimatrice(int M[][MAXR],int *nr,int *nc){
    int i,j;
    FILE *fp;

    fp=fopen("mappa_es1.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
    }
    fscanf(fp,"%d %d",nr,nc);
    for(i=0;i<*nr;i++){
        for(j=0;j<*nc;j++){
            fscanf(fp,"%d",&M[i][j]);
        }
    }
    fclose(fp);
}



int riconosciRegione(int M[][MAXR],int nr,int nc,int r,int c,int *b,int *h){
    int i,j,cont=0,I;
    *h=1;

    for(i=r;i<nr;i++){
        //j<(nc+1) così se sono sul bordo e l'ultima casella è 1 controllo la successiva ed entro nell'else if
        for(j=c;j<(nc+1);j++){
            if(M[i][j]==1 && j!=(nc+1)){
                cont++;
                //scrivo 2 nei punti dove sono già passato
                M[i][j]=2;
            }else if(cont!=0){
                *b=cont;
                I=i;
                //una volta controllata la base scendo lungo l'ultima colonna del rettangolo per controllare l'altezza
                while(M[++I][j-1]==1){
                    *h=*h+1;
                    M[I][j-1]=2;
                }
                return 1;
            }else{
                return 0;
            }
        }
    }
}

void scrivi_struct(int indice,Max m[],int base,int altezza,int coordx,int coordy){

    m[indice].base=base;
    m[indice].h=altezza;
    m[indice].area=m[indice].base*m[indice].h;
    m[indice].coord[1]=coordx;
    m[indice].coord[0]=coordy;
}
