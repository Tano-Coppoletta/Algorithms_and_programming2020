//
// Created by tanoc on 13/01/2020.
//
#include "Graph.h"

typedef struct node *link;

struct node{
    int v;
    int wt;
    link next;
};

struct graph{
    int V;
    int **madj;
    link *ladj;
    ST tab;
    link z;
};
//newnode per lista
static link NEW(int v,int wt,link next){
    link x=malloc(sizeof(*x));
    if(x==NULL)
        exit(1);
    x->v=v;
    x->wt=wt;
    x->next=next;
    return x;
}


static int **MATRIXinit(int r,int c,int val){
    int **t,i,j;
    t=malloc(r*sizeof(int*));
    if(t==NULL)
        exit(1);
    for(i=0;i<r;i++){
        t[i]=malloc(c* sizeof(int));
        if(t[i]==NULL)
            exit(1);
    }
    for(i=0;i<r;i++){
        for(j=0;j<c;j++)
            t[i][j]=val;
    }
    return t;
}

Graph Graphinit(int V){
    int v;
    Graph G=malloc(sizeof(*G));
    G->V=V;
    G->madj=MATRIXinit(V,V,0);
    G->z=NEW(-1,-1,NULL);
    G->ladj=malloc(G->V* sizeof(link));
    if(G->ladj==NULL)
        exit(1);
    for(v=0; v<G->V ;v++)
        G->ladj[v]=G->z;
    G->tab=STinit(V);
    return G;
}

static Edge edgecreate(int v,int w,int wt){
    Edge e;
    e.v=v;
    e.w=w;
    e.wt=wt;
    return e;
}
//funzione che inserisce archi nella matrice
static void insertEM(Graph G,Edge e){
    int v=e.v,w=e.w,wt=e.wt;
    G->madj[v][w]=wt;
    G->madj[w][v]=wt;
}

void GraphinsertEM(Graph G,int v,int w,int wt){
    insertEM(G,edgecreate(v,w,wt));
}

//numeroArchi conta le righe del file
int numeroArchi(FILE *fp){
    int i=0,f;
    while(fscanf(fp,"%*s %*s %*s %*s %d",&f)>0)
        i++;
    return (2*i);
}

//Graphload legge il file e genera la matrice
Graph Graphload(Graph G,FILE *fp){
    int id1,id2,flusso;
    Item e1,e2;
    G->V=0;
    while(!feof(fp)){
        e1=Itemscan(fp);
        if(STinsert(e1,G->tab))
            G->V++;
        e2=Itemscan(fp);
        if(STinsert(e2,G->tab))
            G->V++;
        id1=STsearch(G->tab,keyget(&e1));
        id2=STsearch(G->tab,keyget(&e2));
        fscanf(fp,"%d\n",&flusso);
        if(id1>=0 && id2>=0){
            GraphinsertEM(G,id1,id2,flusso);
        }
    }
    return G;
}

//ordinamento su vettore di indici
static void insertion_sort(ST st,int *A,int N){
    int i,j,x,l=0,r=N-1;
    for(i=l+1;i<=r;i++){
        x=A[i];
        j=i-1;
        while(j>=l && keycmp(keyget(STsearchbyindex(st,A[j])),keyget(STsearchbyindex(st,x)))>0){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=x;
    }
}

//funzione per la stampa dei vertici collegati ad un vertice dato
static void stampaCollegati(Graph G,int *ord,int index){
    int j;
    //guardo sulla riga con i=index e j=ord[j] così stampo in ordine alfabetico
    for(j=0;j<G->V;j++){
        if(G->madj[index][ord[j]]!=0) {
            printf("\n     -");
            Itemshow(*STsearchbyindex(G->tab, ord[j]));
        }
    }
}
//funzione che stampa i vertici in ordine alfabetico
void Graphprint(Graph G){
    int i;
    int *ordinati=malloc(G->V* sizeof(int));
    if(ordinati==NULL)
        exit(1);
    //scrivo indice i dentro vettore e poi chiamo insertion sort
    for(i=0;i<G->V;i++)
        ordinati[i]=i;
    insertion_sort(G->tab,ordinati,G->V);
    for(i=0;i<G->V;i++){
        printf("\n>>>Vertice:");
        //stampo il vertice e poi tutti i vertici a esso collegati
        Itemshow(*STsearchbyindex(G->tab,ordinati[i]));
        stampaCollegati(G,ordinati,ordinati[i]);
    }
}
//funzione che verifica se i vertici formano un sottografo completo da matrice
void adiacenzaM(Graph G){
    int id1,id2,id3;
    char v1[max],v2[max],v3[max];
    printf("inserire nome di 3 vertici distinti:\n");
    scanf("%s%s%s",v1,v2,v3);
    if((id1=STsearch(G->tab,v1))==-1 || (id2=STsearch(G->tab,v2))==-1 || (id3=STsearch(G->tab,v3))==-1){
        printf("errore: vertici non validi\n");
        return;
    }
    if(G->madj[id1][id2]!=0 && G->madj[id1][id3]!=0 && G->madj[id2][id3]!=0){
        printf("i 3 vertici formano un sottografo completo\n");
    }else{
        printf("i vertici NON formano un sottografo massimale\n");
    }
}

//funzione che inserisce un arco in lista
//creando la lista da matrice inserisco solo in ladj[v] per evitare di inserire due volte
static void GraphinsertEL(Graph G,Edge e){
    int v=e.v,w=e.w,wt=e.wt;
    G->ladj[v]=NEW(w,wt,G->ladj[v]);
}

//crea la lista a partire da matrice
void GRAPHlist(Graph G){
    int i,j;
    link t;
    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++)
            if(G->madj[i][j]!=0){
                GraphinsertEL(G,edgecreate(i,j,G->madj[i][j]));
            }
    }
}

//funzione che verifica se i vertici formano un sottografo completo da lista
void adiacenzaList(Graph G){
    link t;
    int id1,id2,id3,trovato=0;
    char v1[max],v2[max],v3[max];
    printf("inserire nome di 3 vertici distinti:\n");
    scanf("%s%s%s",v1,v2,v3);
    if((id1=STsearch(G->tab,v1))==-1 || (id2=STsearch(G->tab,v2))==-1 || (id3=STsearch(G->tab,v3))==-1){
        printf("errore: vertici non validi\n");
        return;
    }
    for(t=G->ladj[id1];t!=G->z;t=t->next){
        if(t->v==id2 || t->v==id3)
            trovato++;
    }
    if(trovato>=2){
        for(t=G->ladj[id2];t!=G->z;t=t->next){
            if(t->v==id3)
                trovato++;
        }
    }else{
        printf("i vertici NON formano un sottografo massimale\n");
        return;
    }
    if(trovato>=3)
        printf("i vertici formano un sottografo massimale\n");
    else
        printf("i vertici NON formano un sottografo massimale\n");
}

void GRAPHfree(Graph G){
    int i;
    link t,next;
    for(i=0;i<G->V;i++){
        for(t=G->ladj[i];t!=G->z;t=next){
            next=t->next;
            free(t);
        }
    }
    free(G->ladj);
    free(G->z);
    for(i=0;i<G->V;i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}
