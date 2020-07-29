//
// Created by tanoc on 14/01/2020.
//
#include "collez_quot.h"


typedef struct BSTnode *link;
//il nodo contiene la quota, il massimo e il minimo del suo albero
struct BSTnode{
    Quota q;
    Quota max,min;
    int N;
    link l;
    link r;
};
struct COLLEZIONEquot{
    link root;
    link z;
};

static link NEW(Quota q,link l,link r,int N){
    link x=malloc(sizeof(*x));
    if(x==NULL)
        exit(1);
    x->q=q;
    x->l=l;
    x->r=r;
    x->N=N;
    x->max=x->min=QsetNULL();
    return x;
}

BST BSTinit(){
    BST bst=malloc(sizeof(*bst));
    if(bst==NULL)
        exit(1);
    bst->z=NEW(QsetNULL(),NULL,NULL,0);
    bst->root=bst->z;
    return bst;
}

static int BSTcountR(link h,link z){
    if(h==z)
        return 0;
    return BSTcountR(h->l,z)+BSTcountR(h->r,z)+1;
}

int BSTcount(BST bst){
    return BSTcountR(bst->root,bst->z);
}

int BSTempty(BST bst){
    if(BSTcount(bst)==0)
        return 1;
    return 0;
}

static void aggiornaNODO(link h,int num,float val){
    h->q=aggiornaQ(h->q,num,val);
}

static link BSTinsertR(link h,Data d,float  val,int num,int *Nonincrementa,link z){
    if(h==z )
        return NEW(generaQ(d,val,num),z,z,1);
    if(Kcompare(d,Kget(h->q))<0){
        h->l=BSTinsertR(h->l,d,val,num,Nonincrementa,z);
        h->min=minQ(h->l->min,h->min) ? h->l->min:h->min;
        h->max=maxQ(h->l->max,h->max) ? h->l->max:h->max;
        if(*Nonincrementa==1)
            return h;
    }
    else if(Kcompare(d,Kget(h->q))==0){
        aggiornaNODO(h,num,val);
        h->min=minQ(h->min,h->q) ? h->q:h->min;
        h->max=maxQ(h->max,h->q) ? h->q:h->min;
        *Nonincrementa=1;
        return h;
    }else {
        h->r = BSTinsertR(h->r, d, val, num,Nonincrementa, z);
        h->min = minQ(h->r->min, h->q) ? h->r->min : h->min;
        h->max = maxQ(h->r->max, h->q) ? h->r->max : h->min;
        if(*Nonincrementa==1)
            return h;
    }
    (h->N)++;
    return h;
}

void BSTinsert(BST bst,Data d,float val,int num){
    int a=0;
    bst->root=BSTinsertR(bst->root,d,val,num,&a,bst->z);
}

static void BSTsearchR(link h,Data d,link z){
    if(h==z){
        printf("data non trovata\n");
        return;
    }
    if(Kcompare(d,Kget(h->q))<0)
        BSTsearchR(h->l,d,z);
    else if(Kcompare(d,Kget(h->q))==0)
        Qprint(h->q);
    else
        BSTsearchR(h->r,d,z);
}

void BSTsearch(BST bst,Data d){
    BSTsearchR(bst->root,d,bst->z);
}

static void BSTiR(link h,Data d1,Data d2,link z,float *min,float *max){
    if(h==z)
        return;
    if(Datacmp(d2,Kget(h->q))<0)
        BSTiR(h->l,d1,d2,z,min,max);
    else if(Datacmp(d1,Kget(h->q))>0)
        BSTiR(h->r,d1,d2,z,min,max);
    else if(confrontaF(h->min,min) || confrontaF(h->max,max)==0){
        BSTiR(h->l,d1,d2,z,min,max);
        BSTiR(h->r,d1,d2,z,min,max);
        *min=confrontaF(h->q,min) ? h->q.q:*min;
        *max=confrontaF(h->q,max) ? *max:h->q.q;
    }
}

void BSTintervallo(BST bst,Data d1,Data d2){
    if(bst==NULL)
        return;
    float min=INT_MAX,max=0;
    BSTiR(bst->root,d1,d2,bst->z,&min,&max);
    printf("il minimo e' %f\nil massimo e' %f\n",min,max);
}

static link rotR(link h){
    link x=h->l;
    h->l=x->r;
    x->r=h;
    x->N=h->N;
    h->N=1;
    h->N+=(h->l) ? h->l->N:0;
    h->N+=(h->r) ? h->r->N:0;
    return x;
}

static link rotL(link h){
    link x=h->r;
    h->r=x->l;
    x->l=h;
    x->N=h->N;
    h->N=1;
    h->N+=(h->l) ? h->l->N:0;
    h->N+=(h->r) ? h->r->N:0;
    return x;
}

static link partitionR(link h,int r){
    int t=h->l->N;
    if(t>r){
        h->l=partitionR(h->l,r);
        h=rotR(h);
    }
    if(t<r){
        h->r=partitionR(h->r,r-t-1);
        h=rotL(h);
    }
    return h;
}

static link balanceR(link h,link z){
    int q;
    if(h==z)
        return z;
    q=(h->N+1)/2-1;
    h=partitionR(h,q);
    h->l=balanceR(h->l,z);
    h->r=balanceR(h->r,z);
    return h;
}

void BSTbalance(BST bst){
    bst->root=balanceR(bst->root,bst->z);
}

static void camminiR(link h,int *min,int *max,int corrente,link z){
    if(h==z){
        corrente--;
        if(corrente<(*min) && corrente>0)
            *min=corrente;
        if(corrente>(*max) && corrente>0)
            *max=corrente;
        return;
    }
    camminiR(h->l,min,max,corrente+1,z);
    camminiR(h->r,min,max,corrente+1,z);

}

int rapportoCAMMINI(BST bst){
    int min=INT_MAX,max=0,curr=0;
    camminiR(bst->root,&min,&max,curr,bst->z);
    return(max/min);
}

static void BSTprintR(link h,link z){
    if(h==z)
        return;
    BSTprintR(h->l,z);
    Qprint(h->q);
    BSTprintR(h->r,z);
}

void BSTprintINORDER(BST bst){
    if(BSTempty(bst))
        return;
    BSTprintR(bst->root,bst->z);
}

void BSTfreeR(link h,link z){
    if(h==z)
        return;
    BSTfreeR(h->l,z);
    BSTfreeR(h->r,z);
    free(h);
}


void BSTfree(BST bst){
    if(bst->root==NULL)
        return;
    BSTfreeR(bst->root,bst->z);
    free(bst->z);
    free(bst);
}

