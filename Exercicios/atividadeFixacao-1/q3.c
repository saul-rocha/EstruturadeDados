#include <stdio.h>
#include <stdlib.h>


int maiusculasVogais(char string1[],  char string2[], int *qtdUpper1, int *qtdUpper2);
int vogais1(char string[], int *qtd);

/* sao necessárias duas strings e tres int, uma para quantidade de vogais e duas para
quantidade de maiusculas

com as variaveis prontas, a função é chamada passando os parametro as duas strings, e 
dois ints por referência, esses valores  que representam a quantidade de maiusculas
serão alterados por parametro. 
E a variavel que representa a quantidade de vogais irá
receber o resultado do return da função.

*/
int main()
{
    char str1 [10], str2 [10];
    int qtdV, qtdM1=0, qtdM2=0;

    scanf("%s %s", str1, str2);

    qtdV = maiusculasVogais(str1,str2,&qtdM1,&qtdM2);

    printf("M1 = %d \nM2 = %d \nVogais Total = %d\n", qtdM1, qtdM2, qtdV);



    return (0);

}

//recebe trẽs parâmetros, duas strings de entrada e dois inteiros referenciados de como entrada e saída
int maiusculasVogais(char string1[],  char string2[], int *qtdUpper1, int *qtdUpper2){

    int qtdVogais=0; // variavel que irá retornar o valor da quantidade de vogais total
    
    // laço de repetição para percorrer toda a string até que
    for (int i = 0; string1[i] != '\0'; i++) // '\0' é a condição para que quando a string enconte um espaço vazio
    {
        // aqui utiliza a tabela ascii para comparar os caracteres (um recurso da liguagem)
        // caso o char na posição i estiver entre A e Z(um intervalo de chars maiúsculos)
        if (string1[i] >= 'A' && string1[i] <= 'Z'){
            *qtdUpper1 += 1; // incrementa o valor do endereço referênciado
        }

    }
    // idem anterior só que para a string2
    for (int i = 0; string2[i] != '\0'; i++)
    {
        if (string2[i] >= 'A' && string2[i] <= 'Z'){
            *qtdUpper2 += 1;
        }
    }


    // qtdVogais += vogais1(string1, &qtdVogais);
    // qtdVogais += vogais1(string2, &qtdVogais);
    // return qtdVogais;

    // aqui utiliza a função do exercício anterior para contar as vogais das duas strings
    // ela é chamada duas vezes e seus parametros sao uma string e um int passado por referencia.
    // no return pode-se fazer as somas assim como mostra abaixo, na qual a mesma variavel declarada no inicio
    // dessa função recebe a soma das vogais da primeira string + as da segunda
    // o pode ser da forma que está nas linhas 49 a 51

    return qtdVogais += vogais1(string1, &qtdVogais) + vogais1(string2, &qtdVogais);
}

int vogais1(char string[], int *qtd)
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