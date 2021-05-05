#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// fila de carros com 10 vagas, quantidades de manobras feitas, inicio e  fim da fila
struct Carro{
    int placa[10], manobras[10], inicio, fim;
};

//coloca um carro na fila
int entrada(struct Carro *c, int placa){
    int res;
    if(c->inicio == -1 && c->fim == -1){
        c->placa[c->inicio+1] = placa;
        c->fim++;
        c->inicio++;
        res = 1;
    }
    // < 9 pois inicia de 0 e a fila tem tamanho maximo 10 e o fim é incrementado antes de adicionar o carro na fila
    else if(c->fim < 9){
        c->fim++;
        c->placa[c->fim] = placa;
        res = 1;
    }else{
        res = 0;
    }

    return res;

}

int saida(struct Carro *c, int placa, int primeiro){
    int aux, cont=0, i;
    if(c->inicio <= c->fim){
        //quando encontrar a placa diminui a fila movimentando todos os carros em uma posição
        if(c->placa[c->inicio] == placa){
            //realoca os carros
            for(i=0; i < c->fim;i++){
                c->placa[i] = c->placa[i+1];
            }
            primeiro = c->placa[c->inicio];
            //diminui o fim da fila em 1 posição
            c->fim--;
            i=0;
            
        }else{
            aux = c->placa[c->inicio];
            for(int i=0; i < c->fim;i++){
                c->placa[i] = c->placa[i+1];
            }
            c->placa[c->fim] = aux;
            cont = saida(c, placa, primeiro) + 1;// chama recursivamente e soma pendentemente uma manobra feita pelo carro
        }
        // coloca a fila como era antes, assimque o carro é retirado
        while (c->placa[c->inicio] != primeiro)
            {
                aux = c->placa[c->inicio];
                for(i=0; i < c->fim;i++){
                    c->placa[i] = c->placa[i+1];
                }
                c->placa[c->fim] = aux;
            }

    }else{
        c->inicio = c->fim = -1;
    }

    return cont;
}

void imprime_fila(struct Carro *c){
    for (int i=0; i <= c->fim;i++){
        printf("%d ", c->placa[i]);
    }
}

char menu(){
    char op;

    printf("E - Entrar carro  ||  S - Sair Carro\n");
    scanf("%c", &op);

    return toupper(op);
}

int main(){
    
    struct  Carro carros;

    int placa, continua, verifica, qtd_manobras;
    char op;

    carros.inicio = -1;
    carros.fim = -1;

    //inicia a contagem de manobras como sendo 0
    for(int i=0; i < 10;i++){
        carros.manobras[i] = 0;
    }

    do{

        op = menu();

        switch (op)

        {
        case 'E':
            printf("Placa do carro: ");
            scanf("%d", &placa);
            verifica = entrada(&carros, placa);
            if(verifica){
                printf("Existe vaga\n%d entrou no escionamento!\n", placa);
            }else{
                printf("Não existe vagas!\n");
            }
            break;

        case 'S':
            printf("Placa do carro: ");
            scanf("%d", &placa);

            qtd_manobras = saida(&carros, placa, carros.placa[0]);

            printf("%d saiu do escionamento!\n", placa);
            printf("Carros manobrados %d vezes!\n", qtd_manobras);

            break;

        case 'I':
            imprime_fila(&carros);
            break;

        default:
            break;
        }
     

    }while(op != '0');

    return 0;
}