#include <stdio.h>
#include <stdlib.h>

// OBS :. mesmo com a releitura não há alterações nos endereços

// dados de uma pessoa
struct Pessoa
{
    char nome[50];
    int cpf;
};

// altera o nome
// passa uma struct do tipo pessoa referenciada como parametro
void alteraNome(struct Pessoa *p){
    printf("NOVO NOME: ");
    scanf("%s", (*p).nome);//ler uma nova string e coloca no conteúdo do endereço referenciado
    // OBS:. poderia também ser dereferenciado da seguinte forma: p->nome
}


int main(){

    int esc;
    // cria um ponteiro do tipo Pessoa
    struct Pessoa *pessoa;
    do{
        //aloca um espaço de memória para pessoa
        pessoa = (struct Pessoa *)malloc(sizeof(struct Pessoa));
        // ler os dados e armazena em um ponteiro 
        printf("Nome: ");
        scanf("%s", pessoa->nome);
        printf("CPF: ");
        scanf("%d", &pessoa->cpf);

        // imprime o endereço na qual os dados da pessoa está alocado e os dados (nome e cpf)
        printf("\nend. Pessoa: %p\nNOME: %s\nCPF: %d\n", pessoa, pessoa->nome, pessoa->cpf);
        alteraNome(pessoa);
        // imprime novamente depois de alterar o nome
        printf("\nend. Pessoa: %p\nNOME: %s\nCPF: %d\n", pessoa, pessoa->nome, pessoa->cpf);
        //desalocando memoria (libera os espaço de memória alocado no malloc)
        // menu
        printf("\n1- continuar\n0- sair\n");
        scanf("%d", &esc);

        free(pessoa);

    }while (esc != 0);//condição de parada

    return (0);
}