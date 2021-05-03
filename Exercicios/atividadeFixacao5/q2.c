#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 3


struct Fila{
    char modelo[30], marca[30], cor[20];
    int ano, placa, chassi;
    
};

// recebe uma fila de carros e o inicio e o fim da mesmo por referência
void insere(struct Fila f[], int *inicio, int *fim){
    if((*inicio == -1 && *fim == -1)){ // verifica se a fila está vazia
        (*inicio)++;
        (*fim)++;
        printf("Chassi: ");
        scanf("%d", &f[(*inicio)].chassi);
        printf("Placa: ");
        scanf("%d", &f[(*inicio)].placa);
        printf("Modelo: ");
        scanf("%s", f[(*inicio)].modelo);
        printf("Marca: ");
        scanf("%s", f[(*inicio)].marca);
        printf("Cor: ");
        scanf("%s", f[(*inicio)].cor);
        printf("Ano: ");
        scanf("%d", &f[(*inicio)].ano);
        

    }else if(*fim < TAM){//caso naoo esteja lotada, adiciona ao fim da fila 
        (*fim)++;
        printf("Chassi: ");
        scanf("%d", &f[(*fim)].chassi);
        printf("Placa: ");
        scanf("%d", &f[(*fim)].placa);
        printf("Modelo: ");
        scanf("%s", f[(*fim)].modelo);
        printf("Marca: ");
        scanf("%s", f[(*fim)].marca);
        printf("Cor: ");
        scanf("%s", f[(*fim)].cor);
        printf("Ano: ");
        scanf("%d", &f[(*fim)].ano);
        
    }else{
        printf("cheia!\n");
    }
}
//mesmos parametros da anterior, porém retorna o primeiro carro(o que irá ser removido)
struct Fila remover_carro(struct Fila f[], int *inicio, int *fim){
    struct Fila carro = f[0];
    if(*inicio <= *fim){
        for(int i = 0; i < *fim;i++){// retira o primeiro carro e coloca o segundo no inicio
            f[i] = f[i+1];
        }
        (*fim)--;// fila diminui de tamanho
    }else{
        (*inicio) = (*fim) = -1; // quando a fila ficar vazia. irá ser reiniciada para seus valores iniciais
    }
    return carro;
}

//imprime recursivamente toda a fila
void imprimir (struct Fila f[], int inicio, int fim){
    if (inicio <= fim && inicio != -1){
        printf("\n-----------------------\n");

        printf("Chassi: %d\n", f[inicio].chassi);
        printf("Placa: %d\n", f[inicio].placa);
        printf("Modelo: %s\n", f[inicio].modelo);
        printf("Marca: %s\n", f[inicio].marca);
        printf("Cor: %s\n", f[inicio].cor);
        printf("Ano: %d\n", f[inicio].ano);

        printf("\n-----------------------\n");
        inicio++;
        imprimir (f, inicio, fim);// recursão sem pendencia;
    }
}


// recebe uma fila de carros e o primeiro carro, a placa do carro que irá ser removido, o inicio e o fim da fila
// por referencia
int tirar_carro(struct Fila f[], int placa, int *inicio, int *fim){
    int chas;
    struct Fila aux = f[0];
    if(f[(*inicio)].placa == placa){
        chas = f[*inicio].chassi;
        remover_carro(f,inicio,fim);
    }else{
        for(int i = 0; i < *fim;i++){// retira o primeiro carro e coloca o segundo no inicio
            f[i] = f[i+1];
        }
        f[*fim] = aux;// carro no final da fila agora é o que estava no inicio da fila
        tirar_carro(f,placa,inicio,fim);// chama recursivamente para continuar procurando a placa

    }

    return chas; // retorna o chassi do carro removido
}

// recebe tres filas de carros(original, placas pares, placas impares) com seus respectivos inicios e fins por referencia
void filas_impar_par(struct Fila f[], struct Fila par[], struct Fila impar[],int *inicio, int *fim, int *iniciopar, int *fimpar, int *inicioimpar, int *fimimpar){
    if(*inicio <= *fim){
        if(f[*inicio].placa % 2 == 0){//verifica se é par
            if((*iniciopar == -1 && *fimpar == -1)){
                (*iniciopar)++;
                (*fimpar)++;
                //se placa for par insere o caro na fila par
                par[*iniciopar] = remover_carro(f,inicio,fim);// remove o carro da fila original e adiciona na fila par
            }else if(*fimpar < TAM){//caso naoo esteja lotada, adiciona ao fim da fila 
                (*fimpar)++;
                par[*fimpar] = remover_carro(f,inicio,fim);    // remove o carro da fila original e adiciona na fila par        
            }

        }else{
            if((*inicioimpar == -1 && *fimpar == -1)){
                (*inicioimpar)++;
                (*fimimpar)++;
                //se placa for impar insere o carro na fila impar
                impar[*inicioimpar] = remover_carro(f,inicio,fim);// remove o carro da fila original e adiciona na fila impar
            }else if(*fimimpar < TAM){//caso naoo esteja lotada, adiciona ao fim da fila 
                (*fimimpar)++;
                impar[*fimimpar] = remover_carro(f,inicio,fim);   // remove o carro da fila original e adiciona na fila impar
            }
        }
        filas_impar_par(f, par, impar, inicio, fim, iniciopar, fimpar, inicioimpar, fimimpar);
        // recursividade sem pendencia até que a fila original fique vazia
    }
}

//menu
int menu(){
    int op;

    printf("1- Inserir\n2- Remover\n3- Imprimir\n4- Retirar carro\n5- Dividir Fila(Par/Impar)\n6- Imprime Par\n7- Imprime Impar\n0- Sair\n");
    scanf("%d", &op);

    return op;
}

int main(){
    struct Fila fila[TAM];
    struct Fila fila_par[TAM];
    struct Fila fila_impar[TAM];

    int begin = -1, end = -1, begin_par = -1, end_par = -1, begin_impar = -1, end_impar = -1;
    struct Fila aux, carro;
    
    int op, placa, chassi;

    do
    {
        op = menu();

        switch (op)
        {
        case 1:
            insere(fila, &begin, &end);
            break;
        
        case 2:
            carro = remover_carro(fila,&begin, &end);
            break;
        case 3:
            imprimir(fila, begin, end); 
            break;

        case 4:
            printf("Digite a placa: ");
            scanf("%d", &placa);
             // guarda o inicio da fila antes de procurar a placa
            chassi = tirar_carro(fila, placa, &begin, &end);
            printf("Chassi removido: %d\n", chassi);
            break;
        case 5: 
            filas_impar_par(fila, fila_par, fila_impar, &begin, &end, &begin_par, &end_par, &begin_impar, &end_impar);
            break;
        case 6:
            imprimir(fila_par, begin_par, end_par);
            break;
        case 7:
            imprimir(fila_impar, begin_impar, end_impar);
            break;
        default:
            break;
        }
    }while(op != 0);

    return 0;
}