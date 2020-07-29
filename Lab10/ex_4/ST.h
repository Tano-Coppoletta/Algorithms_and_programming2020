//
// Created by tanoc on 13/01/2020.
//
#ifndef PROGETTO_ST_H
#define PROGETTO_ST_H

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
//ADT prima classe tabella di simboli
typedef struct symboltable *ST;

ST STinit(int maxN);
void STfree(ST st);
int STinsert(Item val,ST st);
int STsearch(ST st,Key k);
Item *STsearchbyindex(ST st,int index);


#endif //PROGETTO_ST_H
