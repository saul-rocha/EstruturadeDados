#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//http://www.vision.ime.usp.br/~pmiranda/mac122_2s14/aulas/aula13/aula13.html

struct pos_fixa
{
    char operandos[100];
    char operadores[100];
    int top_operandos, top_operadores;    
};

//i =0 uni = 1
void convert_to_num(char str[4], int i, int tam, int uni, int *valor){
    if(tam  >= i){
        if(isdigit(str[tam])){
            *valor += str[tam] - 48;
            *valor = *valor * uni;
            tam--;
            uni *= 10;
            convert_to_num(str, i, tam, uni, valor);
        }
    }
    
}

// i inicia de 1
int valid_expression(char s[100],int i, int tam){
    int res, valor, cont=0, uni=1, y;
    char aux[4];
    if( i < tam){
        //verifica se inicia com ( ou numero
        if(s[0] != '(' || !isdigit(s[0])){
            res = 0;
            //valida os operadores que devem ser separados por espaços em branco
        }else if((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && (s[i+1] == ' ' && s[i-1] == ' ')){
                i++;
                valid_expression(s, i, tam);// chama recursivamente para verificar o proximo elemento da string
            }else if(isdigit(s[i])){
                //percorre o numero e passa os indices para y
                    for (y=i;s[y] != ' ';y++)
                    i = y;
        
                    //percorre o numero de tras pra frente para poder converter
                    for(y; s[y-1] != ' '; y--){
                        valor += s[y] - 48;
                        valor *= uni;
                        uni *= 10;
                    }
                    
                    if(valor > 1000){
                        res = 0;
                    }else{
                        i++;
                        valid_expression(s, i, tam);
                    }
                }
    }
    return res;
}

int main(){
    char infixa[100];
    int tam, valid;
    do
    {
        printf("Digite a expressão infixa: ");
        scanf("%s", infixa);
        setbuf(stdin,NULL);
        if(strlen(infixa) > 100){
            printf("Expressão muito grande!\nTente novamente\n");
        }
    } while (strlen(infixa) > 100);

    tam = strlen(infixa);
    valid = valid_expression(infixa , 0, tam);
    if(valid){
        printf("Expressao eh Valida!\n");
    }else{
        printf("Expressao NAO eh Valida\n");
    }
    
    

    return 0;
}