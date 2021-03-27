#include <stdio.h>
#include <stdlib.h>

#define TAM 5

// registro de Aluno
struct Aluno
{
    int mat;
    int idade;
    char nome[30];
    float altura;

};

void altinho(struct Aluno *a, float *alto);
int baixinho(struct Aluno *a);

int main(){
    struct Aluno aluno[TAM];
    float altMaior;
    int idadeMenor;

    for (int i = 0; i < TAM; i++)
    {
        printf("idade: ");
        scanf("%d", &aluno[i].idade);
        printf("altura: ");
        scanf("%f", &aluno[i].altura);
    }
    

    idadeMenor = baixinho(aluno);

    altinho(aluno, &altMaior);

    printf("Altura do maior: %.2f\nIdade do menor: %d\n", altMaior, idadeMenor);
    return (0);
}
// recebe um vetor de alunos e um float referenciado como parâmetros
void altinho(struct Aluno *a, float *alto){
    //percorre o vetor de alunos
    for(int i=0; i < TAM; i++)
    {
        // caso a altura do aluno na posição atual for maior que a referenciada
        // o valor da altura nessa posição é atribuida ao endereço referenciado
        if (a[i].altura > *alto)
        {
            *alto = a[i].altura;
        }        
    }
};


// recebe um vetor de Alunos como parâmetro e retorna a idade do aluno mais baixo
int baixinho(struct Aluno *a){
    // recebe como sendo a menor idade a do aluno da posição 0 do vetor
    int menorI = a[0].idade;
    // recebe como sendo a menor altura a do aluno da posição 0 do vetor
    float menor = a[0].altura;
    //percorre o vetor de alunos
    for(int i=0; i < TAM; i++)
    {
        // caso a altura na posição i for menor que a de 'menor'
        // esse valor substitui a menor
        // e a idade em menorI também é substituida; 
        if (a[i].altura < menor){
            menor = a[i].altura;
            menorI = a[i].idade;
        }
    }
    // retorna a menor idade
    return menorI;

}

