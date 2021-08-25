#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5
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
    key = d[begin]; // chave começa da posição inicial
    while (left < right) // condição de parada
    {
        while (d[left].id_disciplina < key.id_disciplina)
        {
            left++; // caso o valor do vetor na posição esquerda for menor ou igual a chave, a esqueda é iterada
        }
        while (d[right].id_disciplina > key.id_disciplina)
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


//verifica se um curso existe
int existe_idcurso(struct Curso c[], int i, int id, int tam){
    int res = 0;
    if (i < tam){// condição de parada
        if ((c[i].id_curso == id)){
            res = 1;
        }else{
            i++;
            res = existe_idcurso(c,i,id,tam); // chama recursivamente sem pendencia
        }
    }
    return res; // retorna 1 se encontrar e 0 caso contrario
}

// verifica se uma disciplina existe
int existe_disciplina(struct Disciplina d[], int i, int id, int tam){
    int res = 0;
    if (i < tam){// condição de parada
        if ((d[i].id_disciplina == id)){
            res = 1;
        }else{
            i++;
            res = existe_disciplina(d,i,id,tam); // chama recursivamente sem pendencia
        }
    }
    return res; // retorna 1 se encontrar e 0 caso contrario
}
//verifica se existe um id e um turno existe na mesma posição do vetor de cursos
int existe_turno_idcurso(struct Curso c[], int i, int id, char turno[], int tam){
    int res = 0;
    if (i < tam){// condição de parada
        if ((c[i].id_curso == id) && (strcmp(c[i].turno, turno) == 0)){// se id e turno estiverem no vetor, ele ja existe
            i++;
            res = existe_turno_idcurso(c, i, id, turno, tam) + 1;
        }else{
            i++;
            res = existe_turno_idcurso(c, i, id, turno, tam) + 0; // chama recursivamente sem pendencia
        }
    }
    return res; // retorna 1 se encontrar e 0 caso contrario
}
// ler um curso

void ler_curso(struct Curso c[],int i, int tam){
        int turno, verif;

        do // 
        {
            printf("Codigo do Curso: ");
            scanf("%d", &c[i].id_curso);
            printf("Nome do Curso: ");
            scanf("%s", c[i].nome);
            printf("Quantidade de Periodos: ");
            scanf("%d", &c[i].periodos);
            printf("Carga Horaria Total: ");
            scanf("%d", &c[i].carga_horaria_total);

            
            do{// de acordo com a escolha, copia para o vetor de curso o nome do turno
                printf("1- manha\n2- tarde\n3- noite\n4- integral\n");
                scanf("%d", &turno);
                if(turno < 1 && turno > 4){
                    printf("Digite uma escolha valida!\n");
                }else{
                    switch (turno)
                    {
                    case 1:
                        strcpy(c[i].turno,"manha");
                        break;
                    case 2:
                        strcpy(c[i].turno,"tarde");
                        break;
                    case 3:
                        strcpy(c[i].turno,"noite");
                        break;
                    case 4:
                        strcpy(c[i].turno,"integral");
                        break;
                    default:
                        break;
                    }
                }
            }while(turno < 1 && turno > 4);

            verif = existe_turno_idcurso(c, 0, c[i].id_curso, c[i].turno, tam);
        } while (verif != 1);
        
}

int existe_periodo(struct Curso c[], int periodo,int i, int tam){
    int res = 0;
    if(i < tam){
        if(c[i].periodos >= periodo){
            res = 1;
        }else{
            i++;
            existe_periodo(c,periodo,i,tam);
        }
    }
    return res;
}
// ler uma disciplina
void ler_disciplina(struct Disciplina d[], struct Curso c[], int tamd, int tamc){
    int valid, valper;
    
    do{
        printf("Codigo da Disciplina: ");
        scanf("%d", &d[tamd].id_disciplina);
        printf("Codigo do Curso: ");
        scanf("%d", &d[tamd].id_curso);
        printf("Nome da Disciplina: ");
        scanf("%s", d[tamd].nome);
        printf("Periodo: ");
        scanf("%d", &d[tamd].periodo);
        printf("Carga Horaria: ");
        scanf("%d", &d[tamd].carga_horaria);

        valid = existe_idcurso(c, 0, d[tamd].id_curso, tamc); // chama a função para verificar se o curso existe
        if(valid != 1){
            printf("Curso inexistente!\n");
        }
        valper = existe_periodo(c, d[tamd].periodo, 0, tamc);
        if(valper != 1){
            printf("periodo inexistente neste curso!\n");
        }
    }while (valid != 1 || valper != 1);
    
}

//imprime curso
void imprime_curso(struct Curso c[],int i, int cod, int tam){
    if(i < tam){
        if(c[i].id_curso == cod){
            printf("\n----------------\n");
            printf("Codigo: %d\n", c[i].id_curso);
            printf("Curso: %s\n", c[i].nome);
            printf("Periodos: %d\n", c[i].periodos);
            printf("Carga Horaria Total: %d\n", c[i].carga_horaria_total);
            printf("Turno: %s\n", c[i].turno);
            printf("\n----------------\n");
        }
        i++;
        imprime_curso(c, i, cod, tam);
    }
}
//imprime curso por turno
void imprime_curso_turno(struct Curso c[],int i, char turno[], int tam){
    if(i < tam){
        if(strcmp(c[i].turno, turno) == 0){
            printf("\n----------------\n");
            printf("Codigo: %d\n", c[i].id_curso);
            printf("Curso: %s\n", c[i].nome);
            printf("Periodos: %d\n", c[i].periodos);
            printf("Carga Horaria Total: %d\n", c[i].carga_horaria_total);
            printf("Turno: %s\n", c[i].turno);
            printf("\n----------------\n");
        }
        i++;
        imprime_curso_turno(c, i,turno, tam);
    }
}

//imprime disciplina
void imprime_disciplina(struct Disciplina d[], int i, int cod, int tam){
    if(i < tam){
        if(d[i].id_disciplina == cod){
            printf("\n----------------\n");
            printf("Codigo: %d\n", d[i].id_disciplina);
            printf("Codigo do Curso: %d\n", d[i].id_curso);
            printf("Nome: %s\n", d[i].nome);
            printf("Periodo: %d\n", d[i].periodo);
            printf("Carga Horaria: %d\n", d[i].carga_horaria);
            printf("\n----------------\n");
        }
        i++;
        imprime_disciplina(d, i, cod, tam);
    }

}
//imprime disciplinas de um curso
void imprime_disciplinas_curso(struct Disciplina d[], int i, int cod, int tam){
    if(i < tam){
        if(d[i].id_curso == cod){
            printf("\n----------------\n");
            printf("Codigo: %d\n", d[i].id_disciplina);
            printf("Codigo do Curso: %d\n", d[i].id_curso);
            printf("Nome: %s\n", d[i].nome);
            printf("Periodo: %d\n", d[i].periodo);
            printf("Carga Horaria: %d\n", d[i].carga_horaria);
            printf("\n----------------\n");
        }
        i++;
        imprime_disciplinas_curso(d, i, cod, tam);
    }
}

void disciplinas_periodo(struct Disciplina d[], int id, int periodo, int i,int tam){
    if(i < tam){
        if((d[i].id_curso == id) && (periodo == d[i].periodo)){
            imprime_disciplina(d,0,d[i].id_disciplina, tam);
        }
        i++;
        disciplinas_periodo(d, id, periodo, i, tam);
    }
}


void remove_disciplina(struct Disciplina d[], int cod, int i, int *tam){
    int j;
    if(i <= (*tam)){
        if(d[i].id_disciplina == cod){
            for(j = i; j < (*tam);j++){
                d[j] = d[j+1];
            }
            *tam = *tam - 1;
        }else{
            i++;
            remove_disciplina(d,cod,i,tam);
        }
    }
}


void remove_curso(struct Curso c[], struct Disciplina d[], int cod, int i, int *tamc, int tamd){
    int a, cont=0, j;
    if(i < *tamc){
        for(a=0; a < tamd;a++){
            if(d[a].id_curso == cod){
                cont++;
            }
        }
        if(cont == 0){
            for(j = i; j < (*tamc);j++){
                c[j] = c[j+1];
            }
            *tamc = *tamc - 1;
        }else{
            i++;
            remove_curso(c,d,cod,i,tamc,tamd);
        }
        
    }
}

// menu de opções
int menu(){
    int opcao;

    printf("1- Ler Curso\n2- Cadastra Disciplina\n3- Mostrar Curso\n4- Mostrar Disciplina\n5- Cursos de um Turno\n6- Mostrar todas as disciplinas de um Curso\n7- Mostrar disciplinas de um periodo\n8- Remover uma disciplina\n9 - Remover um curso\n0- Sair\n");

    printf("Digite um opcao: ");
    scanf("%d",&opcao);

    return (opcao);
}

int main(){
    int tamc=0, tamd=0, i=0, esc, cod, verifica, verifica1, turno,periodo;
    char aux[10];
    struct Curso cursos[TAM];
    struct Disciplina disciplinas[TAM];

    do{
        esc = menu();

        switch (esc)
        {
            case 1:
                if(tamc < TAM){// se o vetor nao estiver cheio
                    ler_curso(cursos, tamc, tamc+1);
                    //ordena cursos
                    quicksort_curso(cursos,0,tamc);
                    printf("ordenado\n");
                    tamc++;
                }else{
                    printf("Vetor cheio!\n");
                }
                break;
            
            case 2:
                if(tamd < TAM){
                    ler_disciplina(disciplinas, cursos, tamd, tamc+1);
                    //ordena disciplinas
                    quicksort_disc(disciplinas,0,tamd);
                    printf("ordenado\n");
                    tamd++;
                }else{
                    printf("Vetor cheio!\n");
                }
                break;
            case 3:
                printf("Codigo do Curso: ");
                scanf("%d", &cod);

                verifica = existe_idcurso(cursos, 0, cod, tamc+1);
                if(verifica == 0){
                    printf("Código não existe!\n");
                }else{
                    imprime_curso(cursos, 0, cod, tamc+1); 
                }
                break;

            case 4:
                printf("Codigo da Disciplina: ");
                scanf("%d", &cod);

                verifica = existe_disciplina(disciplinas, 0, cod, tamd);
                if(verifica == 0){
                    printf("Código não existe!\n");
                }else{
                    imprime_disciplina(disciplinas, 0, cod, tamd+1);
                }
                break;

            case 5:
                do{
                    printf("1- manha\n2- tarde\n3- noite\n4- integral\nTurno dos Cursos: ");
                    scanf("%d", &turno);
                    if(turno < 1 && turno > 4){
                        printf("Digite uma escolha valida!\n");
                    }else{
                        switch (turno)
                        {
                            case 1:
                                strcpy(aux,"manha");
                                break;
                            case 2:
                                strcpy(aux,"tarde");
                                break;
                            case 3:
                                strcpy(aux,"noite");
                                break;
                            case 4:
                                strcpy(aux,"integral");
                                break;
                            default:
                                break;
                        }
                    imprime_curso_turno(cursos, 0, aux, tamc+1);
                
                    }
                }while(turno < 1 && turno > 4);
                break;
            case 6:
                printf("Codigo do Curso: ");
                scanf("%d", &cod);

                verifica = existe_idcurso(cursos, 0, cod, tamc+1);
                if(verifica == 0){
                    printf("Curso não existe!\n");
                }else{
                    imprime_disciplinas_curso(disciplinas, 0, cod, tamc+1); 
                }
                
                break;
            
            case 7:
                printf("Codigo do Curso: ");
                scanf("%d", &cod);
                printf("periodo: ");
                scanf("%d", &periodo);
                verifica =  existe_idcurso(cursos, 0, cod, tamc+1);
                if(verifica == 0){
                    printf("Curso não existe!\n");
                }
                verifica1 = existe_periodo(cursos, periodo, 0, tamc);
                if(verifica1 == 0){
                    printf("Curso não existe!\n");
                }
                if(verifica != 0 && verifica1 != 0){
                    disciplinas_periodo(disciplinas, cod, periodo, 0, tamd+1);
                }
                break;
            
            case 8:
                printf("Codigo da Disciplina: ");
                scanf("%d", &cod);
                remove_disciplina(disciplinas,cod,i,&tamc);
                printf("removido!\n");
                break;
            case 9:
                printf("Codigo do Curso: ");
                scanf("%d", &cod);
                remove_curso(cursos, disciplinas, cod, 0, &tamc, tamd);
                break;
            

            default:
                if(esc != 0){
                    printf("valor invalido!\n");
                }
                break;

        }
    }while(esc != 0);

    return (0);
}