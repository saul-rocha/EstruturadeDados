#include <stdio.h>
#include <stdlib.h>
#define TAM 5

// a função ordena por inserção um vetor
//recebe o vetor, dois contadores(i,j), uma auxiliar e o tamanho do vetor
/*
valores iniciais
    i = 1
    j = i-1
    aux = v[1]
*/
void insertionsort(int *v,int i, int j,int aux, int tam){
    if(i < tam ){//condição de parada
        if((j >= 0) && (v[j] > aux)){// condição para que compare todos os valores anteriores a posição i
            v[j+1] = v[j]; // caso seja cumprido os requisitos é efetuada a troca de valores no vetor
            v[j] = aux;
            // chama recursivamente sem pendencia a função diminuindo o valor de j, percorrendo o vetor para trás
            // até que o valor referenciado na posição j seja o maior ou chegue na primeira posição do vetor
            insertionsort(v, i, j-1,aux,tam); 
        }
        /* quando forem feitas as devidas trocas,
            i é incrementado e j será o valor anterior ao de i. E entao a função é chamada recursivamente sem pendencia
            alterando os valores de i e j como descrito anteriormente e o aux será o vetor referenciado pela posição i

            OBS:. o processo se repete até que percorra todo o vetor
        */
        i += 1;
        insertionsort(v,i,i-1,v[i],tam);
    }
}



//recebe 3 vetores, dois inteiros (i e j) como contadores,
// dois inteiros representando o tamanho dos vetores 1 e 2
// e um inteiro por referencia para representar o tamanho do vetor resultante(vetor 3)
void uniao(int *v1, int *v2, int *v3,int i,int j,int q1, int q2, int *tam){
    if (i < q1 || j < q2){ //condição de parada

        if (v1[i] > v2[j]) //caso v2 seja menor, pega o valor  e adiciona no v3
        {
            v3[*tam] = v2[j];
            *tam = *tam + 1; // tamanho do 3º vetor é incrementado
            
            uniao(v1,v2,v3,i,j+1,q1,q2,tam);// chama recursivamente sem pendencia a função incrementando j

        }else if(v1[i] < v2[j])//caso v1 seja menor, pega o valor  e adiciona no v3
                {
                    v3[*tam] = v1[i];
                    *tam = *tam + 1;
                    uniao(v1,v2,v3,i+1,j,q1,q2,tam);// chama recursivamente sem pendencia a função incrementando j
                }else // caso os valores sejam iguais
                    { 
                        uniao(v1,v2,v3,i+1,j+1,q1,q2,tam); // chama recursivamente sem pendencia a função incrementando j e i
                    }
        
    }
}

//imprime os dados de um vetor
//recebe um vetor e o tamanho
void imprime(int *v,int q3){
    for(int i=0;i<q3;i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}


int main(){
    int v1[TAM], v2[TAM], v3[TAM+TAM];
    int tam = 0;

    //ler vetores 1 e 2
    printf("Vetor1\n");
    for(int i=0; i < TAM;i++){
        scanf("%d", &v1[i]);
    }
    
    printf("Vetor2\n");

    for(int i=0; i < TAM;i++){
        scanf("%d", &v2[i]);
    }

    insertionsort(v1,1,0,v1[1],TAM);
    insertionsort(v2,1,0,v2[1],TAM);

    //imprime ordenado 
    imprime(v1,TAM);
    imprime(v2,TAM);

    uniao(v1,v2,v3, 0,0,TAM,TAM,&tam); // une ordenando os dois vetores

    imprime(v3,tam);

    return(0);
}