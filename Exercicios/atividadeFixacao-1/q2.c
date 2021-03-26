#include <stdio.h>
#include <stdlib.h>

void vogais1(char string[], int *qtd);
int vogais2(char string[]);
int vogais3(char string[], int *qtd);


/* para o funcionamento das funções são necessárias uma variavel do tipo int e uma string
podendo ler do teclado ou se preferir pode ser predefinido

OBS:. esta terceira função foi um teste para tentar juntar as funções. O que deu muito certo :D !!
*/
int main()
{
    int n = 0;
    char str[10];

    scanf("%s", str);
    vogais1(str, &n); // aqui é passado os parâmetros da função sendo a string e o int n por referência
    printf("%d vogais\n", n);

    n = vogais2(str);//  aqui é passada a string como parâmetro, apenas, pois será retornado um valor nesta função,
                    //  que será atribuido a uma cópia d da variavel n.
    printf("%d vogais\n", n);
    return (0);

}


// retorna por parametro a quantidade de vogais que uma string possui
// sendo que recebe uma string de entrada e um int de entrada e saída.
// o parametro que representa a quantidade de vogais é passado por referencia
void vogais1(char string[], int *qtd)
{
    for(int i=0; string[i] != '\0'; i++)
    {
        // verifica se o caractere é vogal e se sim, incrementa o valor
        // que está no endereço referenciado em qtd
        if (string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u')
        {
            *qtd += 1;
        // idem anterior, porem para caracteres maiúsculos
        }else 
        if(string[i] == 'A' || string[i] == 'E' || string[i] == 'I' || string[i] == 'O' || string[i] == 'U' )
        {
            *qtd += 1;
        }
    }
}



//  retorna pela função a quantidade de vogais
// recebe uma string como parametro de entrada e é do tipo int para que posso retornar um resultado
int vogais2(char string[])
{
    int qtd = 0;
    for(int i=0; string[i] != '\0'; i++)
    {
        // verifica se o caractere é vogal e incrementa a variavel local
        // qtd
        if (string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u')
        {
            qtd += 1;
        }else 
        if(string[i] == 'A' || string[i] == 'E' || string[i] == 'I' || string[i] == 'O' || string[i] == 'U' )
        {
            qtd += 1;
        }
    }
    // retorna o valor da variavel qtd
    return qtd;
}


// função que retorna por parametro e pela função (2 em 1) 
int vogais3(char string[], int *qtd)
{
    for(int i=0; string[i] != '\0'; i++)
    {
        // verifica se o caractere é vogal e incrementa a variavel local
        // qtd
        if (string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u')
        {
            *qtd += 1;
        }else 
        if(string[i] == 'A' || string[i] == 'E' || string[i] == 'I' || string[i] == 'O' || string[i] == 'U' )
        {
            *qtd += 1;
        }
    }
    // retorna o valor acumulado em *qtd
    return *qtd;
}