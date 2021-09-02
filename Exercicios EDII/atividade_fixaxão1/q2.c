#include <stdio.h>
#include <stdlib.h>


//Faça uma função que dado um número inteiro 
//devolva os divisores do mesmo, a função 
//deve ser recursiva.

void retorna_divisores(int vet[],int n, int aux, int *tamanho){
    if(aux > 0){
        if(n % aux == 0){
            vet[*tamanho] = aux;
            *tamanho = *tamanho + 1;
        }
        retorna_divisores(vet,n,--aux,tamanho);
    }
}

void imprimir(int vetor[10], int index, int tamanho_vetor){
    if(index < tamanho_vetor){ 
        printf("vetor[%d] = %d\n",index,vetor[index]); 
        imprimir(vetor,++index,tamanho_vetor);
    }
}


int main(){

    int vet[50];
    int n = 10;
    int aux = n;
    int *tamanho = (int *)malloc(sizeof(int));
    *tamanho = 0;

    retorna_divisores(vet,n,aux,tamanho);

    int index = 0;
    imprimir(vet,index,*tamanho);

    return 0;
}