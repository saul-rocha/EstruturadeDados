#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct pessoa{
    int Id;
    char Nome[100];
    int AnoNascimento;
    int Altura;
};
struct lista{
    struct pessoa Info;
    struct lista *Prox;
};

///Aloca e Insere
struct lista *aloca_lista(){
    struct lista *No;
    No = NULL;

    No = (struct lista*)malloc(sizeof(struct lista));

    No->Prox = NULL;


    return No;
}

void insere(struct lista **begin, struct lista **end,struct lista *No){
    struct lista *aux, *ant;

    aux = *begin;
    //insere no inicio
    if(*begin == NULL){
        *begin = No;
        *end = No;

    }else if(No->Info.Id < (*begin)->Info.Id){//se o novo id for menor que o do inicio
        *begin = No; // inicio agora é o novo
        No->Prox = aux; //e o proximo do novo é o aux(que guardou o endereço do incio)
    }
    //insere no fim
    else if(No->Info.Id > (*end)->Info.Id){
        aux = *end;
        aux->Prox = No;
        *end = No;
    }else{
        aux = *begin;
        while( No->Info.Id > aux->Info.Id && aux != NULL){// quando o novo elemento for menor que o aux, faz a inserção
            ant = aux;
            aux = aux->Prox;
        }
        No->Prox = aux;// o proximo do novo elemento aponta para o aux que  é o elemento maior que ele
        ant->Prox = No;// o anterior  apontará para o novo que é o proximo dele
        
    }
}


void imprimir(struct lista *pessoas){
    struct lista *aux;
    aux = pessoas;
    if(aux != NULL){
        printf("ID: %d\nNome: %s \nAno Nasc: %d\nAltura: %d\n\n\n", aux->Info.Id, aux->Info.Nome, aux->Info.AnoNascimento, aux->Info.Altura);

        imprimir(aux->Prox);
    } 
}
//--------------------------------------------------------

//o primeiro parametro inicia com a segunda pessoa da lista e o segundo com a idade da primeira pessoa
// devolve por referencia a idade mais velha
void mais_velha(struct lista *pessoas, int *velha){
    struct lista *aux;
    aux = pessoas;

    int idade;
    if(aux != NULL){
        idade = 2021 - aux->Info.AnoNascimento;

        if(idade > *velha){
            *velha = idade;
        }
        mais_velha(aux->Prox, velha);
    }
}

//retorna a quantidade de pessoas que tem a idade mais velha.
// é passada a lista por parametro e a idade da primeira pessoa da lista para iniciar o segundo parametro.
int qtd_mais_velhas(struct lista *pessoas, int maior_idade){
    struct lista *aux;
    aux = pessoas;

    int qtd=0;

    if(aux != NULL){
        if (2021 - aux->Info.AnoNascimento == maior_idade){
            //chama recursão deixando pendente o incremento de qtd
            qtd = qtd_mais_velhas(aux->Prox, maior_idade) + 1;
        }else{
            //caso não tenha a idade da pessoa mais velha, não incrementa
            qtd = qtd_mais_velhas(aux->Prox, maior_idade) + 0;

        }
    }
    return qtd;
}

//retorna o nome da pessoa mais velha
void nome_velha(struct lista *pessoas, int maior_idade, char nome[100]){
    struct lista *aux;
    aux = pessoas;

    if(aux != NULL){
        if(2021 - aux->Info.AnoNascimento == maior_idade){
            strcpy(nome, aux->Info.Nome);//se pessoa tiver a mesma idade da mais velha, copia o nome da pessoa para a string do parametro de saida .
        }
        //chama recursivamente sem pendencia
        nome_velha(aux->Prox, maior_idade, nome);
    }
}

// retorna um vetor com os nomes das pessoas com a maior idade
// reccebe a lista de pessoas, o vetor de strings como parametro de saída, a maior idade e i por referencia para delimitar o tamanho do vetor preenchido, respectivamente
void mais_velhas(struct lista *pessoas, char nomes[100][100],int velha, int *i){
    struct lista *aux;
    aux = pessoas;

    if(aux != NULL){
        if(2021 - aux->Info.AnoNascimento == velha){
            strcpy(nomes[*i], aux->Info.Nome);
            (*i)++;//se pessoa tiver a idade da pessoas mais velha, copia seu nome para o vetor e incrementa o i
        }
        // chama recursivamente sem pendencia
        mais_velhas(aux->Prox, nomes, velha, i);
    }
}


// devolve menor e maior altura por referência
// paramentro menor e maior inicia com a idade da primeira pessoa da lista e a lista começa da segunda pessoa (pessoas->prox)
void maior_menor_altura(struct lista *pessoas, int *menor, int *maior){
    struct lista *aux;
    aux = pessoas;

    if(aux != NULL){
        if(aux->Info.Altura > *maior){
            *maior = aux->Info.Altura;
        }
        if(aux->Info.Altura < *menor){
            *menor =aux->Info.Altura;
        }
        maior_menor_altura(aux->Prox, menor, maior);
    }
}


void qtd_mediana(struct lista *pessoas, int maior, int menor, int *qtd){
    struct lista *aux;

    if (aux != NULL){
        if (aux->Info.Altura == (menor+maior)/2){
            //incrementa o valor de qtd se a altura for mediana
            (*qtd)++;
        }
        //recursão sem pendencia
        qtd_mediana(aux->Prox, maior, menor, qtd);
    }
    
}

void idade_40_altura_med(struct lista *pessoas,int mediana, int *qtd){
    struct lista *aux;
    aux = pessoas;
    if(aux != NULL){
        if(2021 - aux->Info.AnoNascimento < 40 && aux->Info.Altura > mediana){
            (*qtd)++;
        }
        idade_40_altura_med(aux->Prox, mediana, qtd);
    }
}

int menu(){
    int op;
    printf("1 - Cadastrar Pessoas\n2 - Imprimir Pessoas\n3 - Pessoa mais velha\n4 - Menor e Maior Altura\n5 - Pessoas Com Altura Mediana\n6 - Idade < 40 e Altura > Media\n0 - Sair\n");
    scanf("%d", &op);
    
    return op;
}

int main(){

    struct lista *pessoas, *pessoas_end, *No, *aux;

    pessoas = pessoas_end = NULL;

    int escolha, id, altura, ano, continuar, maior=0, menor, qtd=0, mediana=0, velha=0, i;
    char nome[100], leitura_nome[100], nomes[100][100];


    do
    {
        escolha = menu();
        switch (escolha)
        {
        case 1:
            // insere pessoa(as) na lista
            do{
                printf("id: ");
                scanf("%d", &id);
                printf("nome: ");
                scanf("%s", leitura_nome);
                printf("ano de nascimento: ");
                scanf("%d", &ano);
                printf("altura: ");
                scanf("%d", &altura);
                setbuf(stdin, NULL);
                No = aloca_lista();
                No->Info.Id = id;
                strcpy(No->Info.Nome, leitura_nome);
                No->Info.AnoNascimento = ano;
                No->Info.Altura = altura;

                insere(&pessoas, &pessoas_end, No);

                
                printf("Deseja adicionar mais? (1 - SIM || 0 - NAO)");
                scanf("%d", &continuar);
                setbuf(stdin, NULL);
            }while(continuar != 0); 
            break;
        //imprime a lista de pessoas
        case 2:
            imprimir(pessoas); 
            break;
        
        case 3:
            //pessoa mais velha
            qtd = 0;
            velha = 2021 - pessoas->Info.AnoNascimento;// a idade da pessoa mais velha inicia com a idade da primeira pessoa da lista
            mais_velha(pessoas, &velha);
            qtd = qtd_mais_velhas(pessoas, velha);

            //se tiver apenas uma pessoa mais velhar
            if(qtd == 1){
                nome_velha(pessoas, velha, nome);
                printf("Nome da Pessoa Mais Velha: %s\n", nome);
            // se houver varias pessoas mais velhas
            }else{
                i=0;
                mais_velhas(pessoas, nomes, velha, &i);
                for(int y=0; y < qtd; y++){
                    printf("%s\n", nomes[y]);
                }
            }
            break;
        //maior e menor altura
        case 4:
            maior = menor = pessoas->Info.Altura;
            maior_menor_altura(pessoas->Prox, &menor, &maior);
            printf("Maior Altura: %d\nMenor Altura: %d\n\n", maior, menor);
            break;
        
        //qtd de pessoas com altura mediana
        case 5:
            //pega primeiro a maior e menor altura
            menor = menor = pessoas->Info.Altura;
            maior_menor_altura(pessoas->Prox, &menor, &maior);
            //retorna por parametro a quantidade pessoas com altura mediana
            qtd_mediana(pessoas, maior, menor, &qtd);
            printf("Quantidade de Pessoas com Altura Mediana: %d\n", qtd);
            break;
        //qtd pessoas com idade < 40 e altura acima da mediana
        case 6:
            qtd = 0;
            menor = menor = pessoas->Info.Altura;
            maior_menor_altura(pessoas->Prox, &menor, &maior);
            mediana = (maior + menor)/2;
            idade_40_altura_med(pessoas, mediana, &qtd);
            printf("Quantidade de Pessoas com Altura Maior que a Mediana e idade menor que 40: %d\n", qtd);
            break;
        default:
            if(escolha != 0){
                printf("Valor invalido!\n");
            }
            break;  
        }
    } while (escolha != 0);

    return 0;
}

