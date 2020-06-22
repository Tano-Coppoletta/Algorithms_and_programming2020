//
// Created by tanoc on 27/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#define Npietre 4

int max_rip;

typedef struct{
    int valore;
    int occ;
}Pietre;

int scrivi_occorrenze(Pietre *p);
int disp_rip(int pos,char *val,char *sol,int k,Pietre *p,int curr_val,int *best_val,char *best_sol,int trova_max);
int promising(char prec,char succ);
int controlla(char *sol,int k);
int ripetizioni(char sol[],int pos);




int main(){
    Pietre *p=(Pietre*)malloc(Npietre*sizeof(*p));
    int l,i,best_val=-1,max=0;
    char *sol,val[4],*best;

    val[0]='z';val[1]='r';val[2]='t';val[3]='s';
    //scrivi occorrenze torna la somma di tutte le occorrenze
    l=scrivi_occorrenze(p);
    //allocazione dinamica di best in cui scrivo la soluzione migliore
    best=(char*)malloc(l* sizeof(char));
   for(i=l;i>0;i--){
       sol=(char*)malloc(i* sizeof(char));
       //se disp_rip mi torna 1 significa che la sol di dim i e' la più grande che rispetta le regole, dunque e' quella che ha val massimo
       if(disp_rip(0,val,sol,i,p,0,&best_val,best,max)==1)
           break;
        free(sol);
   }
    printf("valore: %d\n",best_val);
    for(max=0;max<i;max++){
        printf("%c",best[max]);
    }
    free(best);
    free(p);
}


int scrivi_occorrenze(Pietre *p){
    FILE *fp;
    int i,l=0;
    fp=fopen("p2.txt","r");
    if(fp==NULL)
        printf("errore file\n");
    for(i=0;i<4;i++){
        fscanf(fp,"%d",&p[i].occ);
        l+=p[i].occ;
    }
    for(i=0;i<4;i++)
        fscanf(fp,"%d",&p[i].valore);
    fscanf(fp,"%d",&max_rip);
    fclose(fp);
    return l;
}


int disp_rip(int pos,char *val,char *sol,int k,Pietre *p,int curr_val,int *best_val,char *best_sol,int trova_max) {
    int i;

    if(pos>=k && controlla(sol,k)==1){
        if((*best_val<curr_val)){
            for(i=0;i<k;i++)
                best_sol[i]=sol[i];
            *best_val=curr_val;
            return 1;
        }
        return trova_max;
    }
    for(i=0;i<4;i++){
        if(p[i].occ>0){
            //tratto caso pos=0 a parte
            if(pos>0){
                //se il valore e' promettente lo prendo altrimenti vado avanti nel for
                if(promising(sol[pos-1],val[i])){
                        sol[pos]=val[i];
                        //se prendendo val[i] l'elemento si ripete piu' di max_rip volte lo scarto
                        if(ripetizioni(sol,pos)){
                            p[i].occ--;
                            curr_val+=p[i].valore;
                            trova_max=disp_rip(pos+1,val,sol,k,p,curr_val,best_val,best_sol,trova_max);
                            p[i].occ++;
                            curr_val-=p[i].valore;
                        }
                }

            }else{
                sol[pos]=val[i];
                p[i].occ--;
                curr_val += p[i].valore;
               trova_max= disp_rip(pos + 1, val, sol, k, p, curr_val, best_val, best_sol,trova_max);
                p[i].occ++;
                curr_val -= p[i].valore;
            }
        }
    }
    return trova_max;
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


int controlla(char sol[],int k){
    int i,z=0,s=0;
//controllo se ho più s che z
    for(i=0;i<k;i++){
        if(sol[i]=='z')
            z++;
        else if(sol[i]=='s')
            s++;
    }
    if(s>=z)
        return 1;
    return 0;
}



int ripetizioni(char sol[],int pos){
    int occ=2,i;
    if(sol[pos]==sol[pos-1]){
        for(i=pos-max_rip;i>=0 && i<pos-1;i++){
            if(sol[i]==sol[pos])
                occ++;
        }
        if(occ>max_rip)
            return 0;
    }
    return 1;

}