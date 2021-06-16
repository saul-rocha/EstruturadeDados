#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lista{
    int cpf, idade;
    char nome[50];

};

struct Lista1{
    struct Lista *info;
    struct Lista1 *ant, *prox;
};
/* BASICS */

// aloca um elemento
struct Lista1 *aloca_lista(int cpf, char nome[50], int idade){
    struct Lista1 *new;
    new = NULL;

    new = (struct Lista1*)malloc(sizeof(struct Lista1));
    new->info = (struct Lista*)malloc(sizeof(struct Lista));
    
    new->info->cpf = cpf;
    new->info->idade = idade;
    strcpy(new->info->nome,nome);

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
    }else if(No->info->cpf < (*begin)->info->cpf){
        aux = *begin;
        aux->ant = No;
        No->prox = aux;
        *begin = No;
    }
    //insere no fim
    else if(No->info->cpf > (*end)->info->cpf){
       
        aux = *end;
        aux->prox = No;
        No->ant = aux;
        *end = No;
        
    }else{//insere no meio
        aux = *begin;
        while((No->info->cpf > aux->info->cpf) && aux != NULL){// quando o novo elemento for menor que o aux, faz a inserção
            ant = aux;
            aux = aux->prox;
        }
        No->prox = aux;// o proximo do novo elemento aponta para o aux que  é o elemento maior que ele
        aux->ant = No;
        ant->prox = No;// o anterior  apontará para o novo que é o proximo dele
        No->ant = ant;
    }

}


int remover_elemento(struct Lista1 **begin, int cpf){
    struct Lista1 *aux, *ant;

    int res=0;  
    
    aux = *begin;
    
    
    while (aux != NULL && aux->info->cpf != cpf){
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


void gerar_nova_lista(struct Lista1 **begin, struct Lista1 **res_begin, struct Lista1 **res_end, int cpf){
    struct Lista1 *aux, *prox, *prox1, *No;

    aux = *begin;

    while(aux->info->cpf != cpf && aux != NULL){//percorre a lista ate achar o elemento ou percorrer completamente a lista
        aux = aux->prox;
    }
    if(aux != NULL){// se nao fila nao estiver vazia
        prox = aux->prox;
        while(prox != NULL){
            prox1 = prox->prox;//guada o proximo elemento da lista
            No = aloca_lista(prox->info->cpf, prox->info->nome, prox->info->idade);//remove o elemento
            insere(res_begin, res_end, No);//insere na lista resultante
            prox = prox1;//prox recebe o proximo que foi guardado 

        }
        aux->prox = NULL; // anterior aponta para NULL pois agora será o ultimo da lista
    }

}


void imprimir(struct Lista1 *begin){
    struct Lista1 *aux;

    aux = begin;
    
    if(aux != NULL){
        printf("CPF: %d\nNome: %s\nIdade: %d\n\n", aux->info->cpf, aux->info->nome, aux->info->idade);
        imprimir(aux->prox);
    }
    
}
/////////////////////////////////////

int menu(){
    int op;
    
    printf("1 - Criar Lista a Partir de uma pessoa\n2 - Quantidade de Vizinhos\n3 - Produto dos Vizinhos\n4 - Remover Elemento\n0 - Sair\n");
    scanf("%d", &op);
    setbuf(stdin,NULL);

    return (op);

}

int main(){

    struct Lista1 *l1_begin, *l1_end, *l2_begin, *l2_end, *No;
    int op, esc, cpf, idade;
    char nome[50];

    l1_begin = NULL;
    l1_end = NULL;
    l2_begin = NULL;
    l2_end = NULL;

    printf("Preencha a Lista!\n ");
    do{ 
        printf("CPF: ");
        scanf("%d", &cpf);
        printf("Nome: ");
        scanf("%s", nome);
        printf("Idade: ");
        scanf("%d", &idade);
        setbuf(stdin,NULL);
        No = aloca_lista(cpf, nome, idade);  
        insere(&l1_begin, &l1_end, No);

        printf("Continuar? (1-SIM | 0-NAO): ");
        scanf("%d", &esc);
    }while(esc != 0);
    do{
        
        op = menu();
        switch (op)
        {
        case 1:
            printf("CPF: ");
            scanf("%d", &cpf);
            
            gerar_nova_lista(&l1_begin, &l2_begin, &l2_end, cpf);

            printf("\nLista Original\n");
            imprimir(l1_begin);
            printf("\nLista Resultante\n");
            imprimir(l2_begin);
            printf("\n");
            break;
        case 2:
            
            break;

        default:
            if(op != 0){
                printf("Opcao invalida!\n");
            }
            break;
        }   
        
    }while(op != 0);

    return 0;
}