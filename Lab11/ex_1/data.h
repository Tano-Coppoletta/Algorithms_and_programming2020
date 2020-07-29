//
// Created by tanoc on 14/01/2020.
//

#ifndef PROGETTO_DATA_H
#define PROGETTO_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int a;
    int m;
    int g;
}Data;


Data Datascan(FILE *fp);
void Dataprint(Data d);
int Datacmp(Data d1,Data d2);
Data datasetNULL();
Data datasetMAX();

#endif //PROGETTO_DATA_H
