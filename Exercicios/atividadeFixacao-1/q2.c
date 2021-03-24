#include <stdio.h>
#include <stdlib.h>

void vogais1(char string[], int *qtd);
int vogais2(char string[]);

int main()
{
    int n = 0;
    char str[10];
    int x;

    scanf("%s", str);
    vogais1(str, &n);
    printf("%d vogais\n", n);
    x = vogais2(str);
    printf("%d vogais\n", x);
    return (0);

}


// retorna por parametro a quantidade de vogais que uma string possui
// sendo que o parametro que representa a quantidade de vogais é passado por referencia
void vogais1(char string[], int *qtd)
{
    for(int i=0; string[i] != '\0'; i++)
    {
        // verifica se o caractere é vogal e se sim, incrementa o valor
        // que está no endereço referenciado por qtd
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