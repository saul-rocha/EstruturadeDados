#include <stdio.h>
#include <stdlib.h>

//nro = 5   i = 0     bin=[]
void binario(int nro, int *i,char bin[8])
{
    if (nro < 256)
    {
        if(nro / 2 > 0)
        {
            binario(nro/2,i,bin);   // 1º nro=2 | 2º nro=0
            bin[*i] = (nro % 2) + 48; //pendencia -> bin[0] = 5%2=1+48 = '1' | bin[1] = 2%2=0+48 = '0'
            printf("bin[%d] = %c\n",*i,bin[*i]); //bin[0] = 1 | bin[0] = 0
            (*i)++; // i=1 | i = 2
        }
        else { bin[*i] = (nro % 2) + 48; // 3º nro = 0 -> nro%2 =0+48 = '1'
            printf("bin[%d] = %c\n",*i,bin[*i]);
            (*i)++;
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
