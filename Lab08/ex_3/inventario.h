//
// Created by tanoc on 04/12/2019.
//

#ifndef PROGETTO_INVENTARIO_H
#define PROGETTO_INVENTARIO_H

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}Stat;

typedef struct{
    char *nome;
    char *tipo;
    Stat stat_ogg;
}Inv_t;

typedef struct tabInv_t *tabInv;

struct tabInv_t{
    Inv_t *vettinv;
    int n_inv;
};

typedef struct{
    Inv_t **inUso;
    int n;
}Equip;

tabInv carica_oggetti(tabInv inv);
void dealloca_inv(tabInv inv);
#endif //PROGETTO_INVENTARIO_H
