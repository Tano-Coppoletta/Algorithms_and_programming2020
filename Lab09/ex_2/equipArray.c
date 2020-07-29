//
// Created by tanoc on 11/12/2019.
//
#include "equipArray.h"
#define MAX 10

struct equipArray_s{
    int indici[MAX];
    int N;
};


equipArray_t equipArray_init(){
    equipArray_t equip;
    equip=malloc(sizeof(struct equipArray_s));
    equip->N=0;
    return equip;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->N;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i;
    for(i=0;i<equipArray->N;i++){
        fprintf(fp,"      ");
        //stampo con indice di invArray
        invArray_printByIndex(fp,invArray,equipArray->indici[i]);
    }
}

/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    char ogg[LEN];
    int i,j,scelta;
    printf("1 > aggiungi oggetto\n2 > togli oggetto\n");
    scanf("%d",&scelta);
    if(scelta==1){
        printf("inserire nome oggetto da aggiungere\n");
        scanf("%s",ogg);
        //cerco indice nel vettore inventario
        i=invArray_searchByName(invArray,ogg);
        if(i==-1)
            printf("oggetto assente\n");
        else {
            //aggiungo ogg e incremento num oggetti equipaggiati
            equipArray->indici[equipArray->N]=i;
            equipArray->N+=1;
        }
    }else if(scelta ==2){
        printf("inserire nome oggetto da eliminare\n");
        scanf("%s",ogg);
        i=invArray_searchByName(invArray,ogg);
        if(i==-1)
            printf("oggetto non equipaggiato\n");
        else{
            for(j=0;j<equipArray->N;j++){
                if(equipArray->indici[j]==i){
                    while(j!=equipArray->N){
                        equipArray->indici[j]=equipArray->indici[j+1];
                        j++;
                    }
                    break;
                }
            }
            equipArray->N--;
        }
    }else
        printf("comando errato\n");
}

/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->indici[index];
}