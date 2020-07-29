//
// Created by tanoc on 13/01/2020.
//

#ifndef PROGETTO_ITEM_H
#define PROGETTO_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 30

//quasi ADT Item
typedef struct{
    char id_elab[max];
    char id_rete[max];
}Item;

typedef char *Key;

Key keyget(Item *pval);
Item Itemscan(FILE *fp);
void Itemshow(Item val);
Item ItemsetNULL(void);
int keycmp(Key k1,Key k2);

#endif //PROGETTO_ITEM_H
