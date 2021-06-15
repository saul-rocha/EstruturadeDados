#include <stdio.h>
#include <stdlib.h>

struct Lista{
    int valor;
};

struct Lista1{
    struct Lista *info;
    struct Lista1 *ant, *prox;
};
/* BASICS */

// aloca um elemento
struct Lista *aloca_lista(int info){
    struct Lista1 *new;

    new = (struct Lista1*)malloc(sizeof(struct Lista1));

    new->info->valor = info;
    new->prox = NULL;
    new->ant = NULL;

    return new;
}


void insere(struct Lista1 **begin, struct Lista1 **end, struct Lista1 *No){

    struct Lista1 *aux, *ant;

    //insere no inicio e no fim
    if(*begin == NULL){
        *begin = No;
        *end = No;
    //insere no inicio
    }else if(No->info->valor < (*begin)->info->valor){
        aux = *begin;
        aux->ant = No;
        No->prox = aux;
        *begin = No;
    }
    //insere no fim
    else if(No->info->valor > (*end)->info->valor){
       
        aux = *end;
        aux->prox = No;
        No->ant = aux;
        *end = No;

        
    }else{//insere no meio
        aux = *begin;
        while((No->info->valor > aux->info->valor) && aux != NULL){// quando o novo elemento for menor que o aux, faz a inserção
            ant = aux;
            aux = aux->prox;
        }
        No->prox = aux;// o proximo do novo elemento aponta para o aux que  é o elemento maior que ele
        aux->ant = No;
        ant->prox = No;// o anterior  apontará para o novo que é o proximo dele
        No->ant = ant;
    }

}


int remover_elemento(struct Lista1 **begin, int elem){
    struct Lista1 *aux, *ant;
    int res=0;

    aux = *begin;
    
    
    while (aux != NULL && aux->info->valor != elem){
        ant = aux;
        aux = aux->prox;
    }

    if(aux != NULL){
        ant->prox = aux->prox;
        aux->prox->ant = ant;
        res = 1;
        free(aux);
    }
    
    return res;
}


/*------------------------------*/


void imprimir(struct Lista1 *begin){
    struct Lista1 *aux;

    if(aux != NULL){
        printf("%d - ", aux->info->valor);
    }
    imprimir(aux->prox);
}


int main(){

    struct Lista1 *l1_begin, *l1_end;

    l1_begin = NULL;
    l1_end = NULL;

    return 0;
}