#ifndef LISTA_OCORRENCIA_H_   /* Include guard */
#define LISTA_OCORRENCIA_H_

struct lista {
    int conteudo;
    int ocorrencias; 
    struct lista *prox;
};

struct lista* list_cria_vazia();
struct lista* list_cria(int conteudo,struct lista* prox);
void list_imprime (struct lista *le);
struct lista* list_busca(struct lista *le, int x);
int list_insere(struct lista **p, int x);
int list_insere_na_lista(struct lista **p,struct lista **novo);
void lista_contagem_ocorrencia(struct lista **p, int valor);
struct lista *list_ocorrencias(struct lista *p, int valor, int inicial);

#endif // LISTA_OCORRENCIA_H_