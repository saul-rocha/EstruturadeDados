#include <stdio.h>
#include <stdlib.h>
#include "arvore_binaria.h"


void ola_mundo(){
    printf("Ola mundo");
}

//Função que retorna uma função vazia
struct noArv* arv_criavazia (void){
    return NULL;
}

//Inicia uma arvore com seu primeiro valor.
struct noArv* arv_cria(int id, struct noArv* sae, struct noArv* sad)
{
 struct noArv* arvore_binaria=(struct noArv*)malloc(sizeof(struct noArv));
 if(arvore_binaria==NULL) exit(1);
 arvore_binaria->id = id;
 arvore_binaria->esq = sae;
 arvore_binaria->dir = sad;
 return arvore_binaria;
}

//Liberando a arvore
struct noArv* avr_libera(struct noArv* arvore)
{
    if(arvore != NULL){
        avr_libera(arvore->esq); //Libera esq
        avr_libera(arvore->dir); // Libera dir
        free(arvore);
    }
    return NULL;
};

//Verificando a ocorrencia de um ID em uma ARVORE
int arv_pertence(struct noArv* arvore, int id)
{
    if (arvore == NULL){
        return 0; /* árvore vazia: não encontrou */
    }else{
        return arvore->id==id || arv_pertence(arvore->esq,id) || arv_pertence(arvore->dir,id);
    }
}

//Imprimir os elementos das arvores
void arv_imprime(struct noArv* arvore)
{
    if (arvore != NULL){
        arv_imprime(arvore->esq); //mostra sae 
        printf("%d \n",arvore->id); //mostra raiz
        arv_imprime(arvore->dir); //mostra sad
    }
}

//Retorna o 'No' de uma arvore usado o 'id' como parametro
struct noArv* abb_busca (struct noArv* arvore, int id)
{
    struct noArv* aux;

    if (arvore == NULL)
        aux = NULL;
    else if (arvore->id > id)
        aux = abb_busca(arvore->esq, id);
    else if (arvore->id < id)
        aux = abb_busca(arvore->dir, id);
    else aux = arvore;

    return aux;
}

//Insere um elemento na ABB
int abb_insere (struct noArv **arvore, int id)
{
    int flag = 0;
    if (*arvore==NULL) {
        *arvore = (struct noArv*)malloc(sizeof(struct noArv));
        (*arvore)->id = id;
        (*arvore)->esq = NULL;
        (*arvore)->dir = NULL;
        flag = 1;
    }
    else if (id < (*arvore)->id){
        flag = abb_insere(&((*arvore)->esq),id);
    }
    else if (id > (*arvore)->id) {
        flag = abb_insere(&((*arvore)->dir),id);
    }
    return flag;
}

//Realiza a remoção do elemento raiz Raiz
struct noArv* abb_removeraiz (struct noArv* r) {  
    struct noArv *p, *q;
    if (r->esq == NULL) {
       q = r->dir;
       free (r);
    }else{
        p = r; q = r->esq;
        while (q->dir != NULL) {
        p = q; q = q->dir;
        }
        // q é nó anterior a r na ordem e-r-d
        // p é pai de q
        if (p != r) {
        p->dir = q->esq;
        q->esq = r->esq;
        }
        q->dir = r->dir;
        free (r);
    }

    return q;
}

//Busca o No que deseja remover e realiza a remoção com a 
//função 'abb_removeraiz'.
struct noArv* abb_remove (struct noArv* arvore, int id)
{
    struct noArv* aux;
    aux = arvore;

    if (arvore == NULL){
        aux = NULL;
    }else if (arvore->id > id){
        aux->esq = abb_remove(arvore->esq, id);
    }else if (arvore->id < id){
        aux->dir = abb_remove(arvore->dir, id);
    }else {
        printf("Else: Raiz = %d\n",arvore->id);
        printf("secao: ");arv_imprime(aux);
        aux = abb_removeraiz(aux);
    }
    return aux;
}

//Retorna o valor da autua do No('root') passado por parametro. 
//Parametros:
//struct arv *root - No;
//Retorno: 
//Retorna o valor da autua do No passado por parametro. 
int altura_No(struct noArv *root){
    int res, r=0, l=0;
    if (root == NULL){
        res = -1;
    }else{
        l = altura_No(root->esq);
        r = altura_No(root->dir);
        if(l > r){
            res = l+1;
        }else{
            res = r+1;
        }
    }
    return res;
   
}

int menor_profundidade_No(struct noArv *root){
    int res, r=0, l=0;
    if (root == NULL){
        res = -1;
    }else{
        l = altura_No(root->esq);
        r = altura_No(root->dir);
        if(l < r){
            res = l+1;
        }else{
            res = r+1;
        }
    }
    return res;
   
}