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

 // arvore_binaria=NULL;
 
 struct noArv* arvore_binaria = (struct noArv*)malloc(sizeof(struct noArv));

 if(arvore_binaria==NULL) exit(1);
 arvore_binaria->id = id;
 arvore_binaria->altura = 0;
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

//-----------------------------------------------------
//Arvore AVL

// Retorna o maior valor entre dois inteiros
int avl_max(int a, int b){
	if (a>b) 
        b = a;
	return b;
}

// Retorna a altura de uma (sub-)arvore
int avl_altura(struct noArv *p){
	int autura = 0;
    if (p == NULL)
        autura = autura - 1;
	else 
        autura = 1 + avl_max(avl_altura(p->esq),avl_altura(p->dir));

    return autura;
}

/* Exibe arvore Em Ordem de inserção (com parenteses para os filhos) */
void exibirArvore(struct noArv *raiz){
	if (raiz == NULL) return;
	printf("%i[%i]",raiz->id,avl_fator_balanceamento(raiz));
	printf("(");     
	exibirArvore(raiz->esq);
	exibirArvore(raiz->dir);
	printf(")");     
}

//Rotação a direita
  struct noArv *avl_rot_dir(struct noArv *p){
  struct noArv *q, *temp;
  q = p->esq;
  temp = q->dir;
  q->dir = p;
  p->esq = temp;
  p = q;

return p;
}

//Rotação a esquerda
struct noArv *avl_rot_esq(struct noArv *p){
  struct noArv *q, *temp;
  q = p->dir;
  temp = q->esq;
  q->esq = p;
  p->dir = temp;
  p = q;

  return p;
}

//Rotação dupla 1° esquerda 2° direita
struct noArv *avl_rot_esq_dir(struct noArv *p){
  p->esq =avl_rot_esq(p->esq);
  p = avl_rot_dir(p);
  return p;
}

//Rotação dupla 1° direita 2° esquerda
struct noArv *avl_rot_dir_esq(struct noArv *p){
  p->dir = avl_rot_dir(p->dir);
  p = avl_rot_esq(p);
  return p;
}

//X
//Calcula o fator de balanceamento
int avl_fator_balanceamento(struct noArv *p){
  int al_esq, al_dir;
  if(p->esq == NULL){
    al_esq = 0;
  }else{
    al_esq = p->esq->altura + 1;
  }
  if(p->dir == NULL){
    al_dir = 0;
  }else{
    al_dir = p->dir->altura + 1;
  }

  return al_esq - al_dir;
}

//Ajustar a altura de todos os elementos do No
struct noArv *avl_ajustar_altura(struct noArv *arvore){
    if (arvore != NULL){
        arvore->esq = avl_ajustar_altura(arvore->esq); 
        arvore->dir = avl_ajustar_altura(arvore->dir);
        arvore->altura = avl_altura(arvore);
    }
    return arvore;
}

//Realiza o balanceamento da arvore
struct noArv *avl_balancear_No(struct noArv *p){
  struct noArv *aux;
  aux = NULL;

  if(p != NULL){
    if(avl_fator_balanceamento(p) > 0){
      if(avl_fator_balanceamento(p->esq) > 0){
        aux = avl_rot_dir(p);
      }else if(avl_fator_balanceamento(p->esq) < 0){
        aux = avl_rot_esq_dir(p);
      }
    }else if(avl_fator_balanceamento(p) < 0){
      if(avl_fator_balanceamento(p->dir) < 0){
        aux = avl_rot_esq(p);
      }else if(avl_fator_balanceamento(p->dir) > 0){
        aux = avl_rot_dir_esq(p);
      }
    }
  }

  return aux;
}

//-----------------------------------------------------

//Insere um elemento na ABB
int abb_insere (struct noArv **arvore, int id)
{

    int flag = 0;
    int fator_bal;
    if (*arvore==NULL) {
        *arvore = (struct noArv*)malloc(sizeof(struct noArv));
        (*arvore)->id = id;
        (*arvore)->esq = NULL;
        (*arvore)->dir = NULL;
        (*arvore)->altura = 0;
        flag = 1;
    }
    else if (id < (*arvore)->id){
        flag = abb_insere(&((*arvore)->esq),id);
    }
    else if (id > (*arvore)->id) {
        flag = abb_insere(&((*arvore)->dir),id);
    }


    //Re-calcular a autura do No
    if(flag == 1 && (*arvore)->id != id){
      (*arvore)->altura = avl_altura((*arvore));
    }

    //Balanceamento da arvore
    fator_bal = avl_fator_balanceamento((*arvore));

    //printf("FB = %d\n",fator_bal);
    if(fator_bal < -1 || fator_bal > 1){
      *arvore = avl_balancear_No(*arvore);
      *arvore = avl_ajustar_altura(*arvore);
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
    int fator_bal;
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

    fator_bal = avl_fator_balanceamento(aux);
    printf("FB = %d",fator_bal);
    if(fator_bal <= -1 && fator_bal >= 1){
      printf("Entrou");
      aux = avl_balancear_No(aux);
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