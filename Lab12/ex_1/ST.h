//
// Created by tanoc on 21/01/2020.
//

#ifndef PROGETTO_ST_H
#define PROGETTO_ST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 30

typedef struct st *ST;

ST STinit(int V);
void STinsert(ST st,char *s);
int STgetindex(ST st,char *s);
char *STsearchbyindex(ST st,int index);
void STfree(ST st);


#endif //PROGETTO_ST_H
