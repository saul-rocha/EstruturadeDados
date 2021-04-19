#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
int partition(struct Curso *c, int begin, int end){
    int left, right;
    struct Curso key, aux;

    left = begin; // esquerda recebe o inicio do vetor
    right = end; // direita recebe o final do vetor
    key = c[begin]; // pivô começa da posição inicial
    while (left < right) // condição de parada
    {
        while (c[left].id_curso <= key.id_curso)
        {
            left++; // caso o valor do vetor na posição esquerda for menor ou igual ao pivô, a esqueda é iterada
        }
        while (c[right].id_curso > key.id_curso)
        {
            right--; // caso o valor do vetor na posiçãodireita for maior que o pivô a direita e decrementada
        }
        // logo, o andamento do vetor ocorre nas duas direções
        if(left < right){ // caso esquerda seja menor que a direita, é feita as trocas no vetor
            aux = c[left];
            c[left] = c[right];
            c[right] = aux;
        }
        
    }
    c[begin] = c[right]; // o vetor inicial recebe o valor do veotr na posição direita               
    c[right] = key;///e o vetor da direita agora é o pivô

    return right;
    
}

//de forma geral o algoritmo quicksort particiona o vetor em duas partes de acordo com o pivô(um ponto de partida)
// valores menores que o pivô sao alocados à esquerda e os maiores à direita

//recebe um vetor e as posições de inicio e fim
int quicksort(struct Curso *c, int begin, int end){
    int key;
    if(end > begin){
        key = partition(c,begin,end); // separa o vetor em duas partições (esquerda e direita)
        quicksort(c,begin,key-1); // chama a função para a partição esquerda
        quicksort(c,key+1, end); // chama a função para a partição direita
    }
}


void ler_curso(struct Curso *c,int i, int tam){
    if (i < tam){
        printf("Codigo do Curso: ");
        scanf("%d", &c[i].id_curso);
        printf("Nome do Curso: ");
        scanf("%s", c[i].nome);
        printf("Quantidade de Periodos: ");
        scanf("%d", &c[i].periodos);

        ler_curso(c,i+1,tam);
    }
}

int existe_curso(struct Curso *c, int i, int id, int tam){
    if (i < tam){
        if (c[i].id_curso == id){
            return 1;
        }
        existe_curso(c,i+1,id,tam);
    }
    return 0;
}

char ler_disciplina(struct Disciplina *d, struct Curso *c, int i, int tamd, int tamc){
    int valid = 0;
    if (i < tamd){
        printf("Codigo da Disciplina: ");
        scanf("%d", &d[i].id_disciplina);

        while (valid == 0)
        {
            printf("Codigo do Curso: ");
            scanf("%d", &d[i].id_curso);
            valid = existe_curso(c,0,d[i].id_curso,tamc);
            if(valid == 0){
                printf("Digite um código de curso válido!\n");
            }
        }
        
        
        printf("Nome da Disciplina: ");
        scanf("%s", d[i].nome);
        printf("Periodo: ");
        scanf("%d", &d[i].periodo);
        printf("Carga Horaria: ");
        scanf("%d", &d[i].carga_horaria);

        ler_disciplina(d,c,i+1,tamd,tamc);
    }
}




int qtd_disciplinas(struct Disciplina *d,int id_curso, int i, int tam){
    int qtd = 0;
    if(i < tam){
        if(d[i].id_curso == id_curso){
            qtd = qtd_disciplinas(d,id_curso,i+1,tam) + 1;
        }
        qtd_disciplinas(d,id_curso,i+1,tam);
    }
    return qtd;
}


int qtd_disc_periodo(struct Disciplina *d, int id_curso, int periodo, int i, int tam){
    
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

int main(){
    int tamc, tamd, qtd_dis, id_c,per_c;
    char nome;
    struct Curso *cursos;
    struct Disciplina *disciplinas;

    printf("quantas cursos deseja cadastrar? ");
    scanf("%d", &tamc);

    printf("quantas disciplinas deseja cadastrar? ");
    scanf("%d", &tamd);

    cursos = (struct Curso *)malloc(tamc * sizeof(struct Curso));
    disciplinas = (struct Disciplina *)malloc(tamd * sizeof(struct Disciplina));

    ler_curso(cursos, 0, tamc);
    ler_disciplina(disciplinas, cursos, 0, tamd, tamc);

    //ordena curso
    quicksort(cursos,0,tamc-1);//ordena apenas vetores acima de 5 nao sei por que

    //imprime
    for(int i=0; i < tamc;i++){
        printf("id_curso: %d\ncurso: %s\nperiodos: %d\n----------------\n", cursos[i].id_curso,cursos[i].nome,cursos[i].periodos);
    }
    //nome do curso com mais periodos
    
    //qtd de disciplinas de um curso
    printf("id do curso: ");
    scanf("%d", &id_c);
    qtd_dis = qtd_disciplinas(disciplinas,id_c,0,tamd);

    printf("quantidade de disciplinas: %d\n", qtd_dis);


    // qtd de disciplinas de um determinado periodo de um curso
    printf("id do curso: ");
    scanf("%d", &id_c);
    printf("periodo: ");
    scanf("%d", &per_c);

    qtd_dis = qtd_disc_periodo(disciplinas, id_c, per_c,0,tamd);
    printf("quantidade de disciplinas no periodo %d: %d\n",per_c, qtd_dis);

    free(cursos);
    free(disciplinas);

    return 0;
}