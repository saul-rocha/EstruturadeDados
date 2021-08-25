#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Lista{
    int i;
};

struct Lista1{
    struct Lista *info;
    struct Lista1 *prox;
};

struct Lista1 *aloca_lista(int i){
    struct Lista1 *new;
    new = NULL;

    new = (struct Lista1*)malloc(sizeof(struct Lista1));
    new->info = (struct Lista*)malloc(sizeof(struct Lista));
    
    new->info->i = i;
    new->prox = new;

    return new;
}



void insere_sort(struct Lista1 **begin, struct Lista1 *No){

    struct Lista1 *aux, *ant;

    aux = *begin;
    //insere no inicio e no fim
    if(*begin == NULL){
        *begin = No;
        No->prox = No;
    //se o valor for menor que o inicio
    }else if(No->info->i < aux->info->i){
        while(aux->prox != *begin){
            aux = aux->prox;
        }
        aux->prox = No;
        No->prox = *begin;
        *begin = No;
    }else{
        
        while(aux->prox != *begin && aux->prox->info->i < No->info->i){// enquanto o proximo elemento não apontar para o inicio
                                                                        //  e o valor dele for menor que o novo valor
            aux = aux->prox;
        }
        No->prox = aux->prox;
        aux->prox = No;

    }

}

//busca um valor  e devolve a quantidade de vezez que foi sorteado
int consult(struct Lista1 *begin, int valor, int *flag){
    struct Lista1 *aux, *ant;
    int res=0;
    aux = begin->prox;
    
    while(aux->info->i <= valor){
        if(aux != begin && aux->info->i == valor){
            *flag = 1;// se encontrar flag recebe um
            res ++;//conta quantas vezes foi sorteado
        }
        aux = aux->prox;
    }
    
    if(*flag == 0){
        res = 0;
        aux = begin->prox;
    
        while(aux->info->i < valor ){
            ant = aux;
            aux = aux->prox;
        }
        if(aux->prox == begin){
            printf("valor mais proximo = %d\n", aux->info->i);
        }else if(aux->prox != begin){
            printf("valor mais proximo = %d e %d\n", aux->info->i, aux->prox->info->i);
        }else if(ant->info->i < valor){
            printf("valor mais proximo = %d\n", ant->info->i);
        }
    }
    return res;


}

void imprimir(struct Lista1 *begin){
    struct Lista1 *aux;
    aux = begin;
    
    while(aux->prox != begin){
        printf("%d --> ", aux->info->i);
        aux = aux->prox;
    }
    
}

int menu(){
    int op;
    
    printf("1 - Lançar Ficha\n0 - Sair\n");
    scanf("%d", &op);
    setbuf(stdin,NULL);

    return (op);

}

int main(){
    struct Lista1 *begin, *No;
    int op, res, flag=0, ficha, prox1, prox2, i;

    begin = NULL;

    srand(time(NULL));
    
    while(flag < 100){
        i = 1 + rand() % 499; // numero aleatorio de (0 a 500) + 1
        No = aloca_lista(i);
        insere_sort(&begin, No);
        flag++;
    }
    imprimir(begin);
    printf("\n");

    do{
        op = menu();
        switch (op)
        {
        case 1:
            //scanf("%d", &ficha);
            ficha = 1 + rand() % 499;
            printf("Ficha lancada: %d\n", ficha);
            flag = 0;
            res = consult(begin, ficha, &flag);
            if(flag != 0){
                printf("Numero Sorteado: %d\nQuantidade de vezes escolhido: %d\n", ficha, res);
            }
            
            break;
        
        default:
            if(op != 0){
                printf("tente uma opcao valida!\n");
            }
            break;
        }
    }while(op != 0);

    return 0;
}