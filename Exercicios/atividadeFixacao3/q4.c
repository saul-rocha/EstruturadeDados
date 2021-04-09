#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Alunos{
    int matricula;
    char nome[100];
    char curso[50];
    int periodo;
};

//ler um vetor de alunos
// recebe um vetor de alunos e o tamanho do mesmo como parametros
void leitura(struct Alunos *aluno, int tam){
    for(int i=0;i<tam;i++){
        printf("\nMatricula: ");
        scanf("%d", &aluno[i].matricula);
        printf("Nome: ");
        scanf("%s", aluno[i].nome);
        printf("Curso: ");
        scanf("%s", aluno[i].curso);
        printf("Periodo: ");
        scanf("%d", &aluno[i].periodo);
    }
}

//imprime um vetor de alunos
// recebe um vetor de alunos e o tamanho do mesmo como parametros
void imprime(struct Alunos *aluno, int tam){
    for(int i=0;i<tam;i++){
        printf("-----------------\n");
        printf("Matricula : %d\n", aluno[i].matricula);
        printf("Nome: %s\n", aluno[i].nome);
        printf("Curso: %s\n", aluno[i].curso);
        printf("Perido: %d\n", aluno[i].periodo);
        printf("-----------------\n");
    }
}


/*ordenação dos alunos pela matricula

recebe um vetor de alunos, dois contadores(i,j), uma auxiliar(vetor de Alunos na posição i) e o tamanho do vetor

valores iniciais
    i = 1
    j = i-1
    aux = v[1]
*/
void insertionsort(struct Alunos *v,int i, int j,struct Alunos aux, int tam){
    if(i < tam ){//condição de parada
        if((j >= 0) && (v[j].matricula > aux.matricula)){// condição para que compare todos os valores anteriores a posição i
            // caso seja cumprido os requisitos é efetuada a troca de valores no vetor
            v[j+1] = v[j]; 
            v[j] = aux;
            // chama recursivamente sem pendencia  a função diminuindo o valor de j, percorrendo o vetor para trás
            // até que o valor referenciado na posição j seja o maior ou chegue na primeira posição do vetor
            insertionsort(v, i, j-1,aux,tam); 
        }
        /* quando forem feitas as devidas trocas,
            i é incrementado e j será o valor anterior ao de i. E entao a função é chamada recursivamente
            alterando os valores de i e j como descrito anteriormente e o aux será o vetor referenciado pela posição i

            OBS:. o processo se repete até que percorra todo o vetor
        */
        i += 1;
        insertionsort(v,i,i-1,v[i],tam);
    }
}



/*
devolve em um vetor os nomes dos alunos que estao no mesmo periodo
 recebe um vetor de Alunos, o periodo de busca, um int como contador( i )
 uma matriz de char,o tamanho do vetor referenciado que é incrementado de
  acordo com a quantidade de alunos em determinado periodo

valores iniciais
    i = 0
*/
void alunosPeriodo(struct Alunos *v,int per,int i ,char nomes[][100],int vtam, int *nomestam){
    if(i < vtam){//condição de parada
        if(v[i].periodo == per){ // se o periodo do aluno for igual ao periodo que procura
            // o nome daquele aluno é copiado para o vetor resultante
            /* para isto, utiliza uma função da biblioteca string.h, strcpy que copia a string do
                segundo parametro para o primeiro
            */
            strcpy(nomes[*nomestam], v[i].nome); 
            *nomestam = *nomestam + 1; // tamanho do vetor resultante é incrementado
            //chama recursivamente sem pendencia a função para procurar o proximo aluno, incrementando  i
            alunosPeriodo(v,per,i+1,nomes,vtam,nomestam);
        }else{
            //caso nao encontre um aluno naquele periodo, procura o proximo
            // chamando recursivamente a função sem pendencia apenas incrementando o valor de i
            alunosPeriodo(v,per,i+1,nomes,vtam,nomestam);
                                                        
        }
    }
}


/*
    devolve a quantidade de alunos em um curso(qtda), um vetor de char com o nome do curso,
    um int contador (i), tamanho do vetor de alunos(vtam) e a quantidade referenciada

    recebe um vetor de alunos, 

    i = 0
*/
void qtdAlunos(struct Alunos *v, char curso[50], int i,int vtam ,int *qtda){
    if(i < vtam){//condição de parada

        //utiliza uma função da biblioteca string.h que compara duas strings e devolve 0 se forem iguais
        // -1 se a string do primeiro parametro for menor e 1 caso contrario
        if((strcmp(v[i].curso,curso) == 0)){ // caso a condição seja verdadeira a quantidade é incrementada
            *qtda = *qtda + 1;
            //chama a função recursivamente sem pendencia, incrementando o i
            qtdAlunos(v,curso,i+1,vtam,qtda);
        }else{
            //caso contrario do if, apenas incrementa o i na recursão 
            qtdAlunos(v,curso,i+1,vtam,qtda);
        }
    }
}

//devolve o indice do vetor e que  um aluno se encontra
//recebe um vetor de alunos como parâmetro, o inicio do vetor que deve iniciar de 0,
//o tamanho do vetor que indica o final do mesmo, a matricula que deseja buscar e o inteiro
//referenciado para se armazenado o indice em que se encontra o aluno com aquela matricula
void buscaMat(struct Alunos *v,int i,int vtam, int mat,int *info){
    
    // j recebe o índice que representa o item do meio do vetor de alunos
    int j = (i + vtam)/2;

    if(i < vtam){//condição de parada
        if(v[i].matricula == mat){ //caso a amtricula seja encontrada
            *info = i; // info recebe o indice em que o aluno se encontra
        }else if(v[i].matricula < mat){            // se a matricula do aluno na posição i for 
                                                // menor do que a que esta sendo procurada
                    buscaMat(v,j,vtam,mat,info);  // significa que o valor deve está a direita
                    //logo a recursão sem pendencia é chamada
                    //passando o inicio do vetor(i) agora sendo j(que é a metade do vetor)

                }else{
                    buscaMat(v,i,j,mat,info);
                    //caso a matricula do aluno na posição i seja maior que a que está sendo buscada
                    // significa que o valor deve está a esquerda do vetor, logo o final do vetor se torna
                    // a metade, passando como parametro de vtam como sendo agora j, na chamada recursiva
                    //sem pendencia.
                }
    }
}

int main(){
    int qtd, tam=0, per,cont=0;//qtd é a qauntidade de alunos, tam é o tamanho do vetor do alunos em um periodo

    // per é o periodo que será buscado 
    //cont é a quantida de alunos em um curso

    struct Alunos *aluno;//cria um ponteiro do tipo Alunos

    char nomes[100][100];
    char curso[50];// 
    int matric, inf = -1;

    //ler quantos alunos deseaja cadastrar
    printf("Quantos alunos deseja cadastrar? ");
    scanf("%d", &qtd);

    //aloca memoria para um vetor do tipo Alunos de tamanho qtd
    aluno = (struct Alunos *)malloc(qtd * sizeof(struct Alunos));
    
    leitura(aluno,qtd);
    //ordena
    insertionsort(aluno,1,0,aluno[1],qtd);
    //imprime todos os alunos
    imprime(aluno,qtd);

    //ler o periodo
    printf("Qual o periodo deseja buscar os alunos: ");
    scanf("%d", &per);
    //busca os alunos do periodo per
    alunosPeriodo(aluno,per,0,nomes,qtd,&tam);

    //imprime os nome dos alunos daquele periodo
    printf("Alunos do %do periodo\n",per);
    for(int i=0;i<tam;i++){
        printf("%s\n", nomes[i]);
    }
    // ler o curso para busca
    printf("Qual o curso deseja buscar: ");
    scanf("%s", curso);

    //busca os alunos de um curso
    qtdAlunos(aluno, curso, 0, qtd , &cont);

    printf("Há %d alunos no curso %s\n", cont, curso);

    //ler a matricula do aluno para busca
    printf("Qual a matricula do aluno deseja buscar: ");
    scanf("%d", &matric);
    //busca matricula
    buscaMat(aluno,0,qtd,matric,&inf);
    //imprime os dados do aluno
    if(inf >= 0){
        printf("\nDADOS DO ALUNO\n");
        printf("Matricula: %d\n", aluno[inf].matricula);
        printf("Nome: %s\n", aluno[inf].nome);
        printf("Curso: %s\n", aluno[inf].curso);
        printf("Periodo: %d\n", aluno[inf].periodo);

    }else{
        printf("\nNenhum aluno encontrado com esta matricula\n");
    }

    return (0);
}