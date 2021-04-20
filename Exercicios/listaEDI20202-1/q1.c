#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//preenche uma matriz
void preenche(int **mat,int i,int j,int tam){
    if (i < tam){
        if(j < tam){
            mat[i][j] =  rand() % 10;//preenche a matriz com valores aleatoria entre 0 e 9
            preenche(mat,i,j+1,tam);
        }
        preenche(mat,i+1,0,tam);
    }
    
}

//calculo do determinante pelo teorema de laplace,
//O teorema de Laplace utiliza uma expansão em cofatores para realizar o cálculo de determinantes. 

int laplace(int **mat, int tam){
    int det = 0,i, i1,j1, j1_aux, i1_aux, **mat_aux, cofator;
    //caso matriz de ordem 1
    if(tam == 1){

        det = mat[0][0];

    }else if(i < tam)//condição de parada(fim da matriz)
    {
        for(i=0;i<tam;i++)// percorre cada linha da matriz
        {
        //seleciona a primeira linha para efetuar o calculo dos cofatores
        // e ignora quando for igual a zero pois o produto seria 0 e não precisa calcular
            if(mat[0][i] != 0){
                i1_aux = 0;
                j1_aux = 0;
                //cria submatrizes matrizes 
                mat_aux = malloc(tam * sizeof(int));// aloca um vetor de ordem ponteiros para linhas
                for(int i=0;i < tam;i++){
                    mat_aux[i] = malloc(tam * sizeof(int));// aloca cada uma das linhas
                }
                //gera submatriz para calculo dos cofatores
                for(i1 = 1; i1 < tam; i1++){
                    for(j1 = 0; j1 < tam; j1++){
                        if(j1 != i){
                            mat_aux[i1_aux][j1_aux] = mat[i1][j1];
                            j1_aux++;
                        }
                    }
                    i1_aux++;
                    j1_aux = 0;
                }
                // a condição do cofator irá semar é se posição da linha dividido por 2 tem o resto 0
                // caso contrario irá subtrair(é passo como negativo) 
                cofator = (i % 2 == 0) ? mat[0][i] : -mat[0][i];
                // o determinte é a soma  entre cada elemento multiplicado pelo seu cofator
                det = det + cofator * laplace(mat_aux, tam-1); // ou seja, a cada recursão soma o determinante ao cofator multiplicando
                // com a proximo cofator

                free(mat_aux);// ao final de toda a recursão libera a matriz auxiliar da pilha pendente           
            }
        }
    }
    return det;
}


int main(){
    int ordem, dets, **matriz;

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
    
    matriz = malloc(ordem * sizeof(int));// aloca um vetor de ordem ponteiros para linhas
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

    dets = laplace(matriz,ordem);
    printf("determinante = %d\n", dets);


    free(matriz);


}