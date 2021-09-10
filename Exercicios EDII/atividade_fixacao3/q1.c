#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct participantes{
    char nm_artista[100], nm_personagem[100], decription[200];
};

struct arv_part{
    struct participantes infopart;
    struct arv_part *left, *right;
};

struct temporada{
    int nro, qtd_ep, year;
    char title[100];
    struct arv_part *root_part; 
};

struct listaTemp{
    struct temporada info_temp;
    struct listaTemp *prox;
};

struct series{
    int cod, n_temporada;
    char title[100];
    struct listaTemp *begin;
};

struct arv_series{
    struct series info;
    struct arv_series *left, *right;
};

//////PARTICIPANTES

//aloca memoria e adiciona as informações do participante
struct arv_part *aloca_arv_participantes(struct participantes info){
    struct arv_part *new;
    new = NULL;

    new = (struct arv_part*)malloc(sizeof(struct arv_part));

    new->infopart = info;
    new->left = NULL;
    new->right = NULL;

    return new;
}

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
    if(strlen(s1) < strlen(s2)){
        res = 0;
    }
    if(strlen(s1) > strlen(s2)){
        res = 1;
    }
	return res;
    // retona 0 se string1 for menor que string2 e 1 caso contrario
}
//insere um particpante na arvore e reetorna o endereço onde onde foi inserido na arvore
//recebe a raiz da arvore por referencia como parametro e o participante a ser adicionado
int inserir_arv_part(struct arv_part **root, struct arv_part *No){
    int res=0, str;

    if(*root == NULL){
        *root = No;
        res = 1;
    }else{
        str = compare_strings(No->infopart.nm_personagem, (**root).infopart.nm_personagem);
        if(str == 0){
            res = inserir_arv_part(&(**root).left, No);
        }else if (str == 1){
            res = inserir_arv_part(&(**root).right, No);
        }
    }
    return res;
}
///////////////////////////////////////


/* BASICS FUNCTIONS LIST*/

// aloca um elemento
struct listaTemp *aloca_lista(int numero,int qtd_episodio, char titulo[100], int ano){
    struct listaTemp *new;
    struct arv_part *root_part, *No_part;

    struct participantes participante;
    
    int continuar=0, inseriu=0;

    new = NULL;
    root_part = NULL;
    
    new = (struct listaTemp*)malloc(sizeof(struct listaTemp));

    strcpy(new->info_temp.title, titulo);
    new->info_temp.nro = numero;
    new->info_temp.qtd_ep = qtd_episodio;
    new->info_temp.year = ano;


    //insere os participantes da serie na temporada
    do{
        printf("Nome do Artista: ");
        scanf("%s", participante.nm_artista);
        printf("Nome do Personagem: ");
        scanf("%s", participante.nm_personagem);
        printf("Descricao: ");
        scanf("%s", participante.decription);
        setbuf(stdin, NULL);

        No_part = aloca_arv_participantes(participante);
        inseriu = inserir_arv_part(&root_part, No_part);

        while(inseriu != 1){
            printf("\nparticipante ja existe!Deseja adicionar outro?(1 - SIM || 0 - NAO)");
            scanf("%d", &continuar);
            setbuf(stdin, NULL);
            if(continuar == 1){
                printf("Nome do Artista: ");
                scanf("%s", participante.nm_artista);
                printf("Nome do Personagem: ");
                scanf("%s", participante.nm_personagem);
                printf("Descricao: ");
                scanf("%s", participante.decription);
                setbuf(stdin, NULL);

                No_part = aloca_arv_participantes(participante);
                inseriu = inserir_arv_part(&root_part, No_part);
            }

        }
        printf("Adicionar outro participante? (1 - SIM || 0 - NAO):  ");
        scanf("%d", &continuar);
        setbuf(stdin, NULL);
    }while(continuar != 0);
    
    new->info_temp.root_part = root_part;

    new->prox = NULL;

    return new;
}

//tem como parametro uma lista do tipo listaTemp, e o novo No do mesmo tipo a ser inserido
void insere(struct listaTemp **begin,struct listaTemp **end, struct listaTemp *No){

    struct listaTemp *aux, *ant;
    aux = *begin;
    //insere no inicio
    if(*begin == NULL){
        *begin = No;
        *end = No;

    }else if(No->info_temp.nro < (*begin)->info_temp.nro){//se o novo id for menor que o do inicio
        *begin = No; // inicio agora é o novo
        No->prox = aux; //e o proximo do novo é o aux(que guardou o endereço do incio)
    }
    //insere no fim
    else if(No->info_temp.nro > (*end)->info_temp.nro){
        aux = *end;
        aux->prox = No;
        *end = No;
    }else{
        aux = *begin;
        while( No->info_temp.nro > aux->info_temp.nro && aux != NULL){// quando o novo elemento for menor que o aux, faz a inserção
            ant = aux;
            aux = aux->prox;
        }
        No->prox = aux;// o proximo do novo elemento aponta para o aux que  é o elemento maior que ele
        ant->prox = No;// o anterior  apontará para o novo que é o proximo dele
        
    }

}

void imprimir(struct listaTemp *begin){
    struct listaTemp *aux;
    aux = begin;
    if(aux != NULL){
        printf("Numero: %d\nQuantidade de EPs: %d \nTitulo: %s\nAno: %d\n\n\n", aux->info_temp.nro, aux->info_temp.qtd_ep, aux->info_temp.title, aux->info_temp.year);

        imprimir(aux->prox);
    } 
}


////////////////////////////////////////////////////////////////////////
/* INSERSION B-TREE*/

///SERIES
//aloca memoria e são inseridos os dados da serie
//recebe as informações de uma serie por parâmetro
struct arv_series *aloca_arv_series(struct series info){
    struct arv_series *new;
    struct listaTemp *lista_begin, *lista_end, *No;

    int ano, qtd_episodio, numero;
    char titulo[100];

    new = NULL;
    lista_begin = lista_end = NULL;

    new = (struct arv_series*)malloc(sizeof(struct arv_series));

    new->info = info;
    new->left = NULL;
    new->right = NULL;

    // insere informações de uma temporada na lista
    for(int i=0; i < info.n_temporada;i++){
        printf("Numero da temporada: ");
        scanf("%d", &numero);
        printf("Titulo: ");
        scanf("%s", titulo);
        printf("Quantidade de episodios: ");
        scanf("%d", &qtd_episodio);
        printf("Ano: ");
        scanf("%d", &ano);
        setbuf(stdin, NULL);

        No = aloca_lista(numero, qtd_episodio, titulo, ano);

        insere(&lista_begin,&lista_end, No);
        //imprimir(lista_begin);
    }
    new->info.begin = lista_begin;

    return new;
}

//insere uma serie na arvore
//recebe a raiz da arvore por referencia como parametro e a serie a ser adicionada e retorna 1 se foi adicionado e 0 caso contrario
int inserir_arv_series(struct arv_series **root, struct arv_series *No){
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

////////////////////////////

//recebe a raiz da arvore de series como parametro e imprime in-ordem -> esq -> raiz -> dir
void imprimir_inorder(struct arv_series *root){
    if(root != NULL){
        imprimir_inorder(root->left);
        printf("\nCodigo: %d\n\nTitulo: %s\nNumero de Temporadas: %d\n\n",root->info.cod, root->info.title, root->info.n_temporada);
        imprimir_inorder(root->right);
    }
}


void imprimir_temporadas(struct arv_series *root, int codigo){
    
    if(root != NULL){

        if(codigo < root->info.cod){
            imprimir_temporadas(root->left, codigo);
        }
        if(codigo > root->info.cod){
            imprimir_temporadas(root->right, codigo);
            
        }else{
            imprimir(root->info.begin);
        }
    }
}

void imprimir_arv_part(struct arv_part *root){
    if(root != NULL){    
        printf("Personagem: %s\n", root->infopart.nm_personagem);
        imprimir_arv_part(root->left);
        imprimir_arv_part(root->right);      
    }
}

void imprimir_personagens(struct arv_series *root,int codigo, int temp){
    struct listaTemp *aux;
    if(root != NULL){

        if(codigo < root->info.cod){
            imprimir_personagens(root->left, codigo, temp);
        }
        if(codigo > root->info.cod){
            imprimir_personagens(root->right, codigo,temp);
            
        }else{
            aux = root->info.begin;
            while(aux->info_temp.nro != temp && aux != NULL){
                aux = aux->prox;
            }
            if(aux != NULL){
                imprimir_arv_part(aux->info_temp.root_part);
            }
            else{
                printf("Temporada NAO encontrada\n");
            }
        }
    }
}

int menu(){
    int op;
    printf("1 - Listar Series\n2 - Imprimir Em Ordem\n3 - Imprimir Info Temporadas\n4 - Imprimir Persongens\n5 - Imprimir Artistas\n0 - Sair\n");
    scanf("%d", &op);
    
    return op;
}

int main(){
    
    
    struct arv_series *root_series, *No_serie;
    struct series serie;
    
    int continuar, escolha,codigo, temporada, inseriu=0, cont=0;
    
    root_series = NULL;

    do
    {
        escolha = menu();
        switch (escolha)
        {
        //cadastra uma serie
        case 1:
            do{
                printf("Codigo da serie: ");
                scanf("%d", &serie.cod);
                printf("Titulo da Serie: ");
                scanf("%s", serie.title);
                printf("Numero de temporadas: ");
                scanf("%d", &serie.n_temporada);
        
                setbuf(stdin, NULL);

                
                //aloca memoria e insere na arvore de series a serie
                No_serie = aloca_arv_series(serie);
                inseriu = inserir_arv_series(&root_series, No_serie);
                if(inseriu){
                    printf("Serie adicionada!\n");
                }else{
                    printf("Serie NAO adicionada!\n");
                }
                printf("Adicionar outra serie? (1 - SIM || 0 - NAO):  ");
                scanf("%d", &continuar);
                setbuf(stdin, NULL);
            }while(continuar != 0);

            break;
        //imprime a lista de series em ordem de código
        case 2:
            imprimir_inorder(root_series);
            break;
        case 3:
            printf("Codigo da Serie: ");
            scanf("%d", &codigo);
            imprimir_temporadas(root_series, codigo);
            break;
        case 4:
            printf("Codigo da Serie: ");
            scanf("%d", &codigo);
            printf("Temporada: ");
            scanf("%d", &temporada);
            imprimir_personagens(root_series, codigo, temporada);
            break;
        case 5:
            break;
        default:
            if(escolha != 0){
                printf("Valor invalido!\n");
            }
            break;  
        }
    } while (escolha != 0);

    return 0;
}