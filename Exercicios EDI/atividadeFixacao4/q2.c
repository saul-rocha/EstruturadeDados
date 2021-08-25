#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// recebe uma string de numeros, a unidade iniciando de 1, e o tamanho da string
int converte(char str[],int unit, int tam){

    int valor=0; // valor de retorno
    if(tam >= 0){ // como a string vai começar ser convertida do fim para o inicio entao o final da recursao é quando a posição for a 0
        valor = converte(str,unit*10,tam-1)+((str[tam]-48) * unit);// chama recursivamnte com pendencia.
        // a unidade será mudada a cada recursão(unidade,dezena,centana....),o tamanho é decrementado
        // logo fica pendente a soma na variavel valor, o produto entre valor do char - 48(equivale a 0 na table ascii)
        // e a unidade.
    }
    return valor; // retorna o valor resultante
}


int main(){
    int tam; // irá armazenar o tamanho da string
    char str[50]; // string que será lida
    int i; // armazenará o valor inteiro

    scanf("%s", str);// ler a string
    tam = strlen(str);// atribui a variavel tam o tamanho da string
    str[tam+1] = '\0'; // determina o fim da string
    i = converte(str,1,tam-1); // chama a função colocando i para receber seu retorno
    printf("%d\n",i);// imprime o valor inteiro

    return (0);
}