#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 100
////////////////////////BASICS///////////////////
struct pilha
{
    char notation[TAM];
    int top;
};


int pilha_full(int top){
    int full=0;

    if(top > TAM - 1)
        full = 1;
    

return full;

}

int pilha_empty(int top){
    int empty = 0;

    if(top == -1)
        empty = 1;
    
return empty;

}


void empilhar(struct pilha *p, char item){
    if (!pilha_full(p->top)){
        p->top ++;
        p->notation[p->top] = item;
    }
}

char desempilhar(struct pilha *p){
    char item;
    
    if(!pilha_empty(p->top)){
        item = p->notation[p->top];
        p->top--;
    }

    return item;
}
///////////////////////////////////////////////////////

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

int precedence(char symbol)
{
    int res;
    
	if(symbol == '*' || symbol == '/')
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

void infix_posfix(char infix[100], struct pilha *p, char posfix[100]){
    int i, j;
    char item_infix, operator;

    empilhar(p, '('); // add um ( na pilha de operadores
    strcat(infix,")");

    i = 0;
    j = 0;  

    item_infix = infix[i];

    while(item_infix != '\0'){//percorre toda a string com a expressão
        if(item_infix == '('){
            empilhar(p, item_infix);
        }
        else if(isdigit(item_infix)){//add operando a string posfixa
            
            while(isdigit(item_infix)){
                posfix[j] = item_infix;
                i++;
                j++;
                item_infix = infix[i];
            }
            posfix[j] = ' ';
            j++;
            
            
        }
        else if(is_operator(item_infix)){
            operator = desempilhar(p);
            while(is_operator(operator) && (precedence(operator) > precedence(item_infix))){
                //enquanto operador desempilhado for de maior prioridade  que o item da infixa
                posfix[j] = operator;
                j++;
                operator = desempilhar(p);
            }
            // se o operador desempilhado nao for de maior prioridade, entao 
            empilhar(p, operator);
            empilhar(p, item_infix);
            
        }
        else if(item_infix == ')'){
            //se for um ),
            operator = desempilhar(p);
            while(operator != '('){
                //até que encontre um ( desempilha os operadores da pilha
                
                posfix[j] = operator;
                j++;
                operator = desempilhar(p);

            }
        }
       
        i++;
        item_infix = infix[i];
    }
    posfix[j] = '\0';
}

int main(){
    //cria a pilha e inicia
    struct pilha p;
    p.top = -1;

    int tam=0;
    char infixa[100], posfixa[100];

    do
    {
        printf("Digite a expressão infixa: ");
        scanf("%[^\n]", infixa);//forma do scanf ler espaços
        setbuf(stdin,NULL);
        for(int i=0;infixa[i] != '\0' ;i++){
            
            tam++;
            
        }
        if(tam > 100){
            printf("Expressão muito grande!\nTente novamente\n");
        }
    } while (tam > 100);

    infix_posfix(infixa, &p, posfixa);

    printf("%s", infixa);
    printf("\n");
    printf("%s", posfixa);

    return 0;

}