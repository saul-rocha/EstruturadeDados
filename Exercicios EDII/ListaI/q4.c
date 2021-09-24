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

int existe_elem_lista(struct lista_equivalentes *begin, char palavra[100]){
    int res;
    res = 0;
    if(compare_strings(palavra,begin->info)==-1){
        res = 1;
    }else if(begin == NULL){
        res = 0;
    }else{
        res = existe_elem_lista(begin->prox, palavra);
    }

    return res;
}
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

//altura de um no
int altura_No(struct arv_palavras *root){
    int res, r=0, l=0;
    if (root == NULL){
        res = -1;
    }else{
        l = altura_No(root->left);
        r = altura_No(root->right);
        if(l > r){
            res = l+1;
        }else{
            res = r+1;
        }
    }
    return res;
   
}

//profundidade de um nó
int maior_profundidade_No(struct arv_palavras *root){
    int res, r=0, l=0;
    if (root == NULL){
        res = -1;
    }else{
        l = altura_No(root->left);
        r = altura_No(root->right);
        if(l > r){
            res = l+1;
        }else{
            res = r+1;
        }
    }
    return res;
   
}

int balanceada(int altura1, int altura2){
    int res;
    res = altura1 - altura2;

    return res;
}


struct arv_palavras *gira_horario(struct arv_palavras *root){
    struct arv_palavras *No;
    No = root->left;

    root->left = No->right;
    No->right = root;

    root = No;

    return root;
}
struct arv_palavras *gira_anti_horario(struct arv_palavras *root){
    struct arv_palavras *No;

    No = root->right;

    root->right = No->left;
    No->left = root;

    root = No;

    return root;
}


void balanco_avl(struct arv_palavras **root){
    int altura_left, altura_rigth, fator_b;
    struct arv_palavras *No;

    fator_b =balanceada(altura_No((*root)->left), altura_No((*root)->right));

    // > 1 se desbalanceada para a esquerda
    if(fator_b > 1){
        No = (*root)->left;
        //ver qual o galho é maior. interno se fator_b < 0 e externo caso contrario
        fator_b = balanceada(altura_No(No->left), altura_No(No->right));
        if(fator_b < 0){
            //gira no sentido anti-horario se o galho interno for o maior
            (*root)->left = gira_anti_horario((*root)->left);
        }
        //gira o nó desbalanceado
        *root = gira_horario(*root);
    // < 1 se desbalanceada para a direita
    }else if(fator_b < -1){
            No = (*root)->right;
             //ver qual o galho é maior. interno se fator_b > 0 e externo caso contrario
            fator_b = balanceada(altura_No(No->left), altura_No(No->right));
            if(fator_b > 0){
                //gira no sentido horario
                (*root)->right = gira_horario((*root)->right);
            }
            //gira o nó desbalanceado
            *root = gira_anti_horario(*root);

        }
    

}

//recebe a raiz da arvore como parametro e imprime in-ordem -> left -> raiz -> right
void imprimir_arv_palavras(struct arv_palavras *root){
    if(root != NULL){
        printf("Palavra: %s\n", root->info);
        printf("Equivalentes: ");
        imprimir_lista(root->l);
        imprimir_arv_palavras(root->left);
        imprimir_arv_palavras(root->right);
    }
}

//retorna o endereço/No de uma palavra na arvore
struct arv_palavras *busca_palavra(struct arv_palavras *root, char portugues[100]){
    struct arv_palavras *res;
    if(root == NULL){
        res = NULL;
    }else{
        if(compare_strings(portugues, root->info) == 0){
            res = busca_palavra(root->left, portugues);
        }else if (compare_strings(portugues, root->info) == 1){
            res = busca_palavra(root->right, portugues);
        }else{
            res = root;
        }
    }
    return res;
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

            No = aloca_arv_palavras(portugues_word, english_word);
            res = inserir_arv_palavras(&unidade.words, No);
            balanco_avl(&unidade.words);
            //printf("unit: %s\n", unidade.words->l->info);
            j=0;
            if(!res){
                printf("[%s] Nao Inserida!\n", portugues_word);
            }
        }
    }
    return unidade;
    
}


//libera lista
void list_libera(struct lista_equivalentes *begin) {
   if (begin != NULL) {
      list_libera (begin->prox);
      free(begin);
   }
}
//Realiza a remoção do elemento raiz Raiz passado por parâmetro
struct arv_palavras* abb_removeraiz (struct arv_palavras * r) {  
    struct arv_palavras *p, *q;
    if (r->left == NULL) {
       q = r->right;
       list_libera(r->l);
       free (r);
    }else{
        p = r; 
        q = r->left;
        while (q->right != NULL) {
            p = q; 
            q = q->right;
        }
        // q é nó anterior a r na ordem e-r-d
        // p é pai de q
        if (p != r) {
        p->right = q->left;
        q->left = r->left;
        }
        q->right = r->right;
        list_libera(r->l);
        free (r);
        
    }

    return q;
}

//Busca o No que deseja remover e realiza a remoção com a 
//função 'abb_removeraiz'.
struct arv_palavras* abb_remove (struct arv_palavras *arvore, char info[100])
{
    struct arv_palavras* aux;
    aux = arvore;

    if (arvore == NULL){
        aux = NULL;
    }else if (compare_strings(info, arvore->info) == 0){
        aux->left = abb_remove(arvore->left, info);
    }else if (compare_strings(info, arvore->info) == 1){
        aux->right = abb_remove(arvore->right, info);
    }else {
        
        aux = abb_removeraiz(aux);
    }
    return aux;
}



int menu(){
    int escolha;
    printf("1 - Preencher Arvores\n2 - Imprimir tudo\n3 - Imprimir Todas As Palavras Inglesas Equivalentes A Uma Portuguesa\n4 - Remover Palavra De Uma Unidade\n0 - Sair\n");
    scanf("%d", &escolha);

    return escolha;
}

int main(){
    struct unit port_ingles[TAM];
    struct arv_palavras *teste;
    int escolha, res, i=-1, j=0;
    char c[100], word[100];
    char a;
    FILE *filename;
    clock_t t_insercao, t_busca;
    float t_insercao_medio,t_busca_medio;

    for(int a=0; a < TAM; a++){
        port_ingles[a].words = NULL;
    }
    
    printf("AVL\n");
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
                }else if (strlen(c) > 0){
                    t_insercao = (double)clock();//Tempo inicial
                    port_ingles[i] = unidade(port_ingles[i],c);
                    t_insercao = (((double)clock()) - t_insercao); //tempo final
                } 
            }
           

            printf("TEMPO DE INSERCAO: %.2lf\n", ((double)t_insercao));
            //imprimir_arv_palavras(port_ingles[2].words);
            break; 
        case 2:
            
            setbuf(stdin,NULL);
            printf("Informe uma Unidade: ");
            scanf("%c", &a);
            setbuf(stdin,NULL);
            printf("%c", a);
            for(j=0; j < i; j++){
                if(a == port_ingles[j].unidade){
                    imprimir_arv_palavras(port_ingles[j].words); 
                    j = i;
                }
            }
            
            break;
        case 3:
            printf("Informe uma Palavra em Portugues: ");
            scanf("%s", word);
            
            for(j=0;j<i;j++){
                t_busca = clock();//Tempo inicial
                teste = busca_palavra(port_ingles[j].words,word);
                t_busca = (clock() - t_busca);
                //tempo final - tempo inicial
                if(teste != NULL){
                    printf("TEMPO DE BUSCA: %.2lf\n", ((double)t_busca));
                    imprimir_lista(teste->l);

                }
            }
            
            break;
        
        case 4:
            printf("Informe uma Palavra:");
            scanf("%s", word);
            setbuf(stdin, NULL);
             
            for(j=0; j< i; j++){
                port_ingles[j].words = abb_remove(port_ingles[j].words, word);
            }
            balanco_avl(&port_ingles->words);
    
            break;
        
        default:
            break;
        }

    }while(escolha != 0);
    fclose(filename);

    return 0;
}