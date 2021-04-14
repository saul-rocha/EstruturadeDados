#include <stdio.h>
#include <stdlib.h>
/*
// 1° nro = 5   i = 0    bin[8] |  2° nro = 2 i = 0 bin[8] | 3° nro = 1 i = 0 bin[8]
void binario(int nro, int *i,char bin[8])
{
    if (nro < 256)
    {
        if(nro / 2 > 0)
        {
            binario(nro/2,i,bin);  // 1° | 2°
            bin[*i] = (nro % 2) + 48; //pendencia desempilha -> nro = 2, bin[1]= 0 + 48 = '0' | nro = 5, bin[0] = 1 +  48 = '1'
            printf("bin[%d] = %c\n",*i,bin[*i]); //pendencia bin[1] = '0' | bin[2] = '1'
            (*i)++; //pendencia  i = 2
        }
        // na terceira vez da recursão vem para esta condição e depois faz as operações pendentes acima
        else { bin[*i] = (nro % 2) + 48; // 3º bin[0] = 1 % 2 = 1 + 48 = '1'
            printf("bin[%d] = %c\n",*i,bin[*i]); //3º bin[0] = '1'
            (*i)++; //3º i = 1
        }
    }
}
int main()
{
    int n, i = 0;
    char bin[9];
    printf("n: ");
    scanf("%d",&n);
    if(n < 256)
    {
        binario(n,&i,bin);
        bin[i+1] = '\0';
        printf("O número binario e: %s\n",bin);
    }
    else printf("O maior número possível com 8 dígitos é 255. \n");
    return(0);
}
*/

// MODIFICAÇÃO