#include <stdio.h>
#include <stdlib.h>


struct fila_process{
    int id, time, priority, qtd_out;
    struct fila_process *prox;
};



///////////////////////// BASICS ///////////////////////////////

struct fila_process *alocaNo(){
    struct fila_process *new;
    new = NULL;

    new = (struct fila_process*)malloc(sizeof(struct fila_process));


    return new;
}

void ler_info(struct fila_process *No){
    int id, time, priority;

    printf("Numero do Processo: ");
    scanf("%d", &id);
    printf("Tempo do Processo: ");
    scanf("%d", &time);
    do{
        printf("Prioridade do Processo: ");
        scanf("%d", &priority);
    }while(priority > 3 || priority < 1);
    

    (*No).id = id;
    (*No).time = time;
    (*No).priority = priority;
    (*No).qtd_out = 0;
    (*No).prox = NULL;

}

void insere_fila(struct fila_process **begin, struct fila_process **end, struct fila_process *No){
    if(*begin == NULL && *end == NULL){
        *begin = No;
        *end = No;
    }
    else{
        (**end).prox = No;
        *end= No;
    }
}

struct fila_process *remove_fila(struct fila_process **begin, struct fila_process **end){
    struct fila_process *aux, *out;
    out = alocaNo();
    if(*begin != NULL){
        aux = *begin;

        (*out).id = (**begin).id;
        (*out).time = (**begin).time;
        (*out).priority = (**begin).priority;
        (*out).qtd_out = (**begin).qtd_out;

        if((*begin)->prox != NULL){
            *begin = (**begin).prox;
        }else{
            *begin = *end = NULL;
        }
        free(aux);
    }
    return out;
}

////////////////////////////////////////////////////////////////

int escalonador(struct fila_process **begin1, struct fila_process **end1, struct fila_process **begin2, struct fila_process **end2, struct fila_process **begin3, struct fila_process **end3){
    struct fila_process *aux;
    aux = alocaNo();
    int res=-1;
    if(*begin3 != NULL){
        aux = remove_fila(begin3,end3);
        if(aux->time != 0){
            aux->time--; //diminui o tempo do processo
            printf("Processando o processo %d na fila de prioridade %d...\n", aux->id, aux->priority);
        }
        aux->qtd_out++; // qtd de vezes que processou 
        if (aux->time == 0)
        {
            res = aux->id;
            free(aux);
        }else if(aux->qtd_out < 2){
            insere_fila(begin3,end3,aux);
        }else{
            aux->qtd_out = 0;
            insere_fila(begin2, end2, aux);
        }
        
    }else if( *begin2 != NULL){
        aux = remove_fila(begin2,end2);
        if(aux->time != 0){
            aux->time--; //diminui o tempo do processo
            printf("Processando %d na fila de prioridade %d...\n", aux->id, aux->priority);
        }
        aux->qtd_out++;
        
        if(aux->time == 0){
            res = aux->id;
            free(aux);
        }else if( aux->qtd_out < 2){
            insere_fila(begin2, end2, aux);
        }
        else{
            aux->qtd_out = 0;
            insere_fila(begin1, end1, aux);
        }
    }else if(*begin1 != NULL){
        aux = remove_fila(begin1,end1);
        if(aux->time != 0){
            aux->time--; //diminui o tempo do processo
            printf("Processando %d na fila de prioridade %d...\n", aux->id, aux->priority);
        }
        if(aux->time == 0){
            res = aux->id;
            free(aux);
        }else{
            insere_fila(begin1, end1, aux);
        }
    }else{
        res = -2;
    }
    return res;
}


void mostrar_processos(struct fila_process *I){
    struct fila_process *aux;
    aux = I;
    while (aux != NULL)
    {
        printf("\n------------------\nNumero do Processo: %d\nTempo do Processo: %d\nPrioridade do Processo: %d\n------------------\n", aux->id,aux->time, aux->priority);
        aux = aux->prox;
    }
    

}


void prox_process(struct fila_process *begin1, struct fila_process *begin2, struct fila_process *begin3){
    if(begin3 != NULL){
        
    }
}

int menu(){
    int opcao;

    printf("1- Adicionar Processos\n2- Escolher Processo\n3- Mostrar Processos\n4- Proximo Processo\n5- Quantidade de Processos\n6- Tempo Restante em Uma Fila\n7- Tempo Ate Chegar Em Um Processo\n8- Tempo Restante Em Cada Fila E Em Todas\n0- Sair\n");

    printf("Digite uma opcao: ");
    scanf("%d",&opcao);

    return (opcao);
}

int main(){
    struct fila_process *I1, *I2, *I3, *F1, *F2, *F3, *No;

    int op, op2, id_saiu=-1;

    I1 = NULL;
    F1 = NULL;
    I2 = NULL;
    F2 = NULL;
    I3 = NULL;
    F3 = NULL;
    


    do{
        op = menu();
        switch (op)
        {
        case 1:
            do{
                No = alocaNo();
                ler_info(No);
                if(No->priority == 1){
                    insere_fila(&I1, &F1, No);
                }else if(No->priority == 2){
                    insere_fila(&I2, &F2, No);
                }else{
                    insere_fila(&I3, &F3, No);
                }
                printf("Continuar? (1-SIM || 0-NAO): ");
                scanf("%d", &op2);
            }while(op2 == 1);
 
            break;
        case 2:
            id_saiu = escalonador(&I1,&F1,&I2,&F2,&I3,&F3);
            if(id_saiu != -1 && id_saiu != -2){
                printf("Processo %d Finalizado!\n", id_saiu);
                id_saiu = -1;
            }else if (id_saiu == -2){
                printf("Nenhum processo na fila!\n");
            }
            break;
        case 3:
            printf("FILA DE PRIORIDADE 1\n");
            mostrar_processos(I1);
            printf("FILA DE PRIORIDADE 2\n");
            mostrar_processos(I2);
            printf("FILA DE PRIORIDADE 3\n");
            mostrar_processos(I3);
            break;
        
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    }while(op != 0);


    return 0;
}