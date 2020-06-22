//
// Created by tanoc on 06/11/2019.
//
#include <stdio.h>
#include <ctype.h>

char *cercaRegexp(char *src, char *regexp);
int conta(char *regexp);
int escludi(char *src,char *regexp,int l);
int corrispondenze(char *src,char *regexp);
int trova_singolo(char *src,char *regexp,int l);


int main(){
    int i;
    char regexp[50];
    char frase[50],parola[30];
    char *p=NULL,*c;

    printf("inserire espressione regolare\n");
   scanf("%s\n",regexp);
   gets(frase);
    c=frase;
    while((sscanf(c,"%s%n",parola,&i))>0 && p==NULL){
        c=c+i;
        p=cercaRegexp(parola,regexp);
    }

    if(p==NULL)
        printf("occorrenza non trovata\n");
    else {
        printf("%s",parola);
    }
}

char *cercaRegexp(char *src, char *regexp){
    int trovato=0,i=0,j=0,k;
    char *c=regexp;

    while(*src!='\0'){
        switch (*regexp){
            case '.':
                src++;
                regexp++;
                k=corrispondenze(src,regexp);
                j=j+k;
                //se k e' 1 ho trovato la parola
                if(k==-1)
                    return (char *)(src-regexp);
                else if(k==0)
                    regexp=c;
                else{
                    regexp=regexp+k;
                    src=src+k;
                }
                break;
            case '[':
                if(*(regexp+1)=='^'){
                    regexp+=2;
                    i=conta(regexp);
                    if(escludi(src,regexp,i)){
                        src++;
                        regexp=regexp+i+1;
                       k=corrispondenze(src,regexp);
                       j=j+k;
                       if(k==-1)
                           return (char*)(src-regexp);
                       else if(k==0)
                           regexp=c;
                       else {
                           regexp=regexp+k;
                           src=src+k;
                       }
                    }else{
                        return NULL;
                    }
                }else {
                    regexp++;
                    i = conta(regexp);
                    //la funzione trova singolo torna uno se trova almeno uno dei caratteri tra []
                    if (trova_singolo(src, regexp, i)) {
                        src++;
                        regexp = regexp + i + 1;
                        k = corrispondenze(src, regexp);
                        j = j + k + 1;
                        if (k == -1)
                            return (char *) (src - regexp);
                        else if (k == 0)
                            regexp = c;
                        else {
                            regexp = regexp + k;
                            src = src + k;
                        }
                        //se non trovo neanche un carattere di quelli tra [] torno NULL
                    } else
                        return NULL;
                }
                break;
            case '\\':
                if(*(regexp+1)=='A'){
                    regexp+=2;
                    if(isupper(*src)){
                        src++;
                        k=corrispondenze(src,regexp);
                        j=j+k;
                        if(k==-1)
                            return (char*)(src-regexp);
                        else if(k==0)
                            regexp=c;
                        else{
                          regexp=regexp+k;
                          src=src+k;
                          }
                    }
                }else{
                    regexp+=2;
                    if(islower(*src)){
                        src++;
                        k=corrispondenze(src,regexp);
                        j=j+k;
                        if(k==-1)
                            return (char*)(src-regexp);
                        else if(k==0)
                            regexp=c;
                        else{
                            regexp=regexp+k;
                            src=src+k;
                        }
                    }
                }
                break;
            default:
                while(*src==*regexp){
                    src++;
                    regexp++;
                    if(*regexp=='\0')
                        return (char *)(src-regexp);
                    else if(*regexp=='\\' || *regexp=='[' || *regexp=='.')
                        trovato=1;
                }
                if (trovato==0)
                    regexp=c;

        }
        if(j==0)
            src++;
    }
}

int conta(char *regexp){
    int l=0;
    while(*(regexp+l)!=']'){
        l++;
    }
    return l;
}


int escludi(char *src,char *regexp,int l){
    int i;
    //l e' il numero di caratteri da escludere
    for(i=0;i<l;i++){
        //se trovo un carattere che era da escludere torno 0
        if(*src==(*(regexp+i))){
            return 0;
        }
    }
    return 1;
}


int corrispondenze(char *src,char *regexp){
    int l=0;
    while(*regexp==*src){
        regexp++;
        src++;
        l++;
        //se arrivo alla fine di regexp ho trovato la parola e torno -1
        if(*regexp=='\0')
            return -1;
        //se regexp non e' ancora finita torno di quanto sono andato avanti
        else if(*regexp=='\\' || *regexp=='[' || *regexp=='.')
            return l;
    }
    return 0;
}

int trova_singolo(char *src,char *regexp,int l){
    int i;

    for(i=0;i<l;i++){
        if(*src==(*(regexp+i))){
            return 1;
        }
    }
    return 0;
}