/*

1) (2,5 pontos) Faça um programa em C que gere 1000 números 
aleatórios, insira-os em uma árvore binária de busca, 
incialmente vazia. Os valores para compor a árvore devem ser 
gerados aleatoriamente utilizando 2 métodos para garantir a 
aleatoriedade. 

(X)Teste 1:
Depois imprima o nível da folha de maior 
profundidade e o nível da folha de menor profundidade. 
Repita o processo 30 vezes. 

(X)Teste 2:
Depois mostre quantas das 30 vezes 
a diferença entre a profundidade máxima e mínima foram de 0, 1, 
2 , 3 e assim por diante. 

()Teste 3:
Também contabilize o tempo gasto 
para inserir todos os elementos na árvore. 

()Teste 4:
E depois em cada 
uma das inserções faça experimento de verificar o tempo de 
busca de elementos, use sempre os mesmo elementos em todos os 
experimentos.

obs. 1: Todas as vezes que for criar uma nova árvore, você 
deve liberar a anterior, para que você tenha memória 
disponível.


gcc -o a q1.c arvore_binaria.c lista_ocorrencia.c
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "arvore_binaria.h"
#include "lista_ocorrencia.h"

int main(){
    
    int i,j,flag;
    int intervalo,valor;
    int folha_maior_prof;
    int folha_menor_prof;
    int diferenca;
    clock_t t_insercao, t_busca;
    float t_insercao_medio = 0,t_busca_medio = 0;
    srand(time(NULL));

    struct noArv *abb,*No;
    No = NULL;
    abb = NULL;
    struct lista *lista_ocorrencias;
    lista_ocorrencias = NULL;

    /*1 - Faça um programa em C que gere 1000 números aleatórios, insira-os em uma árvore binária de busca, incialmente vazia. Os valores para compor a árvore devem ser gerados aleatoriamente utilizando 2 métodos para garantir a aleatoriedade.Depois imprima o nível da folha de maior profundidade e o nível da folha de menor profundidade. Repita o processo 30 vezes */

    printf("Dados das insercoes:\n\n");

    for(j = 0; j < 30; j++){
        t_insercao = clock();//Tempo inicial
        for (i = 0; i < 1000; i++)
        {
            //printf("Entrou\n");
            valor = rand() % (rand() % 1000000);
            //flag = abb_insere(&abb,i);
            flag = abb_insere(&abb,valor);
            if(flag == 0){
                i--;
            }
            
        }
        // A função clock devolve o tempo de CPU decorrido desde o
        // início da execução do seu programa. O tempo é medido em
        // ciclos do relógio interno. Cada  CLOCKS_PER_SEC ciclos
        // correspondem aproximadamente a 1 segundo.
        t_insercao = clock() - t_insercao; //tempo final - tempo inicial

        t_insercao_medio = t_insercao_medio + ((double)t_insercao)/((CLOCKS_PER_SEC/1000));

        t_busca = clock();//Tempo inicial
        No = abb_busca (abb, 100);
        t_busca = clock() - t_busca; //tempo final - tempo inicial
        t_busca_medio = t_busca_medio + ((double)t_busca)/((CLOCKS_PER_SEC/1000));

        printf("%d - Insercao:\n",j);
        folha_maior_prof = altura_No(abb);
        folha_menor_prof = menor_profundidade_No(abb);
        diferenca = folha_maior_prof-folha_menor_prof;
        printf("Folha de MAIOR profundidade = %d\n",folha_maior_prof);
        printf("Folha de MENOR profundidade = %d\n",folha_menor_prof);
        printf("Diferenca = %d\n",diferenca);
        printf("Tempo de INSERCAO = %lf\n", ((double)t_insercao)/((CLOCKS_PER_SEC/1000)));
        printf("Tempo de BUSCA (buscar por id==100) = %lf\n", ((double)t_busca)/((CLOCKS_PER_SEC/1000)));        
        printf("\n\n");

        lista_ocorrencias = list_ocorrencias(lista_ocorrencias, diferenca, 0);

        abb = avr_libera(abb);
      }

    printf("Tempos medios:\n\n");
    printf("Tempo medio de INSERCAO = %lf\n",(t_insercao_medio/30));
    printf("Tempo medio de BUSCA = %lf\n\n\n",(t_busca_medio/30));


    /*2 - Depois mostre quantas das 30 vezes a diferença entre a profundidade máxima e mínima foram de 0, 1, 2 , 3 e assim por diante*/
    printf("Mostrando a lista de ocorrencias:\n\n");
    list_imprime(lista_ocorrencias);


    return 0;
}