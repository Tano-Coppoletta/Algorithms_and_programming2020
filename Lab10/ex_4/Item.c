//
// Created by tanoc on 13/01/2020.
//
#include "Item.h"

Key keyget(Item *pval){
    return (pval->id_elab);
}

Item Itemscan(FILE *fp){
    Item i;
    fscanf(fp,"%s %s",i.id_elab,i.id_rete);
    return i;
}
void Itemshow(Item val){
    printf("%s",val.id_elab);
}

Item ItemsetNULL(void){
    Item i;
    strcpy(i.id_rete,"\0");
    strcpy(i.id_elab,"\0");
    return i;
}


int keycmp(Key k1,Key k2){
    //se k1 viene dopo torno 1
    if(strcmp(k1,k2)>0)
        return 1;
    else if(strcmp(k1,k2)==0)
        return 0;
    return -1;
}
