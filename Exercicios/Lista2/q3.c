#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//http://www.vision.ime.usp.br/~pmiranda/mac122_2s14/aulas/aula13/aula13.html

struct pos_fixa
{
    char operandos[100];
    char operadores[100];
    int top;    
};

//i =0 uni = 1
void convert_to_num(char str[4], int i, int tam, int uni, int *valor){
    if(tam >= i){
        if(isdigit(str[tam])){
            *valor += str[tam] - 48;
            *valor = *valor * uni;
            convert_to_num(str, i, tam-1, uni*10, valor);
        }
    }
}

// i inicia de 1
int valid_expression(char s[100],int i, int tam){
    int res;
    if( i < tam){
        //verifica se inicia com ( ou numero
        if(s[0] != '(' || !isdigit(s[0])){
            res = 0;
            //valida os operadores que devem ser separados por espaços em branco
        }else if(((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && (s[i+1] == ' ' && s[i-1] == ' ')){
                i++;
                valid_expression(s, i, tam);// chama recursivamente para verificar o proximo elemento da string
            }else if(isdigit(s[i])){
                    
                }

}

int main(){
    char infixa[100];

    do
    {
        printf("Digite a expressão infixa: ");
        scanf("%s", infixa);
        setbuf(stdin,NULL);
        if(strlen(infixa) > 100){
            printf("Expressão muito grande!\nTente novamente\n");
        }
    } while (strlen(infixa) > 100);

    
    

    return 0;
}