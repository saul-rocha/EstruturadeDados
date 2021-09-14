#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



struct lista{
	char info[100];
	struct lista *prox;
};

struct arv{
	char info[100];
	struct arv *left, *right;
	struct lista *l;
};

//compara duas strings
int compare_strings(char s1[100], char s2[100]){
	int i = 0, j = 0, res = -1;
	while(res == -1 && s1[i] != '\0' && s2[j] != '\0'){
        if(tolower(s1[i]) < tolower(s2[j])){//como podem ser palavras 
            //maisculas e minusculas a função tolower transformara todas em minusculas
            res = 0;
        }
        else if(tolower(s1[i]) > tolower(s2[j])){
            res = 1;
        }
        i++;
        j++;
    }
	//caso sejam igual entra em uma dessas condições
    if(strlen(s1) < strlen(s2) && (res != -1)){
        res = 0;
    }
    if(strlen(s1) > strlen(s2) && (res != -1)){
        res = 1;
    }
	return res;
    // retona 0 se string1 for menor que string2 e 1 caso contrario
}


////LISTA
struct lista *aloca_lista(char palavra[100]){
    struct lista *new;

    new = NULL;
    
    new = (struct lista*)malloc(sizeof(struct lista));

    strcpy(new->info, palavra);
    

    return new;
}

//insere em ordem alfabetica
//recebe o iniccio e o fim de uma lista por referencia eo No a ser adicionado
void insere(struct lista **begin,struct lista **end, struct lista *No){
    int s;
    struct lista *aux, *ant;
    aux = *begin;
    //insere no inicio
    if(*begin == NULL){
        *begin = No;
        *end = No;
        s = compare_strings(No->info, (*begin)->info);
    }else if(compare_strings(No->info, (*begin)->info) == 0){//se No for menor que inicio
        *begin = No; // inicio agora é o novo
        No->prox = aux; //e o proximo do novo é o aux(que guardou o endereço do incio)
    }
    //insere no fim
    else if(compare_strings(No->info, (*end)->info) == 1){//Se o No for maior que o fim
        aux = *end;
        aux->prox = No;
        *end = No;
    }else{
        aux = *begin;
        while(compare_strings(No->info, aux->info) == 0 && aux != NULL){// quando o novo elemento for menor que o aux, faz a inserção
            ant = aux;
            aux = aux->prox;
        }
        No->prox = aux;// o proximo do novo elemento aponta para o aux que  é o elemento maior que ele
        ant->prox = No;// o anterior  apontará para o novo que é o proximo dele
    }

}


///ALOCAÇÃO E INSERSÃO NA ARVORE
struct arv *aloca_arv(){
    struct arv *new;
    struct lista *lista_begin, *lista_end, *No;

    int continuar;
    char palavra[100];

    new = NULL;
    lista_begin = lista_end = NULL;

    new = (struct arv*)malloc(sizeof(struct arv));

    new->left = NULL;
    new->right = NULL;

    // insere informações na lista
    do{
        printf("Palavra: ");
        scanf("%s", palavra);
        setbuf(stdin, NULL);

        No = aloca_lista(palavra);
        insere(&lista_begin,&lista_end, No);

        printf("Adicionar outra palavra?(1-SIM || 2-NAO): ");
        scanf("%d", &continuar);
    //imprimir(lista_begin);
    }while(continuar != 0);
    new->l = lista_begin;

    return new;
}

//insere uma serie na arvore
//recebe a raiz da arvore por referencia como parametro e a serie a ser adicionada e retorna 1 se foi adicionado e 0 caso contrario
int inserir_arv(struct arv_series **root, struct arv_series *No){
    int res=0;

    if(*root == NULL){
        *root = No;
        res = 1;
    }else{
        if(No->info.cod < (**root).info.cod){
            res = inserir_arv_series(&(**root).left, No);
        }else if (No->info.cod > (**root).info.cod){
            res = inserir_arv_series(&(**root).right, No);
        }
    }
    return res;
}


//recebe a raiz da arvore de series como parametro e imprime in-ordem -> esq -> raiz -> dir
void imprimir_arv(struct arv *root){
    if(root != NULL){
        printf("\nCodigo: %d\n\nTitulo: %s\nNumero de Temporadas: %d\n\n",root->info.cod, root->info.title, root->info.n_temporada);
        imprimir_inorder(root->left);
        imprimir_inorder(root->right);
    }
}
////////////////////////////

int main(){
    struct arv *vocab;

    FILE *filename;

    filename = fopen("livro_texto.txt", "w");
    if(filename == NULL)
    {
        printf("Erro na abertura do arquivo!");
    }