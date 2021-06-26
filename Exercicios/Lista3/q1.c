#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>// gcc q1.c -lm ----- compilar desta forma

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

//insere elementos no polinomio
void insere_elemento(struct Lista1 **begin, struct Lista1 *No){

    struct Lista1 *aux;

    aux = *begin;
    //insere o primeiro elemento
    if(*begin == NULL){
        *begin = No;
        No->prox = No;
    }else{
        while(aux->prox != *begin){// enquanto o proximo elemento não apontar para o inicio
            aux = aux->prox;
        }
        No->prox = *begin;
        aux->prox = No;

    }

}

void imprimir(struct Lista1 *begin){
    struct Lista1 *aux;
    aux = begin;
    while(aux->prox != begin){
        printf("%d^%d\n", aux->info->coeficente, aux->info->exp);
        aux = aux->prox;
    }
    printf("%d^%d\n", aux->info->coeficente, aux->info->exp);

}


//exibe a soma de dois polinomios
void soma_polinomios(struct Lista1 *pol1, struct Lista1 *pol2){
    struct Lista1 *aux1, *aux2;

    int s;
    
    aux1 = pol1;
    aux2  = pol2;
    //soma x
    if(aux1->info->exp == aux2->info->exp){
        s = aux1->info->coeficente + aux2->info->coeficente;
        printf("%dx^%d ", s, aux1->info->exp);
    }else{
        printf("%dx^%d + %dx^%d + ", aux1->info->coeficente, aux1->info->exp, aux2->info->coeficente, aux2->info->exp);
    }
    //soma y
    if((aux1->prox != pol1 && aux2->prox != pol2) && aux1->prox->info->exp == aux2->prox->info->exp){
        s = aux1->prox->info->coeficente + aux2->prox->info->coeficente;
        printf("+ %dy^%d ", s, aux1->prox->info->exp);
    }else if(aux1->prox != pol1 && aux2->prox == pol2){
        printf("+ %dy^%d ", aux1->prox->info->coeficente, aux1->prox->info->exp);
    }else if(aux1->prox == pol1 && aux2->prox != pol2){
        printf("+ %dy^%d ", aux2->prox->info->coeficente, aux2->prox->info->exp);
    }
    else if(aux1->prox != pol1 && aux2->prox != pol2){
        printf("+ %dy^%d + %dy^%d ", aux1->prox->info->coeficente, aux1->prox->info->exp, aux2->prox->info->coeficente, aux2->prox->info->exp);
    }
    //soma z
    if((aux1->prox->prox != pol1 && aux2->prox->prox != pol2) && aux1->prox->prox->info->exp == aux2->prox->prox->info->exp){
        s = aux1->prox->prox->info->coeficente + aux2->prox->prox->info->coeficente;
        printf("+ %dz^%d ", s, aux1->prox->prox->info->exp);
    }else if(aux1->prox->prox != pol1 && aux2->prox->prox == pol2){
        printf("+ %dz^%d ", aux1->prox->prox->info->coeficente, aux1->prox->prox->info->exp);
    }else if(aux1->prox->prox == pol1 && aux2->prox->prox != pol2){
        printf("+ %dz^%d ", aux2->prox->prox->info->coeficente, aux2->prox->prox->info->exp);
    }
    else if(aux1->prox->prox != pol1 && aux2->prox->prox != pol2){
        printf("+ %dz^%d + %dz^%d ", aux1->prox->prox->info->coeficente, aux1->prox->prox->info->exp, aux2->prox->prox->info->coeficente, aux2->prox->prox->info->exp);
    }
    

        
}



//multiplica polinomios

void mult_polinomios(struct Lista1 *pol1, struct Lista1 *pol2){
    struct Lista1 *aux1, *aux2;

    int m;
    
    aux1 = pol1;
    aux2  = pol2;

    //multiplica x
    if(aux1->info->coeficente == aux2->info->coeficente){
        m = aux1->info->exp + aux2->info->exp;
        printf("%dx^%d ", aux1->info->coeficente, m);
    }else{
        printf("%dx^%d * %dx^%d ", aux1->info->coeficente, aux1->info->exp, aux2->info->coeficente, aux2->info->exp);
    }
    //multiplica y
    if((aux1->prox != pol1 && aux2->prox != pol2) && aux1->prox->info->coeficente == aux2->prox->info->coeficente){
        m = aux1->prox->info->exp + aux2->prox->info->exp;
        printf("+ %dy^%d ", aux1->prox->info->coeficente, m);
    }else if(aux1->prox != pol1 && aux2->prox == pol2){
        printf("+ %dy^%d ", aux1->prox->info->coeficente, aux1->prox->info->exp);
    }else if(aux1->prox == pol1 && aux2->prox != pol2){
        printf("+ %dy^%d ", aux2->prox->info->coeficente, aux2->prox->info->exp);
    }
    else if(aux1->prox != pol1 && aux2->prox != pol2){
        printf("+ %dy^%d * %dy^%d ", aux1->prox->info->coeficente, aux1->prox->info->exp, aux2->prox->info->coeficente, aux2->prox->info->exp);
    }
    //multiplica z
    if((aux1->prox->prox != pol1 && aux2->prox->prox != pol2) && aux1->prox->prox->info->coeficente == aux2->prox->prox->info->coeficente){
        m = aux1->prox->prox->info->exp + aux2->prox->prox->info->exp;
        printf("+ %dz^%d ", aux1->prox->prox->info->coeficente, m);
    }else if(aux1->prox->prox != pol1 && aux2->prox->prox == pol2){
        printf("+ %dz^%d ", aux1->prox->prox->info->coeficente, aux1->prox->prox->info->exp);
    }else if(aux1->prox->prox == pol1 && aux2->prox->prox != pol2){
        printf("+ %dz^%d ", aux2->prox->prox->info->coeficente, aux2->prox->prox->info->exp);
    }
    else if(aux1->prox->prox != pol1 && aux2->prox->prox != pol2){
        printf("+ %dz^%d * %dz^%d ", aux1->prox->prox->info->coeficente, aux1->prox->prox->info->exp, aux2->prox->prox->info->coeficente, aux2->prox->prox->info->exp);
    }
}


//avalia polinomio

void avaliacao_poli(struct Lista1 *pol1, int x, int y, int z){
    struct Lista1 *aux;
    int total=0;

    aux = pol1;
    printf("%d * %d^%d ", aux->info->coeficente, x, aux->info->exp);
    total += aux->info->coeficente * (pow(x,aux->info->exp));

    if (aux->prox != pol1){
        printf("+ %d * %d^%d ", aux->prox->info->coeficente, y, aux->prox->info->exp);
        total += aux->prox->info->coeficente * (pow(y,aux->prox->info->exp));
    }

    if(aux->prox->prox != pol1){
        printf("+ %d * %d^%d ", aux->prox->prox->info->coeficente, z, aux->prox->prox->info->exp);
        total += aux->prox->prox->info->coeficente * (pow(z,aux->prox->prox->info->exp));
    }
    printf("= %d", total);

}


void representar_poli(struct Lista1 *pol){
    struct Lista1 *aux;

    aux = pol;

    printf("%dx^%d ", aux->info->coeficente, aux->info->exp);
    if(aux->prox != pol){
        printf("+ %dy^%d ", aux->prox->info->coeficente, aux->prox->info->exp);
        if(aux->prox->prox != pol){
            printf("+ %dz^%d ", aux->prox->prox->info->coeficente, aux->prox->prox->info->exp);
        }
    }
    
}


void derivada_parcial(struct Lista1 *pol, int xyz){
    struct Lista1 *aux;

    aux = pol;
    //em f(x)
    if(xyz == 1){
        printf("%dx ", aux->info->exp);
        if(aux->prox != pol){
            printf("+ %dy^%d ", aux->prox->info->coeficente, aux->prox->info->exp);
            if(aux->prox->prox != pol){
                printf("+ %dz^%d ", aux->prox->prox->info->coeficente, aux->prox->prox->info->exp);
            }
        }
    }
//em f(y)
    if(xyz == 2){
        printf("%dy^%d ", aux->info->coeficente,aux->prox->info->exp);
        if(aux->prox != pol){
            printf("+ %dy ", aux->prox->info->exp);
            if(aux->prox->prox != pol){
                printf("+ %dz^%d ", aux->prox->prox->info->coeficente, aux->prox->prox->info->exp);
            }
        }
    }
//em f(z)
    if(xyz == 3){
        printf("%dy^%d ", aux->info->coeficente,aux->prox->info->exp);
        if(aux->prox != pol){
            printf("+ %dy^%d ", aux->prox->info->coeficente, aux->prox->info->exp);
            if(aux->prox->prox != pol){
                printf("+ %dz ", aux->prox->prox->info->exp);
            }
        }
    }

}




int menu(){
    int op;
    printf("1...Cadastrar Polinomios\n2...Somar Dois Polinomios\n3...Multiplicar Dois Polinomios\n4...Avaliar Polinomio\n5...Representacao de Um Polinomio\n6...Representacao de Todos os Polinomios\n7...Derivada Parcial\n0...Sair\n");
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

    int op, op1, i=0, esc1, esc2, x, y, z,v;
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

            printf("Pretende ler Y? (1 - SIM || 2  - NAO): ");
            scanf("%d", &op1);
            if(op1 == 1){
                printf("y: ");
                scanf("%d", &coef);
                setbuf(stdin, NULL);
                printf("expoente de y: ");
                scanf("%d", &exp);

                No = aloca_lista(coef, exp);
                insere_elemento(&pol[i], No);

                printf("Pretende ler Z? (1 - SIM || 2  - NAO): ");
                scanf("%d", &op1);

            }
            if(op1 == 1){
                printf("z: ");
                scanf("%d", &coef);
                setbuf(stdin, NULL);
                printf("expoente de z: ");
                scanf("%d", &exp);
                setbuf(stdin, NULL);

                No = aloca_lista(coef, exp);
                insere_elemento(&pol[i], No);
            }
            i++;

            break;
        case 2:
            //soma
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
            printf("\n");
            break;

        case 3:
        //multiplica
            for(int a=0; a < i; a++){
                printf("Polinomio %d\n", a);
                imprimir(pol[a]);
            }
            printf("Escolha um polinomio: ");
            scanf("%d", &esc1);
            setbuf(stdin, NULL);
            printf("Escolha outro polinomio: ");
            scanf("%d", &esc2);
            mult_polinomios(pol[esc1], pol[esc2]);
            printf("\n");
            break;

        case 4:
            for(int a=0; a < i; a++){
                printf("Polinomio %d\n", a);
                imprimir(pol[a]);
            }
            printf("Escolha um polinomio: ");
            scanf("%d", &esc1);
            setbuf(stdin, NULL);

            printf("Valor de X: ");
            scanf("%d", &x);
            if(pol[esc1]->prox != pol[esc1]){
                printf("Valor de Y: ");
                scanf("%d", &y);
                if(pol[esc1]->prox->prox != pol[esc1]){
                    printf("Valor de Z: ");
                    scanf("%d", &z);
                }
            }
            avaliacao_poli(pol[esc1], x, y, z);
            printf("\n");

            break;

        case 5:
            for(int a=0; a < i; a++){
                printf("Polinomio %d\n", a);
                imprimir(pol[a]);
            }
            printf("Escolha um polinomio: ");
            scanf("%d", &esc1);
            setbuf(stdin, NULL);
            representar_poli(pol[esc1]);
            printf("\n");
            break;
        
        case 6:
            for(int a=0; a < i; a++){
                printf("Polinomio %d\n", a);
                representar_poli(pol[a]);
                printf("\n\n");
            }  
            break;
        
        case 7:
            for(int a=0; a < i; a++){
                printf("Polinomio %d\n", a);
                imprimir(pol[a]);
            }
            printf("Escolha um polinomio: ");
            scanf("%d", &esc1);

            printf("Em relacao a qual variavel? (1 p/ x || 2 p/ y || 3 p/ z): ");
            scanf("%d", &v);
            derivada_parcial(pol[esc1], v);
            printf("\n");
            break;
        default:
            if(op != 0){
                printf("Opcao Invalida!\n");
            }
            break;
        }
    }while(op != 0);


    return 0;
}