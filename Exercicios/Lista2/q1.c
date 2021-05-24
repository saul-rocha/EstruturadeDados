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

//retira um carro
int saida(struct Carro c[10], int placa, int *manob, int primeiro){
    int aux, aux2, cont=0, i;
    if(c->inicio <= c->fim){
        //quando encontrar a placa diminui a fila movimentando todos os carros em uma posição
        if(c->placa[c->inicio] == placa){
            *manob = c->manobras[c->inicio];
            //realoca os carros
            for(i=0; i < c->fim;i++){
                c->placa[i] = c->placa[i+1];
                c->manobras[i] = c->manobras[i+1];
            }
            primeiro = c->placa[c->inicio];
            //diminui o fim da fila em 1 posição
            c->fim--;
            i=0;
            
        }else{
            //incrementa a quantidade de manobras e guarda o carro do inicio da fila e qtd de manobras que ele ja fez
            c->manobras[c->inicio]++;
            aux = c->placa[c->inicio];
            aux2 = c->manobras[c->inicio];
            for(int i=0; i < c->fim;i++){
                //anda a fila uma posição
                c->manobras[i] = c->manobras[i+1];
                c->placa[i] = c->placa[i+1];
            }
            //coloca no final da fila o carro guardado
            c->manobras[c->fim] = aux2;
            c->placa[c->fim] = aux;
            cont = saida(c, placa, manob, primeiro) + 1;// chama recursivamente e soma pendentemente uma manobra feita pelo carro
        }
        // coloca a fila como era antes, assim que o carro é retirado
        while (c->placa[c->inicio] != primeiro)
            {
                aux = c->placa[c->inicio];
                aux2 = c->manobras[c->inicio];
                for(i=0; i < c->fim;i++){
                    c->placa[i] = c->placa[i+1];
                    c->manobras[i] = c->manobras[i+1];
                }
                c->placa[c->fim] = aux;
                c->manobras[c->fim] = aux2;
            }

    }else{
        // se inicio for maior ou igual ao fim reinicia a fila
        c->inicio = c->fim = -1;
    }

    return cont;
}

void imprime_fila(struct Carro *c){
    struct Carro aux;

    for (int i=0; i <= c->fim;i++){
        printf("Placa: %d\n", c->placa[i]);
        printf("manobras feitas: %d\n", c->manobras[i]);  
    }
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
    
    struct  Carro carros;

    int placa, continua, verifica, qtd_manobras, carros_manobrados;
    char op;

    // inicia a fila
    carros.inicio = -1;
    carros.fim = -1;

    //inicia a contagem de manobras como sendo 0
    for(int i=0; i < 10;i++){
        carros.manobras[i] = 0;
    }

    do{
        //está duplicando o menu :(
        op = menu();

        switch (op)

        {
        case 'E':
            printf("Placa do carro: ");
            scanf("%d", &placa);
            //limpa o buffer do teclado
            setbuf(stdin,NULL);
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
            setbuf(stdin,NULL);

            carros_manobrados = saida(&carros, placa, &qtd_manobras, carros.placa[0]);

            printf("%d saiu do estacionamento!\n", placa);
            printf("Manobras Feitas: %d!\n", qtd_manobras);
            printf("Carros manobrados: %d!\n", carros_manobrados);

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