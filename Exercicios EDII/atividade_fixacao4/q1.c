#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct arv{
    int info;
    struct arv *left, *right;
};


//// ALOCAÇÃO l INSERSÃO da ARVORE
struct arv *aloca_arv(int i){
    struct arv *new;

    new = NULL;

    new = (struct arv*)malloc(sizeof(struct arv));
    new->info = i;

    return new;
}

//insere um elemento na arvore
//recebe a raiz da arvore por referencia como parametro l o novo nó a ser adicionado
int inserir_arv(struct arv **root, struct arv *No){
    int res=0;

    if(*root == NULL){
        *root = No;
        res = 1;
    }else{
        if(No->info < (**root).info){
            res = inserir_arv(&(**root).left, No);
        }else if (No->info > (**root).info){
            res = inserir_arv(&(**root).right, No);
        }
    }
    return res;
}

//recebe a raiz da arvore como parametro l imprime em pre-ordem  raiz-> esq -> dir
void imprimir_preorder(struct arv*root){
    if(root != NULL){
        printf("\nInfo:%d\n",root->info);
        imprimir_preorder(root->left);
        imprimir_preorder(root->right);
    }
}
///////////////////
//recebe como parametros a arvore l dois inteiros por referencia para devolver as quantidades
void Nos_Ramos(struct arv *root, int *qtd_No, int *qtd_Ramo){
    
    if(root != NULL){
        if(root->right == NULL && root->left == NULL){
            (*qtd_No)++;
        }else if(root->right != NULL && root->left == NULL){
            (*qtd_Ramo)++;
            (*qtd_No)++;    
        }else if(root->right == NULL && root->left != NULL){
            (*qtd_Ramo)++;
            (*qtd_No)++;    
        }else{
            (*qtd_Ramo)+= 2;
            (*qtd_No)++; 
        }
        
        Nos_Ramos(root->left, qtd_No, qtd_Ramo);
        Nos_Ramos(root->right, qtd_No, qtd_Ramo);

        
    }
}

//recebe como parametros a arvore l dois inteiros,sendo um deles por referencia para retornar a profundidade
void profundidade(struct arv *root, int elemento, int *profundo){
    if(root != NULL){
        if(elemento < root->info){
            (*profundo)++;
            profundidade(root->left, elemento, profundo);
        }
        else if(elemento > root->info){
            (*profundo)++;
            profundidade(root->right, elemento, profundo);
        }
    }
}

//recebe uma arvore l o elemento a ser buscado l então retorna se endereço
struct arv *busca_element(struct arv *root, int elemento){
    struct arv *res;
    if(root != NULL){
        if(elemento < root->info){
            res = busca_element(root->left, elemento);
        }
        else if(elemento > root->info){
            res = busca_element(root->right, elemento);
        }
    }
    if (root->info == elemento){
        res = root;

    }else{
        res = NULL;
    }
    
    
    return res;
}

///recebe um Nó de uma arvores seja ele a raiz da arvore ou não
int altura_No(struct arv *root){
    int res = -1, r, l;
    if (root == NULL){
        res += 0;
    }else{
        l = altura_No(root->left) + 1;
        r = altura_No(root->right) + 1;
        if(l > r){
            res = l;
        }else{
            res = r;
        }
    }
    return res;
   
}


int menu(){
    int res;

    printf("1 - Preencher arvore\n2 - Numero de Nos e Ramos\n3 - Profundidade do Elemento\n4 - Alturado Elemento\n5 - Descendentes\n0 - Sair\n");
    scanf("%d", &res);

    return res;
}


int main(){
    
    struct arv *root, *No;
    int escolha,qtd_no, qtd_ramo, elemento, profundo, alt, elem;

    root = NULL;

    srand(time(NULL));

    do{
        escolha = menu();
        switch (escolha)
        {
        case 1:
        // / 3 5 2 1 4 6 7
           //No = aloca_arv(1 + rand()%99);
            printf("\nInfo: ");
            scanf("%d", &elem);
            No = altura_No();
            inserir_arv(&root, No);
            break;
        case 2:
            qtd_no = qtd_ramo = 0;
            Nos_Ramos(root, &qtd_no, &qtd_ramo);
            //imprimir_preorder(root);
            printf("Quantidade de Nos: %d\nQuantidade de Ramos: %d\n", qtd_no, qtd_ramo);
            break;
        case 3:
            profundo = 0;
            printf("Elemento: ");
            scanf("%d", &elemento);
            profundidade(root, elemento, &profundo);
            printf("Profundidade de %d eh %d \n\n", elemento, profundo);
            break;
        case 4:
            printf("Elemento: ");
            scanf("%d", &elemento);
            No = busca_element(root, elemento);
            //printf("%d", No1->left->info);
            alt = 0;  
            if (No != NULL){
                alt = altura_No(No);
                printf("Altura: %d\n", alt);
                free(No);

            }else{
                printf("Valor nao existe!\n");
            }
            
            break;
        default:
            break;
        }

    }while(escolha != 0);

    return 0;
}