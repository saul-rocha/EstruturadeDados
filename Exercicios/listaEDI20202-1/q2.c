#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 2

// ler a matriz de strings 
// recebe a matriz, dois contadores i e j iniciandondo  de 0 e as dimenssões da matriz
void lerMatriz(char m[TAM][TAM][100],int i,int j, int tami,int tamj){
    if(i < tami){//condição de parada

        if(j < tamj){
            scanf("%s", m[i][j]); // ler o valor
            lerMatriz(m,i,j+1,tami,tamj); // chama recursivamente sem pendencia incrementando j que representa a coluna
        }else{
            lerMatriz(m,i+1,0,tami,tamj);// chama recursivamente sem pendencia incrementando i que representa a linha
        }
    }

}

void quicksort(char m[TAM][TAM][100],char aux[100],int inicioi, int inicioj, int fimi, int fimj,int i){
    int x1,x2,y1,y2;
    if (m[inicioi][inicioj][i] > m[fimi][fimj][i]){
        aux = m[inicioi][inicioj][i];
        x1 = inicioi;
        x2 = inicioj;
        y1 = fimi;
        y2 = fimj;
        
    }
}


int menu(){
    int opcao;

    printf("1- Ler Matriz\n2- Ordenar Colunas\n3- Mostar Ordenada\n4- Mostar Desordenada\n5- Quantidade de Digitos e maiusculas\n6- Quantidade que iniciam com Consoantes\n");
    printf("Digite um opcao: ");
    scanf("%d",&opcao);

    return (opcao);
}


int main(){
    
    int op;

    char mat[TAM][TAM][100];

    op = menu();
    while (op < 6 && op > 0)
    {
    
        switch(op)
        {
            case 1:
                lerMatriz(mat,0,0,TAM,TAM);
                printf(" ");
                break;
            case 2:
                for(int i=0;i <TAM;i++){

                    for(int j=0;j<TAM;j++){
                        printf("string[%d][%d]: %s\n",i, j, mat[i][j]);
                    }

                }

        }
        op = menu();
    }
    return(0);
}