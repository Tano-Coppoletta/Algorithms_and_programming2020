//
// Created by tanoc on 14/01/2020.
//
#include "collezione.h"
#define maxS 50


int main(){
    int continua=1,scelta=0;
    char file[maxS],stringa[maxS];
    CT ct=CTinit();
    Data d1,d2;
    FILE *fp;

    while(continua){
        printf("inserire intero tra:\n1 > file\n2 > ricerca titolo\n3 > ricerca quotazioni"
               "\n4 > ricerca max e min in intervallo\n5 > ricerca max e min globale\n6 >bilancia\n7 > fine\n");
        scanf("%d",&scelta);
        switch(scelta){
            case 1:
                printf("inserire nome file\n");
                scanf("%s",file);
                fp=fopen(file,"r");
                if(fp==NULL)
                    return -1;
                CTscan(fp,ct);
                fclose(fp);
                break;
            case 2:
                printf("inserire nome titolo da cercare\n");
                scanf("%s",stringa);
               ricercaTIT(ct,stringa);
                break;
            case 3:
                printf("inserire nome titolo\n");
                scanf("%s",stringa);
                printf("inserire data aaaa/mm/gg\n");
                BSTsearch(estraiBST(estraiTIT(ct,stringa)),Datascan(stdin));
                break;
            case 4:
                printf("inserire nome titolo\n");
                scanf("%s",stringa);
                printf("inserire intervallo date aaaa/mm/gg\n");
                d1=Datascan(stdin);
                d2=Datascan(stdin);
                BSTintervallo(estraiBST(estraiTIT(ct,stringa)),d1,d2);
                break;
            case 5:
                printf("inserire nome titolo\n");
                scanf("%s",stringa);
                BSTintervallo(estraiBST(estraiTIT(ct,stringa)),datasetNULL(),datasetMAX());
                break;
            case 6:
                printf("inserire nome titolo\n");
                scanf("%s",stringa);
                cercaeBILANCIA(ct,stringa);
                break;
            case 7:
                continua=0;
                break;
            default:
                printf("comando errato\n");
                break;
        }

    }
    CTfree(ct);
}
