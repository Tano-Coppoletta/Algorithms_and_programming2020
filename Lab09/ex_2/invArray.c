//
// Created by tanoc on 11/12/2019.
//
#include "invArray.h"


struct invArray_s{
    inv_t *ogg;
    int N;
};

invArray_t invArray_init(){
    invArray_t inv;
    inv=malloc(sizeof(struct invArray_s));
    if(inv==NULL)
        exit(1);
    inv->ogg=malloc(sizeof(inv_t));
    if(inv->ogg==NULL)
        exit(1);
    inv->N=0;
    return inv;
}

void invArray_free(invArray_t invArray){
    free(invArray->ogg);
    free(invArray);
}

void invArray_read(FILE *fp, invArray_t invArray){
    int i;
    fscanf(fp,"%d\n",&invArray->N);
    invArray->ogg=realloc(invArray->ogg,(invArray->N)* sizeof(inv_t));

    if(invArray->ogg==NULL)
        exit(1);

    for(i=0;i<invArray->N;i++){
        inv_read(fp,&invArray->ogg[i]);
    }
}

void invArray_print(FILE *fp, invArray_t invArray){
    //stampa vettore inventario
    int i;
    for(i=0;i<invArray->N;i++){
        inv_print(fp,&invArray->ogg[i]);
    }
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    //stampa di un oggetto con indice
    inv_print(fp,&invArray->ogg[index]);
}

/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &(invArray->ogg[index]);
}

/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    for(i=0;i<invArray->N;i++){
        if(strcmp(invArray->ogg[i].nome,name)==0)
            return i;
    }
    return -1;
}

