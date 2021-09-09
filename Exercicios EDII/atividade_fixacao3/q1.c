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


/* BASICS FUNCTIONS LIST*/

// aloca um elemento
struct listaTemp *aloca_lista(int numero,int qtd_episodio, char titulo[100], int ano, struct arv_part *root_arv_part){
    struct listaTemp *new;
    new = NULL;
    
    new = (struct listaTemp*)malloc(sizeof(struct listaTemp));

    strcpy(new->info_temp.title, titulo);
    new->info_temp.nro = numero;
    new->info_temp.qtd_ep = qtd_episodio;
    new->info_temp.year = ano;

    new->info_temp.root_part = root_arv_part;

    

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

void imprimir(struct listaTemp *pessoas){
    struct listaTemp *aux;
    aux = pessoas;
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
    new = NULL;

    new = (struct arv_series*)malloc(sizeof(struct arv_series));

    new->info = info;
    new->left = NULL;
    new->right = NULL;

    return new;
}

//insere uma serie na arvore
//recebe a raiz da arvore por referencia como parametro e a seie a ser adicionada
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

//insere um particpante na arvore
//recebe a raiz da arvore por referencia como parametro e o participante a ser adicionado
int inserir_arv_part(struct arv_part **root, struct arv_part *No){
    int res=0;

    if(*root == NULL){
        *root = No;
        res = 1;
    }else{
        if(strcmp(tolower(No->infopart.nm_personagem), tolower((**root).infopart.nm_personagem)) < 0){
            res = inserir_arv_part(&(**root).left, No);
        }else if (strcmp(tolower(No->infopart.nm_personagem), tolower((**root).infopart.nm_personagem)) > 0){
            res = inserir_arv_part(&(**root).right, No);
        }
    }
    return res;
}
///////////////////////////////////////


int menu(){
    int op;
    printf("1 - Listar temporadas\n");
    scanf("%d", &op);
    
    return op;
}

int main(){
    struct listaTemp *lista_begin, *lista_end, *No;
    struct series serie;
    
    int continuar, ano, qtd_episodio, numero, escolha;
    char titulo[100];

    lista_begin = NULL;
    lista_end = NULL;

    do
    {
        escolha = menu();
        switch (escolha)
        {
        case 1:
            // insere pessoa(as) na lista
            do{
                printf("Numero: ");
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

                printf("Deseja adicionar mais? (1 - SIM || 0 - NAO)");
                scanf("%d", &continuar);
                setbuf(stdin, NULL);
            }while(continuar != 0);
            break;
        //imprime a lista de temporadas
        /*case 2:
            imprimir(lista_begin);
            break;*/
        default:
            if(escolha != 0){
                printf("Valor invalido!\n");
            }
            break;  
        }
    } while (escolha != 0);

    return 0;
}