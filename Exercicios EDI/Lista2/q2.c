#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//carro
struct carro{
    int placa, manobras;
    struct carro *prox;
};  


//aloca espaço e atribui informações de um carro
struct  carro *aloncaNo(int placa, int manobras){
    struct carro *new;

    new = (struct carro*)malloc(sizeof(struct carro));  

    new->placa = placa;
    new->manobras = manobras;
    new->prox = NULL;
    
    return new; 

}

//add um carro(No) a fila
void entrada(struct carro **I, struct carro **F, struct carro *No){

    if(*I == NULL){
        *I = No;
        *F = No;    
    }else{
        (*F)->prox = No;
        *F = No;
    }
}

// retira um carro da fila, retorno um carro pela função e não um ponteiro pra um carro
struct carro saida(struct carro **I, struct carro **F, int placa, int *cont, int first_placa){
    
    struct carro *aux, *aux2, saiu;

    if(*I != NULL && (*I)->placa == placa){
        aux = *I;//aux recebe o endereço de I
        saiu = **I;//saiu recebe as informações do carro que vai sair
        if((*I)->prox != NULL){
            *I = (*I)->prox;//se o proximo carro existir, I recebe o endereço do proximo carro
        }else{
            *I = *F = NULL;// se nao reseta a fila
        }
        
        //libera a memoria alocada pelo carro que saiu
        free(aux);
    }
    else if (*I != NULL){ 
        aux2 = *I;
        (*cont)++;
        aux = aloncaNo((*I)->placa, (*I)->manobras+1);
        *I = (*I)->prox;
        entrada(I, F, aux);
        free(aux2);
        saiu = saida(I, F, placa, cont, first_placa);
        //deixa pendente a realocação dos carros
        while(first_placa != (*I)->placa){
            aux2 = *I;
            aux = aloncaNo((*I)->placa, (*I)->manobras);
            *I = (*I)->prox;
            entrada(I, F, aux);
            free(aux2);
        }
    }
    return saiu;

}


//imprime fila função temporária para testes
void imprime(struct carro *I){
    if (I != NULL){
        printf("%d ", (*I).placa);
        imprime(I->prox);
    }
    
}
// retorna um char maiusculo
char menu(){
    char op;
    
    printf("E - Entrar carro  |  S - Sair Carro | 0 - Sair\n");
    scanf("%c", &op);
    setbuf(stdin,NULL);

    return toupper(op);
}

int main(){
  
    struct carro *I, *F, *No, saiu;

    int placa, verifica=0, cont=0;
    char op;

    // inicia a fila
    I = NULL;
    F = NULL;

    do{
        
        op = menu();

        switch (op)

        {
        case 'E':
            printf("Placa: ");
            scanf("%d", &placa);
            setbuf(stdin,NULL);
            if(verifica < 10){
                No = aloncaNo(placa,0);
                entrada(&I, &F, No);
                printf("Existe vaga!\nCarro com placa de numero %d entrou na fila!\n", placa);
            }else{
                printf("Nao existe vagas!\n");
            }
    
            verifica++;

            break;

        case 'S':
            printf("Placa: ");
            scanf("%d", &placa);
            setbuf(stdin,NULL);

            saiu = saida(&I, &F, placa, &cont, I->placa);

            printf("%d saiu do estacionamento!\n", saiu.placa);
            printf("Manobras Feitas: %d!\n", saiu.manobras);
            printf("Carros manobrados: %d!\n", cont);
            cont = 0;
            verifica --;
            break;

        case 'I':
            imprime(I);
            printf("\n");
            setbuf(stdin,NULL);     

            break;

        default:
            break;
        }
     

    }while(op != '0');

    return 0;
}