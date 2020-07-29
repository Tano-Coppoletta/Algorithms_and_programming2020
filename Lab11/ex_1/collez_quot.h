//
// Created by tanoc on 14/01/2020.
//

#ifndef PROGETTO_COLLEZ_QUOT_H
#define PROGETTO_COLLEZ_QUOT_H
#include "quotazione.h"

typedef struct COLLEZIONEquot *BST;

BST BSTinit();
void BSTinsert(BST bst,Data d,float val,int num);
void BSTsearch(BST bst,Data d);
void BSTintervallo(BST bst,Data d1,Data d2);
void BSTfree(BST bst);
int BSTcount(BST bst);
int BSTempty(BST bst);
void BSTprintINORDER(BST bst);
int rapportoCAMMINI(BST bst);
void BSTbalance(BST bst);



#endif //PROGETTO_COLLEZ_QUOT_H
