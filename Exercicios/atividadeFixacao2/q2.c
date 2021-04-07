#include <stdio.h>
#include <stdlib.h>


void altera1(int **p1, int **p2)
{  
    //o conteudo do endereço de p1 recebe o conteudo de p2
    **p1 = **p2;
    // soma 50 no conteúdo do endereço que p2 aponta
    **p2 = **p2 + 50;
}
void altera2(int **p1,int **p2)
{   
    //o endereço que p1 aponta recebe o endereço que p2 aponta, porém quando incrementa o conteudo de p2, p1 também é alterado
    *p1 = *p2;
    //p1 = p2;
    //desta forma acima comentada, o endereço de p1 recebe o de p2, e mesmo incrementadno p2 nao irá incrementar p1
    // porém no print do endereço de p1 não mostra que o valor muda 

    // o conteudo que o endereço de p1 aponta é incrementado em 300
    **p2 = **p2 + 300;
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
    // passa referênciando py e soma 50 ao conteúdo do end. que py aponta
    altera1(&px,&py);
    printf("px = %d, End. px = %p, px = %p, py = %d \n",*px,&px,px,*py);
    getchar();
    printf("py = %d, End. py = %p, py = %p, px = %d \n",*py,&py,py,*px);
    // referencía px no parâmetro alocando um novo espaço de memória e atribuindo 1000 como seu conteúdo
    altera2(&py,&px);
    printf("py = %d, End. py = %p, py = %p, px = %d \n",*py,&py,py,*px);


    return(0);
}