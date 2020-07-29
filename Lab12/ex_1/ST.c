//
// Created by tanoc on 21/01/2020.
//
#include "ST.h"

typedef char stringa[max];

struct st{
    stringa *a;
    int size,maxN;
};


ST STinit(int V){
    int i;
    ST st=malloc(sizeof(*st));
    if(st==NULL)
        exit(1);
    st->a=malloc(V* sizeof(stringa));
    if(st->a==NULL)
        exit(1);
    for(i=0;i<V;i++)
        strcpy(st->a[i],"\0");
    st->size=0;
    st->maxN=V;
    return st;
}

void STinsert(ST st,char *s){
    //non controllo se supero maxN perchè so a priori quanti elementi ci sono in st
    int i=st->size;
    strcpy(st->a[i],s);
    st->size++;
}

int STgetindex(ST st,char *s){
    int i;
    for(i=0;i<st->size;i++){
        if(strcmp(st->a[i],s)==0)
            return i;
    }
    return -1;
}

char *STsearchbyindex(ST st,int index){
    return st->a[index];
}

void STfree(ST st){
    free(st->a);
    free(st);
}


