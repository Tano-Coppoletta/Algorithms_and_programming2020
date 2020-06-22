//
// Created by tanoc on 23/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 51

typedef enum{tastiera, file, Ricerca,estrai_cod, estrai_date, stampa, fine}comando_e;

typedef struct{
    int g,m,a;
}Data;


typedef struct{
    char *codice;
    char *nome;
    char *cognome;
    Data data;
    char *via;
    char *citta;
    int cap;
}Item;

typedef struct node *link;

struct node{
    Item  val;
    link next;
};

Item leggi(void);
comando_e leggicomando(char *comando);
link new_node(link next,Item val);
link inserisci_ord(link h,Item val);
Data getdata(Item val);
char *getcodice(Item val);
int confronta_data(Data d1,Data d2);
link acquisisci_file(link h);
link ricerca(link h);
link estrai_codice(link *hp);
void cerca_data(link *h);
link cerca_primadata(link *h,Data d1,Data d2);
void stampa_file(link h);
void free_list(link h);
void free_stringhe(Item d);

int main(){
    link head=NULL,x;
    Item d;
    comando_e cmd;
    char comando[max];
    int continua=1;

    while(continua) {
        printf("inserire comando tra 'tastiera', 'file', 'ricerca', 'codice', 'data', 'stampa', 'fine'\n");
        scanf("%s", comando);
        cmd = leggicomando(comando);
        switch (cmd){
            case tastiera:
                d=leggi();
                head=inserisci_ord(head,d);
                break;
            case file:
                head=acquisisci_file(head);
                break;
            case Ricerca:
                x=ricerca(head);
                if(x!=NULL) {
                    printf("%s %s %s %d/%d/%d %s %s %d\n", x->val.codice, x->val.nome, x->val.cognome, x->val.data.g,
                           x->val.data.m, x->val.data.a, x->val.via, x->val.citta, x->val.cap);
                }else printf("elemento non trovato\n");
                break;
            case estrai_cod:
                if(head!=NULL){
                    x=estrai_codice(&head);
                    if(x==NULL)
                        printf("elemento non trovato\n");
                    else{
                        d=x->val;
                        printf("%s %s %s %d/%d/%d %s %s %d\n", d.codice, d.nome, d.cognome, d.data.g,
                               d.data.m, d.data.a, d.via, d.citta, d.cap);
                        free_stringhe(x->val);
                        free(x);
                    }
                }else printf("la lista e' vuota\n");
                break;
            case estrai_date:
                cerca_data(&head);
                break;
            case stampa:
                stampa_file(head);
                break;
            case fine:
                continua=0;
                free_list(head);
                break;
            default:
                printf("comando non valido\n");
                break;
        }
    }
}

Item leggi(void){
    Item riga;
    char cod[max],nome[max],cognome[max],via[max],citta[max];
    printf("Inserire: codice nome cognome data via citta cap\n");
    scanf("%s %s %s %d/%d/%d %s %s %d",cod,nome,cognome,
            &riga.data.g,&riga.data.m,&riga.data.a,via,citta,&riga.cap);
    riga.codice=strdup(cod);
    riga.nome=strdup(nome);
    riga.cognome=strdup(cognome);
    riga.via=strdup(via);
    riga.citta=strdup(citta);
    return riga;
}


comando_e leggicomando(char *comando){
    char *scelte[fine+1]={"tastiera", "file", "ricerca","codice", "data", "stampa", "fine"};
    comando_e c=tastiera;
    while(c<=fine && strcmp(scelte[c],comando)!=0){
        c++;
    }
    return c;
}

link new_node(link next,Item val){
    link x=malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    x->val=val;
    x->next=next;
    return x;
}

link inserisci_ord(link h,Item val){
    link x,p;
    Data k=getdata(val);
    //se la lista e' vuota o l'elemento e' il primo in base all'ordine aggiungo il nodo in testa
    if(h==NULL || confronta_data(getdata(h->val),k)<0)
        return new_node(h,val);
    for(x=h->next,p=h;x!=NULL && confronta_data(k,getdata(x->val))<0;p=x,x=x->next);
    p->next=new_node(x,val);
    return h;

}

Data getdata(Item val){
    Data k;
    k.g=val.data.g;
    k.m=val.data.m;
    k.a=val.data.a;
    return k;
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

void stampa_file(link h){
    FILE *fp;
    link x;
    char file[max];

    printf("inserire nome file\n");
    scanf("%s",file);
    fp=fopen(file,"w");
    if(fp==NULL)
        printf("errore nell'apertura del file\n");
    for(x=h;x!=NULL;x=x->next){
        fprintf(fp,"%s %s %s %d/%d/%d %s %s %d\n",x->val.codice,x->val.nome,x->val.cognome,x->val.data.g,
                x->val.data.m,x->val.data.a,x->val.via,x->val.citta,x->val.cap);
    }
    fclose(fp);
}


link acquisisci_file(link h){
    FILE *fp;
    Item riga;
    char file[max],cod[max],nome[max],cognome[max],via[max],citta[max];
    printf("inserire nome file\n");
    scanf("%s",file);
    fp=fopen(file,"r");

    while(fscanf(fp,"%s %s %s %d/%d/%d %s %s %d",cod,nome,cognome,
                  &riga.data.g,&riga.data.m,&riga.data.a,via,citta,&riga.cap)>=0){
        riga.codice=strdup(cod);
        riga.nome=strdup(nome);
        riga.cognome=strdup(cognome);
        riga.via=strdup(via);
        riga.citta=strdup(citta);
        h=inserisci_ord(h,riga);
    }
    fclose(fp);
    return h;
}


link ricerca(link h){
    char codice[max];
    link x;

    printf("inserire codice da cercare\n");
    scanf("%s",codice);
    for(x=h;x!=NULL;x=x->next){
        if(strcmp(getcodice(x->val),codice)==0){
            return x;
        }
    }
    return NULL;
}




char *getcodice(Item val){
    char *c;
    c=val.codice;
    return c;
}


link estrai_codice(link *hp){
    link *xp,t=NULL;
    char codice[max];

    printf("inserire codice da estrarre\n");
    scanf("%s",codice);
    for(xp=hp;(*xp)!=NULL;xp=&((*xp)->next)){
        if(strcmp(getcodice((*xp)->val),codice)==0){
            t=*xp;
            *xp=(*xp)->next;
            break;
        }
    }
    return t;
}

void cerca_data(link *h){
    Data d1,d2;
    link t;
    int continua=1;

    printf("inserire intervallo nel formato gg/mm/aaaa\n");
    scanf("%d/%d/%d %d/%d/%d",&d1.g,&d1.m,&d1.a,&d2.g,&d2.m,&d2.a);
    while(continua){
        if(*h==NULL){
            printf("lista vuota\n");
            return;
        }
        t=cerca_primadata(h,d1,d2);
        if(t==NULL){
            continua=0;
        }else{
            printf("%s %s %s %d/%d/%d %s %s %d\n", t->val.codice, t->val.nome, t->val.cognome, t->val.data.g,
                   t->val.data.m, t->val.data.a, t->val.via, t->val.citta,t->val.cap);
            //free del nodo
            free_stringhe(t->val);
            free(t);
        }
    }
}


link cerca_primadata(link *h,Data d1,Data d2){
    link *xp,t=NULL;
    Data d3;
    for(xp=h;(*xp)!=NULL && confronta_data(getdata((*xp)->val),d1)>=0;xp=&((*xp)->next)){
        d3=getdata((*xp)->val);
        if(confronta_data(d1,d3)<=0 && confronta_data(d3,d2)<=0){
            t=*xp;
            *xp=(*xp)->next;
            break;
        }
    }
    return t;
}


void free_list(link h){
    if(h==NULL)
        return;
    free_list(h->next);
    free_stringhe(h->val);
    free(h);
}


void free_stringhe(Item d){
    free(d.codice);
    free(d.nome);
    free(d.cognome);
    free(d.via);
    free(d.citta);
}