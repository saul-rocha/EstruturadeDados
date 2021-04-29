#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5

// pilha de string com uma string e a posiçao do topo
struct Pilha{
    char str[TAM][100];
    int top;
};
// pilha que irá armazenar as strings de inicio consoantes na qual seu tamanho maximo é a soma de duas pilhas
struct Pilha3{
    char str[TAM+TAM][100];
    int top;
};

// funções básicas
////////////////////////////////////////////////////////////////
//verifica se a pilha está cheia
int pilha_full(int top){
    int full = 0;
    if(top == TAM-1){ // se o topo igual oa tamanho maximo da pilha a pilha está cheia
        full = 1; 
    }
    //retorna 1 se cheia e 0 se vazia

    return full;
}
//verifica se a pilha é vazia
int pilha_empty(int top){
    int empty = 0;

    if(top == (-1)){
        empty = 1;
    }

    return empty;
}

void empilha(struct Pilha *p, char str[100]){
    // se a pilha !nao estiver cheia copia na posição do topo a string passada por parametro
    if(!pilha_full(p->top)){
        p->top ++;
        strcpy(p->str[p->top],str);
    }
}
// desempilha uma pilha e retorna o valor desempilhado
char *desempilha(struct Pilha *p){
    char str[100];
    //se a pilha !nao for vazia copia para str a string na posição do topo e decrementa o topo
    // por fim retona a string desempilhada
    if(!pilha_empty(p->top)){
        strcpy(str,p->str[p->top]);
        p->top --;
    }

    return str;
}

//////////////////////////////////////////////////////////////////
// tam = tamanho da pilha ou indice do topo da pilha
void imprime(struct Pilha *p, int tam){
    // imprime recursivamente sem pendencia até que a pilha esteja vazia
    if(!pilha_empty(tam)){
        printf("%s\n", p->str[tam]);
        tam--;
        imprime(p, tam);
    }

}
//idem anterior, para pilha de consoantes
void imprime3(struct Pilha3 *p, int tam){
    // imprime recursivamente sem pendencia até que a pilha esteja vazia
    if(!pilha_empty(tam)){
        printf("%s\n", p->str[tam]);
        tam--;
        imprime3(p, tam);
    }

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

// devolve uma terceira pilha com as strings que iniciam com consoantes de forma alternada
void consos(struct Pilha *p1, struct Pilha *p2, struct Pilha3 *p3){
    // enquanto uma pilha nao for vazia ou ambas, copia recursivamente sem pendencia as strings para a pilha 3
    if(!pilha_empty(p1->top) || !pilha_empty(p2->top)){
        //procura primeiro uma string na pilha 1
        while(!pilha_empty(p1->top) && is_vogal(p1->str[p1->top][0])){
            (p1->top) --;
        }
        // quando encontrar a string que inicia com consoante na primeira pilha faz as atribuições para a pilha 3
        // se a pilha não for vazia
        if(!pilha_empty(p1->top)){
            p3->top ++;
            strcpy(p3->str[p3->top],p1->str[p1->top]);
            (p1->top) --;
        }
        //idem anterior só que para a pilha 2
        while(!pilha_empty(p2->top) && is_vogal(p2->str[p2->top][0])){
            (p2->top) --;
        }
        if(!pilha_empty(p2->top)){
            (p3->top) ++;
            strcpy(p3->str[p3->top],p2->str[p2->top]);
            (p2->top) --;
        }
        consos(p1, p2, p3); // recursão
    }

}

//menu
int menu(){
    int op;

    printf("1- Empilhar na Pilha 1\n2- Empilhar na Pilha 2\n3- Imprimir\n4- Pilha de Init Consoantes\n5- Desempilhar\n0- Sair\n");
    scanf("%d", &op);

    return op;
}

int main(){
    struct Pilha p1;
    struct Pilha p2;

    struct Pilha3 p3;
    // inicia os topos das pilhas
    p1.top = -1;
    p2.top = -1;
    p3.top = -1;

    int op, esc;
    char str[100];
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            // usuario empilha um valor na pilha 1
            if(!pilha_full(p1.top)){
            
                printf("Digite a string: ");
                scanf("%s", str);
                empilha(&p1,str);
                  
            }else{
                printf("Pilha cheia!\n");
            }
            
            break;

        case 2:
            // usuario empilha um valor na pilha 2
            if(!pilha_full(p2.top)){
        
                printf("Digite a string: ");
                scanf("%s", str);
                empilha(&p2,str);

                
            }else{
                printf("Pilha cheia!\n");
            }
            break;

        case 3:
            printf("1- Pilha 1\n2- Pilha 2\n3- Pilha 3\n");
            scanf("%d", &esc);
            if(esc == 1){
                imprime(&p1, p1.top);
            }else if(esc == 2){
                imprime(&p2, p2.top);
                    }else if(esc == 3){
                            imprime3(&p3, p3.top);
                        }else{
                            printf("valor invalido!\n");
                        }
            break;
        case 4:
            consos(&p1, &p2, &p3);
            printf("Pronto!\n");
            break;
        
        case 5:
            printf("1- Pilha 1\n2- Pilha 2\n");
            scanf("%d", &esc);
            if(esc == 1){
                desempilha(&p1);
            }else if(esc == 2){
                desempilha(&p2);
                }else{
                    printf("valor invalido!\n");
                }
            break;

        default:
            break;
        }
    } while (op != 0);
    
    
    
    return 0;
}