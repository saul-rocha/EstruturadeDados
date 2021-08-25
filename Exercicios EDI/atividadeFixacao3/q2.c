/*
COMENTARIO GERAL
void misterio1(char str[TAM], int i, int uni, int *valor) // recebe um vetor de char, dois interiros e um int por referencia
{ // i refere-se ao tamanho do vetor de char, uni é a unidade
    int n; // n é uma variavel auxiliar
    if(i >=0)// condição de parada da recursividade
    { 
        if(isdigit(str[i]))// verifica se o caractere na posição i é um número
        { n = str[i] - 48; // de acordo com a tabela ascii n vai receber o valor do char na posição i menos 48(na tabela ascii representa o 0)
        *valor = *valor + (n * uni); // valor acumula a soma de do produto de n * uni(unidade inicia com 1, pois tá efetuando uma multiplicação)
                                        // e irá representar a unidade, dezena,centena e assim por diante
        misterio1(str,i -1, uni * 10, valor); // quando o digito é encontrado a recursão reduz o tamaho do vetor e avança para a proxima unidade multiplicando uni por 10 
                                            //e o valor é passado por referência novemente acumulando o valor representado na string
    }
    else misterio1(str,i -1, uni, valor);//caso nao seja um digito na posição i, é chamada a recursiva passando para a proxima posição
    }

    de forma geral esta função percorre uma string começando do final e converte para inteiro.
}

RASTREIO
            //str = "54ul", i = 3, uni = 1, *valor = 0
void misterio1(char str[TAM], int i, int uni, int *valor)
{ int n;
if(i >=0)
{ if(isdigit(str[i]))//  1º 'l' nao é digito | 2º 'u' nao é digito | 3º '4' é digito | 4º '5' é digito
{ n = str[i] - 48; //3º '4' - 48 -> (52-48) -> n = 4 | 4º '5' - 48 -> (53 - 48) -> n = 5
*valor = *valor + (n * uni); //3º 0 + (4 * 1) -> 4 | 4º 4 + (5*10) -> 54
misterio1(str,i -1, uni * 10, valor);//3º i= 0, uni = 10, valor = 4 | 4º  i= -1, uni = 100, valor = 54 
}
else misterio1(str,i -1, uni, valor);// 1º i= 2, uni = 1, valor = 0| 2º i= 1, uni = 1, valor = 0 
}
}

    indentifica os numeros numa string e transforma em um inteiro
*/

void misterio1(char str[TAM], int i, int uni, int *valor)
{ 
    int n;
    while(i >=0)
    { 
        if(isdigit(str[i]))
        { 
            n = str[i] - 48;
            *valor = *valor + (n * uni);
            i = i - 1;
            uni = uni * 10;
        }
        else (i = i-1);
    }
}

