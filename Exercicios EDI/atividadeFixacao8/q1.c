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
struct Lista1 *aloca_lista(int info){
    struct Lista1 *new;
    new = NULL;

    new = (struct Lista1*)malloc(sizeof(struct Lista1));
    new->info = (struct Lista*)malloc(sizeof(struct Lista));
    
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

//imprime invertido
void imprimir(struct Lista1 *begin){
    struct Lista1 *aux;

    aux = begin;
    
    if(aux != NULL){
        imprimir(aux->prox);
        printf("<- %d -> ", aux->info->valor);
    }
    
}

//retorna a quantidade de vizinhos
int vizinhos(struct Lista1 **begin, int elem){
    struct Lista1 *ant, *aux;
    int qtd=0;

    ant = *begin;
    aux = (*begin)->prox;

    if(ant->info->valor == elem && aux != NULL){//se for o primeiro e o prox for != NULL
        qtd++;

    }else if(aux != NULL){
        while(aux != NULL && aux->info->valor != elem){//percorre a lista até encontrar valor ou chegar ao final
            ant = aux;
            aux = aux->prox;
        }
        if (aux->info->valor == elem && aux->prox != NULL)// se encontrar o valor e o proximo nao for NULL
        {
            qtd += 2;
        }else if(aux->info->valor == elem)// se o proximo for NULL so tem o vizinho da esquerda
            {
                qtd++;
            }
    }

    return qtd;
}


int prod_vizinhos(struct Lista1 **begin, struct Lista1 **end, int elem){
    struct Lista1 *ant, *aux;
    int qtd, prod;


    qtd = vizinhos(begin, elem);//verifica quantos vizinhos tem

    if(qtd == 2){// se houver dois vizinhos
        ant = *begin;
        aux = (*begin)->prox;
        while(aux->info->valor != elem){
            ant = aux;
            aux = aux->prox;
        }
        prod = ant->info->valor * aux->prox->info->valor;
    }else if(qtd == 1){//se tiver somente um vizinho
        if((*begin)->info->valor == elem){//se for o primeiro elemento
            prod = (*begin)->prox->info->valor;// devolve o valor do vizinho a direita
        }else{// se nao é o ultimo elemento
             prod = (*end)->ant->info->valor;
        }
    }else{// se nao houver vizinhos
        prod = -1;
    }

    return prod;
}

int menu(){
    int op;
    
    printf("1 - Imprimir Invertida\n2 - Quantidade de Vizinhos\n3 - Produto dos Vizinhos\n4 - Remover Elemento\n0 - Sair\n");
    scanf("%d", &op);
    setbuf(stdin,NULL);

    return (op);

}

int main(){

    struct Lista1 *l1_begin, *l1_end, *No;
    int op, esc, valor, qtd_viz, produto, removido;

    l1_begin = NULL;
    l1_end = NULL;

    printf("Preencha a Lista!\n ");
    do{ 
        printf("Digite um Inteiro: ");
        scanf("%d", &valor);
        No = aloca_lista(valor); 

        insere(&l1_begin, &l1_end, No);
        printf("Continuar? (1-SIM | 0-NAO): ");
        scanf("%d", &esc);

    }while(esc != 0);
    do{
        
        op = menu();
        switch (op)
        {
        case 1:
            imprimir(l1_begin);
            printf("\n");
            break;
        case 2:
            printf("Digite o numero: ");
            scanf("%d", &valor);
            qtd_viz = vizinhos(&l1_begin, valor);
            printf("%d tem %d vizinhos\n", valor, qtd_viz);
            break;
        
        case 3:
            printf("Digite o numero: ");
            scanf("%d", &valor);
            produto = prod_vizinhos(&l1_begin, &l1_end, valor);
            printf("Produto dos vizinhos = %d\n", produto);
            break;
        case 4:
            printf("Digite o numero: ");
            scanf("%d", &valor);
            removido = remover_elemento(&l1_begin, valor);
            if(removido){
               printf("Removido!\n");
            }else{
                printf("Elemento não encontrado!\n");
            }
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }   
        
    }while(op != 0);

    return 0;
}