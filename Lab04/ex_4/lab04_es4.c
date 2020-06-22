//
// Created by tanoc on 09/11/2019.
//
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define maxr 1000
#define maxs 30

typedef enum{r_stampa,r_data,r_codice,r_partenza,r_arrivo,r_ricerca,r_fine}comando_e;

typedef struct{
    char codice_tratta[maxs];
    char partenza[maxs];
    char destinazione[maxs];
    char data[maxs];
    char ora_partenza[maxs];
    char ora_arrivo[maxs];
    int ritardo;
}Riga;



Riga Log[maxr];

comando_e leggicomando(char *comando);
void stampa(int nr);
void ordina_data(Riga *B,int l,int r);
void mergedata(Riga *B,int l,int q,int r);
void ordina_codice(Riga *B,int l,int r);
void mergecodice(Riga *B,int l,int q,int r);
void ordina_partenza(Riga *B,int l,int r);
void mergepartenza(Riga *B,int l,int q,int r);
void ordina_arrivo(Riga *B,int l,int r);
void mergearrivo(Riga *B,int l,int q,int r);
void strLow(char *s);
void menu(int nr);
void cambia_data(char *data);
int ric_dic(int a,int b,char *chiave);
void ricercal(int nr,char *chiave);



int main(){
    FILE *fp;
    int nr,i;

    fp=fopen("C:\\Users\\tanoc\\Desktop\\Algoritmi e programmazione\\progetto\\lab04\\corse_lab4.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
        return -1;
    }
    fscanf(fp,"%d",&nr);
    for(i=0;i<nr;i++){
        fscanf(fp,"%s %s %s %s %s %s %d",Log[i].codice_tratta,Log[i].partenza,Log[i].destinazione,
                             Log[i].data,Log[i].ora_partenza,Log[i].ora_arrivo,&Log[i].ritardo);
        cambia_data(Log[i].data);
    }
    fclose(fp);
    menu(nr);
    return 0;
}

void cambia_data(char *data){
    int g,m,a;
    sscanf(data,"%2d/%2d/%d",&g,&m,&a);
    sprintf(data,"%2d/%2d/%d",a,m,g);
}


comando_e leggicomando(char *comando){
    comando_e c;
    char *tabella[r_fine+1]={"stampa","data","codice"
                                ,"partenza","arrivo","ricerca","fine"};
    strLow(comando);
    c=r_stampa;
    while(c<=r_fine && strcmp(comando,tabella[c])!=0)
        c++;
    return c;
}

void strLow(char *s){
    int i;
    for(i=0;i<(int)strlen(s);i++){
        s[i]=tolower(s[i]);
    }
}

void menu(int nr){
    int continua=1,l=0,r=nr-1,dicotomica=0,ind;
    comando_e cmd;
    char comando[maxs],chiave[maxs];
    Riga *B=(Riga *)malloc(nr* sizeof(Riga));

    while(continua){
        printf("inserire comando tra \"stampa\",\"data\",\"codice\""
               ",\"partenza\",\"arrivo\",\"ricerca\",\"fine\"\n");
        scanf("%s",comando);
        cmd=leggicomando(comando);
        switch(cmd){
            case r_stampa:
                stampa(nr);
                break;
            case r_data:
                ordina_data(B,l,r);
                dicotomica=0;
                break;
            case r_codice:
                ordina_codice(B,l,r);
                dicotomica=0;
                break;
            case r_partenza:
                ordina_partenza(B,l,r);
                dicotomica=1;
                break;
            case r_arrivo:
                ordina_arrivo(B,l,r);
                dicotomica=0;
                break;
            case r_ricerca:
                printf("inserire citta da cercare\n");
                scanf("%s",chiave);
                if(dicotomica){
                    ind=ric_dic(l, r, chiave);
                    while(strncmp(Log[ind].partenza,chiave,strlen(chiave))==0){
                        cambia_data(Log[ind].data);
                        printf("%s %s %s %s %s %s %d\n",Log[ind].codice_tratta,Log[ind].partenza,Log[ind].destinazione,
                                Log[ind].data,Log[ind].ora_partenza,Log[ind].ora_arrivo,Log[ind].ritardo);
                        cambia_data(Log[ind].data);
                        ind++;
                }
                }else
                    ricercal(nr,chiave);
                break;
            case r_fine:
                continua=0;
                printf("arrivederci\n");
                break;
            default:
                printf("comando errato\n");
                break;
        }
    }
}


void stampa(int nr){
    int i;
    for(i=0;i<nr;i++){
        cambia_data(Log[i].data);
        printf("%s %s %s %s %s %s %d\n",Log[i].codice_tratta,Log[i].partenza,Log[i].destinazione,
               Log[i].data,Log[i].ora_partenza,Log[i].ora_arrivo,Log[i].ritardo);
        cambia_data(Log[i].data);
    }
}


void ordina_data(Riga *B,int l,int r){
    //mergesort
    int q;
    if(r<=l)
        return;
    q=(l+r)/2;
    ordina_data(B,l,q);
    ordina_data(B,q+1,r);
    mergedata(B,l,q,r);

}

void mergedata(Riga *B,int l,int q,int r){
    int i,j,k;

    i=l;
    j=q+1;
    for(k=l;k<=r;k++){
        if(i>q)
            B[k]=Log[j++];
        else if(j>r)
            B[k]=Log[i++];
        else if((strcmp(Log[i].data,Log[j].data))<0)
            B[k]=Log[i++];
        else if((strcmp(Log[i].data,Log[j].data))==0){
            printf("%s %s\n",Log[i].ora_partenza,Log[j].ora_partenza);
            if((strcmp(Log[i].ora_partenza,Log[j].ora_partenza))<0)
                B[k]=Log[i++];
            else
                B[k]=Log[j++];
        }
        else
            B[k]=Log[j++];
    }
    for(k=l;k<=r;k++)
        Log[k]=B[k];
}

void ordina_codice(Riga *B,int l,int r){
    int q;
    if(r<=l)
        return;
    q=(l+r)/2;
    ordina_codice(B,l,q);
    ordina_codice(B,q+1,r);
    mergecodice(B,l,q,r);
}

void mergecodice(Riga *B,int l,int q,int r){
    int i,k,j;

    i=l;
    j=q+1;
    for(k=l;k<=r;k++){
        if(i>q)
            B[k]=Log[j++];
        else if(j>r)
            B[k]=Log[i++];
        else if(strcmp(Log[i].codice_tratta,Log[j].codice_tratta)<=0)
            B[k]=Log[i++];
        else
            B[k]=Log[j++];
    }
    for(k=l;k<=r;k++)
        Log[k]=B[k];
}

void ordina_partenza(Riga *B,int l,int r){
    int q;
    if(r<=l)
        return;
    q=(l+r)/2;
    ordina_partenza(B,l,q);
    ordina_partenza(B,q+1,r);
    mergepartenza(B,l,q,r);
}

void mergepartenza(Riga *B,int l,int q,int r){
    int k,i,j;
    i=l;
    j=q+1;
    for(k=l;k<=r;k++){
        if(i>q)
            B[k]=Log[j++];
        else if(j>r)
            B[k]=Log[i++];
        else if((strcmp(Log[i].partenza,Log[j].partenza))<=0)
            B[k]=Log[i++];
        else
            B[k]=Log[j++];
    }
    for(k=l;k<=r;k++)
        Log[k]=B[k];
}

void ordina_arrivo(Riga *B,int l,int r){
    int q;
    if(r<=l)
        return;
    q=(l+r)/2;
    ordina_arrivo(B,l,q);
    ordina_arrivo(B,q+1,r);
    mergearrivo(B,l,q,r);
}

void mergearrivo(Riga *B,int l,int q,int r){
    int k,i,j;
    i=l;
    j=q+1;
    for(k=l;k<=r;k++){
        if(i>q)
            B[k]=Log[j++];
        else if(j>r)
            B[k]=Log[i++];
        else if((strcmp(Log[i].destinazione,Log[j].destinazione))<=0)
            B[k]=Log[i++];
        else
            B[k]=Log[j++];
    }
    for(k=l;k<=r;k++)
        Log[k]=B[k];
}

int ric_dic(int a,int b,char *chiave){
    int c,n;

    n=strlen(chiave);
    if((b-a)==0){
        if((strncmp(Log[a].partenza,chiave,n))==0)
            return a;
    }
    c=(a+b)/2;
    if((strcmp(Log[c].partenza,chiave))>=0)
        return (ric_dic(a,c,chiave));
    else
        return (ric_dic(c+1,b,chiave));


}
void ricercal(int nr,char *chiave){
    int i,n;

    n=(int)strlen(chiave);
    for(i=0;i<nr;i++){
        if((strncmp(Log[i].partenza,chiave,n))==0){
            cambia_data(Log[i].data);
            printf("%s %s %s %s %s %s %d\n",Log[i].codice_tratta,Log[i].partenza,Log[i].destinazione,
               Log[i].data,Log[i].ora_partenza,Log[i].ora_arrivo,Log[i].ritardo);
            cambia_data(Log[i].data);
        }

    }

}