#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 3

// registro de Aluno
struct Aluno
{
    int mat;
    int idade;
    char nome[30];
    float altura;

};
// FUNCTIONS
void altinho(struct Aluno *a, float *alto);
int baixinho(struct Aluno *a);
float mediaAltura(struct Aluno *a,char *nomes);

//MAIN
int main(){

    struct Aluno aluno[TAM];
    float altMaior=0,media;
    int idadeMenor;
    char nomes[30];

    //leitura dos dados dos alunos
    for (int i = 0; i < TAM; i++)
    {
        printf("matricula: ");
        scanf("%d", &aluno[i].mat);
        printf("nome: ");
        scanf("%s", aluno[i].nome);
        printf("altura: ");
        scanf("%f", &aluno[i].altura);
        printf("idade: ");
        scanf("%d", &aluno[i].idade);
    }
    
    // variavel recebe a idade do menor aluno do retorno da função baixinho
    idadeMenor = baixinho(aluno);
    //aqui deve passar a variável altMaior por referência
    altinho(aluno, &altMaior);

    printf("Altura do maior: %.2f\nIdade do menor: %d\n", altMaior, idadeMenor);


    media = mediaAltura(aluno, nomes);
    printf("media: %.2f\n", media);


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


float mediaAltura(struct Aluno *a,char *nomes){

    float media = 0;
    int cont = 0;
    char vet[TAM][30];
    //percorre o vetor de alunos e soma as alturas
    for (int i = 0; i < TAM; i++)
    {
        media += a[i].altura;
    }
    // a media recebe ela mesma dividido pela quantidade de alunos
    media = media / TAM;
    
    //percorre novamente o vetor de alunos e adiciona o nome dos que tem altura mediana
    // em um outro vetor
    for(int i=0; i < TAM;i++)
    {
        if(a[i].altura >= media)
        {
            //como colocar os nomes no vetor?
        }
    }
    //retona a altura media dos alunos
    return media;
}