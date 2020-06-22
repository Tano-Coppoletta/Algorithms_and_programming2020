//
// Created by tanoc on 08/10/2019.
//
#include <stdio.h>
#define max 200

typedef struct{
    char originale[max];
    char  codifica[max];
}Dizionario;

void copia_d(FILE *diz,Dizionario d[],int s);
void cifra(char riga[],FILE *ricodifica,int S,Dizionario d[]);

int main(){
    Dizionario d[10];
    char riga[max];
    int S;
    FILE *rc;
    FILE *diz;
    FILE *sorgente;

    //apro file ricodifica
    rc=fopen("ricodifica_es2.txt","w");
    if(rc==NULL){
        printf("errore nell'aoertura del file rc\n");
    }
    //apro dizionario
    diz=fopen("dizionario_es2.txt","r");
    if(diz==NULL){
        printf("errore nell'apertura del file dizionario\n");
    }
    //apro file sorgente
    sorgente=fopen("sorgente_es2.txt","r");
    if(sorgente==NULL){
        printf("errore nell'apertura del file sorgente\n");
    }
    //scrivo numero di righe del dizionario in S
    fscanf(diz,"%d\n",&S);
    //uso la funziona copia_d per scrivere il dizionario dentro la struct
    copia_d(diz,d,S);
    fclose(diz);
    //prendo ogni riga del file sorgente e uso la funzione cifra
    while(fgets(riga,max,sorgente)!=NULL){
        cifra(riga,rc,S,d);
    }
    fclose(sorgente);
    fclose(rc);
    return 0;


}


void copia_d(FILE *diz,Dizionario d[],int s){
    int i;
    //per ogni riga prendo due stringhe che corrispondono rispettivamente alla parola codificata e all'originale
    for(i=0;i<s;i++){
        fscanf(diz,"%s %s",d[i].codifica,d[i].originale);
    }
}

void cifra(char riga[],FILE *ricodifica,int S,Dizionario d[]){
    int i=0,h=0,j=0,trovato=0,fine_riga=0;
    //primo for che controlla la riga carattere per carattere, flag che diventa uno se la riga finisce
    for(i=0;i<max && fine_riga==0;i++){
        //for che controlla le righe del dizionario, flag che diventa uno se trovo la sequenza di caratteri nel dizionario
        for(j=0;j<S && trovato==0;j++){
            //se trovo una corrispondenza tra i caratteri controllo carattere successivo della riga e della parola del dizionario
            while(riga[i]==d[j].originale[h] && trovato==0) {
                //se il carattere h+1 della parola del dizionario è '\0' ho trovato la corrispondenza,il flag diventa 1
                if(d[j].originale[h+1]=='\0'){
                    trovato = 1;
                    //pongo h=-1 perchè viene incrementato subito dopo
                    h=-1;
                    //diminusco i di 1 perchè viene incrementato subito dopo
                    i-=1;
                }
                i++;
                h++;
            }
            //se non ho trovato la parola nel dizionario torno indietro sulla riga del file sorgente e al primo carattere del dizionario
            if(trovato==0){
                i=i-h;
                h=0;
            }else{
                fprintf(ricodifica,"%s",d[j].codifica);
            }
        }
        if(riga[i+1]=='\0'){
            fine_riga=1;

        }
        //se dopo aver controllato ogni parola del dizionario non ho trovato corrispondenze stampo il carattere
        if(trovato==0){
            fprintf(ricodifica,"%c",riga[i]);
        }
        trovato=0;
    }
}