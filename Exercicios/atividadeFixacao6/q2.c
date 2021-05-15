#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct alunos{
    int matricula, ano_escolar, idade;
    char nome[100];

    struct alunos *prox;
};

////////////////////////BASICS//////////////////////////////////////

//aloca  espaço para um aluno
struct alunos *alocaNo(){
    struct alunos *new;

    new = NULL;
    new = (struct alunos*)malloc(sizeof(struct alunos));
    
    
    return new;

}

//Ler os dados de um aluno diretamente
void ler_aluno(struct alunos *No){
    
    printf("Matricula: ");
    scanf("%d", &(*No).matricula);
    printf("Nome: ");
    scanf("%s", No->nome);
    do{
        printf("Ano Escolar: ");
        scanf("%d", &(*No).ano_escolar);
        if(No->ano_escolar < 5 || No->ano_escolar > 9){
            printf("so existem os anos entre 5 e 9\n");
        }
    }while(No->ano_escolar < 5 || No->ano_escolar > 9);
    printf("Idade: ");
    scanf("%d", &(*No).idade);

}


// adiciona um aluno na fila
void add_fila(struct alunos **I, struct alunos **F, struct alunos *No){

    if(*I == NULL){
        *I = *F = No;
    }else{  
        (**F).prox = No;
        *F = No;
    }

}

//retira o primeiro da fila

void out_fila(struct alunos *I, struct alunos **F){
    struct alunos *aux;

    if(I != NULL){
        aux = I;
        if (I->prox != NULL)
        {
            I = I->prox;
            
        }else{
            I = *F = I->prox;
        }
        free(aux);
    }
       
}



/////////////////////////////////////////////////

///imprime fila
void imprimir(struct alunos *I){
    if(I != NULL){
        printf("=======================\n");
        printf("Matricula: %d\n", I->matricula);
        printf("Nome: %s\n", I->nome);
        printf("Ano Escolar: %d\n", I->ano_escolar);
        printf("Idade: %d\n", I->idade);
        printf("=======================\n");
        imprimir(I->prox);// chama recursivamente passando o proximo como parametro
    }
}


//tira aluno pela matricula
void out_matricula(struct alunos *I, struct alunos *F, int mat){
    
    if(I != NULL){
        if(I->matricula == mat){
            out_fila(I,&F);
        }else{
            out_matricula(I->prox, F, mat);
        }
    }
}

void divide(struct alunos *I, struct alunos **F, struct alunos **Ires, struct alunos **Fres, int ano){
    
    if (I != NULL && I->ano_escolar == ano)
    {
        
        if(*Ires == NULL){
            *Ires = *Fres = I;
        }else{
            (**Fres).prox = I;
            *Fres = I;
        }
        out_fila(I,F);
        printf("matricula %d adicionado a fila do %d ano\n", (**Fres).matricula , ano);
    }else if(I != NULL){
        divide(I,F, Ires, Fres, ano);
    }
    
}

// menu de opções
int menu(){
    int opcao;

    printf("1- Adicionar na fila\n2- Imprimir Fila\n3- Retirar Por Matricula\n4- Dividir Fila\n0- Sair\n");

    printf("Digite uma opcao: ");
    scanf("%d",&opcao);

    return (opcao);
}

int submenu(){
    int op;

    printf("0- fila Principal\n1- 5ano\n2- 6ano\n3- 7ano\n4- 8ano\n5- 9ano\n");
    printf("Digite uma opcao: ");
    scanf("%d",&op);

    return (op);
}


int main(){
    struct alunos *begin, *end, *begin1, *end1, *begin2, *end2, *begin3, *end3, *begin4, *end4, *begin5, *end5, *No;

    int matricula, mat, ano_escolar, idade, op, op2;
    char nome[100];

    begin = end = NULL;
    begin1 = end1 = NULL;
    begin2 = end2 = NULL;
    begin3 = end3 = NULL;
    begin4 = end4 = NULL;
    begin5 = end5 = NULL;
    
    do{
        op = menu();

        switch (op)
        {
            case 1:
                No = alocaNo();
                ler_aluno(No); 
                add_fila(&begin, &end, No);
                break;
            
            case 2:
                op2 = submenu();
                switch (op2)
                {
                case 0:
                    imprimir(begin);
                    break;
                case 1:
                    imprimir(begin1);
                    break;
                case 2:
                    imprimir(begin2);
                    break;
                case 3:
                    imprimir(begin3);
                    break;
                case 4:
                    imprimir(begin4);
                    break;
                case 5:
                    imprimir(begin5);
                    break;
                default:
                    break;
                }
                break;
            case 3:
                printf("Digite a matricula: ");
                scanf("%d", &mat);
                out_matricula(begin,end, mat);
               
                break;
            
            case 4:
                divide(begin, &end, &begin1, &end1, 5);
                //divide(begin, &end, &begin2, &end2, 6);
                //divide(begin, &end, &begin3, &end3, 7);
                //divide(begin, &end, &begin4, &end4, 8);
                //divide(begin, &end, &begin5, &end5, 9);
                printf("Fila dividida em 5 filas diferentes!\nTente imprimir alguma fila.\n");
                break;
            default:
                break;
        }
        
    }while(op != 0);

    return 0;
}