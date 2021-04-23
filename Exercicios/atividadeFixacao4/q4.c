#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5

struct Curso{
    int id_curso;
    char nome[100];
    int periodos;
};

struct Disciplina{
    int id_disciplina;
    int id_curso;
    char nome[100];
    int periodo;
    int carga_horaria;
};


//QuickSort
// separa o vetor em duas partições
int partition(struct Curso c[], int begin, int end){
    int left, right;
    struct Curso key, aux;

    left = begin; // esquerda recebe o inicio do vetor
    right = end; // direita recebe o final do vetor
    key = c[begin]; // chave começa da posição inicial (esquerda)
    while (left < right) // condição de parada
    {
        while (c[left].id_curso < key.id_curso)
        {
            left++; // caso o valor do vetor na posição esquerda for menor que a chave, a esqueda é iterada
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

    return right;
    
}

//de forma geral o algoritmo quicksort particiona o vetor em duas partes de acordo com uma chave(um ponto de referencia)
// valores menores que a chave sao colocados à esquerda e os maiores à direita

//recebe um vetor e as posições de inicio e fim
void quicksort_curso(struct Curso c[], int begin, int end){
    int key;
    if(end > begin){
        key = partition(c,begin,end); // separa o vetor em duas partições (esquerda e direita)
        quicksort_curso(c,begin,key-1); // chama a função para ordenar a partição esquerda
        quicksort_curso(c,key+1, end); // chama a função para ordenar a partição direita como pendencia da primeira chamada
    }
}

//IDEM ANTERIOR
// separa o vetor em duas partições
int partition_disc(struct Disciplina d[], int begin, int end){
    int left, right;
    struct Disciplina key, aux;

    left = begin; // esquerda recebe o inicio do vetor
    right = end; // direita recebe o final do vetor
    key = d[end]; // chave começa da posição inicial
    while (left < right) // condição de parada
    {
        while (d[left].id_disciplina < key.id_curso)
        {
            left++; // caso o valor do vetor na posição esquerda for menor ou igual a chave, a esqueda é iterada
        }
        while (d[right].id_curso > key.id_curso)
        {
            right--; // caso o valor do vetor na posição direita for maior que a chavea direita e decrementada
        }
        
        if(left < right){ // caso esquerda seja menor que a direita, é feita as trocas no vetor
            aux = d[left];
            d[left] = d[right];
            d[right] = aux;
        }
        
    }

    return right;
    
}

//de forma geral o algoritmo quicksort particiona o vetor em duas partes de acordo com uma chave(um ponto de referencia)
// valores menores que a chave sao colocados à esquerda e os maiores à direita

//recebe um vetor e as posições de inicio e fim
void quicksort_disc(struct Disciplina d[], int begin, int end){
    int key;
    if(end > begin){
        key = partition_disc(d,begin,end); // separa o vetor em duas partições (esquerda e direita)
        quicksort_disc(d,begin,key-1); // chama a função para ordenar a partição esquerda
        quicksort_disc(d,key+1, end); // chama a função para ordenar a partição direita
    }
}


// ler um curso
void ler_curso(struct Curso c[],int i){

        printf("Codigo do Curso: ");
        scanf("%d", &c[i].id_curso);
        printf("Nome do Curso: ");
        scanf("%s", c[i].nome);
        printf("Quantidade de Periodos: ");
        scanf("%d", &c[i].periodos);

}

//verifica se um curso existe, recebe 
int existe_curso(struct Curso c[], int i, int id, int tam){
    int res =0;
    if (i < tam){// condição de parada
        if (c[i].id_curso == id){
            res = 1;
        }else{
            res = existe_curso(c,i+1,id,tam); // chama recursivamente sem pendencia
        }
    }
    return res; // retorna 1 se encontrar e 0 caso contrario
}


// ler uma disciplina
void ler_disciplina(struct Disciplina d[], struct Curso c[], int tamd, int tamc){
    int valid = 0;
    
    printf("Codigo da Disciplina: ");
    scanf("%d", &d[tamd].id_disciplina);

    while (valid == 0)
    {
        printf("Codigo do Curso: ");
        scanf("%d", &d[tamd].id_curso);
        valid = existe_curso(c,0,d[tamd].id_curso,tamc); // chama a função para verificar se o curso existe
        if(valid == 0){
            printf("Digite um código de curso válido!\n");
        }
    }
    
    
    printf("Nome da Disciplina: ");
    scanf("%s", d[tamd].nome);
    printf("Periodo: ");
    scanf("%d", &d[tamd].periodo);
    printf("Carga Horaria: ");
    scanf("%d", &d[tamd].carga_horaria);

    
}

// recebe um vetor de cursos como parametro, uma string que izniciará na main como a primeira posição do vetoro de alunos.nome
// o maior periodo que recebe a primeira posiçãio do vetor na main,
// e o indice i para percorrer o vetor e o tamanho do vetor de curso
void more_periods(struct Curso c[], char maiornome[], int *maiorperiodo, int i, int tam){
    
    if (i < tam){ // condição de parada
    more_periods(c,maiornome,maiorperiodo,i+1,tam);// chama a recursão até cheagar ao final do vetor
        if (*maiorperiodo < c[i].periodos){// resolve a pendecia após percorrer o vetor
            strcpy(maiornome,c[i].nome); // caso o curso na posição i tenha mais periodos que a anterior
            *maiorperiodo = c[i].periodos;  // o conteúdo do maior periodo é alterado recebendo o maior
        }
    }    
}

//recebe um vetor de disciplinas, o id de um curso, i para percorrer o curso e o tamanho do vetor 
int qtd_disciplinas(struct Disciplina d[],int id_curso, int i, int tam){
    int qtd = 0; // retornará a quantidade de disciplinas
    if(i < tam){
        if(d[i].id_curso == id_curso){ // virifica o id do curso
            qtd = qtd_disciplinas(d,id_curso,i+1,tam) + 1; // se o id do curso da discplina for igual ao id passado
            // qtd é iterado pendentemente
        }
        qtd_disciplinas(d,id_curso,i+1,tam);// caso contraio, apenas passa para o proximo
    }
    return qtd; // retorna a quantidade total
}

// idem anterior, tendo agora o periodo adiconado como parametro e tambem entra para verificação
int qtd_disc_periodo(struct Disciplina d[], int id_curso, int periodo, int i, int tam){
    
    int qtd_d = 0;
    if(i < tam){
        if((d[i].id_curso == id_curso) && (d[i].periodo == periodo)){
            qtd_d = qtd_disc_periodo(d, id_curso, periodo, i+1,tam) + 1;
        }else{
            qtd_d = qtd_disc_periodo(d, id_curso, periodo, i+1,tam)+0;
        }
    }
    return qtd_d;
}

// menu de opções
int menu(){
    int opcao;

    printf("1- Ler Curso\n2- Ler disciplina\n3- Ordenar Cursos\n4- Ordenar Discuplinas\n5- Curso Com Mais Periodos\n6- Imprimir Cursos\n7- Quantidade de Disciplinas Em Um Curso\n8- Quantidade de Disciplinas Em Um Periodo Do Curso\n0- Sair\n");

    printf("Digite um opcao: ");
    scanf("%d",&opcao);

    return (opcao);
}

int main(){
    int tamc=0, tamd=0, qtd_dis, id_c,per_c, esc, maiorperiodo, i=0;
    char maiornome[100];
    struct Curso cursos[TAM];
    struct Disciplina disciplinas[TAM];

    do{
        esc = menu();

        switch (esc)
        {
            case 1:
                if(tamc < TAM){// se o vetor nao estiver cheio
                    ler_curso(cursos, tamc);
                    tamc++;
                }else{
                    printf("Vetor cheio!\n");
                }
                break;
            
            case 2:
                if(tamd < TAM){
                    ler_disciplina(disciplinas, cursos, tamd, tamc+1);
                    tamd++;
                }else{
                    printf("Vetor cheio!\n");
                }
                break;

            case 3:
                //ordena curso
                quicksort_curso(cursos,0,tamc-1);
                break;
                
            case 4:
                //ordena disciplina
                quicksort_disc(disciplinas,0,tamd-1);
                break;

            case 5:
                //nome do curso com mais periodos
                strcpy(maiornome, cursos[0].nome);
                maiorperiodo = cursos[0].periodos;
                
                more_periods(cursos,maiornome,&maiorperiodo,0,tamc);
                printf("mais periodos: %s\n", maiornome);

                break;
            case 6:
                //imprime curso 
                for(int i=0; i < tamc;i++){
                    printf("id_curso: %d\ncurso: %s\nperiodos: %d\n----------------\n", cursos[i].id_curso,cursos[i].nome,cursos[i].periodos);
                }
                break;
            
            case 7: 
                //qtd de disciplinas de um curso
                printf("id do curso: ");
                scanf("%d", &id_c);
                qtd_dis = qtd_disciplinas(disciplinas,id_c,0,tamd+1);

                printf("quantidade de disciplinas: %d\n", qtd_dis);

                break;

            case 8:
                // qtd de disciplinas de um determinado periodo de um curso
                printf("id do curso: ");
                scanf("%d", &id_c);
                printf("periodo: ");
                scanf("%d", &per_c);

                qtd_dis = qtd_disc_periodo(disciplinas, id_c, per_c,0,tamd+1);
                printf("quantidade de disciplinas no periodo %d: %d\n",per_c, qtd_dis);

                break;

            default:
                printf("valor invalido!\n");
                break;

        }
    }while(esc != 0);

    return (0);
}