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


void insere(struct Lista **begin, struct Lista **end, struct Lista *No){

    struct Lista *aux, *ant;

    aux = *begin;
    //insere no fim
    if(*begin == NULL){
        *begin = No;
        *end = No;

    }else if(No->valor < (*begin)->valor){//se o novo valor for menor que o inicio
        *begin = No; // inicio agora é o novo
        No->prox = aux; //e o proximo do novo é o aux(que guardou o endereço do incio)

      
    }
    //insere no fim
    else if(No->valor > (*end)->valor){
        aux = *end;
        aux->prox = No;
        *end = No;

    
        
    }else{
        aux = *begin;
        while( No->valor > aux->valor && aux != NULL){// quando o novo elemento for menor que o aux, faz a inserção
            ant = aux;
            aux = aux->prox;
        }
        No->prox = aux;// o proximo do novo elemento aponta para o aux que  é o elemento maior que ele
        ant->prox = No;// o anterior  apontará para o novo que é o proximo dele
        
    }


}

int remover_item(struct Lista **begin, int item){
    struct Lista *aux, *ant;
    int res=0;

    if((*begin)->valor == item){//caso seja o primeiro elemento da lista
        res = (*begin)->valor;
        aux = *begin;
        *begin = (*begin)->prox;

        free(aux);
        
    }else{
        aux = (*begin)->prox;//aux recebe o segundo valor da lista
        ant = *begin; // ant recebe o o inicio
        while(aux != NULL && aux->valor != item){// enquanto aux for diferente de null e diferente do valor buscado, avança os dois ponteiras aux e ant
            ant = aux;
            aux = aux->prox;
        }
        if (aux != NULL){//caso encontre o valor res recebe o valor e o ant agora aponta para o proximo depois do aux.
            res = aux->valor;
            ant->prox = aux->prox;
            free(aux);//libera o aux
        }
    }    
    
    
    return res;
    
}


void imprimir_invertido(struct Lista *begin){
    struct Lista *aux;
    aux = begin;
    if(aux != NULL){
        imprimir_invertido(aux->prox);// chama recursivamentte passando o proximo elemento da lista como parametro  e deixando pendente o printf do valor
        printf("%d - ", aux->valor);
    }
}

//iterativa
void mult3_menor_60(struct Lista *begin){
    struct Lista *aux;
    aux = begin;
    while(aux != NULL){
        if(aux->valor % 3 == 0 && aux->valor < 60){
            printf("%d - ", aux->valor);
        }
        aux = aux->prox;
    }
}

//recursiva
void mult3_menor_60_rec(struct Lista *begin){
    struct Lista *aux;
    aux = begin;
    if(aux != NULL){
        if(aux->valor % 3 == 0 && aux->valor < 60){
            printf("%d - ", aux->valor);
        }
        mult3_menor_60_rec(aux->prox);//recursão sem oendência
    }
}

void altera(struct Lista **begin, struct Lista **end, int alterando, int alterador){
    struct Lista *aux, *ant, *No;
    int a;

    aux = (*begin)->prox;
    ant = *begin;

    if(ant->valor == alterando){//caso esteja no inicio
        ant->valor = alterador;//altera o valor
        if(ant->valor > aux->valor){//se estiver desordenado
            a = remover_item(begin, ant->valor);//remove
            No =  aloca_lista(a);
            insere(begin, end, No);// add novamente ordenado
        }
    }

    while (aux != NULL && aux->valor != alterando)
    {
        ant = aux;
        aux = aux->prox;
    }

    if(aux != NULL){
        aux->valor = alterador;
        if(aux->prox != NULL && aux->valor > aux->prox->valor){//se estiver desordenado
            a = remover_item(begin, aux->valor);//remove
            No =  aloca_lista(a);
            insere(begin, end, No);// add novamente ordenado
        }else if(aux->prox != NULL  && ant->valor > aux->valor){//se estiver desordenado
            a = remover_item(begin, aux->valor);//remove
            No =  aloca_lista(a);
            insere(begin, end, No);// add novamente ordenado
        }
    }
    
    

}

int menu(){
    int op;
    
    printf("1 - Inserir\n2 - Imprimir Invertido\n3 - Mult 3 && < 60\n4 - Remover\n5 - Alterar Valor\n0 - Sair\n");
    scanf("%d", &op);
    setbuf(stdin,NULL);

    return (op);
}

int main(){
    
    struct Lista *begin, *end, *No;
    int esc, num, verifica, op, removido, elem, elem2;

    begin = NULL;
    end = NULL;

    do{
        op = menu();
        switch (op)
        {
        case 1:
            do{ 
        
                printf("Digite um valor: ");
                scanf("%d", &num);
                No = aloca_lista(num);
                insere(&begin, &end, No);


                printf("Continuar? (1-SIM | 0-NAO): ");
                scanf("%d", &esc);
            }while(esc != 0);

            break;
        case 2:
            imprimir_invertido(begin);
            printf("\n");
            break;
        
        case 3:
            mult3_menor_60_rec(begin);
            printf("\n");
            break;
        
        case 4:
            printf("Digite o elemento que deseja remover: ");
            scanf("%d", &elem);
            removido = remover_item(&begin, elem);
            printf("Item removido %d!\n", removido);
            break;
        
        case 5:
            printf("Digite o elemento que deseja alterar: ");
            scanf("%d", &elem);

            printf("Digite o novo elemento: ");
            scanf("%d", &elem2);

            No = aloca_lista(elem2);
            altera(&begin, &end, elem, elem2);
        default:
            break;
        }
        
    }while(op != 0);
    
    return 0;
}