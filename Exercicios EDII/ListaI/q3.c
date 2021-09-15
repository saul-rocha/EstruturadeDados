#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>



struct lista_equivalentes{
	char info[100];
	struct lista_equivalentes *prox;
};

struct arv_palavras{
	char info[100];
	struct lista_equivalentes *l;
	struct arv *left, *right;
};

struct arv_unidade{
    char unidade[100];
    struct arv_palavras *nm_unidade;
    struct unidade *left, *right;
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
struct lista_equivalentes *aloca_lista(char palavra[100]){
    struct lista_equivalentes *new;

    new = NULL;
    
    new = (struct lista_equivalentes*)malloc(sizeof(struct lista_equivalentes));

    strcpy(new->info, palavra);
    

    return new;
}

//insere em ordem alfabetica
//recebe o iniccio e o fim de uma lista por referencia eo No a ser adicionado
void insere(struct lista_equivalentes **begin,struct lista_equivalentes **end, struct lista_equivalentes *No){
    int s;
    struct lista_equivalentes *aux, *ant;
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
struct arv_palavras *aloca_arv(){
    struct arv_palavras *new;
    struct lista_equivalentes *lista_begin, *lista_end, *No;

    int continuar;
    char palavra[100];

    new = NULL;
    lista_begin = lista_end = NULL;

    new = (struct arv_palavras*)malloc(sizeof(struct arv_palavras));

    new->left = NULL;
    new->right = NULL;

    // insere informações na lista
    do{
        printf("Palavra: ");
        scanf("%s", palavra);// aqui vai ser a string que vem do arquivo
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

/*/insere uma serie na arvore
//recebe a raiz da arvore por referencia como parametro e a serie a ser adicionada e retorna 1 se foi adicionado e 0 caso contrario
int inserir_arv_palavras(struct arv_palavras **root, struct arv_palavras *No){
    int res=0;
    if(*root == NULL){
        *root = No;
        res = 1;
    }else{
        if(compare_strings(No->info, (*root)->info) == 0){
            res = inserir_arv_palavras(&(**root).left, No);
        }else if (compare_strings(No->info, (*root)->info) == 1){
            res = inserir_arv_palavras(&(**root).right, No);
        }
    }
    return res;
}


//recebe a raiz da arvore como parametro e imprime in-ordem -> esq -> raiz -> dir
void imprimir_arv(struct arv_palavras *root){
    if(root != NULL){
        printf("Titulo: %s\n\n", root->info);
        imprimir_arv(root->left);
        imprimir_arv(root->right);
    }
}
*/
////////////////////////////



int menu(){
    int escolha;
    printf("1 - Preencher Arvores\n0 - Sair\n");
    scanf("%d", &escolha);

    return escolha;
}

int main(){
    struct arv *port_ingles;

    int escolha;
    char c[100];

    port_ingles = NULL;


    FILE *filename;

    filename = fopen("livro_texto.txt", "r");

    do{
        escolha = menu();
        switch (escolha)
        {
        case 1:
            fgets(c,100,filename);
            printf("%s\n", c);
            break;
        
        default:
            break;
        }

    }while(escolha != 0);
    fclose(filename);

    return 0;
}