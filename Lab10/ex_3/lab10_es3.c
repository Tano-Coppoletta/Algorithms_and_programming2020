//
// Created by tanoc on 11/01/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxs 100
#define maxd 5
#define DD 10
#define DP 20
#define DBG 0

typedef struct{
    char *nome;
    int tipo;
    int dir_ingr, dir_usc;
    int primo, finale;
    float valore;
    int difficolta;
}Elemento;


typedef struct{
    Elemento e[maxd];
    int num_e;
    float val;
    int diff;
}Diagonale;

typedef struct{
    Diagonale *d;
    float v;
    int di;
}Programma;

int alloca_elem(Elemento **e);
void free_elem(Elemento *e,int N);
void insertion_sort(Elemento *e,int l,int r);
int appetibilita(Elemento e1,Elemento e2);
Programma *programmainit(void);
void programma_greedy(Programma *p,Elemento *e,int N);
void genera_diag(Diagonale *d,Elemento *e,int N,int newdp,int pos,int diffp);
int posiziona_primo(Diagonale *d,Elemento *e,int N,int tipo);
void posiziona_ultimo(Diagonale *d,Elemento *e,int N,int i,int pos,int bonus,int diffp);


int main(){
    Elemento *e=NULL;
    Programma *p=programmainit();
    int i,N;

    N=alloca_elem(&e);
    insertion_sort(e,0,N-1);
#if DBG
    for(i=0;i<N;i++){
        printf("%s %d %d %d %d %d %f %d\n",e[i].nome,e[i].tipo,e[i].dir_ingr,e[i].dir_usc,e[i].primo,
               e[i].finale,e[i].valore,e[i].difficolta);
    }
    for(i=0;i<3;i++){
        printf("%d %f\n",p->d[i].diff,p->d[i].val);
    }
#endif
    programma_greedy(p,e,N);

    for(i=0;i<3;i++){
        printf("DIAGONALE: ");
        for(int j=0;j<p->d[i].num_e;j++){
            printf("%s ",p->d[i].e[j].nome);
        }
        printf("\nDifficolta': %d\nValore: %f\n",p->d[i].diff,p->d[i].val);
    }
    printf("valore tot: %f difficolta': %d",p->v,p->di);
    free_elem(e,N);
}

int alloca_elem(Elemento **e){
    int N,i;
    Elemento *ep;
    char stringa[maxs];
    FILE *fp=fopen("elementi.txt","r");
    if(fp==NULL){
        printf("errore file\n");
        exit(0);
    }
    fscanf(fp,"%d",&N);
    ep=malloc(N* sizeof(*ep));
    if(ep==NULL)
        exit(1);
    for(i=0;i<N;i++){
        fscanf(fp,"%s %d %d %d %d %d %f %d\n",stringa,&ep[i].tipo,&ep[i].dir_ingr,&ep[i].dir_usc,&ep[i].primo,
                &ep[i].finale,&ep[i].valore,&ep[i].difficolta);
        ep[i].nome=strdup(stringa);
    }
    *e=ep;
    return N;
}

void free_elem(Elemento *e,int N){
    int i;
    for(i=0;i<N;i++)
        free(e[i].nome);
    free(e);
}

void insertion_sort(Elemento *e,int l,int r){
    //vettore ordinato secondo una funzione di appetibilità
    int i,j;
    Elemento x;
    for(i=l+1;i<=r;i++){
        x=e[i];
        j=i-1;
        while(j>=l && appetibilita(x,e[j])){
            e[j+1]=e[j];
            j--;
        }
        e[j+1]=x;
    }
}

int appetibilita(Elemento e1,Elemento e2){
    //appetibilitò calcolata come rapporto tra valore e difficoltà
    float a1,a2;
    a1=e1.valore/(float)e1.difficolta;
    a2=e2.valore/(float)e2.difficolta;
    if(a1>a2)
        return 1;
    return 0;
}

Programma *programmainit(void){
    Programma *p=malloc(sizeof(*p));
    if(p==NULL)
        exit(1);
    p->d=malloc(3* sizeof(*(p->d)));
    p->di=0;
    p->v=0;
    for(int i=0;i<3;i++){
        p->d[i].diff=0;
        p->d[i].val=0;
    }
    return p;
}

void programma_greedy(Programma *p,Elemento *e,int N){
    int i,newdp=DP;
    for(i=2;i>=0;i--){
        genera_diag(&(p->d[i]),e,N,newdp,i,p->di);
        p->v+=p->d[i].val;
        p->di+=p->d[i].diff;
        newdp-=p->d[i].diff;
    }

}

void genera_diag(Diagonale *d,Elemento *e,int N,int newdp,int pos,int diffp){
    int i,j=1,last=0;
    if(pos==2){
        last=posiziona_primo(d,e,N,-1);
        for(i=0;i<N  && j<5;i++){
            if(j==4 || (e[i].difficolta+d->diff)>DD){
                posiziona_ultimo(d,e,N,last,j,1,diffp);
                break;
            }else{
                if(e[i].finale==0 && e[i].dir_usc==d->e[j-1].dir_ingr && (d->diff+e[i].difficolta)<DD){
                    d->e[j++]=e[i];
                    d->diff+=e[i].difficolta;
                    d->num_e++;
                    d->val+=e[i].valore;
                    last=i;
                    i=0;
                }
            }
        }
    }else if(pos==1){
        //posiziono il primo di tipo 2
        last=posiziona_primo(d,e,N,2);
        for(i=0;i<N && j<5 && d->diff<(DP-d->diff);i++){
            //con j=0 ho inserito elemento acrobatico, faccio lo stesso con j=1
            while(j==1){
                if(e[i].finale==0 && e[i].dir_ingr==e[j-1].dir_usc && e[i].tipo>0 && (d->diff+e[i].difficolta)<DD){
                    d->e[j++]=e[i];
                    d->diff+=e[i].difficolta;
                    d->num_e++;
                    d->val+=e[i].valore;
                    last=i;
                    i=-1;
                }
                i++;
            }
            if(j==4 || (e[i].difficolta+d->diff)>DD){
                posiziona_ultimo(d,e,N,last,j,0,diffp);
                break;
            }else{
                if(e[i].finale==0 && e[i].dir_usc==d->e[j-1].dir_ingr && (d->diff+e[i].difficolta)<DD){
                    d->e[j++]=e[i];
                    d->diff+=e[i].difficolta;
                    d->num_e++;
                    d->val+=e[i].valore;
                    last=i;
                    i=0;
                }
            }
        }

    }else{
        //posiziono il primo elemento acrobatico
        last=posiziona_primo(d,e,N,-1);
        for(i=0;i<N && j<5 && d->diff<newdp;i++){
            if(j==4 || (e[i].difficolta+d->diff)>DD){
                posiziona_ultimo(d,e,N,last,j,0,diffp);
                break;
            }else{
                if(e[i].finale==0 && e[i].dir_usc==d->e[j-1].dir_ingr && (d->diff+e[i].difficolta)<DD){
                    d->e[j++]=e[i];
                    d->diff+=e[i].difficolta;
                    d->num_e++;
                    d->val+=e[i].valore;
                    last=i;
                    i=0;
                }
            }
        }

    }
}

int posiziona_primo(Diagonale *d,Elemento *e,int N,int tipo){
    int i;
//tipo mi dice se voglio prendere un elemento acrobatico specifico o qualsiasi
    for(i=0;i<N;i++){
        if(tipo>=0){
            if(e[i].primo==0 && e[i].dir_ingr==1 && e[i].tipo==tipo){
                d->e[0]=e[i];
                d->diff+=e[i].difficolta;
                d->num_e=1;
                d->val+=e[i].valore;
               // printf("%s\n",d->e[0].nome);
                break;
            }
        }else{
            if(e[i].primo==0 && e[i].dir_ingr==1 && e[i].tipo>0){
                d->e[0]=e[i];
                d->diff+=e[i].difficolta;
                d->num_e=1;
                d->val+=e[i].valore;
               // printf("%s\n",d->e[0].nome);
                break;

            }
        }
    }
    return i;
}

void posiziona_ultimo(Diagonale *d,Elemento *e,int N,int i,int pos,int bonus,int diffp){
    int j;
    for(j=0;j<N;j++){
        if(e[j].finale==1 && e[j].dir_ingr==e[i].dir_usc && (d->diff+e[j].difficolta)<=DD && diffp<DD){
            d->e[pos]=e[j];
            d->diff+=e[j].difficolta;
            d->num_e++;
            d->val+=e[j].valore;
            //printf("%s",d->e[pos].nome);
            break;
        }
    }
    if(bonus){
        if(d->e[pos].difficolta>=8){
            d->val*=(float)1.5;
        }
    }
}
