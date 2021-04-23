#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define TAM 3

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
void lower_string(char s, char slower){
        slower = s + 32;
}


// verifica se um char é vogal
int is_vogal(char c){
    int res;
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
        res = 1;
    }else if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'){
            res = 1;
        }else{
            res = 0;
        }
    return res;
}


// copia uma coluna da matriz e copia para um vetor
void vetor(char mat[TAM][TAM][100], char vet[TAM][100], int i,int j, int tam){
    if (i < tam){
        strcpy(vet[i],mat[i][j]);
        i+=1;
        vetor(mat,vet,i,j,tam);
    }
}

int partition(char vet[][100], int begin, int end){
    int left, right, i=0; 
    char key[100], aux[100], low;

    left = begin; // esquerda recebe o inicio do vetor
    right = end; // direita recebe o final do vetor
    strcpy(key, vet[begin]); // chave começa da posição inicial
    while (left < right) // condição de parada
    {
        if(maiuscula(vet[right][i]) && maiuscula(key[i])){
            while (vet[right][i] > key[i])
            {
                right--; // caso o valor do vetor na posiçãodireita for maior que a cheve, a direita é decrementada
            }
        }else if(!maiuscula(vet[right][i]) && !maiuscula(key[i])){
                    while (vet[right][i] > key[i])
                    {
                        right--; // caso o valor do vetor na posiçãodireita for maior que a cheve, a direita é decrementada
                    }
                }else if(maiuscula(vet[right][i]) && !maiuscula(key[i])){
                            lower_string(vet[right][i],low);
                            while (low > key[i])
                            {
                                right--; // caso o valor do vetor na posiçãodireita for maior que a cheve, a direita é decrementada
                            }
                            }else if(!maiuscula(vet[right][i]) && maiuscula(key[i])){
                                        lower_string(key[i],low);
                                        while (vet[right][i] > low)
                                        {
                                            right--; // caso o valor do vetor na posiçãodireita for maior que a cheve, a direita é decrementada
                                        } 
                                }

        if(maiuscula(vet[left][i]) && maiuscula(key[i])){    
            while (vet[left][i] < key[i])
            {
                left++; // caso o valor do vetor na posição esquerda for menor ou igual a chave, a esqueda é iterada
            }
        }else if(!maiuscula(vet[left][i]) && !maiuscula(key[i])){    
                while (vet[left][i] < key[i])
                {
                    left++; // caso o valor do vetor na posição esquerda for menor ou igual a chave, a esqueda é iterada
                }
            }else if(maiuscula(vet[left][i]) && !maiuscula(key[i])){ 
                        lower_string(vet[left][i],low);   
                        while (low < key[i])
                        {
                            left++; // caso o valor do vetor na posição esquerda for menor ou igual a chave, a esqueda é iterada
                        }
                }else if(!maiuscula(vet[left][i]) && maiuscula(key[i])){ 
                            lower_string(key[i],low);   
                            while (vet[left][i] < low);
                            {
                                left++; // caso o valor do vetor na posição esquerda for menor ou igual a chave, a esqueda é iterada
                            }
                    }
        

        if(left < right){ // caso esquerda seja menor que a direita, é feita as trocas no vetor
            
            strcpy(aux, vet[right]);
            strcpy(vet[right], vet[left]);
            strcpy(vet[left], aux);
        }
        
    }

    return right; // retorna a posição da nova key
    
}
//de forma geral o algoritmo quicksort particiona o vetor em duas partes de acordo com a chave(um ponto de referência)
// valores menores que a chave sao colocados à esquerda e os maiores à direita

//recebe um vetor e as posições de inicio e fim
void quicksort(char vet[][100], int begin, int end){
    int key;
    if(end > begin){
        key = partition(vet,begin,end); // separa o vetor em duas partições (esquerda e direita)
        quicksort(vet,begin,key-1); // chama a função para a partição esquerda
        quicksort(vet,key+1, end); // chama a função para a partição direita
    }
}

//ordena todas as colunas
void sort_mat(char mat[TAM][TAM][100],char mat1[TAM][TAM][100], char vet[][100],int coluna, int tam){
    int j;
    if(coluna < tam){
        vetor(mat,vet,0,coluna,tam);
        quicksort(vet,0,tam-1);
        for(j=0;j<tam;j++){
            strcpy(mat1[j][coluna],vet[j]);
        }
        coluna += 1;
        sort_mat(mat,mat1,vet,coluna,tam);
    }
}
//mostra colunas desordenadas
void mostrar_unsort(char mat[TAM][TAM][100], int tam){
    for(int i = 0; i < tam;i++){
        printf("Coluna %d Desordenada\n", i);
        for(int j = 0; j < tam;j++){
            printf("%s \n", mat[j][i]);
        }
        printf("\n--------\n");
    }
}

//mostra colunas ordenadas
void mostrar_sort(char mat[TAM][TAM][100], int tam){
    for(int i = 0; i < tam;i++){
        printf("Coluna %d Ordenada\n", i);
        for(int j = 0; j < tam;j++){
            printf("%s \n", mat[j][i]);
        }
        printf("\n--------\n");
    }
}

//qts de digitos em uma string
int qtd_digit(char c[100], int i, int tam){
    int qtd=0;
    if (i < tam){
        if(isdigit(c[i])){
            i++;
            qtd = qtd_digit(c,i,tam) + 1;
        }else{
            i++;
            qtd = qtd_digit(c,i,tam) + 0;
        } 
    }
    return qtd;
}
//numero de maiusculas em uma string
int qtd_maius(char c[100], int i, int tam){
    int qtd=0;
    if (i < tam){
        if(maiuscula(c[i])){
            i++;
            qtd = qtd_maius(c,i,tam) + 1;
        }else{
            i++;
            qtd = qtd_maius(c,i,tam) + 0;
        } 
    }
    return qtd;
}

//qtd de string numa coluna que inicia com Consoante
int conso_init(char c[TAM][TAM][100], int coluna, int i, int tam){
    int qtd=0;
    if(i < tam){
        // se nao é volgal é consoante
        if(!is_vogal(c[i][coluna][0])){
            i++;
            qtd = conso_init(c,coluna,i,tam) + 1;
        }else{
            i++;
            qtd = conso_init(c,coluna,i,tam) + 0;
        }
    }

    return qtd;

}

int menu(){
    int opcao;

    printf("1- Ler Matriz\n2- Ordenar Colunas\n3- Mostrar Desordenada\n4- Mostrar Ordenada\n5- Quantidade de Digitos e maiusculas\n6- Quantidade que iniciam com Consoantes\n0- Sair");

    printf("Digite um opcao: ");
    scanf("%d",&opcao);

    return (opcao);
}


int main(){
    
    int op,row,colum, tam, digit, maius,conso;

    char mat[TAM][TAM][100], mat1[TAM][TAM][100], col[TAM][100];
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
                sort_mat(mat, mat1, col, 0, TAM);
                printf("Ordenado!\n");
                break;

            case 3:
                mostrar_unsort(mat, TAM);
                break;
            
            case 4:
                mostrar_sort(mat1, TAM);
                break;
            case 5:
                printf("linha: ");
                scanf("%d", &row);
                printf("coluna: ");
                scanf("%d", &colum);

                tam = strlen(mat1[row][colum]);

                digit = qtd_digit(mat1[row][colum],0, tam);
                maius = qtd_maius(mat1[row][colum],0, tam);
                printf("%d Digitos\n", digit);
                printf("%d Maiusculas\n", maius);

                break;

            case 6:
                printf("coluna: ");
                scanf("%d", &colum);
                conso = conso_init(mat1, colum, 0, TAM);
                printf("%d Iniciam com Consoante\n", conso);
                break;

        }
    }while(op < 7 && op > 0);
    printf("Obrigado!\n");
    return(0);
}