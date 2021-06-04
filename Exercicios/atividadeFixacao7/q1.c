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


int insere(struct Lista **begin, struct Lista **end, struct Lista *No){

    struct Lista *aux, *ant;
    int res = 0;

    aux = *begin;
    //insere no fim
    if(*begin == NULL){
        *begin = No;
        *end = No;
        res = 1;
    }else if(No->valor < (*begin)->valor){//se o novo valor for menor que o inicio
        *begin = No; // inicio agora é o novo
        No->prox = aux; //e o proximo do novo é o aux(que guardou o endereço do incio)

        res = 1;
    }
    //insere no fim
    else if(No->valor > (*end)->valor){
        aux = *end;
        aux->prox = No;
        *end = No;

        res = 1;
        
    }else{
        aux = *begin;
        while( No->valor > aux->valor && aux != NULL){// quando o novo elemento for menor que o aux, faz a inserção
            ant = aux;
            aux = aux->prox;
        }
        No->prox = aux;// o proximo do novo elemento aponta para o aux que  é o elemento maior que ele
        ant->prox = No;// o anterior  apontará para o novo que é o proximo dele
        res = 1;
    }

    return res;
}



void imprimir(struct Lista *begin){
    struct Lista *aux;
    aux = begin;
    while(aux != NULL){
        printf("%d - ", aux->valor);
        aux = aux->prox;
    }

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
        verifica = insere(&begin, &end, No);


        printf("Continuar? (1-SIM | 0-NAO): ");
        scanf("%d", &esc);
    }while(esc != 0);

    imprimir(begin);

    return 0;
}