//
// Created by tanoc on 14/01/2020.
//
#include "data.h"

int Datacmp(Data d1,Data d2){
    if(d1.a!=d2.a)
        return d1.a-d2.a;
    if(d1.m!=d2.m)
        return d1.m-d2.m;
    if(d1.g!=d2.g)
        return d1.g-d2.g;
    return 0;
}

Data Datascan(FILE *fp){
    Data d;
    fscanf(fp,"%d/%d/%d",&d.a,&d.m,&d.g);
    return d;
}

void Dataprint(Data d){
    printf("%d/%d/%d",d.a,d.m,d.g);
}

Data datasetNULL(){
    Data d;
    d.a=d.m=d.g=-1;
    return d;
}

Data datasetMAX(){
    Data d;
    d.a=d.m=d.g=INT_MAX;
    return d;
}