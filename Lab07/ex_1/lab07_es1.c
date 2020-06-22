//
// Created by tanoc on 26/11/2019.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int z;
    int s;
    int r;
    int t;
}Pietre;

int scrivi_pietre(Pietre *p);
void scrivi_occorrenze(int *mark,Pietre *p);
int disp_rip(int pos,char *val,char *sol,int k,int *mark);
int promising(char prec,char succ);

int main(){
    Pietre *p=(Pietre*)malloc(sizeof(*p));
    int i,l,mark[4];
    char val[4],*sol;

    l=scrivi_pietre(p);
    scrivi_occorrenze(mark,p);
    val[0]='z';val[1]='r';val[2]='t';val[3]='s';
    for(i=l;i>0;i--){
        sol=(char*)malloc(i* sizeof(char));
        if(disp_rip(0,val,sol,i,mark)>=1){
            printf("%d",i);
            break;
        }
    }
}


int scrivi_pietre(Pietre *p){
    FILE *fp;
  //  char file[30];
    int l;

    fp=fopen("C:\\Users\\tanoc\\Desktop\\Algoritmi e programmazione\\progetto\\lab07\\pietre.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
        return -1;
    }
    fscanf(fp,"%d%d%d%d",&p->z,&p->r,&p->t,&p->s);
    fclose(fp);
    l=p->s+p->z+p->r+p->t;
    return l;
}


void scrivi_occorrenze(int *mark,Pietre *p){
    mark[0]=p->z;
    mark[1]=p->r;
    mark[2]=p->t;
    mark[3]=p->s;
}

int disp_rip(int pos,char *val,char *sol,int k,int *mark){
    int i;

    if(pos>=k)
            return 1;

    for(i=0;i<4;i++){
        if(mark[i]>0){
           if(pos>0){
               if(promising(sol[pos-1],val[i])){
                   mark[i]--;
                   sol[pos]=val[i];
                   if(disp_rip(pos+1,val,sol,k,mark)>=1)
                       return 1;
                   mark[i]++;
               }
            }else{
               sol[pos]=val[i];
               mark[i]--;
                 if(disp_rip(pos+1,val,sol,k,mark)>=1)
                     return 1;
               mark[i]++;
           }
        }
    }
    return 0;
}

int promising(char prec,char succ) {
    int ok=0;
    switch (prec){
        case 'z':
            if(succ=='z' || succ=='r')
                ok=1;
            break;
        case 's':
            if(succ=='s' || succ=='t')
                ok=1;
            break;
        case 'r':
            if(succ=='s' || succ=='t')
                ok=1;
            break;
        case 't':
            if(succ=='z' || succ=='r')
                ok=1;
            break;
    }
    return ok;
}



