#include <stdio.h>
#include <stdlib.h>


void altera1(int **p)
{  
    // soma 50 no conteúdo do endereço que p aponta
    **p = **p + 50;
}
void altera2(int **p)
{
    //aloca um espaço de memória para p
    *p = (int *)malloc(sizeof(int));
    // atribui 1000 para o conteúdo do endereço que p aponta
    **p = 1000;
}
int main()
{
    //declaração dos ponteiros
    int *px, *py;
    
    // reserva o endereço para os ponteiros
    px = (int *)malloc(sizeof(int));
    py = (int *)malloc(sizeof(int));

    // conteúdos de px e py são definidos
    *px = 500;
    *py = *px + 200;

    // imprime o conteúdo no end. px, o end de px, o end. que px aponta e o conteúdo de py
    printf("px = %d, End. px = %p, px = %p, py = %d \n",*px,&px,px,*py);
    // o conteúdo de px agora passa a ser o de py
    *px = *py;
    // passa referênciando py e soma 50 ao conteúdo do end. que py aponta
    altera1(&py);
    printf("px = %d, End. px = %p, px = %p, py = %d \n",*px,&px,px,*py);
    getchar();
    printf("py = %d, End. py = %p, py = %p, px = %d \n",*py,&py,py,*px);
    // passa referênciando px e soma 50 ao conteúdo do end. que px aponta
    altera1(&px);
    // o end. que py aponta agora será o end. que px aponta.
    py = px;
    // OBS:. caso seja feita essa alteração depois, os valores de px e py seriam iguais no último printf
    // referencía px no parâmetro alocando um novo espaço de memória e atribuindo 1000 como seu conteúdo
    altera2(&px);
    printf("py = %d, End. py = %p, py = %p, px = %d \n",*py,&py,py,*px);
    getchar();
    return(0);
}