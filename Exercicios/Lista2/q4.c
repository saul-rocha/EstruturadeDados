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

//imprimir provisório
void imprimir(struct pilha *top){
    if(top != NULL){
        printf("%s\n", top->notation);
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


// i inicia de 1
int valid_expression(char s[100], int i){
    int res=1;
    if(is_operator(s[0]) || (!isdigit(s[0]) && s[0] != '(')){
        res = 0;
    }else{//se ultimo elemento é um fecha parêntese ou digito
            res = 1;
            while(res != 0 && s[i] != '\0'){
                
                if(s[i] == ' ' || (isdigit(s[i]) && ((s[i+1] == ' ') || (isdigit(s[i+1])))) || is_operator(s[i]) && (s[i+1] == ' ')){//se na posição i for digito/ouperador o proximo dever ser um espaço ou outro digito
                    res = 1;
                }
                i++;
            }
        }
    return res;
}




int main(){
    struct  pilha *pilha_operandos, *pilha_operadores, *No;

    pilha_operandos = NULL;
    pilha_operadores = NULL;

    char infixa[100], num[4];
    int  tam=0, valid, numero, cont, flag;
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
    valid = valid_expression(infixa , 1);

    if(valid){
        printf("Expressao eh Valida!\n");


            //cria pos-fixa
            for(int i=0; infixa[i] != '\0'; i++){
                if(infixa[i] != ' '){

                    cont = 0;
                    if(isdigit(infixa[i])){
                        while(isdigit(infixa[i])){
                            num[cont] = infixa[i];
                            cont++;
                            i++;
                        }
                        convert_to_num(num,0,strlen(num),1,&numero);
                        if(numero < 1001){

                            empilhar(&pilha_operandos, No, num);
                                
                            num[0] = num[1] = num[2] = num[3] = '\0';

                        }

                    }else if(is_operator(infixa[i])){
                       
                        num[0] = infixa[i];

                        empilhar(&pilha_operadores, No, num);
                        num[0] = '\0';

                    }else if(infixa[i] == '(' || infixa[i] == ')'){
                        num[0] = infixa[i];
                        empilhar(&pilha_operandos, No, num);
                        num[0] = '\0';
                    }

                }
            }
        
            

    }else{
        printf("Expressao NAO eh Valida\n");
    }
    
    imprimir(pilha_operandos);
    imprimir(pilha_operadores);


    return 0;
}