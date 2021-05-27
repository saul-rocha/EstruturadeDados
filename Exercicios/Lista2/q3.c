#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 100
//////////////////////////////////////
struct pilha
{
    char notation[TAM][4];
    int top;
};


int pilha_full(int top){
    int full=0;

    if(top > TAM - 1)
        full = 1;
    

return full;

}

int pilha_empty(int top){
    int empty = 0;

    if(top == -1)
        empty = 1;
    
return empty;

}


void empilhar(struct pilha top[100],int tam, char item[4]){
    if (top[tam].top >= -1){

    }
}

struct pilha *desempilhar(struct pilha **top){
    struct pilha *aux, *out;
    out = alocaNo();

    if (*top != NULL){
        aux = *top;

        *out = **top;

        *top = (*top)->top;

        free(aux);
    }

    return out;
}

int main(){
    struct pilha p;
    p.top = -1;
}