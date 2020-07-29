//
// Created by tanoc on 30/12/2019.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int z,s,r,t;
}Pietre;


void scrivi_pietre(Pietre *p);
void allocam(int *****m,Pietre p);
int fx(Pietre p,int ****mz,int ****ms,int ****mt,int ****mr);
int fz(Pietre p,int ****mz,int ****ms,int ****mt,int ****mr,int max);
int ft(Pietre p,int ****mz,int ****ms,int ****mt,int ****mr,int max);
int fr(Pietre p,int ****mz,int ****ms,int ****mt,int ****mr,int max);
int fs(Pietre p,int ****mz,int ****ms,int ****mt,int ****mr,int max);
void freem(int ****m,Pietre p);


int main(){
    Pietre *p=malloc(sizeof(*p));
    int l,****mz,****ms,****mt,****mr;
    scrivi_pietre(p);
    //alloco 4 matrici 4x4
    allocam(&mz,*p);
    allocam(&ms,*p);
    allocam(&mt,*p);
    allocam(&mr,*p);
    l=fx(*p,mz,ms,mt,mr);
    printf("%d",l);
    //deallocazione matrici
    freem(mz,*p);freem(ms,*p);freem(mt,*p);freem(mr,*p);
}

void scrivi_pietre(Pietre *p){
    FILE *fp;

    fp=fopen("pietre.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
    }
    fscanf(fp,"%d%d%d%d",&p->z,&p->r,&p->t,&p->s);
    fclose(fp);
}

void allocam(int *****m,Pietre p){
    int ****mp,i,j,z,a;
    mp=malloc((p.z+1)* sizeof(int***));
    for(i=0;i<=p.z;i++){
        mp[i]=malloc((p.r+1)*sizeof(int**));
    }
    for(i=0;i<=p.z;i++){
        for(j=0;j<=p.r;j++){
            mp[i][j]=malloc((p.s+1)*sizeof(int*));
        }
    }
    for(i=0;i<=p.z;i++){
        for(j=0;j<=p.r;j++){
            for(z=0;z<=p.s;z++){
                mp[i][j][z]=malloc((p.t+1)*sizeof(int));
            }
        }
    }
    //inizializzo a -1
    for(i=0;i<=p.z;i++){
        for(j=0;j<=p.r;j++){
            for(z=0;z<=p.s;z++){
                for(a=0;a<=p.t;a++){
                    mp[i][j][z][a]=-1;
                }
            }
        }
    }
    *m=mp;
}

void freem(int ****m,Pietre p){
    int i,j,z;
    for(i=0;i<p.z;i++){
        for(j=0;j<=p.r;j++){
            for(z=0;z<=p.s;z++){
                free(m[i][j][z]);
            }
        }
    }
    for(i=0;i<p.z;i++){
        for(j=0;j<p.r;j++){
            free(m[i][j]);
        }
    }
    for(i=0;i<p.z;i++)
        free(m[i]);
    free(m);
}

int fx(Pietre p,int ****mz,int ****ms,int ****mt,int ****mr){
    int l1,l2,l3,l4;
    l1=fz(p,mz,ms,mt,mr,0);
    l2=fr(p,mz,ms,mt,mr,0);
    l3=ft(p,mz,ms,mt,mr,0);
    l4=fs(p,mz,ms,mt,mr,0);
    if(l1>l2 && l1>l3 && l1>l4){
        return l1;
    }else if(l2>l3 && l2>l4)
        return l2;
    else if(l3>l4)
        return l3;
    return l4;
}

int fz(Pietre p,int ****mz,int ****ms,int ****mt,int ****mr,int max){
    int l=0,l1=0;
    if(p.z<=0)
        return 0;
    //se ho già calcolato la lunghezza la ritorno
    if(mz[p.z][p.r][p.s][p.t]!=-1){
        return mz[p.z][p.r][p.s][p.t];
    }
    //decremento e calcolo le due lunghezze
    p.z--;
    l=1+fz(p,mz,ms,mt,mr,max);
    l1=1+fr(p,mz,ms,mt,mr,max);
    //scelgo la l max e la salvo sulla matrice
    if(l>l1) {
        max = l;
        mz[p.z+1][p.r][p.s][p.t]=l;
    }
    else{
        max=l1;
        mz[p.z+1][p.r][p.s][p.t]=l1;
    }
    return max;
}



int ft(Pietre p,int ****mz,int ****ms,int ****mt,int ****mr,int max) {
    int l, l1;
    if (p.t <= 0)
        return 0;
    if (mt[p.z][p.r][p.s][p.t] != -1)
        return mt[p.z][p.r][p.s][p.t];
    p.t--;
    l = 1 + fz(p, mz, ms, mt, mr, max);
    l1 = 1 + fr(p, mz, ms, mt, mr, max);
    if (l > l1) {
        mt[p.z][p.r][p.s][p.t+1] = l;
        if(max<l)
            max=l;
    } else {
        mt[p.z][p.r][p.s][p.t+1] = l;
        if(max<l1)
            max=l1;
    }
    return max;

}

int fr(Pietre p,int ****mz,int ****ms,int ****mt,int ****mr,int max){
    int l,l1;
    if(p.r<=0)
        return 0;
    if(mr[p.z][p.r][p.s][p.t]!=-1)
        return mr[p.z][p.r][p.s][p.t];
    p.r--;
    l=1+fs(p,mz,ms,mt,mr,max);
    l1=1+ft(p,mz,ms,mt,mr,max);
    if(l>l1){
        mr[p.z][p.r+1][p.s][p.t]=l;
        if(max<l)
            max=l;
    }else{
        mr[p.z][p.r+1][p.s][p.t]=l1;
        if(max<l1)
            max=l1;
    }
    return max;
}
int fs(Pietre p,int ****mz,int ****ms,int ****mt,int ****mr,int max){
    int l,l1;
    if(p.s<=0)
        return 0;
    if(ms[p.z][p.r][p.s][p.t]!=-1)
        return ms[p.z][p.r][p.s][p.t];
    p.s--;
    l=1+fs(p,mz,ms,mt,mr,max);
    l1=1+ft(p,mz,ms,mt,mr,max);
    if(l>l1){
        ms[p.z][p.r][p.s+1][p.t]=l;
        if(max<l)
            max=l;
    }else{
        ms[p.z][p.r][p.s+1][p.t]=l1;
        if(max<l1)
            max=l1;
    }
    return max;
}