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

//verifica se um char é maiusculo
int maiuscula(char c){
    int i=0;
    if (c > 64 && c < 91){
        i=1;
    }
    return i;
}

//converte a string pra minusculo
void lower_string(char s[], char slower[]){
    for(int i=0; i < strlen(s); i++){
        slower[i] = s[i] + 32;
    }
}


void vetor(char mat[TAM][TAM][100], char vet[TAM][100], int i,int j, int tam){
    if (i < tam){
        strcpy(vet[i],mat[i][j]);
        i+=1;
        vetor(mat,vet,i,j,tam);
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

    char mat[TAM][TAM][100], col[TAM][100];
    char b[100];
    do 
    {
    
        op = menu();
        switch(op)
        {
            case 1:
                lerMatriz(mat,0,0,TAM,TAM);
                printf("Lido!\n");
                break;
            case 2:
                lower_string(mat[0][0],b);
                printf("%s\n", b);
                break;

            case 3:
                for(int i=0;i <TAM;i++){

                    for(int j=0;j<TAM;j++){
                        printf("string[%d][%d]: %s ",i, j, mat[i][j]);
                    }
                    printf("\n");
                }
                break;

        }
    }while(op < 7 && op > 0);
    printf("Obrigado!\n");
    return(0);
}