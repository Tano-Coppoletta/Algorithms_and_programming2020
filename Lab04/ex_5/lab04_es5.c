//
// Created by tanoc on 13/11/2019.
//
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define maxr 1000
#define maxs 31

typedef enum{r_stampa,r_data,r_codice,r_partenza,r_arrivo,r_ricerca,r_fine}comando_e;

typedef struct{
    int g;
    int m;
    int a;
}Data;

typedef struct{
    char codice_tratta[maxs];
    char partenza[maxs];
    char destinazione[maxs];
    Data data;
    char ora_partenza[maxs];
    char ora_arrivo[maxs];
    int ritardo;
}Riga;



comando_e leggicomando(char *comando);
void strLow(char *s);
void menu(int nr);
void ordina(Riga **ord,int nr,comando_e cmd);
int confronta(Riga *x1,Riga *x2,comando_e cmd);
int confronta_date(Data d1,Data d2);
void stampa(Riga **ord,int nr);
int dicotomica(int l,int r,char *c,int n,Riga **ord);
void lineare(int nr,int n,char *c);

Riga Log[maxr];

int main(){
    FILE *fp;
    int nr,i;

    fp=fopen("log.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
        return -1;
    }
    fscanf(fp,"%d",&nr);
    for(i=0;i<nr;i++){
        fscanf(fp,"%s %s %s %d/%d/%d %s %s %d",Log[i].codice_tratta,Log[i].partenza,Log[i].destinazione,
               &Log[i].data.g,&Log[i].data.m,&Log[i].data.a,Log[i].ora_partenza,Log[i].ora_arrivo,&Log[i].ritardo);
        strLow(Log[i].partenza);
    }
    fclose(fp);
    menu(nr);
    return 0;
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
    comando_e cmd;
    char comando[maxs],ordinamento[maxs],chiave[maxs];
    int continua=1,i,d=0,p=0,c=0,a=0,ind,n;
    Riga *ord_data[maxr],*ord_codice[maxr],*ord_partenza[maxr],*ord_arrivo[maxr];

    //inizializzo vettori di puntatori a struct
    for(i=0;i<nr;i++)
        ord_data[i]=ord_codice[i]=ord_partenza[i]=ord_arrivo[i]=&Log[i];

    while(continua){
        printf("inserire comando tra \"stampa\",\"data\",\"codice\""
               ",\"partenza\",\"arrivo\",\"ricerca\",\"fine\"\n");
        scanf("%s",comando);
        cmd=leggicomando(comando);
        switch (cmd){
            case r_stampa:
                printf("scegli ordinamento tra : data, codice, partenza, arrivo,nessuno\n");
                scanf("%s",ordinamento);
                if(strcmp(ordinamento,"data")==0)
                    //gli if ==1 servono a capire se il file e' già stato ordinato secondo la chiave richiesta
                    if(d==1)
                        stampa(ord_data,nr);
                    else printf("il file non e' ancora stato ordinato per data\n");
                else if(strcmp(ordinamento,"codice")==0)
                    if(c==1)
                        stampa(ord_codice,nr);
                    else printf("il file non e' ancora stato ordinato per codice\n");
                else if(strcmp(ordinamento,"partenza")==0)
                    if(p==1)
                        stampa(ord_partenza,nr);
                    else printf("il file non e' ancora stato ordinato per partenza\n");
                else if(strcmp(ordinamento,"arrivo")==0)
                    if(a==1)
                        stampa(ord_arrivo,nr);
                    else printf("il file non e' ancora stato ordinato per arrivo\n");
                else if(strcmp(ordinamento,"nessuno")==0){
                    for(i=0;i<nr;i++){
                        printf("%s %s %s %d/%d/%d %s %s %d\n",Log[i].codice_tratta,Log[i].partenza,
                                Log[i].destinazione,Log[i].data.g,Log[i].data.m,Log[i].data.a,Log[i].ora_partenza,
                                Log[i].ora_arrivo,Log[i].ritardo);
                    }
                }else
                    printf("scelta non valida\n");
                break;
            case r_data:
                ordina(ord_data,nr,cmd);
                d=1;
                break;
            case r_codice:
                ordina(ord_codice,nr,cmd);
                c=1;
                break;
            case r_partenza:
                ordina(ord_partenza,nr,cmd);
                p=1;
                break;
            case r_arrivo:
                ordina(ord_arrivo,nr,cmd);
                a=1;
                break;
            case r_ricerca:
                printf("inserire chiave da cercare\n");
                scanf("%s",chiave);
                strLow(chiave);
                n=strlen(chiave);
                //p==1 se ho ordinato in base alla partenza
                if(p){
                   ind=dicotomica(0,nr-1, chiave,n,ord_partenza);
                   if(ind==-1)
                       printf("chiave non trovata\n");
                   else{
                       //non devo controllare al di fuori del vettore di struct quindi inserisco ind<nr
                       while(ind<nr && strncmp(ord_partenza[ind]->partenza,chiave,n)==0){
                           printf("%s %s %s %d/%d/%d %s %s %d\n",ord_partenza[ind]->codice_tratta,ord_partenza[ind]->partenza,
                                   ord_partenza[ind]->destinazione,ord_partenza[ind]->data.g,ord_partenza[ind]->data.m,
                                   ord_partenza[ind]->data.a,ord_partenza[ind]->ora_partenza,ord_partenza[ind]->ora_arrivo,
                                   ord_partenza[ind]->ritardo);
                           ind++;
                       }
                   }
                }else{
                    lineare(nr,n,chiave);
                }

                break;
            case r_fine:
                printf("arrivederci\n");
                continua=0;
                break;
            default:
                printf("inserire comando valido\n");
                break;
        }
    }
}


void ordina(Riga **ord,int nr,comando_e cmd){
    //insertion sort
    Riga *x;
    int i,j;
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
        r=confronta_date(x1->data,x2->data);
        if(r==0)
            r=strcmp(x1->ora_partenza,x2->ora_partenza);
        return r;
    }else if(cmd==2){
        return strcmp(x1->codice_tratta,x2->codice_tratta);
    }else if(cmd==3){
        return strcmp(x1->partenza,x2->partenza);
    }else if(cmd==4){
        return strcmp(x1->destinazione,x2->destinazione);

    }
}

int confronta_date(Data d1,Data d2){
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


int dicotomica(int l,int r,char *c,int n,Riga **ord){
    int q;

    //caso terminale o trovo la chiave o torno -1
    if((l-r)==0){
        if(strncmp(ord[l]->partenza,c,n)==0)
            return l;
        else return -1;
    }
    q=(l+r)/2;
    if(strncmp(ord[q]->partenza,c,n)>=0)
        return dicotomica(l,q,c,n,ord);
    else
        return dicotomica(q+1,r,c,n,ord);
}

void lineare(int nr,int n,char *c){
    int i;
    //scandisco tutto il vettore di struct, ogni volta che trovo una corrispondenza la stampo
    for(i=0;i<nr;i++){
        if(strncmp(Log[i].partenza,c,n)==0){
            printf("%s %s %s %d/%d/%d %s %s %d\n",Log[i].codice_tratta,Log[i].partenza,Log[i].destinazione,
                   Log[i].data.g,Log[i].data.m,Log[i].data.a,Log[i].ora_partenza,Log[i].ora_arrivo,Log[i].ritardo);
        }
    }
}