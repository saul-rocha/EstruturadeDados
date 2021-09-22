void misterio1(char b[TAM], float *dec, int i)
{
    if(i < strlen(b))
    {
        if(b[i] == '1')
            *dec = *dec + pow(2,i);
            misterio1(b,dec,++i);
    }
}

/*
Transforma uma string que representa um numero em binário e transforma para decimal

Tem como parâmetros um vetor de caracteres com 0s e 1s, um valor float passado por referência (sendo ele de entrada e saída) e um inteiro i como contador.

Dentro da função há o primeiro IF como condição de parada da recursão, que é quando i for igual ou maior que o tamanho do vetor.

O segundo if é para efetuar a portencia do valor do vetor elevado a i, caso ele seja igual a 1. Se for 0 então chama apenas a recursão e não entra na condição do IF;

e chama a recursão sem pendência alterando apenas o valor de i

Obs!!!
++i é para incrementar o valor antes de ser executada a função novamente.

Ex:.
1º entrada -> b = "101", dec = 0, i = 0, b[i] = 1
2º entrada -> b = "101", dec = 1, i = 1, b[i] = 0
3º entrada -> b = "101", dec = 5, i = 2, b[i] = 1
Fim da recursão dec = 1 + 2^2 -> dec = 5
*/


float misterio2(char b[TAM], float dec, int i)
{
    if(i < strlen(b))
    {   
        dec = misterio2(b,dec,i+1);
        if(b[i] == '1')
        dec = dec + pow(2,i);
    }
    return(dec);
}

/*
Idem anterior, porém o parametro dec não é passado por referencia e é retornado na função.

A recursão é chamada com pendência.

1º entrada -> b = "101", dec = 0, i = 0, b[i] = 1,  pilha de pendencia [i=0]
2º entrada -> b = "101", dec = 0, i = 1, b[i] = 1,  pilha de pendencia [i=0 (dec = dec + 2^0, i=1]
2º entrada -> b = "101", dec = 0, i = 2, b[i] = 1,  pilha de pendencia [i=0, i=1, i=2(dec = dec + 2^2)]

Fim da recursão e resulve as pendencias -> dec = dec + 2^2 e dec = dec + 2^0
retornando dec=5


*/