#include <stdio.h>
#include <stdlib.h>


struct Lista{
    int valor;

    struct Lista *prox;
};

struct Lista *aloca_lista(int info){
    struct Lista *new;

    new = (struct Lista*)malloc(sizeof(struct Lista));

    new->valor = info;
    new->prox = NULL;
}


int insere_begin(struct Lista **begin, struct Lista **end, struct Lista *No){

    struct Lista *aux;
    int res = 0;

    aux = *begin;

    if(*begin == NULL){
        *begin = No;
        *end = No;
        res = 1;
    }else if((*begin)->valor > No->valor){//se o novo valor for menor que o inicio
        *begin = No; // inicio agora é o novo
        No->prox = aux; //e o proximo do novo é o aux(que guardou o endereço do incio)

        res = 1;
    }

    return res;
}

int insere_end(struct Lista **begin, struct Lista **end, struct Lista *No){

    struct Lista *aux;
    int res = 0;
    aux = *begin;
    
    if(aux != NULL){
        while(aux->valor < No->valor){
            aux = aux->prox;
        }
        aux->prox = No;
        *end = No;
        res = 1;
    }

    return res;

}

int insere_mid(struct Lista **begin, struct Lista **end, struct Lista *No){

    struct Lista *aux, *ant;
    int res = 0;
    aux = *begin;
    
    if(aux != NULL){
        while( No->valor < aux->valor){// quando o novo elemento for menor que o aux, faz a inserção
            ant = aux;
            aux = aux->prox;
        }
        No->prox = aux;// o proximo do novo elemento aponta para o aux que  é o elemento maior que ele
        ant->prox = No;// o anterior  apontapara o novo que é o proximo dele
        res = 1;
    }

    return res;

}


void imprimir(struct Lista *begin){
    if(begin != NULL){
        printf("%d - ", begin->valor);
    }
    imprimir(begin->prox);
}



int main(){
    
    struct Lista *begin, *end, *No;
    int esc, num, verifica;

    begin = NULL;
    end = NULL;

   do{ 
        printf("Digite um valor: ");
        scanf("%d", &num);
        No = aloca_lista(num);
        if(num < begin->valor || begin == NULL){
            verifica = insere_begin(&begin, &end, No);
            printf("Isetido no inicio!\n");

        }else if(num > end->valor){
            verifica = insere_end(&begin, &end, No);
            printf("Isetido no fim!\n");

        }else{
            verifica = insere_mid(&begin, &end, No);
            printf("Isetido no meio!\n");
        }
   

        printf("Continuar? (1-SIM | 0-NAO): ");
        scanf("%d", &esc);
    }while(esc != 0);

    imprimir(begin);

    return 0;
}