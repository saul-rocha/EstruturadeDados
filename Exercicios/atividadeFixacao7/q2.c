#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Lista{
    char string[100];
    struct Lista *prox;
};

// aloca um elemento
struct Lista *aloca_lista(char info[100]){
    struct Lista *new;

    new = (struct Lista*)malloc(sizeof(struct Lista));

    strcpy(new->string, info);
    new->prox = NULL;

    return new;
}


void insere(struct Lista **begin, struct Lista **end, struct Lista *No){


    //insere no inicio e no fim
    if(*begin == NULL){
        *begin = No;
        *end = No;
    //insere no inicio
    }else {
        (*end)->prox = No;
        *end = No;
    }
}

void insere_ordenado(struct Lista **begin, struct Lista **end, struct Lista *No){

    struct Lista *aux, *ant;

    aux = *begin;
    //insere no inicio e no fim
    if(*begin == NULL){
        *begin = No;
        *end = No;
    //insere no inicio
    }else if(strlen(No->string) < strlen((*begin)->string)){
        *begin = No; // inicio agora é o novo
        No->prox = aux; //e o proximo do novo é o aux(que guardou o endereço do incio)

      
    }
    //insere no fim
    else if(strlen(No->string) > strlen((*end)->string)){
        aux = *end;
        aux->prox = No;
        *end = No;

        
    }else{//insere no meio
        aux = *begin;
        while((strlen(No->string) > strlen(aux->string)) && aux != NULL){// quando o novo elemento for menor que o aux, faz a inserção
            ant = aux;
            aux = aux->prox;
        }
        No->prox = aux;// o proximo do novo elemento aponta para o aux que  é o elemento maior que ele
        ant->prox = No;// o anterior  apontará para o novo que é o proximo dele
        
    }


}


int is_vogal(char a){
    int res = 0;
    if (toupper(a) == toupper('a') || toupper(a) == toupper('e') || toupper(a) == toupper('i') || toupper(a) == toupper('o') || toupper(a) == toupper('u')){
        res = 1;
    }
    return res;
}

void lista_conso_vogal(struct Lista **begin, struct Lista **res1, struct Lista **res_end1, struct Lista **res2, struct Lista **res2_end2){
    struct Lista *aux, *No;

    char str[100];

    aux = *begin; 
    while(aux != NULL){
        if (is_vogal(aux->string[0]) == 1){
            strcpy(str,aux->string);
            No = aloca_lista(str);
            insere(res1, res_end1, No);
            printf("aaa\n");
        }else{
            strcpy(str,aux->string);
            No = aloca_lista(str);
            insere(res2, res2_end2, No);
        }
        aux = aux->prox;
    }  
       
}

void vizinhas(struct Lista **begin, char str[100], char anterior[100], char prox[100]){
    struct Lista *ant, *aux;

    ant = *begin;
    aux = (*begin)->prox;

    if(strcmp(ant->string,str) == 0 && aux != NULL){//se for igual
        strcpy(prox,aux->string);
        strcpy(anterior,"Sem vizinho a esquerda");

    }else if(aux != NULL){
        while(aux != NULL && strcmp(aux->string,str) != 0){//percorre a lista até encontrar a string ou chegar ao final
            ant = aux;
            aux = aux->prox;
        }
        if (strcmp(aux->string,str) == 0 && aux->prox != NULL)// se encontrar a string e o proximo nao for NULL
        {
            strcpy(anterior,ant->string);
            strcpy(prox,aux->prox->string);
        }else if(strcmp(aux->string,str) == 0)// se o proximo for NULL
            {
                strcpy(anterior,ant->string);
                strcpy(prox,"Sem vizinho a direita");
            }
            else{//quando só tem uma string na lista
                strcpy(prox,"Sem vizinho a direita");
                strcpy(anterior,"Sem vizinho a esquerda");
            }
    }else{//string nao encontrada/lista vazia
        strcpy(anterior,"Nao encontrada");
        strcpy(prox,"Nao encontrada");
        
    }

}

//imprime
void imprimir(struct Lista *begin){
    struct Lista *aux;
    aux = begin;
    if(aux != NULL){
        printf("%s - ", aux->string);
        imprimir(aux->prox);//recursao sem pendencia
    }

}



int menu(){
    int op;
    
    printf("1 - Preencher Lista\n2 - Dividir em Lista Vogais e Lista Consoantes\n3 - Ordenar Lista\n4 - Strings Vizinhas\n0 - Sair\n");
    scanf("%d", &op);
    setbuf(stdin,NULL);

    return (op);
}

int main(){
    struct Lista *l_begin_origin, *l_end_origin, *l2, *l2_end, *l3, *l3_end, *l_ord, *l_end_ord, *No, *aux;

    char str[100], esq[100], dir[100];
    int op, esc;
    

    l_begin_origin = NULL;
    l_end_origin = NULL;
    l2 = NULL;
    l2_end = NULL;
    l3 = NULL;
    l3_end = NULL;
    l_ord = NULL;
    l_end_ord = NULL;

    do{
        op = menu();
        switch (op)
        {
        case 1:
            do{ 
        
                printf("Digite uma string: ");
                scanf("%s", str);
                No = aloca_lista(str);  
                insere(&l_begin_origin, &l_end_origin, No);

                printf("Continuar? (1-SIM | 0-NAO): ");
                scanf("%d", &esc);
            }while(esc != 0);

            break;
        case 2:
            lista_conso_vogal(&l_begin_origin, &l2, &l2_end, &l3, &l3_end);
            printf("Lista Vogais\n");
            imprimir(l2);
            printf("\n");
            printf("Lista Consoantes\n");
            imprimir(l3);
            printf("\n");
           break;
        
        case 3: 
            aux = l_begin_origin;
            while(aux != NULL){
                strcpy(str, aux->string);
                No = aloca_lista(str);  
                insere_ordenado(&l_ord, &l_end_ord, No);
                aux = aux->prox;
            }
            printf("Lista Ordenada\n");
            imprimir(l_ord);
            printf("\n");
            break;
        
        case 4:
            printf("Digite uma string: ");
            scanf("%s", str);
            vizinhas(&l_begin_origin, str, esq, dir);

            printf("Vizinha da Esquerda: %s\nVizinha da Direita: %s\n", esq, dir);
            break;
        default:
            break;
        }   
        
    }while(op != 0);

    return 0;
}