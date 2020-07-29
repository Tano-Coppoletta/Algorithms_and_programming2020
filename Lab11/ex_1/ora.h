//
// Created by tanoc on 14/01/2020.
//

#ifndef PROGETTO_ORA_H
#define PROGETTO_ORA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int hh;
    int mm;
}Ora;

Ora Orascan(FILE *fp);
void Oraprint(Ora ora);
#endif //PROGETTO_ORA_H
