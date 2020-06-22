//
// Created by tanoc on 16/11/2019.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define maxs 31

typedef enum{r_stampa,r_data,r_codice,r_partenza,r_arrivo,r_ricerca,r_lettura,r_fine}comando_e;

typedef struct{
    int g;
    int m;
    int a;
}Data;

typedef struct{
    char *codice_tratta;
    char *partenza;
    char *destinazione;
    Data data;
    char ora_partenza[6];
    char ora_arrivo[6];
    int ritardo;
}Riga;


int leggi(FILE *fp,Riga **l);
comando_e leggicomando(char *comando);
void strLow(char *s);
void menu(Riga *l,int nr);
void ordina(Riga **ord,int nr,comando_e cmd);
int confronta(Riga *x1,Riga *x2,comando_e cmd);
int confronta_data(Data d1,Data d2);
void stampa(Riga **ord,int nr);
int dicotomica(int l,int r,char *chiave,int n,Riga **ord);
void ricerca_lineare(Riga *l,char *chiave,int n,int nr);
void freestruct(Riga *l,int nr);


int main(){
    FILE *fp;
    Riga *l;
    int nr;

    fp=fopen("corse_lab5.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
        return -1;
    }
    nr=leggi(fp,&l);
    menu(l,nr);
    return 0;
}

int leggi(FILE *fp,Riga **l){
    int N,i;
    Riga *r;
    char cod[30],part[30],dest[30];

    fscanf(fp,"%d",&N);
    r=(Riga *)malloc(N* sizeof(Riga));
    if(l==NULL)
        exit(1);
    for(i=0;i<N;i++){
        fscanf(fp,"%s %s %s %d/%d/%d %s %s %d",cod,part,dest,&r[i].data.g,&r[i].data.m,
                &r[i].data.a,r[i].ora_partenza,r[i].ora_arrivo,&r[i].ritardo);
        r[i].codice_tratta=strdup(cod);
        r[i].partenza=strdup(part);
        r[i].destinazione=strdup(dest);
        if(r[i].codice_tratta==NULL || r[i].partenza==NULL || r[i].destinazione==NULL)
            exit(1);
    }
    *l=r;
    fclose(fp);
    return N;
}

void menu(Riga *l,int nr){
    Riga **ord_data,**ord_part,**ord_dest,**ord_cod;
    int continua=1,i,d=0,p=0,a=0,c=0,ind,n;
    comando_e cmd;
    char comando[maxs],ordinamento[maxs],chiave[maxs],file[maxs];
    FILE *fp;

//allocazione dinamica vettori di puntatori a struct
    ord_data=(Riga **)malloc(nr* sizeof(Riga *));
    ord_part=(Riga **)malloc(nr* sizeof(Riga *));
    ord_dest=(Riga **)malloc(nr* sizeof(Riga *));
    ord_cod=(Riga **)malloc(nr* sizeof(Riga *));
    //inizializzazione
    for(i=0;i<nr;i++)
        ord_cod[i]=ord_data[i]=ord_part[i]=ord_dest[i]=&l[i];


    while(continua){
        printf("inserire comando tra: stampa, data, codice, partenza, arrivo, ricerca, lettura, fine\n");
        scanf("%s",comando);
        strLow(comando);
        cmd=leggicomando(comando);
        switch (cmd){
            case r_stampa:
                printf("scegliere l'ordinamento tra: data, codice, partenza, arrivo, nessuno\n");
                scanf("%s",ordinamento);
                strLow(ordinamento);
                if(strcmp(ordinamento,"data")==0) {
                    if (d == 1)
                        stampa(ord_data, nr);
                    else printf("ordinamento per data non disponibile\n");
                }else if(strcmp(ordinamento,"codice")==0){
                        if(c==1)
                            stampa(ord_cod,nr);
                        else printf("ordinamento per codice non disponibile\n");
                }else if(strcmp(ordinamento,"partenza")==0){
                    if(p==1)
                        stampa(ord_part,nr);
                    else printf("ordinamento per partenza non disponibile\n");
                }else if(strcmp(ordinamento,"arrivo")==0){
                    if(a==1)
                        stampa(ord_dest,nr);
                    else printf("ordinamento per arrivo non disponibile\n");
                }else if(strcmp(ordinamento,"nessuno")==0){
                    for(i=0;i<nr;i++){
                        printf("%s %s %s %d/%d/%d %s %s %d\n",l[i].codice_tratta,l[i].partenza,l[i].destinazione,
                               l[i].data.g,l[i].data.m,l[i].data.a,l[i].ora_partenza,l[i].ora_arrivo,l[i].ritardo);
                    }
                }else printf("scelta non valida\n");
                break;
            case r_data:
                ordina(ord_data,nr,r_data);
                d=1;
                break;
            case r_codice:
                ordina(ord_cod,nr,r_codice);
                c=1;
                break;
            case r_partenza:
                ordina(ord_part,nr,r_partenza);
                p=1;
                break;
            case r_arrivo:
                ordina(ord_dest,nr,r_arrivo);
                a=1;
                break;
            case r_ricerca:
                printf("inserire chiave da cercare\n");
                scanf("%s",chiave);
                n=(int)strlen(chiave);
                if(p==1){
                    ind=dicotomica(0,nr-1,chiave,n,ord_part);
                    if(ind==-1)
                        printf("chiave non trovata\n");
                    else{
                        //non devo controllare al di fuori del vettore di struct quindi inserisco ind<nr
                    while(ind<nr && strncmp(ord_part[ind]->partenza,chiave,n)==0){
                        printf("%s %s %s %d/%d/%d %s %s %d\n",ord_part[ind]->codice_tratta,ord_part[ind]->partenza,
                                ord_part[ind]->destinazione,ord_part[ind]->data.g,ord_part[ind]->data.m,ord_part[ind]->data.a,
                                ord_part[ind]->ora_partenza,ord_part[ind]->ora_arrivo,ord_part[ind]->ritardo);
                        ind++;
                    }
                    }
                }else
                    ricerca_lineare(l,chiave,n,nr);
                break;
            case r_lettura:
                printf("inserire nome file\n");
                scanf("%s",file);
                fp=fopen(file,"r");
                if(fp==NULL) {
                    printf("errore nell'apertura del file %s\n",file);
                }else{
                    //libero struttura
                    freestruct(l,nr);
                    //leggo nuovo file e alloco struct dinamica
                    nr=leggi(fp,&l);
                    ord_data=(Riga **)realloc(ord_data,nr*sizeof(Riga *));
                    ord_part=(Riga **)realloc(ord_part,nr* sizeof(Riga *));
                    ord_dest=(Riga **)realloc(ord_dest,nr* sizeof(Riga *));
                    ord_cod=(Riga **)realloc(ord_cod,nr* sizeof(Riga *));
                }
                for(i=0;i<nr;i++)
                    ord_cod[i]=ord_data[i]=ord_part[i]=ord_dest[i]=&l[i];
                break;
            case r_fine:
                continua=0;
                break;
            default:
                printf("comando non valido\n");
        }

    }

}


void strLow(char *s){
    int i;
    for(i=0;i<(int)strlen(s);i++){
        s[i]=tolower(s[i]);
    }
}

comando_e leggicomando(char *comando){
    char *scelte[r_fine+1]={"stampa","data","codice","partenza",
                         "arrivo","ricerca","lettura","fine"};
    comando_e c=r_stampa;
    while(c<=r_fine && strcmp(scelte[c],comando)!=0)
        c++;
    return c;
}


void ordina(Riga **ord,int nr,comando_e cmd){
    //insertion sort
    int i,j;
    Riga *x;
    for(i=1;i<nr;i++){
        x=ord[i];
        j=i-1;
        while(j>=0 && confronta(x,ord[j],cmd)<0){
            ord[j+1]=ord[j];
            j--;
        }
        ord[j+1]=x;
    }
}

int confronta(Riga *x1,Riga *x2,comando_e cmd){
    int r;
    if(cmd==1){
        r=confronta_data(x1->data,x2->data);
        if(r==0)
            return (strcmp(x1->ora_partenza,x2->ora_partenza));
    }else if(cmd==2)
        return strcmp(x1->codice_tratta,x2->codice_tratta);
    else if(cmd==3)
        return strcmp(x1->partenza,x2->partenza);
    else if(cmd==4)
        return strcmp(x1->destinazione,x2->destinazione);
}

int confronta_data(Data d1,Data d2){

    if(d1.a!=d2.a)
        return (d1.a-d2.a);
    else if(d1.m!=d2.m)
        return (d1.m-d2.m);
    else if(d1.g!=d2.g)
        return (d1.g-d2.g);
    return 0;
}

void stampa(Riga **ord,int nr){
    int i;

    for(i=0;i<nr;i++){
        printf("%s %s %s %d/%d/%d %s %s %d\n",ord[i]->codice_tratta,ord[i]->partenza,ord[i]->destinazione,
                ord[i]->data.g,ord[i]->data.m,ord[i]->data.a,ord[i]->ora_partenza,ord[i]->ora_arrivo,ord[i]->ritardo);
    }
}


int dicotomica(int l,int r,char *chiave,int n,Riga **ord){
    int q;

    if((l-r)==0){
        if(strncmp(ord[l]->partenza,chiave,n)==0)
            return l;
        else return -1;
    }
    q=(l+r)/2;
    if(strncmp(ord[q]->partenza,chiave,n)>=0)
        return dicotomica(l,q,chiave,n,ord);
    else
        return dicotomica(q+1,r,chiave,n,ord);
}

void ricerca_lineare(Riga *l,char *chiave,int n,int nr){
    int i;
    for(i=0;i<nr;i++){
        if(strncmp(chiave,l[i].partenza,n)==0){
            printf("%s %s %s %d/%d/%d %s %s %d\n",l[i].codice_tratta,l[i].partenza,l[i].destinazione,
                    l[i].data.g,l[i].data.m,l[i].data.a,l[i].ora_partenza,l[i].ora_arrivo,l[i].ritardo);
        }
    }
}

void freestruct(Riga *l,int nr){
    int i;

    for(i=0;i<nr;i++){
        free(l[i].codice_tratta);
        free(l[i].partenza);
        free(l[i].destinazione);
    }
    free(l);
}