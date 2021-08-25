#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//////////////////BASICS////////////////////
struct pilha
{
    char notation;
    struct pilha *ant;
};


struct pilha *alocaNo(){
    struct pilha *new;

    new = NULL;

    new = (struct pilha*)malloc(sizeof(struct pilha));

    return new;
}


void empilhar(struct pilha **top, struct pilha *No, char item){
    if(No != NULL){
        (*No).notation = item;
        (*No).ant = *top;
        *top = No;
    }
}


char desempilhar(struct pilha **top){
    struct pilha *aux;  
    char item;

    if(*top != NULL){

        item = (**top).notation;

        aux = *top;

        *top = (**top).ant; 

        free(aux);
    }

    return item;
}


///////////////////////////////////////


void convert_to_num(char str[4], int tam, int uni, int *valor){
    int n;
    if(tam  >= 0){
        if(isdigit(str[tam])){
            n = str[tam] - 48;
            *valor +=  n * uni;
            tam--;
            uni *= 10;
            convert_to_num(str, tam, uni, valor);
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

//retorna a prioridade do sinal
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

int verifica_exp(char exp[100]){
    int res = 0;
    int i=0, qtd_open=0, qtd_closed=0, tam;

    
    //se nãao inciar com digito ou ( a expressão é inválida
    if(isdigit(exp[0]) || exp[0] == '('){
        res = 1;
        while(exp[i] != '\0' && res != 0){
            if(isdigit(exp[i]) && ((isdigit(exp[i+1]) || exp[i+1] == ' ' || exp[i+1] == '\0'))){
                i++;
                if(exp[i] == ' ' && isdigit(exp[i+1])){
                    res = 0;    
                }
            }else if(exp[i] == ' ' && exp[i+1] != ' '){// se for um espaço em branco e o proximo char for diferente de um espaço
                i++;
            }else if(is_operator(exp[i]) && (exp[i+1] == ' ' || exp[i+1] == '\0')){//sinal deve ser separado por espaço
                i++;
                if(is_operator(exp[i+1])){//se o proximo do proximo char for igual a um operador
                    res = 0;    
                }
            }else if(exp[i] == '(' && exp[i+1] == ' '){
                i++;
                qtd_open++;
            }else if(exp[i] == ')' && (exp[i+1] == ' ' || exp[i+1] == '\0')){
                i++;
                qtd_closed++;
            }
            else{
                res = 0;
            }
        }

        if(exp[i] == '\0' && qtd_open == qtd_closed){
            res = 1;
        }else{
            res = 0;
        }

    }else{
        res = 0;
    }

    return res;
}


void infix_posfix(char infix[100], struct pilha **top, char posfix[100]){
    int i, j;
    char item_infix, operator;

    struct pilha *No;

    No = alocaNo();
    empilhar(top, No, '('); // add um ( na pilha de operadores
    strcat(infix," )"); // add um ) no fim da sttring infixa , poiss para cada expressão
                        // o final da mesma é delimitada por um ) mesmo que o usuário não tenha colocado

    i = 0;
    j = 0;  

    item_infix = infix[i];

    while(item_infix != '\0'){//percorre toda a string com a expressão
        if(item_infix == '('){
            No = alocaNo();
            empilhar(top, No, item_infix);
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
            operator = desempilhar(top);
            while(is_operator(operator) && (precedence(operator) > precedence(item_infix))){
                //enquanto operador desempilhado for de maior prioridade  que o item da infixa
                posfix[j] = operator;
                j++;
                operator = desempilhar(top);
            }
            // se o operador desempilhado nao for de maior prioridade, entao 
            No = alocaNo();
            empilhar(top, No, operator);
            No = alocaNo();
            empilhar(top, No, item_infix);
            
        }
        else if(item_infix == ')'){
            //se for um ),
            operator = desempilhar(top);
            while(operator != '('){
                //até que encontre um ( desempilha os operadores da pilha
                
                posfix[j] = operator;
                j++;
                operator = desempilhar(top);

            }
        }
       
        i++;
        item_infix = infix[i];
    }
    posfix[j] = '\0';
}


int main(){
    struct  pilha *pilha_operadores;

    pilha_operadores = NULL;


    char infixa[100], posfixa[100];
    int  valid, tam=0, i=0, verif;
    //ler a expressão
    do
    {
        printf("Digite a expressão infixa: ");
        scanf("%[^\n]", infixa);//forma do scanf ler espaços
        setbuf(stdin,NULL);

        while(infixa[i] != '\0'){
            if (infixa[i] != ' '){
                while(isdigit(infixa[i])){
                    i++;
                }  
                tam ++;     
            }
            i++;    
           
        }
        printf("%d tam\n", tam);
        if(tam > 100){
            printf("Expressão muito grande!\nTente novamente\n");
        }
    } while (tam > 100);

    verif = verifica_exp(infixa);
    if(verif){
        printf("Eh valida!!\n");
        printf("\n");
        infix_posfix(infixa, &pilha_operadores, posfixa);
        printf("%s", posfixa);
        //exibir(pilha_operadores);
    }else{
        printf("NAO eh valida!!\n");
    }

    return 0;
}