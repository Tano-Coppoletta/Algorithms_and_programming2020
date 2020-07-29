//
// Created by tanoc on 14/01/2020.
//

#ifndef PROGETTO_COLLEZIONE_H
#define PROGETTO_COLLEZIONE_H

#include "titolo.h"

typedef struct collezione *CT;

CT CTinit();
CT CTscan(FILE *fp,CT ct);
void CTfree(CT ct);
void insert(CT ct,Titolo tit);
Titolo estraiTIT(CT ct,char *codice);
void ricercaTIT(CT ct,char *codice);
void cercaeBILANCIA(CT ct,char *nome);



#endif //PROGETTO_COLLEZIONE_H
