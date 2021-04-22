#include <stdio.h>
#include <stdlib.h>

struct Curso{
    int id_curso;
    char nome[100];
    int periodos;
    int carga_horaria_total;
    char turno[10];
};

struct Disciplina{
    int id_disciplina;
    int id_curso;
    char nome[100];
    int periodo;
    int carga_horaria;
};

int partition(struct Curso *c, int begin, int end){
    int left, right;
    struct Curso key, aux;

    left = begin; // esquerda recebe o inicio do vetor
    right = end; // direita recebe o final do vetor
    key = c[begin]; // chave começa da posição inicial
    while (left < right) // condição de parada
    {
        while (c[left].id_curso <= key.id_curso)
        {
            left++; // caso o valor do vetor na posição esquerda for menor ou igual a chave, a esqueda é iterada
        }
        while (c[right].id_curso > key.id_curso)
        {
            right--; // caso o valor do vetor na posição direita for maior que a chavea direita e decrementada
        }
        
        if(left < right){ // caso esquerda seja menor que a direita, é feita as trocas no vetor
            aux = c[left];
            c[left] = c[right];
            c[right] = aux;
        }
        
    }
    c[begin] = c[right]; // a posição do vetor inicial recebe o valor do vetor na posição direita               
    c[right] = key;///e o vetor da direita agora é a chave

    return right;
    
}

//de forma geral o algoritmo quicksort particiona o vetor em duas partes de acordo com uma chave(um ponto de referencia)
// valores menores que a chave sao colocados à esquerda e os maiores à direita

//recebe um vetor e as posições de inicio e fim
int quicksort(struct Curso *c, int begin, int end){
    int key;
    if(end > begin){
        key = partition(c,begin,end); // separa o vetor em duas partições (esquerda e direita)
        quicksort(c,begin,key-1); // chama a função para ordenar a partição esquerda
        quicksort(c,key+1, end); // chama a função para ordenar a partição direita
    }
}


int main(){

}