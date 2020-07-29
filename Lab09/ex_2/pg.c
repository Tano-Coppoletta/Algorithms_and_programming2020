//
// Created by tanoc on 11/12/2019.
//
#include "pg.h"


int pg_read(FILE *fp, pg_t *pgp){
    if(fscanf(fp,"%s %s %s",pgp->cod,pgp->nome,pgp->classe)==3){
        stat_read(fp,&(pgp->b_stat));
        pgp->equip=equipArray_init();
        //all'inizio eqstat e bstat sono uguali
        pgp->eq_stat=pgp->b_stat;
        return 1;
    }
    return 0;
}
/* non essendo struct dinamica, pulisce chiamando il distruttore di equipArray */
void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp,"%s %s %s statistiche base: ",pgp->cod,pgp->nome,pgp->classe);
    stat_print(fp,&pgp->b_stat,MIN_STAT);
    fprintf(fp,"statistiche con equipaggiamento: ");
    stat_print(fp,&pgp->eq_stat,MIN_STAT);
    equipArray_print(fp,pgp->equip,invArray);
}
/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    int j,N,indice;
    stat_t st;
    inv_t *ogg;
    //aggiungo/tolgo oggetto
    equipArray_update(pgp->equip,invArray);
    //ricalcolo statistiche pg
    N=equipArray_inUse(pgp->equip);
    pgp->eq_stat=pgp->b_stat;
    for(j=0;j<N;j++){
       indice=equipArray_getEquipByIndex(pgp->equip,j);
       ogg=invArray_getByIndex(invArray,indice);
       st=inv_getStat(ogg);
       pgp->eq_stat.hp+=st.hp;
       pgp->eq_stat.mp+=st.mp;
       pgp->eq_stat.atk+=st.atk;
       pgp->eq_stat.def+=st.def;
       pgp->eq_stat.mag+=st.mag;
       pgp->eq_stat.spr+=st.spr;
    }
}