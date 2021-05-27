#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//////////////////////////////////////
struct pilha
{
    char notation[4];
    struct pilha *top;
};


struct pilha *alocaNo(){
    struct pilha *new;

    new = (struct pilha *)malloc(sizeof(struct pilha));
    for(int i =0; i < 4; i++){
        new->notation[i] = '\0';    
    }
    new->top = NULL;

    return new;
}


void empilhar(struct pilha **top, struct pilha *No, char elem[4]){
    //se elemento for diferente de espaço em branco adiciona o mesmo no topo da pilha
    if(elem[0] != ' '){
        No = alocaNo();
        
        strcpy(No->notation,elem);
        No->top = *top;

        *top = No;
    }
}

struct pilha *desempilhar(struct pilha **top){
    struct pilha *aux, *out;
    out = alocaNo();

    if (*top != NULL){
        aux = *top;

        *out = **top;

        *top = (*top)->top;

        free(aux);
    }

    return out;
}



///////////////////////////////////////
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
void convert_to_str(char str[4], int i, int tam, int uni, int valor){
    if(i < tam){
        if(valor > 9){
            str[i] = valor / uni;
            valor = valor % uni;
            i++;
            uni /= 10;
            convert_to_str(str, i, tam, uni, valor);
        }
        str[i] = valor;
    }
    
}

int is_operator(char o){
    int res = 0;

    if( o == '/' || o == '*' || o == '-' || o == '+'){
        res = 1;
    }

    return res;
}

//retorna a precedencia
int precedence(char symbol)
{
    int res;
    
	if(symbol == '(')
	{
		res = 3;
	}
	else if(symbol == '*' || symbol == '/')
	{
		res = 2;
	}
	else if(symbol == '+' || symbol == '-')          
	{
		res = 1;
	}
	else
	{
		res = 0;
	}

    return res;
}

// i inicia de 1
int valid_expression(char s[100], int i){

}




int main(){
    struct  pilha *pilha_operandos, *pilha_operadores;

    pilha_operandos = NULL;
    pilha_operadores = NULL;

    char infixa[100];
    int  valid, tam=0;
    //ler a expressão
    do
    {
        printf("Digite a expressão infixa: ");
        scanf("%[^\n]", infixa);//forma do scanf ler espaços
        setbuf(stdin,NULL);
        for(int i=0;infixa[i] != '\0' ;i++){
            if(infixa[i] != ' '){
                tam++;
            }
        }
        if(tam > 100){
            printf("Expressão muito grande!\nTente novamente\n");
        }
    } while (tam > 100);


    printf("%d\n", tam);
    //valida a expressão
    valid = valid_expression(infixa , 1);

    if(valid){
        printf("Expressao eh Valida!\n");

        pilha_posfixa(infixa, &pilha_operandos, &pilha_operadores);

    }else{
        printf("Expressao NAO eh Valida\n");
    }
    imprimir(pilha_operandos);
    printf("\n");
    imprimir(pilha_operadores);


    return 0;
}