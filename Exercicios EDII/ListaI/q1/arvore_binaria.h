#ifndef ARVORE_BINARIA_H_   /* Include guard */
#define ARVORE_BINARIA_H_

struct noArv {
    int id;
    struct noArv* esq;
    struct noArv* dir;
};

void ola_mundo();
struct noArv* arv_criavazia (void);
struct noArv* arv_cria(int id, struct noArv* sae, struct noArv* sad);
struct noArv* avr_libera(struct noArv* arvore);
int arv_pertence(struct noArv* arvore, int id);
void arv_imprime(struct noArv* arvore);
struct noArv* abb_busca (struct noArv* arvore, int id);
int abb_insere (struct noArv **arvore, int id);
struct noArv* abb_removeraiz (struct noArv* r);
struct noArv* abb_remove (struct noArv* arvore, int id);
int altura_No(struct noArv *root);
int menor_profundidade_No(struct noArv *root);

#endif // ARVORE_BINARIA_H_

