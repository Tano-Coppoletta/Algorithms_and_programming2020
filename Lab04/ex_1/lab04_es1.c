//
// Created by tanoc on 05/11/2019.
//
#include <stdio.h>

void scambia(int *a,int *b);
int gdc(int a,int b);

int main(){
    int a,b,x;

    printf("inserire due numeri interi\n");
    scanf("%d %d",&a,&b);

    x=gdc(a,b);
    printf("%d",x);
    return 0;
}

void scambia(int *a,int *b){
    int tmp;

    tmp=*b;
    *b=*a;
    *a=tmp;
}


int gdc(int a,int b){
    if(a==b){
        return(b);
    }
    if(a<b){
        scambia(&a,&b);
    }
    if(a%2==0 && b%2==0){
        return(2*gdc(a/2,b/2));
    }else if(b%2==0 && a%2!=0){
        return (gdc(a,b/2));
    }else if(a%2==0 && b%2!=0){
        return(gdc(a/2,b));
    }else{
        return gdc((a-b)/2,b);
    }
}


