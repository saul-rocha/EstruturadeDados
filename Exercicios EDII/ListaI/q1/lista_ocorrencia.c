#include <stdio.h>
#include <stdlib.h>
#include "lista_ocorrencia.h"


struct lista *list_cria_vazia(){
    return NULL;
}

struct lista* list_cria(int conteudo,struct lista* prox){
    struct lista* lista = (struct lista*)malloc(sizeof(struct lista*));
    lista->conteudo = conteudo;
    lista->ocorrencias = 0;
    lista->prox = prox;
    return lista;
}

void list_imprime(struct lista *le) {
   if (le != NULL) {
      printf ("Diferenca = %d\n", le->conteudo);
      printf ("Quantidade de Ocorrencias = %d\n\n", le->ocorrencias);
      list_imprime (le->prox);
   }
}

struct lista* list_busca(struct lista *le, int x)
{
   struct lista *p;
   p = le;
    if(le != NULL){
        if(p->conteudo != x){
            list_busca(p->prox,x);
        }        
    }
   return p;
}

//Cira um elemento de lista com o parametro 'x', apos isso insere o elemento na lista com a função 'list_insere_na_lista'.
int list_insere(struct lista **p, int x){
    struct lista* novo;
    novo = list_cria(x,NULL);
    list_insere_na_lista(p,&novo);

    return 0;
}

//Insere um elemento 'novo' na lista 'p' 
int list_insere_na_lista(struct lista **p,struct lista **novo)
{

    int flag = 1;//Indica se o elemento foi inserido (0 = Não, 1 = Sim)

    if(*p == NULL){//"p" é uma lista vazia
        *p = *novo;
    }else if((*p)->conteudo == (*novo)->conteudo){//Elemento ja existente
        flag = 0;
    }else if((*p)->conteudo > (*novo)->conteudo){
        struct lista *aux = NULL;
        (*novo)->prox = *p;
        *p = *novo;
    }else if((*p)->conteudo < (*novo)->conteudo){
        list_insere_na_lista(&((*p)->prox),novo);
    }
    return flag;
}


struct lista *list_ocorrencias(struct lista *p, int valor, int inicial){
  if(p == NULL && valor > inicial){
    //printf("%d - Entrou >> p == NULL && valor > inicial\n",inicial);
    p = list_cria(inicial,NULL);
    p->prox = list_ocorrencias(p->prox,valor,++inicial);
  }else if(valor > inicial){
    //printf("%d - Entrou >> p == NULL && valor > inicial >> valor > inicial\n",inicial);
    p->prox = list_ocorrencias(p->prox,valor,++inicial);
  }else if(p == NULL && valor == inicial){
    //printf("%d - Entrou >> p == NULL && valor == inicial\n",inicial);
    p = list_cria(inicial,NULL);
    p->ocorrencias +=  1;
  }else if(valor == inicial){
    //printf("%d - Entrou >> valor == inicial\n",inicial);
    p->ocorrencias += 1;
  }
  return p;
}