#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TAM 20
struct lista_equivalentes{
	char info[100];
	struct lista_equivalentes *prox;
};

struct arv_palavras{
	char info[100];
	struct lista_equivalentes *l;
	struct arv_palavras *left, *right;
};

struct unit{
    char unidade;
    struct arv_palavras *words;
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
    if(strlen(s1) < strlen(s2) && (res == -1)){
        res = 0;
    }
    if(strlen(s1) > strlen(s2) && (res == -1)){
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
    new->prox = NULL;

    strcpy(new->info, palavra);

    return new;
}

//insere em ordem alfabetica
//recebe o iniccio e o fim de uma lista por referencia eo No a ser adicionado
void insere_lista(struct lista_equivalentes **begin, struct lista_equivalentes *No){

    if(*begin == NULL){
        *begin = No;
        
    }else{
        printf("aqui No.info = %s\n", No->info);
        insere_lista(&(**begin).prox, No);
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
struct arv_palavras *aloca_arv_palavras(char port_word[100], char english_word[100]){
    struct arv_palavras *new;
    struct lista_equivalentes *lista_begin, *No;

    new = NULL;

    lista_begin = NULL;

    new = (struct arv_palavras*)malloc(sizeof(struct arv_palavras));
    strcpy(new->info, port_word);

    No = aloca_lista(english_word);
    insere_lista(&lista_begin, No);

    lista_begin->prox = NULL;
    
    new->l = lista_begin;
    new->left=NULL;
    new->right=NULL;
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
        printf("Palavra: %s\n", root->info);
        printf("Equivalentes: ");
        imprimir_lista(root->l);
        imprimir_arv_palavras(root->left);
        imprimir_arv_palavras(root->right);
    }
}

////////////////////////////


/// UNIDADES
struct unit unidade(struct unit unidade,char palavra[100]){
    struct arv_palavras *No;
    struct unit resultado;
    int  i,j, res;
    char english_word[100],portugues_word[100];
    ///inserir todas as palavras em uma unidade
   
    j=0;
    for(i=0;palavra[i] != ':'; i++){//pega a palavra em ingles
        english_word[j] = palavra[i];
        j++;
    }
    
    english_word[j] = '\0';
    j=0;
    for(i=i+1;palavra[i] != '\0'; ++i){//pega adiciona todas na arvore de palavras
        portugues_word[j] = palavra[i];
        j++;
    
        if(palavra[i] == '.' || palavra[i] == '\0'|| palavra[i] == ','){

            portugues_word[j-1] = '\0';
            printf("Port: %s - En: %s\n", portugues_word, english_word);

            No = aloca_arv_palavras(portugues_word, english_word);
            res = inserir_arv_palavras(&unidade.words, No);
            //printf("unit: %s\n", unidade.words->l->info);
            j=0;
            if(!res){
                printf("[%s] Nao Inserida!\n", portugues_word);
            }
        }
    }
    return unidade;
    
}

int menu(){
    int escolha;
    printf("1 - Preencher Arvores\n0 - Sair\n");
    scanf("%d", &escolha);

    return escolha;
}

int main(){
    struct unit port_ingles[TAM];

    int escolha, res, i=-1;
    char c[100], c1;
    FILE *filename;

    

    filename = fopen("livro_texto.txt", "r");
   
    do{
        escolha = menu();
        switch (escolha)
        {
        case 1:
            while(!feof(filename)){
                fgets(c,100,filename);

                if(c[0] == '%'){
                    i++;
                    port_ingles[i].unidade = c[1];
                    //printf("%s\n", c);
                }else if (strlen(c) > 0){
                    port_ingles[i] = unidade(port_ingles[i],c);
                } 
            }
  
            //printf("%c\n", port_ingles[2].unidade);
            
            break;
        case 2:
            for(int j=0;j < i;j++){
                printf("Unidade: %c\n", port_ingles[j].unidade);
                imprimir_arv_palavras(port_ingles[j].words);
                //printf("%s\n", port_ingles[j].words->info);
            }
            break;
            
        default:
            break;
        }

    }while(escolha != 0);
    fclose(filename);

    return 0;
}