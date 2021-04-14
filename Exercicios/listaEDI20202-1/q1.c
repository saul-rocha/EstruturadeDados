#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//preenche uma matriz
void preenche(int **mat,int i,int j,int tam){
    if (i < tam){
        if(j < tam){
            mat[i][j] = rand() % 10;//preenche a matriz com valores aleatoria entre 0 e 10
            preenche(mat,i,j+1,tam);
        }
        preenche(mat,i+1,0,tam);
    }
    
}

//calculo do determinante de ordem 2
//até a gora só sei como passar  a matriz por parametro
int ordem2(int **mat){


    
}


int main(){
    int ordem;

    //ler a ordem da matriz
    do{
        printf("1 - Ordem 1\n2 - Ordem 2\n3 - Ordem 3\n4 - Ordem 4\n");
        printf("Defina a Ordem da matriz: ");
        scanf("%d", &ordem);
        if (ordem > 4 || ordem < 1)
        {
            printf("digite um valor entre 1 e 4\n");
        }
        
    }while (ordem < 1 || ordem > 4);
    
    //aloca a matriz dinamicamente
    
    int **matriz = malloc(ordem * sizeof(int));// aloca um vetor de ordem ponteiros para linhas
    for(int i=0;i < ordem;i++){
        matriz[i] = malloc(ordem * sizeof(int));// aloca cada uma das linhas (vetores de oredem inteiros)
    }
    //preenche a matriz
    preenche(matriz,0,0,ordem);//passa o endereço da matriz e o endereço de sua ordem

    for(int  i=0; i < ordem;i++){
        for(int  j=0; j < ordem;j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }


    free(matriz);


}