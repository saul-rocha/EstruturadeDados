#include <stdio.h>
#include <stdlib.h>


//recebe dois ponteiros como prametros
void altera1(int *p1, int *p2)
{  
    //o conteudo de p1 recebe o conteudo de p2
    *p1 = *p2;
    // soma 50 no conteúdo de p2 
    *p2 = *p2 + 50;
}

//recebe um ponteiro por referencia e um ponteiro normalmente
void altera2(int **p1,int *p2)
{   
    //o endereço de p1 aponta recebe o endereço que p2 aponta
    *p1 = p2;

    //quando incrementa o conteudo de p2, p1 também é alterado, pois ambos agora apontam para o mesmo endereço de memória

    // o conteudo p2 é incrementado em 300
    *p2 = *p2 + 300;
}

int main()
{
    //declaração dos ponteiros
    int *px, *py;
    
    // aloca os endereços para os ponteiros
    px = (int *)malloc(sizeof(int));
    py = (int *)malloc(sizeof(int));

    // conteúdos de px e py são definidos
    *px = 500;
    *py = *px + 200;
    
    // imprime o conteúdo no end. que px aponta, o end. que px aponta e o conteúdo de py
    printf("px = %d,  End. px = %p py = %d\n",*px,px,*py);
    // chama a função aletra1
    altera1(px,py);
    //imprime as informações depois de serem alteradas na função
    printf("px = %d,  End. px = %p py = %d\n",*px,px,*py);
    getchar();
     // imprime o conteúdo no end. que py aponta, o end. que py aponta e o conteúdo de px
    printf("py = %d, End. py = %p px = %d\n",*py,py,*px);
    // referencía px no parâmetro alocando um novo espaço de memória e atribuindo 1000 como seu conteúdo
    altera2(&py,px);
    //imprime as informações depois de serem alteradas na função
    printf("py = %d, End. py = %p px = %d\n",*py,py,*px);


    return(0);
}