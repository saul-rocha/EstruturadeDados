#include <stdio.h>
#include <stdlib.h>

#define TAM 3

//QuickSort
// separa o vetor em duas partições
int partition(int vet[], int begin, int end){
    int left, right, key, aux;

    left = begin; // esquerda recebe o inicio do vetor
    right = end; // direita recebe o final do vetor
    key = vet[begin]; // pivô começa da posição inicial
    while (left < right) // condição de parada
    {
        while (vet[left]<= key)
        {
            left++; // caso o valor do vetor na posição esquerda for menor ou igual ao pivô, a esqueda é iterada
        }
        while (vet[right] > key)
        {
            right--; // caso o valor do vetor na posiçãodireita for maior que o pivô a direita e decrementada
        }
        // logo, o andamento do vetor ocorre nas duas direções
        if(left < right){ // caso esquerda seja menor que a direita, é feita as trocas no vetor
            aux = vet[left];
            vet[left] = vet[right];
            vet[right] = vet[aux];
        }
        
    }
    vet[begin] = vet[right]; // o vetor inicial recebe o valor do veotr na posição direita               
    vet[right]= key;///e o vetor da direita agora é o pivô

    return right; // retorna a nova key
    
}
//de forma geral o algoritmo quicksort particiona o vetor em duas partes de acordo com o pivô(um ponto de partida)
// valores menores que o pivô sao alocados à esquerda e os maiores à direita

//recebe um vetor e as posições de inicio e fim

int quicksort(int vet[], int begin, int end){
    int key;
    if(end > begin){
        key = partition(vet,begin,end); // separa o vetor em duas partições (esquerda e direita)
        quicksort(vet,begin,key-1); // chama a função para a partição esquerda
        quicksort(vet,key+1, end); // chama a função para a partição direita
    }
}


//recebe 3 vetores, dois inteiros (i e j) como contadores para percorrer os vetores,
// dois inteiros representando o tamanho dos vetores 1 e 2
// e um inteiro por referencia para representar o tamanho do vetor resultante(vetor 3)
void intersection(int *v1, int *v2, int *v3,int i,int j,int q1, int q2, int *tam){
    if (i < q1 && j < q2){ //condição de parada é se um vetor chegar ao fim antes do outro 

        if (v1[i] > v2[j]) //caso v2 seja menor
        {   
            intersection(v1,v2,v3,i,j+1,q1,q2,tam);// chama recursivamente sem pendencia a função incrementando j
                                                    // que consequentemente irá pegar o proximo valor de de v2

        }else if(v1[i] < v2[j])//caso v1 seja menor
                {
                    intersection(v1,v2,v3,i+1,j,q1,q2,tam);// chama recursivamente sem pendencia a função incrementando i
                                                            //que consequentemente irá pegar o proximo valor de de v1
                }else // caso os valores sejam iguais
                    { 
                        v3[*tam] = v1[i];
                        *tam = *tam + 1;
                        intersection(v1,v2,v3,i+1,j+1,q1,q2,tam); // chama recursivamente sem pendencia a função incrementando j e i

                    }
        
    }
}


int main(){
    int vet1[TAM], vet2[TAM], vet3[TAM];
    int tam3=0;

    //ler os vetores
    printf("Primeiro Vetor\n");
    for(int i=0;i<TAM;i++){
        scanf("%d", &vet1[i]);
        vet3[i]=0;
    }
    printf("\nSegundo Vetor\n");
    for(int j=0;j<TAM;j++){
        scanf("%d", &vet2[j]);
    }

    //ordena
    quicksort(vet1,0,TAM-1);
    quicksort(vet2,0,TAM-1);

    //intersect
    intersection(vet1,vet2,vet3,0,0,TAM,TAM,&tam3);

    //imprime
    for(int x=0; x < tam3;x++){
        printf("%d ", vet3[x]);
    }

    return 0;

}