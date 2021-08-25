#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

    struct Lista1 *aux;

    aux = *begin;
    //insere no inicio e no fim
    if(*begin == NULL){
        *begin = No;
        No->prox = No->ant;
        No->ant = No->prox;
    //se o valor for menor que o inicio
    }else{
        while(aux->prox != *begin ){// enquanto o proximo elemento não apontar para o inicio                                                
        //  e o valor dele for menor que o novo valor
            aux = aux->prox;
        }

        No->prox = *begin;
        No->ant = aux;
        aux->prox = No;
        (*begin)->ant = No;
    }
}



void roletada(struct Lista1 **premios, int giradas, int direcao){
    struct Lista1 *retira;

    if(*premios != NULL){
        if(direcao % 2 != 0){//se direção for impar, entao vai girar no sentido horario
            while(giradas > 0){
                *premios = (*premios)->prox;
                giradas--;
            }
            (*premios)->info->qtd--;
            printf("Premio: %s\n", (*premios)->info->description);

            if((*premios)->info->qtd == 0){
                if((*premios)->prox == *premios){
                    *premios = NULL;
                }else{
                //retira = *premios;
                (*premios)->ant->prox = (*premios)->prox;
                (*premios)->prox->ant = (*premios)->ant;
                //free(retira);

                }
            }
        }else{
            while(giradas > 0){
                (*premios) = (*premios)->ant;
                giradas--;
            }
            (*premios)->info->qtd--;
            printf("Premio: %s\n", (*premios)->info->description);

            if((*premios)->info->qtd == 0){
                if((*premios)->prox == *premios){
                    *premios = NULL;
                }else{
                //retira = *premios;
                (*premios)->ant->prox = (*premios)->prox;
                (*premios)->prox->ant = (*premios)->ant;
                //free(retira);

                }
            }   
        }
    }
}


void imprimir(struct Lista1 *begin){
    struct Lista1 *aux;
    aux = begin;
    while(aux->prox != begin){
        printf("Codigo: %d\nDescricao: %s\nQuantidade: %d\n", aux->info->cod, aux->info->description, aux->info->qtd);
        aux = aux->prox;
    }
    printf("Codigo: %d\nDescricao: %s\nQuantidade: %d\n", aux->info->cod, aux->info->description, aux->info->qtd);

}



int menu(){
    int op;
    printf("1...Cadastrar Premio\n2...Girar Roleta\n0...Sair\n");
    scanf("%d", &op);
    setbuf(stdin, NULL);
    return op;
}

int main(){
    struct Lista1 *premios, *No;
    int op,cod=1, qtd, giradas, direcao=0;
    char descricao[100];

    srand(time(NULL));

    premios = NULL;

    do{
        op = menu();
        switch (op)
        {
        case 1:

            printf("Descricao: ");
            scanf("%[^\n]", descricao);//forma do scanf ler espaços
            setbuf(stdin,NULL);

            printf("Quantidade: ");
            scanf("%d", &qtd);
            setbuf(stdin,NULL);

            No = aloca_lista(cod, descricao, qtd);
            insere_sort(&premios, No);
            cod++;
            
            break;
        case 2:
            
            giradas = 1 + rand() % 99;
            if(premios != NULL){
                roletada(&premios, giradas, direcao);
                direcao++;
            }
            else{
                printf("Lista vazia\n");
            }
            break;
        case 3:
            if(premios != NULL){
                imprimir(premios);
            }
        default:
            break;
        }

    }while(op != 0);

    
    return 0;
}