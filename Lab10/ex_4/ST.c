//
// Created by tanoc on 13/01/2020.
//
#include "ST.h"

struct symboltable{
    Item *a;
    int maxN,size;
};


ST STinit(int maxN){
    ST st;
    int i;
    st=malloc(sizeof(*st));
    if(st==NULL)
        exit(1);
    st->a=malloc(maxN* sizeof(Item));
    for(i=0;i<maxN;i++)
        st->a[i]=ItemsetNULL();
    st->maxN=maxN;
    st->size=0;
    return st;
}

void STfree(ST st){
    free(st->a);
    free(st);
}


static int duplicato(ST st,Item val){
    if(STsearch(st,keyget(&val))>=0)
        return 1;
    return 0;
}


int STinsert(Item val,ST st){
    int i=st->size;
    if(i!=0 && duplicato(st,val))
        return 0;
    if(i>=st->maxN){
        st->a=realloc(st->a,(2*st->maxN)* sizeof(Item));
        if(st->a==NULL)
            exit(1);
        st->maxN*=2;
    }
    st->a[i]=val;
    st->size++;
    return 1;
}

int STsearch(ST st,Key k){
    int i;
    if(st->size==0)
        return -1;
    for(i=0;i<st->size;i++){
        if(keycmp(k,keyget(&st->a[i]))==0)
            return i;
    }
    return -1;
}

Item *STsearchbyindex(ST st,int index){
    return &st->a[index];
}



