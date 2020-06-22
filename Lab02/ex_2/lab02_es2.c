//
// Created by tanoc on 15/10/2019.
//
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define max_r 1000
#define  max_s 30

typedef enum{r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine}comando_e;

typedef struct{
    char codice_tratta[max_s];
    char partenza[max_s];
    char destinazione[max_s];
    char data[max_s];
    char ora_partenza[max_s];
    char ora_arrivo[max_s];
    int ritardo;
}Riga;

comando_e leggiComando(char comando[]);
void strLow(char s[]);
void selezionaDati(Riga corse[],int nr);
void date(Riga corse[],int nr);
void cambia_data(char data[]);
void partenza(Riga corse[],int nr);
void capolinea(Riga corse[],int nr);
void ritardo(Riga corse[],int nr);
void ritardo_tot(Riga corse[],int nr);


int main(){
    FILE *fp;
    Riga corse[max_r];
    int nr,i;

    //apro file corse.txt
    fp=fopen("corse.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file\n");
        return -1;
    }
    //leggo numero di righe presenti nel file corse e lo scrivo in nr
    fscanf(fp,"%d",&nr);
    //per ogni riga del file leggo tutti i campi e li inserisco nella struct
    for(i=0;i<nr;i++){
        fscanf(fp,"%s %s %s %s %s %s %d",corse[i].codice_tratta,corse[i].partenza,corse[i].destinazione,
                corse[i].data,corse[i].ora_partenza,corse[i].ora_arrivo,&corse[i].ritardo);
    }
    fclose(fp);
    selezionaDati(corse,nr);
    return 0;
}

comando_e leggiComando(char comando[]){
    comando_e c;
    char *tabella[r_fine+1]={
            "date","partenza",
            "capolinea","ritardo","ritardo_tot","fine"
    };
    //la funzione strLow scrive in minuscolo il comando inserito dall'utente
    strLow(comando);
    c=r_date;
    while(c<=r_fine && strcmp(comando,tabella[c])!=0){
        c++;
    }
    return c;
}


void strLow(char s[]){
    int i;
    for(i=0;i<(int)strlen(s);i++){
        s[i]=tolower(s[i]);
    }
}

void selezionaDati(Riga corse[],int nr){
    int continua=1;
    comando_e cmd;
    char comando[30];

    while(continua){
        printf("inserire comando tra:\"date\" \"partenza\""
               "\"capolinea\" \"ritardo\" \"ritardo_tot\" e \"fine\"");
        //leggo comando inserito dall'utente e lo passo alla funzione leggiComando
        scanf("%s",comando);
        cmd=leggiComando(comando);
    switch(cmd){
        case r_date: date(corse,nr);
             break;
        case r_partenza: partenza(corse,nr);
             break;
        case r_capolinea: capolinea(corse,nr);
             break;
        case r_ritardo: ritardo(corse,nr);
             break;
        case r_ritardo_tot: ritardo_tot(corse,nr);
             break;
        case r_fine: continua=0;
                printf("Arrivederci\n");
             break;
        default:
            printf("comando errato\n");
            break;
    }
    }
}

void date(Riga corse[],int nr){
    int i;
    char data_inserita1[max_s],data_inserita2[max_s];

    printf("inserire date da controllare\n");
    scanf("%s %s",data_inserita1,data_inserita2);
    //per usare la strcmp scrivo le date come aa/mm/gg, per farlo uso la funzione cambia_data
    cambia_data(data_inserita1);
    cambia_data(data_inserita2);
    for(i=0;i<nr;i++){
        //richiamo la funzione cambia_data per ogni data che controllo
        cambia_data(corse[i].data);
        //se la data presente nell'iesima posizione della struct si trova nell'intervallo inserito dall'utente stampo
        if(strcmp(corse[i].data,data_inserita1)>=0 && strcmp(corse[i].data,data_inserita2)<=0){
            cambia_data(corse[i].data);
            printf("%s %s %s %s %s %s %d\n",corse[i].codice_tratta,corse[i].partenza,corse[i].destinazione,
                    corse[i].data,corse[i].ora_partenza,corse[i].ora_arrivo,corse[i].ritardo);
        }else{
            //riscrivo la data nel formato gg/mm/aa
            cambia_data(corse[i].data);
        }
    }
}

void cambia_data(char data[]){
    int g,m,a;
    sscanf(data,"%d/%d/%d",&g,&m,&a);
    sprintf(data,"%d/%d/%d",a,m,g);
}

void partenza(Riga corse[],int nr){
    int i;
    char fermata[max_s];

    printf("inserire fermata da controllare\n");
    scanf("%s",fermata);
    //assumo che nel file le tratte siano scritte in minuscolo
    strLow(fermata);
    //per ogni fermata controllo la corrispondenza
    for(i=0;i<nr;i++){
      if(strcmp(fermata,corse[i].partenza)==0){
          printf("%s %s %s %s %s %s %d\n",corse[i].codice_tratta,corse[i].partenza,
                  corse[i].destinazione,corse[i].data,corse[i].ora_partenza,corse[i].ora_arrivo,corse[i].ritardo);
      }
    }
}
void capolinea(Riga corse[],int nr){
    int i;
    char fermata[max_s];

    printf("inserire fermata da controllare\n");
    scanf("%s",fermata);
    //assumo che nel file le tratte siano scritte in minuscolo
    strLow(fermata);
    for(i=0;i<nr;i++){
        if(strcmp(fermata,corse[i].destinazione)==0){
            printf("%s %s %s %s %s %s %d\n",corse[i].codice_tratta,corse[i].partenza,corse[i].destinazione,
                    corse[i].data,corse[i].ora_partenza,corse[i].ora_arrivo,corse[i].ritardo);
        }
    }
}

void ritardo(Riga corse[],int nr){
    int i;
    char data_inserita1[max_s],data_inserita2[max_s];

    printf("inserire date da controllare\n");
    scanf("%s %s",data_inserita1,data_inserita2);
    //uso cambia_date per scrivere le date nel formato aa/mm/gg per la strcmp
    cambia_data(data_inserita1);
    cambia_data(data_inserita2);
    for(i=0;i<nr;i++){
        cambia_data(corse[i].data);
        if(strcmp(corse[i].data,data_inserita1)>=0 && strcmp(corse[i].data,data_inserita2)<=0) {
            //riscrivo la data nel formato gg/mm/aa
            cambia_data(corse[i].data);
            if (corse[i].ritardo != 0) {
                    printf("%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione,
                           corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
                }
        }else{
            cambia_data(corse[i].data);
        }
    }
}


void ritardo_tot(Riga corse[],int nr){
    int tot=0,i;
    char codice[max_s];

    printf("inserire codice tratta da controllare\n");
    scanf("%s",codice);
    for(i=0;i<nr;i++){
        if(strcmp(codice,corse[i].codice_tratta)==0){
            tot+=corse[i].ritardo;
        }
    }
    printf("per la corsa con codice %s il ritardo complessivo e' %d\n",codice,tot);

}