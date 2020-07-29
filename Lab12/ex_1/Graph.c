//
// Created by tanoc on 21/01/2020.
//
#include "Graph.h"
#include "ST.h"


typedef struct node *link;

struct node{
    int v,wt;
    link next;
};

struct graph{
    int V,E;
    link *ladj;
    ST st;
    link z;
};

static link NEW(int v,int wt,link next){
    link x=malloc(sizeof(*x));
    if(x==NULL)
        exit(1);
    x->v=v;
    x->wt=wt;
    x->next=next;
    return x;
}

Graph Graphinit(int V){
    Graph G=malloc(sizeof(*G));
    int i;
    if(G==NULL)
        exit(1);
    G->ladj=malloc(V* sizeof(link));
    if(G->ladj==NULL)
        exit(1);
    G->z=NEW(-1,-1,NULL);
    for(i=0;i<V;i++)
        G->ladj[i]=G->z;
    G->st=STinit(V);
    G->E=0;
    G->V=V;
    return G;
}

static Edge Edgecreate(int v,int w,int wt){
    Edge e;
    e.v=v;e.w=w;e.wt=wt;
    return e;
}

static void insertEDGE(Edge e,Graph G){
    int v=e.v,w=e.w,wt=e.wt;
    G->ladj[v]=NEW(w,wt,G->ladj[v]);
    G->E++;
}

void GRAPHinsertE(Graph G,int v,int w,int wt){
    insertEDGE(Edgecreate(v,w,wt),G);
}

Graph Graphload(FILE *fp){
    Graph G;
    int v,i,wt,id1,id2;
    char s1[max],s2[max];
    fscanf(fp,"%d",&v);
    G=Graphinit(v);
    for(i=0;i<G->V;i++){
        fscanf(fp,"%s",s1);
        STinsert(G->st,s1);
    }
    while(fscanf(fp,"%s %s %d",s1,s2,&wt)==3){
        id1=STgetindex(G->st,s1);
        id2=STgetindex(G->st,s2);
        if(id1>=0 && id2>=0){
            GRAPHinsertE(G,id1,id2,wt);
        }
    }
    return G;
}

static int CHECKedge(Edge *escludi,Edge e,int E){
    int i;
    for(i=0;i<E;i++){
        if(escludi[i].v==e.v && escludi[i].w==e.w)
            return 0;
    }
    return 1;
}

static void DFSr(Graph G,Edge e,Edge *escludi,int E,int *pre,int *post,int *st,int *time,int *ciclo){
    link t;
    int v,w=e.w;

    st[w]=e.v;
    pre[w]=(*time)++;
    for(t=G->ladj[w];t!=G->z;t=t->next){
        if(CHECKedge(escludi,Edgecreate(w,t->v,t->wt),E)){
            if(pre[t->v]==-1){
                DFSr(G,Edgecreate(w,t->v,t->wt),escludi,E,pre,post,st,time,ciclo);
            }else{
                v=t->v;
                //se trovo un arco B ho trovato un ciclo
                if(post[v]==-1)
                    *ciclo=1;
            }
        }
    }
    post[w]=(*time)++;
}

int CHECKcicli(Graph G,Edge *escludi,int E){
    //DFS se trovo archi B significa che il grafo contiene cicli
    int *pre,*post,*st,time=0;
    int i,ciclo=0;
    pre=malloc(G->V* sizeof(int));
    post=malloc(G->V* sizeof(int));
    st=malloc(G->V* sizeof(int));
    if(pre==NULL || post==NULL || st==NULL)
        exit(1);
    for(i=0;i<G->V;i++){
        pre[i]=-1;post[i]=-1;st[i]=-1;
    }
   DFSr(G,Edgecreate(0,0,-1),escludi,E,pre,post,st,&time,&ciclo);
    for(i=0;i<G->V;i++){
        if(pre[i]==-1)
           DFSr(G,Edgecreate(i,i,-1),escludi,E,pre,post,st,&time,&ciclo);
    }
    if(ciclo)
        return 1;
    return 0;
}

void GraphEDGE(Graph G,Edge *e){
    link t;
    int i,E=0;
    for(i=0;i<G->V;i++){
        for(t=G->ladj[i];t!=G->z;t=t->next){
            e[E++]=Edgecreate(i,t->v,t->wt);
        }
    }
}

static int calcolaWT(Edge *e,int k){
    int i,wt=0;
    for(i=0;i<k;i++){
        wt+=e[i].wt;
    }
    return wt;
}

static int powerset(Graph G,int pos,Edge *val,Edge *sol,Edge *best_sol,int *peso,int n,int k,int start,int trovato){
    int i,wt;
    if(pos>=k){
        if(CHECKcicli(G,sol,k)==0){
            wt=calcolaWT(sol,k);
            if(wt>*peso){
                *peso=wt;
                for(i=0;i<k;i++)
                    best_sol[i]=sol[i];
            }
            trovato=1;
        }
        return trovato;
    }
    for(i=start;i<n;i++){
        sol[pos]=val[i];
        trovato=powerset(G,pos+1,val,sol,best_sol,peso,n,k,start+1,trovato);
    }
    return trovato;
}

void scriviDAG(Graph G,Graph DAG,Edge *e,int E){
    int i;
    link t;

    for(i=0;i<G->V;i++){
        STinsert(DAG->st,STsearchbyindex(G->st,i));
    }

    for(i=0;i<G->V;i++){
        for(t=G->ladj[i];t!=G->z;t=t->next){
            if(CHECKedge(e,Edgecreate(i,t->v,t->wt),E)){
                DAG->ladj[i]=NEW(t->v,t->wt,DAG->ladj[i]);
            }
        }
    }
}

Graph GraphtoDAG(Graph G){
    Graph DAG;
    Edge *val=malloc(G->E* sizeof(*val));
    Edge *sol=malloc(G->E* sizeof(*sol));
    Edge *best_sol=malloc(G->E* sizeof(*best_sol));
    int peso=0;
    if(val==NULL || sol==NULL || best_sol==NULL)
        exit(1);
    int k;
    GraphEDGE(G,val);
    for(k=1;k<G->E;k++){
        //il primo che trovo è quello con cardinalità k minima
        if(powerset(G,0,val,sol,best_sol,&peso,G->E,k,0,0))
            break;
    }
    printf("cardinalita' sottoinsieme archi da togliere per eliminare cicli %d\n",k);
    DAG=Graphinit(G->V);
    scriviDAG(G,DAG,best_sol,k);
    return DAG;
}

void Graphprint(Graph G){
    int i;
    link t;
    for(i=0;i<G->V;i++){
        for(t=G->ladj[i];t!=G->z;t=t->next){
            printf("%s %s\n",STsearchbyindex(G->st,i),STsearchbyindex(G->st,t->v));
        }
    }
}

static void TSdfsR(Graph D,int v,int *pre,int*ts,int *time){
    link t;
    pre[v]=0;
    for(t=D->ladj[v];t!=D->z;t=t->next){
        if(pre[t->v]==-1)
            TSdfsR(D,t->v,pre,ts,time);
    }
    ts[(*time)++]=v;
}

static void DAGrts(Graph D,int *ts){
    int *pre,time=0,v;
    pre=malloc(D->V* sizeof(int));
    if(pre==NULL)
        exit(1);
    for(v=0;v<D->V;v++){
        pre[v]=-1;
        ts[v]=-1;
    }
    for(v=0;v<D->V;v++){
        if(pre[v]==-1)
            TSdfsR(D,v,pre,ts,&time);
    }
}

static void trovaSORGENTI(Graph D,int *INdegree){
    int i;
    link t;
    for(i=0;i<D->V;i++){
        for(t=D->ladj[i];t!=D->z;t=t->next){
            INdegree[t->v]++;
        }
    }
}

static void camminiMAX(Graph D,int *ts,int i){
    int v,j;
    int *st,*d;
    link t;
    for(j=0;j<D->V;j++)
        if(ts[j]==i){
            v=j;
            break;
        }

    st=malloc(D->V* sizeof(int));
    d=calloc(D->V,sizeof(int));
    if(st==NULL || d==NULL)
        exit(1);
    for(j=0;j<D->V;j++)
        st[j]=-1;

    d[ts[v]]=0;
    st[ts[v]]=0;
    while(v>=0){
        for(t=D->ladj[ts[v]];t!=D->z;t=t->next){
            if(d[t->v]<d[ts[v]]+t->wt){
                d[t->v]=d[ts[v]]+t->wt;
                st[t->v]=ts[v];
            }
        }
        v--;
    }
    printf("cammini massimi da %s\n",STsearchbyindex(D->st,i));
    for(j=0;j<D->V;j++){
        printf("%s %d\n",STsearchbyindex(D->st,j),d[j]);
    }
}

void DAGmax(Graph D){
    int *ts,*indegree,i;
    ts=malloc(D->V* sizeof(int));
    indegree=calloc(D->V, sizeof(int));
    if(indegree==NULL || ts==NULL)
        exit(1);
    trovaSORGENTI(D,indegree);
    DAGrts(D,ts);
    for(i=D->V-1;i>=0;i--){
        if(indegree[i]==0){
            camminiMAX(D,ts,i);
        }
    }
}


static void freeLIST(link h,link z){
    if(h==z)
        return;
    freeLIST(h->next,z);
    free(h);
}

void Graphfree(Graph G){
    int i;
    for(i=0;i<G->V;i++)
        freeLIST(G->ladj[i],G->z);
    free(G->ladj);
    free(G->z);
    STfree(G->st);
    free(G);
}