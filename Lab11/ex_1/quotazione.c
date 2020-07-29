//
// Created by tanoc on 14/01/2020.
//
#include "quotazione.h"

Quota generaQ(Data d,float val,int num){
    Quota q;
    q.d=d;
    q.n=num;
    q.vn=(val*(float)num);
    q.q=(q.vn/(float)num);
    return q;
}

void Qprint(Quota q){
    Dataprint(q.d);
    printf(" %f\n",q.q);
}

k Kget(Quota q){
    return q.d;
}

int Kcompare(k k1,k k2){
    return (Datacmp(k1,k2));
}

Quota aggiornaQ(Quota q1,int num,float val){
    q1.n+=num;
    q1.vn=q1.vn+(val*(float)num);
    q1.q=(q1.vn/(float)q1.n);
    return q1;
}

int minQ(Quota q1,Quota q2){
    if(q1.q<q2.q)
        return 1;
    return -1;
}

int maxQ(Quota q1,Quota q2){
    if(q1.q>q2.q)
        return 1;
    return 0;
}

int confrontaF(Quota q1,float *q2){
     if(q1.q<(*q2))
         return 1;
     return 0;
}

Quota QsetNULL(){
    Quota q;
    q.d=datasetNULL();
    q.vn=-1;
    q.n=-1;
    q.q=-1;
    return q;
}
