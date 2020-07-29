//
// Created by tanoc on 11/12/2019.
//
#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp,"%d %d %d %d %d %d",&statp->hp,&statp->mp,&statp->atk,&statp->def,&statp->mag,&statp->spr);
}
void stat_print(FILE *fp, stat_t *statp, int soglia){
    fprintf(fp,"%d %d %d %d %d %d\n",statp->hp>soglia ? statp->hp:soglia,statp->mp>soglia ? statp->mp:soglia,
            statp->atk>soglia ? statp->atk:soglia,statp->def>soglia ? statp->def:soglia,statp->mag>soglia ? statp->mag:soglia,
            statp->spr>soglia ? statp->spr:soglia);
}

void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp,"%s %s",invp->nome,invp->tipo);
    stat_read(fp,&(invp->stat));
}
void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp,"%s %s ",invp->nome,invp->tipo);
    stat_print(fp,&(invp->stat),INT_MIN);
}

stat_t inv_getStat(inv_t *invp){
    return (invp->stat);
}