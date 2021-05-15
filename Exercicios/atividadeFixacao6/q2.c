#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct alunos{
    int matricula, ano_escolar, idade;
    char nome[100];

    struct alunos *prox, *ant;
};

////////////////////////BASICS//////////////////////////////////////
//aloca espaço de memoria para um aluno e ler os dados
struct alunos *aloca_ler_aluno(int mat, char nome[100], int ano, int idade){
    struct alunos *new;

    new = NULL;
    new = (struct alunos*)malloc(sizeof(struct alunos));

    new->matricula = mat;
    strcpy(new->nome, nome);
    new->ano_escolar = ano;
    new->idade = idade;
    
    return new;

}

void add_fila(struct alunos **I, struct alunos **F, struct alunos *No){

    if(*I == NULL){
        *I = *F = No;
    }else{
        (**F).prox = No;
        *F = No;
    }

}

struct alunos *out_fila(struct alunos *I, struct alunos **F){
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
        
    return I;
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
int out_matricula(struct alunos *I, int mat){
    struct alunos *aux;
    int res=-1;

    if(I != NULL && I->matricula == mat){
        aux = I;

        res = aux->matricula;

        I = I->prox; 
    
        free(aux);

    }else if(I != NULL){
        out_matricula(I->prox, mat);
    }

    return res;
}

void divide(struct alunos *I, struct alunos **F, struct alunos **Ires, struct alunos **Fres, int ano){
    

    if (I != NULL && I->ano_escolar == ano)
    {
        if(*Ires == NULL){
            **Ires = *I;
            **Fres = *I;
        }else{
            
        }
    }
    

}

// menu de opções
int menu(){
    int opcao;

    printf("1- Adicionar na fila\n2- Imprimir Fila\n3- Retirar Por Matricula\n0- Sair\n");

    printf("Digite um opcao: ");
    scanf("%d",&opcao);

    return (opcao);
}

int submenu(){
    int op;

    printf("0- fila Principal\n1- 1ano\n2- 2ano Fila\n3-3ano\n4- 4ano\n5- 5ano\n");
    printf("Digite um opcao: ");
    scanf("%d",&op);

    return (op);
}


int main(){
    struct alunos *begin, *end, *begin1, *end1, *begin2, *end2, *begin3, *end3, *begin4, *end4, *begin5, *end5, *No, *No1, *No2, *No3, *No4, *No5;

    int matricula, mat, ano_escolar, idade, op, op2;
    char nome[100];

    begin = NULL;
    begin1 = NULL;
    begin2 = NULL;
    begin3 = NULL;
    begin4 = NULL;
    begin5 = NULL;
    do{
        op = menu();

        switch (op)
        {
            case 1:
                printf("Matricula: ");
                scanf("%d", &matricula);
                printf("Nome: ");
                scanf("%s", nome);
                do{
                    printf("Ano Escolar: ");
                    scanf("%d", &ano_escolar);
                }while(ano_escolar > 9 && ano_escolar < 5);

                printf("Idade: ");
                scanf("%d", &idade);
                No = aloca_ler_aluno(matricula, nome, ano_escolar, idade);
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
            case 3:
                printf("Digite a matricula: ");
                scanf("%d", &mat);
                mat = out_matricula(begin, mat);
                if (mat == -1){
                    printf("nao encontrado!\n");
                }else{
                    printf("%d removido!\n", mat);
                }
                break;
            
            case 4:
                printf("Fila dividida em 5 filas diferentes!\nTente imprimir alguma fila.\n");
                break;
            default:
                break;
        }
        
    }while(op != 0);

    return 0;
}