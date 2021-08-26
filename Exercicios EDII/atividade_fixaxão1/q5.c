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

// Caso cont seja devolvido diferente de 0, deve-se chamar função *mais_velhas para  retornar o vetor com o nome das pessoas, pois segnfica que tem mais dde uma pessoa com a maior idade da lista

//recebe a lista de pessoas e uma pessoa que deve iniciar com a primeira pessoa da lista, nome é o parâmetro de saída e cont é passado por refência para saber quantas pessoas tem a maior idade
void mais_velha(struct lista *pessoas, struct pessoa velha, char nome[100], int *cont){
    struct lista *aux;
    aux = pessoas->Prox;

    //condição de parada
    if ((*aux).Prox != NULL){
        // atribui para "velha" a pessoa com maior idade
        if(aux->Info.Altura > velha.Altura){
            velha = aux->Info;
            *cont = 0;//quando uma pessoa mais velha é encontrada a quantidade reseta
        }
        
        if(aux->Info.Altura == velha.Altura){
            //quando uma pessoa da mesma idade é encontrada a quantidade é incrementada
            *cont= *cont + 1;
        }
        //chama recursivamente até que tenha percorrido toda a lista
        mais_velha(aux, velha, nome, cont);
    }
    // ao final da recursão atribui à variavel nome, o nome da pessoa mais velha
    strcpy(nome, velha.Nome);
}

//recebe a lista de pessoa e o nome da pessoa retornado na função anterior como parametros de entrada
//i e h iniciam como 0 e cont é a quantidade de pessoas com a idade maior(devolvido por parametro na funçao anterior)
char *mais_velhas(struct lista *pessoas,  char velha[100], int h, int i, int cont){
    struct lista *aux;
    char nomes[cont][100];
    aux = pessoas;
    //verifica o h, pois na recursão ele ja terá um valor diferente de 0 e não precisará executar esta parte novamente
    if(h == 0){
        while(strcmp(aux->Info.Nome, velha) != 0){
            aux = aux->Prox;
        }
        h = aux->Info.Altura;
    }
    //condição de parada é quando o nome de todas as pessoas mais velhas estiverem no vetor
    if (i < cont){
        if(pessoas->Info.Altura == h){
            strcpy(nomes[i], aux->Info.Nome);//adiciona o nome da pessoa no vetor
            i++;
        }
        //chama recursivamente a função passando a proxima pessoa como parametro
        mais_velhas(pessoas->Prox, velha, h, i, cont);
    }
    //retorna o vetor com os nomes
    return nomes;
}






int main(){
    struct pessoa velha;
    struct lista *pessoas;

    pessoas = NULL;

    int cont;
    char nome[100];



}

