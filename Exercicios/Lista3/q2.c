#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lista{
    int cod, qtd;
    char description[100];
};

struct Lista1{
    struct Lista *info;
    struct Lista1 *prox, *ant;
};

struct Lista1 *aloca_lista(int cod, char description[100], int qtd){
    struct Lista1 *new;
    new = NULL;

    new = (struct Lista1*)malloc(sizeof(struct Lista1));
    new->info = (struct Lista*)malloc(sizeof(struct Lista));
    
    new->info->cod = cod;
    strcpy(new->info->description, description);
    new->info->qtd = qtd;
    new->prox = new;
    new->ant = new;

    return new;
}



void insere_sort(struct Lista1 **begin, struct Lista1 *No){

    struct Lista1 *aux, *ant;

    aux = *begin;
    //insere no inicio e no fim
    if(*begin == NULL){
        *begin = No;
        No->prox = No;
        No->ant = No;
    //se o valor for menor que o inicio
    }else if(No->info->cod < aux->info->cod){
        while(aux->prox != *begin){
            aux = aux->prox;
        }
        No->ant = aux->prox; //No.ant apontará pra o ultimo
        aux->prox = No;//o ultimo vai apontar para o novo No
        No->prox = *begin;//No.prox vai apontar para o antigo inicio, tornando-se assim o inicio 
        *begin = No;//inicio recebe o endereço do novo No
    }else{
        while(aux->prox != *begin && aux->info->cod < No->info->cod){// enquanto o proximo elemento não apontar para o inicio
                                                              //  e o valor dele for menor que o novo valor
            aux = aux->prox;
        }
        No->prox = aux->prox;
        No->ant = aux;
        aux->prox = No;

    }

}



int main(){
    return 0;
}