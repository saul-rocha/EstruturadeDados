#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 20
#define ROW 3

// i deve iniciar como sendo 0, res deve ser a primeira string do vetor
//tem como parametros o vetor de strings, uma string res para ficcar com o a maior string e i para percorrer o vetor e determinar a condição de parada da recursão
char *maior_tam(char str[ROW][TAM], char res[TAM], int i){
    if (i < ROW){//condição de parada
        
        res = maior_tam(str, res, i+1);//recursão com pendencia
        if(strlen(str[i]) > strlen(res))
            strcpy(res, str[i]);
    }
    return res;
}

// verifica se um caractere é vogal 0 caso não e 1 se sim
int is_vogal(char v){
    int res=0;

    if(toupper(v) == 'A' || toupper(v) == 'E' || toupper(v) == 'E' || toupper(v) == 'I' || toupper(v) == 'O' || toupper(v) == 'U')
        res = 1;
    
    return res;

}

// retorna pela função a quentidade de strings de um vetor que iniciam com vogais
void qtd_init_vogais(char str[ROW][TAM], int i, int *res){  
    if(i < ROW){//condição de parada

        if(is_vogal(str[i][0])){
            (*res)++;//incrementa a quantidade se iniciar com vogal
        }
        qtd_init_vogais(str, ++i, res);//chama recursiva sem pendencia incrementando i
    }
}

// i e y iniciam com 0, tem também dois vetores de string como paramentos sendo o res de saída.
void str_maior4_maius(char str[ROW][TAM], char res[ROW][TAM], int i, int *y){
    if( i < ROW){
        if(isupper(str[i][0]) && strlen(str[i]) >= 4){
            strcpy(res[*y],str[i]);
            (*y)++;
            str_maior4_maius(str, res, ++i, y);
        }else{
            str_maior4_maius(str, res, ++i, y);
        }
    }
}


int main(){
    char str[ROW][TAM], maior[TAM], maioresq4[ROW][TAM];
    int y, qtd_vogais=0;


    for(int i=0;  i < ROW;i++){
        printf("Digite uma string: ");
        scanf("%s", str[i]);
    }

    strcpy(maior,maior_tam(str,maior, 0));
    printf("Maior string: %s\n", maior);

    qtd_init_vogais(str, 0, &qtd_vogais);
    printf("Quantidade que inciam com Vogais: %d\n", qtd_vogais);

    str_maior4_maius(str, maioresq4, 0, &y);
    printf("Maiores que 4 e inicio maiuscula\n ");
    for(int i=0; i < y; i++){
        printf("%s\n", maioresq4[i]);
    }

    return 0;
}