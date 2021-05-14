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
// menu de opções
int menu(){
    int opcao;

    printf("1- Adicionar na fila\n2- Imprimir Fila\n\n0- Sair\n");

    printf("Digite um opcao: ");
    scanf("%d",&opcao);

    return (opcao);
}

int main(){
    struct alunos *begin, *end, *No;

    int matricula, ano_escolar, idade, op;
    char nome[100];

    do{
        op = menu();

        switch (op)
        {
            case 1:
                printf("Matricula: ");
                scanf("%d", &matricula);
                printf("Nome: ");
                scanf("%s", nome);
                printf("Ano Escolar: ");
                scanf("%d", &ano_escolar);
                printf("Idade: ");
                scanf("%d", &idade);
                No = aloca_ler_aluno(matricula, nome, ano_escolar, idade);
                add_fila(&begin, &end, No);
                break;
            
            default:
                break;
        }
        
    }while(op != 0);

    return 0;
}