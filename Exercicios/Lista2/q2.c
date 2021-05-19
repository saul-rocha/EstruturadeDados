#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct carros{
    int placa, manobras;

    struct carros *prox;
};

//aloca espaço para um carro
struct carros *aloncaNo(){
    struct carros *new;

    new = NULL;
    new = (struct carros*)malloc(sizeof(struct carros));
    
    
    return new;

}
//aloca espaço para um carro
void ler_carro(struct carros *No){
    int placa;
    printf("Placa do carro: ");
    scanf("%d", &placa);
    No->manobras = 0;
    No->placa = placa;
    
}
//add um carro a fila
int entrada(struct carros **I, struct carros **F, struct carros *No){
    int res;
    if(*I == NULL){
        *I = No;
        *F = No;
        res = 1;
    }
    else if(*I != NULL){
        (*F)->prox = No;
        *F = No;
        res = 1;
    }else{
        res = 0;
    }

    return res;

};


//tira o primeiro carro da fila
int saida(struct carros **I, struct carros *F, int placa, int *qtd_manobra, struct carros *first){
    struct carros *aux;
    int cont=0;

    //quando encontra como sendo o primeiro da fila, retira o mesmo e anda a fila
    if(first->placa == (*I)->placa && first->placa == placa){
        *qtd_manobra = (*I)->manobras;
        //anda a fila
        aux = *I;
        *I = (*I)->prox;

        //libera o espaço de memório do carro que saiu
        free(aux); 

    }else if(*I != NULL){
        (*I)->manobras++;
        aux = *I;
        *I = (*I)->prox;
        F->prox = aux;          
        // o fim agora é o carro que saiu do inicio
        // ou seja, ao mesmo tempo que o inicio avança para o proximo, o proximo do fim será o que saiu do inicio
        cont = saida(I, F->prox, placa, qtd_manobra, first) + 1;// chama recursivamente e soma pendentemente a qtd manobras feitas antes que o carro tenha saído
        // alem de deixar pendente a organização da fila


    }

    return cont;
}

void imprime_fila(struct carros *I){
    if(I != NULL){
        printf("Placa: %d\n", I->placa);

        imprime_fila(I->prox);
    }
    setbuf(stdin,NULL);
}

// retorna um char maiusculo
char menu(){
    char op;
    
    printf("E - Entrar carro  |  S - Sair Carro | I - Imprimir | 0 - Sair\n");
    scanf("%c", &op);
    setbuf(stdin,NULL);

    return toupper(op);
}

int main(){
    
    struct  carros *I, *F, *No;


    int placa, continua, verifica, qtd_manobras, carros_manobrados;
    char op;

    // inicia a fila
    F = I = NULL;


    do{
        //está duplicando o menu :(
        op = menu();

        switch (op)

        {
        case 'E':

            No = aloncaNo();
            ler_carro(No);    
            verifica = entrada(&I, &F, No);
            if(verifica){
                printf("Existe vaga\nCarro entrou na fila\n");
               
            }else{
                printf("Nao existe vagas!\n");
                
            }
            setbuf(stdin,NULL);
            break;

        case 'S':
            printf("Placa do carro: ");
            scanf("%d", &placa);
            setbuf(stdin,NULL);

            carros_manobrados = saida(&I, F, placa, &qtd_manobras, I);

            printf("%d saiu do escionamento!\n", placa);
            printf("Manobras Feitas: %d!\n", qtd_manobras);
            printf("Carros manobrados: %d!\n", carros_manobrados);
            setbuf(stdin,NULL);
            break;

        case 'I':
            imprime_fila(I);
            break;

        default:
            break;
        }
     

    }while(op != '0');

    return 0;
}