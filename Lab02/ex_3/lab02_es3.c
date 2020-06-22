//
// Created by tanoc on 16/10/2019.
//
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define max 5
#define max_l 200
#define max_p 25

//nella struttura scrivo tutte le sequenze e per ognuna quante volte ho trovato una corrispondenza nel testo
typedef struct{
    char sequenza[max];
    int cont;
}seq;

void strLow(char s[max_p]);
int controllastringa(seq s[],char parola[],int nr,int np);
void trova_sequenza(char p[],seq S[],int nr,int np);

int main(){
    char parola[max_l];
    seq s[20];
    FILE *fp;
    FILE *tx;
    int i,nr,np=0;

    fp=fopen("sequenze.txt","r");
    if(fp==NULL){
        printf("errore nell'apertura del file sequenze\n");
        return -1;
    }
    //prendo numero righe file
    fscanf(fp,"%d",&nr);
    for(i=0;i<nr;i++){
        //scrivo sequenze dentro struct
        fscanf(fp,"%s",s[i].sequenza);
        strLow(s[i].sequenza);
        s[i].cont=0;
    }
    fclose(fp);

    tx=fopen("C:\\Users\\tanoc\\Desktop\\Algoritmi e programmazione\\progetto\\lab02\\testo_es3.txt","r");
    if(tx==NULL){
        printf("errore nell'apertura del file\n");
        return -2;
    }
    while(fscanf(tx,"%s",parola)==1){
        np++;
        //scrivo in minuscolo ogni parola del testo con la funzione strLow
        strLow(parola);
        //controllastringa torna 1 se trova un apostrofo, così so che devo incrementare np
        if(controllastringa(s,parola,nr,np)==1)
            np++;
    }
}


void strLow(char s[max_p]){
    int i;
    for(i=0;i<strlen(s);i++){
        s[i]=tolower(s[i]);
    }
}

int controllastringa(seq s[],char parola[],int nr,int np){
    int i,j,z,split=0;
    char new_p[max_l]={"\0"};

    for(i=0;i<(int)strlen(parola);i++){
        if(ispunct(parola[i])) {
            //se trovo un apostrofo in mezzo alla parola la divido in due e chiamo due volte la funzione trova_sequenza
            for(j=0;j<i;j++){
                new_p[j]=parola[j];
            }
            trova_sequenza(new_p,s,nr,np);
            for(j=(i+1),z=0;j<(int)strlen(parola);z++,j++){
                new_p[z]=parola[j];
            }
            split++;
            trova_sequenza(new_p,s,nr,np+1);
            break;
            //il -2 è dovuto al fatto che non conto il \0 e l'ultimo carattere dato che non può trovarsi un apostrofo alla fine della parola
        }else if(i==strlen(parola)-2){
            trova_sequenza(parola,s,nr,np);
            break;
            }
        }
    return split;
    }

void trova_sequenza(char p[],seq S[],int nr,int np){
    int i,j,h=0;

    //per ogni lettera della parola cerco corrispondenza con sequenza
    for(i=0;i<(int)strlen(p);i++){
        for(j=0;j<nr;j++){
            while(p[i]==S[j].sequenza[h]){
                h++;
                i++;
                //se h è uguale alla lungheza della sequenza ho trovato una corrispondenza
                if(h==strlen(S[j].sequenza)){
                    if(S[j].cont<=10){
                        printf("la sequenza %s e' presente in %s parola n. %d\n",S[j].sequenza,p,np);
                        S[j].cont++;
                    }
                }
            }
            i-=h;
            h=0;
        }
    }
}