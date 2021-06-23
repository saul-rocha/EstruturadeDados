#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//http://www.uel.br/projetos/matessencial/basico/medio/polinomios.html#sec01

#define TAM 5
struct Polinomio{
    int coeficente, exp;
};

struct Lista1{
    struct Polinomio *info;
    struct Lista1 *prox;
};


//aloca um No e suas informações
struct Lista1 *aloca_lista(int c, int e){
    struct Lista1 *new;
    new = NULL;

    new = (struct Lista1*)malloc(sizeof(struct Lista1));
    new->info = (struct Polinomio*)malloc(sizeof(struct Polinomio));
    
    new->info->coeficente = c;
    new->info->exp = e;
    new->prox = new;

    return new;
}


void insere_elemento(struct Lista1 **begin, struct Lista1 *No){

    struct Lista1 *aux, *ant;

    aux = *begin;
    //insere no inicio e no fim
    if(*begin == NULL){
        *begin = No;
        No->prox = No;
    //se o expoente for menor que o inicio
    }else if(No->info->exp < aux->info->exp){
        while(aux->prox != *begin){
            aux = aux->prox;
        }
            aux->prox = No;
            No->prox = *begin;
            *begin = No;
        
    }else{
        
        while(aux->prox != *begin && aux->prox->info->exp < No->info->exp){// enquanto o proximo elemento não apontar para o inicio
                                                                        //  e o valor dele for menor que o novo valor
            aux = aux->prox;
        }
        No->prox = aux->prox;
        aux->prox = No;

    }

}

void imprimir(struct Lista1 *begin){
    struct Lista1 *aux;
    aux = begin;
    while(aux->prox != begin){
        printf("%dx^%d\n", aux->info->coeficente, aux->info->exp);
        aux = aux->prox;
    }
    printf("%dx^%d\n", aux->info->coeficente, aux->info->exp);

}


//logica incompleta
void soma_polinomios(struct Lista1 *pol1, struct Lista1 *pol2){
    struct Lista1 *aux1, *aux2, *No;

    int s;
    
    aux1 = pol1;
    aux2  = pol2;
    while(aux1->prox != pol1 || aux2->prox != pol2){
        if(aux1->info->exp < aux2->info->exp){
            printf("%dx^%d ", aux1->info->coeficente, aux1->info->exp);
            aux1 = aux1->prox;
        }else if(aux2->info->exp < aux1->info->exp){
            printf("%dx^%d ",aux2->info->coeficente, aux2->info->exp);
            aux2 = aux2->prox;
        }else{
            s = aux2->info->coeficente + aux1->info->coeficente;
            if(s != 0){
                printf("%dx^%d ", s, aux2->info->exp);
            }
            aux1 = aux1->prox;
            aux2 = aux2->prox;
        }
    }
    if(aux1->info->exp < aux2->info->exp){
        printf("%dx^%d ", aux1->info->coeficente, aux1->info->exp);
        aux1 = aux1->prox;
    }else if(aux2->info->exp < aux1->info->exp){
        printf("%dx^%d ",aux2->info->coeficente, aux2->info->exp);
        aux2 = aux2->prox;
    }else{
        s = aux2->info->coeficente + aux1->info->coeficente;
        if(s != 0){
            printf("%dx^%d ", s, aux2->info->exp);
        }
        aux1 = aux1->prox;
        aux2 = aux2->prox;
    }
        
}


int menu(){
    int op;
    printf("1...Cadastrar Polinomios\n2...Somar Dois Polinomios\n3...Multiplicar Dois Polinomios\n0...Sair\n");
    scanf("%d", &op);
    setbuf(stdin, NULL);
    return op;
}

int main(){
    struct Lista1 *pol[TAM], *No, *soma;

    for(int i=0; i < TAM; i++){
        pol[i] = NULL;
    }
    soma = NULL;

    int op, i=0, esc1, esc2;
    int coef, exp;

    do{
        op = menu();
        switch (op)
        {
        case 1:
            printf("x: ");
            scanf("%d", &coef);
            setbuf(stdin, NULL);
            printf("expoente de x: ");
            scanf("%d", &exp);
            No = aloca_lista(coef, exp);
            insere_elemento(&pol[i], No);
            printf("y: ");
            scanf("%d", &coef);
            setbuf(stdin, NULL);
            printf("expoente de y: ");
            scanf("%d", &exp);
            No = aloca_lista(coef, exp);
            insere_elemento(&pol[i], No);
            printf("z: ");
            scanf("%d", &coef);
            setbuf(stdin, NULL);
            printf("expoente de z: ");
            scanf("%d", &exp);
            setbuf(stdin, NULL);
            No = aloca_lista(coef, exp);
            insere_elemento(&pol[i], No);
            i++;
            break;
        case 2:
        for(int a=0; a < i; a++){
            printf("Polinomio %d\n", a);
            imprimir(pol[a]);
        }
        printf("Escolha um polinomio: ");
        scanf("%d", &esc1);
        setbuf(stdin, NULL);
        printf("Escolha outro polinomio: ");
        scanf("%d", &esc2);
        soma_polinomios(pol[esc1], pol[esc2]);

        default:
            break;
        }
    }while(op != 0);


    return 0;
}