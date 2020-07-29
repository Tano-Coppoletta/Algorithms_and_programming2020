//
// Created by tanoc on 14/01/2020.
//

#ifndef PROGETTO_QUOTAZIONE_H
#define PROGETTO_QUOTAZIONE_H

#include "data.h"

typedef struct{
    Data d;
    float q;
    int n;
    float vn;
}Quota;

typedef Data k;

k Kget(Quota q);
int Kcompare(k k1,k k2);

void Qprint(Quota q);
Quota QsetNULL();
Quota generaQ(Data d,float val,int num);
Quota aggiornaQ(Quota q1,int num,float val);
int minQ(Quota q1,Quota q2);
int maxQ(Quota q1,Quota q2);
int confrontaF(Quota q1,float *q2);

#endif //PROGETTO_QUOTAZIONE_H
