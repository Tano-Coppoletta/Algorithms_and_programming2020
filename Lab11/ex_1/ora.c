//
// Created by tanoc on 14/01/2020.
//
#include "ora.h"


Ora Orascan(FILE *fp){
    Ora o;
    fscanf(fp,"%d:%d",&o.hh,&o.mm);
    return o;
}

void Oraprint(Ora ora){
    printf("%d:%d",ora.hh,ora.mm);
}