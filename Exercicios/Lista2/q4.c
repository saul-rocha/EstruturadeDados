#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//////////////////////////////////////
struct pilha
{
    char notation;
    struct pilha *top;
};


struct pilha *alocaNo(){
    struct pilha *new;

    new = (struct pilha *)malloc(sizeof(struct pilha));

    new->notation = '\0';
    new->top = NULL;

    return new;
}


void empilhar(struct pilha **top, struct pilha *No, char elem){
    //se elemento for diferente de espaço em branco adiciona o mesmo no topo da pilha
    if(elem != ' '){
        No = alocaNo();
        
        No->notation = elem;
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

//imprimir provisório
void imprimir(struct pilha *top){
    if(top != NULL){
        printf("%c\n", top->notation);
        imprimir(top->top);
    }
    setbuf(stdin,NULL);
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

// i inicia de 1
int valid_expression(char s[100]){
    int res=0;


    
    return res;
}

int main(){
    struct  pilha *pilha_operandos, *pilha_operadores, *No;

    pilha_operandos = NULL;
    pilha_operadores = NULL;

    char infixa[100];
    int  tam=0, valid;
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
    setbuf(stdin,NULL);
    //valid = valid_expression(infixa , 0, tam);
    //if(valid){
    //    printf("Expressao eh Valida!\n");
    //}else{
    //    printf("Expressao NAO eh Valida\n");
    //}
    
    for(int i=0; infixa[i] != '\0'; i++){
        if(infixa[i] != ' '){
            
            empilhar(&pilha_operadores, No, infixa[i]);

        }
    }
    imprimir(pilha_operadores);


    return 0;
}