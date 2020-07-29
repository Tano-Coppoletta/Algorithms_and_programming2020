//
// Created by tanoc on 14/01/2020.
//

#ifndef PROGETTO_TITOLO_H
#define PROGETTO_TITOLO_H

#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "ora.h"
#include "collez_quot.h"

typedef struct titolo *Titolo;
typedef char *key;

int KEYcompare(key k1,key k2);
key KEYget(Titolo tit);
int KEYgreater(key k1,key k2);

Titolo Tscan(FILE *fp);
void Tprint(Titolo t);
Titolo Tinit();
void Tfree(Titolo tit);
BST estraiBST(Titolo tit);
void bilancia(Titolo tit,int S);
Titolo TsetNULL();

#endif //PROGETTO_TITOLO_H
