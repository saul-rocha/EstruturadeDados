#include <stdio.h>
#include <stdlib.h>

#define MAX 50
//Faça uma função que dado um número inteiro 
//devolva os divisores do mesmo, a função 
//deve ser recursiva.

///tem como parametros o vetor do tipo inteiro onde será colocado os divisores,
/// o valor inteiro a ser retirado os divisores, aux inicia com o mesmo valor de n, 
/// tamanho é passado por referencia para pegar o tamanho do vetor
void retorna_divisores(int vet[MAX],int n, int aux, int *tamanho){
    if(aux > 0){//condição de parada
        if(n % aux == 0){
            vet[*tamanho] = aux;//atribui o valor para o vetor se for divisor
            *tamanho = *tamanho + 1;//tamanho é incrementado
        }
        retorna_divisores(vet,n,--aux,tamanho);//recursão sempendencia decrementando o aux
    }
}

//imprime o vetor de divisores
// recebe o vetor com os divisores, o index inicia de 0 para percorrer o vetor 
// e o tamanho do vetor com conteúdo
void imprimir(int vetor[MAX], int index, int tamanho_vetor){
    if(index < tamanho_vetor){ //condição de parada
        printf("vetor[%d] = %d\n",index,vetor[index]); 
        imprimir(vetor,++index,tamanho_vetor);//recursão sem pendencia incrementando o index
    }
}


int main(){

    int vet[50];
    int n = 50;
    int aux = n;
    int *tamanho = (int *)malloc(sizeof(int));
    *tamanho = 0;

    retorna_divisores(vet,n,aux,tamanho);

    int index = 0;
    imprimir(vet,index,*tamanho);

    return 0;
}