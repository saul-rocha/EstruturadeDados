#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PilhaCD{
    int cod, ano;
    char titulo[50], artista[100];

    struct PilhaCD *ant;
};

// aloca espaço de momoria para um cd
struct PilhaCD *alocaNO(){
    
    struct PilhaCD *new;
    new = NULL;

    new = (struct PilhaCD*)malloc(sizeof(struct PilhaCD));

    return new;
};

//////////////////////////////////BASICS//////////////////////////////////////////////////////////

//ler os dados de um CD e devolve por parametro
void ler_cd(int *cod,char titulo[50],char artista[100],int *ano){
    do{
        printf("Codigo: ");
        scanf("%d", cod);
        printf("Titulo: ");
        scanf("%s", titulo);
        printf("Artista: ");
        scanf("%s", artista);
        printf("Ano: ");
        scanf("%d", ano);

        if (*cod < 0 || titulo[0] == '\0' || artista[0] == '\0' || ano < 0){
            printf("CD inválido!\nTente novamente\n");
        }
    }while(*cod < 0 || titulo[0] == '\0' || artista[0] == '\0' || ano < 0);

}

void empilhar_cd(struct PilhaCD **top, struct PilhaCD *No, int cod, char titulo[50], char artista[100], int ano){
    if(No != NULL){
        //atribui as informações para a pilha
        (*No).cod = cod;
        strcpy((*No).titulo,titulo);
        strcpy((*No).artista,artista);
        (*No).ano = ano;

        //ant aponta para o endereço de memoria do top
        (*No).ant = *top;
        //top agora aponta para o endereço de No    
        *top = No;
    }
}

int desempilhar_cd(struct PilhaCD **top){
    int id = -1;
    struct PilhaCD *aux;
    if(*top != NULL){
        
        id = (**top).cod;//guarda o codigo do cd que será desempilhado
        aux = *top; // aux guarda o endereço do top
        *top = (**top).ant;//top    recebe o endereço do cd anterior
        free(aux);//libera o endereço de aux(onde cd que foi desempilhado esta/estava)
    }
    return id;//retorna o codigo do cd desempilhado
}
/////////////////////////////////////////////////////////

//imprime toda a pilha de cds
void imprimir_PilhaCDs(struct PilhaCD *top){
    struct PilhaCD *aux;
    aux = top;
    if(aux != NULL){//quando top for NULL a pilha está vazia
        printf("------------------\n");
        printf("Codigo: %d\n", (*top).cod);
        printf("Titulo: %s\n", (*top).titulo);
        printf("Artista: %s\n", (*top).artista);
        printf("Ano: %d\n", (*aux).ano);
        printf("------------------\n");

        imprimir_PilhaCDs((*aux).ant);//chama recursivamente passando como parametro o endereço do cd anterior(proximo da pilha)
    }
    
}

void montar_pilha_ano(struct PilhaCD **top_estilo, struct PilhaCD **top, struct PilhaCD *No, int ano){
    int id_cd;
    if(*top_estilo != NULL){// se pilha do estilo musical não estiver vazia e No tiver alocado
        if( (**top_estilo).ano == ano){

            No = alocaNO();
            empilhar_cd(top, No, (**top_estilo).cod, (**top_estilo).titulo, (**top_estilo).artista, (**top_estilo).ano);

            id_cd = desempilhar_cd(top_estilo);//desempilha

            printf("CD de Codigo %d Adicionado!\n", id_cd);
            montar_pilha_ano(top_estilo, top, No, ano);// o primeiro parametro é o próprio endereço do top_estilo musical pois um cd foi adicionado
                                                        // e quando dessempilha o cd o top é alterado por referencia
            
        }else{
            montar_pilha_ano(&(**top_estilo).ant, top, No, ano); // chama recursivamente para procurar no restante da pilha do estilo musical
            // o primeiro parametro é o endereço do cd anterior, pois se não for adicionado a pilha resultante, aquele cd não será desempilhado
        }   

    }
}

// menu de opções
int menu(){
    int opcao;

    printf("1- Ler CD e Adicionar Numa Pilha\n2- Imprimir CDs\n3- Criar Pilha Pelo Ano\n0- Sair\n");

    printf("Digite um opcao: ");
    scanf("%d",&opcao);

    return (opcao);
}
// submenu de opções
int submenu(){
    int opcao;

    printf("1- Adicionar a Pilha POP\n2- Adicionar a Pilha ROCK\n3- Adicionar a Pilha SERTANEJO\n4- Adicionar a Pilha FORRO\n5- Adicionar a Pilha AXE\n");

    printf("Digite um opcao: ");
    scanf("%d",&opcao);

    return (opcao);
}
int submenu2(){
    int opcao;

    printf("1- Imprimir a Pilha POP\n2- Imprimir a Pilha ROCK\n3- Imprimir a Pilha SERTANEJO\n4- Imprimir a Pilha FORRO\n5- Imprimir a Pilha AXE\n6- Imprimir a Pilha do Ano\n");

    printf("Digite um opcao: ");
    scanf("%d",&opcao);

    return (opcao);
}

int main(){
    // um top e um No para cada pilha
    struct PilhaCD *top, *No, *top_pop, *No_pop, *top_rock, *No_rock, *top_sertanejo, *No_sertanejo, *top_forro, *No_forro, *top_axe, *No_axe;
    int cod, ano, id_removido, op, op2, anoCD;
    char titulo[50], artista[100];

    top = NULL;
    top_pop = NULL;
    top_rock = NULL;
    top_sertanejo = NULL;
    top_forro = NULL;
    top_axe = NULL;

    do{
        op = menu();
        switch (op)
        {
        case 1:
            
            //escolhe a pilha que deseja adicionar o cd
            op2 = submenu();
            switch (op2)
            {
                case 1:
                    No_pop = alocaNO();//aloca espaço para um cd na pilha pop
                    ler_cd(&cod ,titulo,artista,&ano);// ler os dados de um CD
                    empilhar_cd(&top_pop, No_pop, cod, titulo, artista,ano);//empilha CD na pilha pop

                    break;
                case 2:
                    No_rock = alocaNO();//aloca espaço para um cd na pilha rock
                    ler_cd(&cod ,titulo,artista,&ano);// ler os dados de um CD
                    empilhar_cd(&top_rock, No_rock, cod, titulo, artista,ano);// empilha CD na pilha rock

                    break;
                case 3:
                    No_sertanejo = alocaNO();//aloca espaço para um cd na pilha sertanejo
                    ler_cd(&cod ,titulo,artista,&ano);// ler os dados de um CD
                    empilhar_cd(&top_sertanejo, No_sertanejo, cod, titulo, artista,ano); // empilha ccd na pilha sertanejo

                    break;
                case 4:
                    No_forro = alocaNO();//aloca espaço para um cd na pilha forro
                    ler_cd(&cod ,titulo,artista,&ano);// ler os dados de um CD
                    empilhar_cd(&top_forro, No_forro, cod, titulo, artista,ano); // empilha cD na pilha forro

                    break;
                case 5:
                    No_axe = alocaNO();//aloca espaço para um cd na pilha axe
                    ler_cd(&cod ,titulo,artista,&ano);// ler os dados de um CD  
                    empilhar_cd(&top_axe, No_axe, cod, titulo, artista,ano); //empilha cd na pilha axe
                    
                    break;
                
                default:
                    printf("Nao Adicionado!\n");
                    break;
            }

            break;
        
        case 2:
            op2 = submenu2();
            switch (op2)
                {
                case 1:
                    imprimir_PilhaCDs(top_pop);
                    break;
                case 2:
                    imprimir_PilhaCDs(top_rock);
                    break;
                case 3:
                    imprimir_PilhaCDs(top_sertanejo);
                    break;
                case 4:
                    imprimir_PilhaCDs(top_forro);
                    break;
                case 5:
                    imprimir_PilhaCDs(top_axe);
                    break;
                case 6:
                    imprimir_PilhaCDs(top);
                    break;
                default:
                    printf("Pilha Nao Existe!\n");
                    break;
                }

            break;
        
        case 3:
            printf("Digite o ano da pilha que deseja formar: ");
            scanf("%d", &anoCD);
            montar_pilha_ano(&top_pop, &top, No, anoCD);
            montar_pilha_ano(&top_rock, &top, No, anoCD);
            montar_pilha_ano(&top_sertanejo, &top, No, anoCD);
            montar_pilha_ano(&top_forro, &top, No, anoCD);
            montar_pilha_ano(&top_axe, &top, No, anoCD);
            break;
        
        default:

            break;

        }
       
    }while(op != 0);

    return 0;
}