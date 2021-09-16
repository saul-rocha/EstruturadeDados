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
	struct arv_palavras *left, *right;
};

struct arv_unidade{
    char nm_unidade[100];
    struct arv_palavras *palavras;
    struct arv_unidade *left, *right;
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

void qtd_virgulas(char palavras[100], int *qtd){
    for(int i=0; palavras[i] != '\0'; i++){
        if(palavras[i] == ','){
            *qtd += 1;
        }
    }
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
    struct lista_equivalentes *aux, *ant;
    aux = *begin;
    //insere no inicio
    if(*begin == NULL){
        *begin = No;
        *end = No;

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

//impime a lista
void imprimir_lista(struct lista_equivalentes *begin){
    struct lista_equivalentes *aux;
    aux = begin;
    if(aux != NULL){
        printf("%s, ", aux->info);
        imprimir_lista(aux->prox);
    } 
    printf("\n");
}
///ALOCAÇÃO E INSERSÃO NA ARVORE
struct arv_palavras *aloca_arv_palavras(char palavra[100], char port_word[100]){
    struct arv_palavras *new;
    struct lista_equivalentes *lista_begin, *lista_end, *No;

    int continuar, i,j;
    char  english_word[100];


    new = NULL;
    lista_begin = lista_end = NULL;

    new = (struct arv_palavras*)malloc(sizeof(struct arv_palavras));
    strcpy(new->info, port_word);

    new->left = NULL;
    new->right = NULL;

    
    for(i=0; palavra[i] != ' '; i++);//anda a string até o primeiro espaço vazio
    j=0;
    for(i; palavra[i] != ':'; i++){//contatena a string até o dois pontos e insere na lista
        english_word[j] =  palavra[i];
        j++;
    }
    english_word[j+1] = '\0';


    No = aloca_lista(english_word);
    insere(&lista_begin,&lista_end, No);
    
    new->l = lista_begin;

    return new;
}

//insere uma palavra em portugues na arvore
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
void imprimir_arv_palavras(struct arv_palavras *root){
    if(root != NULL){
        printf("Palavra: %s\n\n", root->info);
        imprimir_arv_palavras(root->left);
        imprimir_arv_palavras(root->right);
    }
}

////////////////////////////
/// ARVORE DE UNIDADES
struct arv_unidade *aloca_arv_unidade(char palavra[100]){
    struct arv_unidade *new;
    struct arv_palavras *root, *No;
    
    int  i,j,k, qtd_vir=0;
    char unidade[100], port_word[100];
    memset(unidade,'\0',strlen(unidade));
    new = NULL;
    root = NULL;

    new = (struct arv_unidade*)malloc(sizeof(struct arv_unidade));
    new->left = NULL;
    new->right = NULL;

    j=0;
    for(i=0; palavra[i] != ' '; i++){
        if(palavra[i] != '%'){
            unidade[j] = palavra[i];
            j++;

        }
    }
    unidade[j] = '\0';
    strcpy(new->nm_unidade, unidade);

    qtd_virgulas(palavra, &qtd_vir);

    i=0;
    if( qtd_vir > 0){
        for(i; palavra[i] != ':';i++);
        j = i+1;
        k=0;
        for(j; palavra[j] != ',' && palavra[j] != '\0' && palavra[j] != '\n';j++){//pega a palavra entre as virgulas ou a ultima/unica
            
            port_word[k] = palavra[j];
            k++;
            if(palavra[j+1] != ',' && palavra[j+1] != '\0'){
                //quando finalizar a passagem da palavra adiciona na arvore
                No = aloca_arv_palavras(palavra, port_word);
                inserir_arv_palavras(&root, No);
            }
        }
    }

    return new;
}

int inserir_arv_unidade(struct arv_unidade **root, struct arv_unidade *No){
    int res=0;
    if(*root == NULL){
        *root = No;
        res = 1;
    }else{
        if(compare_strings(No->nm_unidade, (*root)->nm_unidade) == 0){
            res = inserir_arv_unidade(&(**root).left, No);
        }else if (compare_strings(No->nm_unidade, (*root)->nm_unidade) == 1){
            res = inserir_arv_unidade(&(**root).right, No);
        }
    }
    return res;
}

void imprimir_arv_unidades(struct arv_unidade *root){
    if(root != NULL){
        printf("Unidade: %s\n\n", root->nm_unidade);
        //printf("Palavra: %s", root->palavras->info);
        imprimir_arv_unidades(root->left);
        imprimir_arv_unidades(root->right);
    }
}
int menu(){
    int escolha;
    printf("1 - Preencher Arvores\n0 - Sair\n");
    scanf("%d", &escolha);

    return escolha;
}

int main(){
    struct arv_unidade *port_ingles, *No;

    int escolha, res, tam, n=0;
    char c[100], c1[100];    
    FILE *filename;

    port_ingles = NULL;


    filename = fopen("livro_texto.txt", "r");
   
    do{
        escolha = menu();
        switch (escolha)
        {
        case 1:
            while(!feof(filename)){
                fgets(c,100,filename);
                
                
                No = aloca_arv_unidade(c);
                res = inserir_arv_unidade(&port_ingles, No);
                if(!res){
                    printf("[%s] Nao inserida! Ja inserida anteriormente!\n", c);
                }
                
            }
            
            imprimir_arv_unidades(port_ingles);
            printf("%s\n",port_ingles->palavras->info);
            break;
        case 2:
            
        default:
            break;
        }

    }while(escolha != 0);
    fclose(filename);

    return 0;
}