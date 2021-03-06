#include <stdio.h>
#include <stdlib.h>

/*
Faça um algoritmo em C que leia 5 números inteiros e então faça:
(a) Uma função recursiva sem pendência que calcule Mínimo Múltiplo Comum (MMC) entre os números 
lidos.
(b) Repita o exercício da letra a, mas agora faça uma função recursiva que deixa pendência.
*/

//recebe os 5 valores e um auxiliar que incia com 2 e 
//um ponteiro MMC que ja começa como sendo 1
// aux inicia de 2 pois 1 já é o MMC
void MMC_sem_pendencia(int a,int b,int c,int d,int e,int aux, int *MMC){
    int flag = 0;
    int numero; 
    //se os valores forem diferente de 1 e o numero for divisivel por auz a flag recebe 1
    if(a != 1 && a % aux == 0){
        a = a/aux;
        flag = 1;
    }
    if(b != 1 && b % aux == 0){
        b = b/aux;
        flag = 1;
    }
    if(c != 1 && c % aux == 0){
        c = c/aux;
        flag = 1;
    }
    if(d != 1 && d % aux == 0){
        d = d/aux;
        flag = 1;
    }
    if(e != 1 && e % aux == 0){
        e = e/aux;
        flag = 1;
    }

    //quando a flag for 1 o MMC é atrubuido se a soma dos valores for igual a 5
    if( a+b+c+d+e == 5 && flag == 1){
        *MMC = (*MMC) * aux;
    }else{
        //caso contrario, se somente a flag for 1   , numero recebe a aux
        if(flag == 1){
            numero = aux;
        //SSe flag for 0, numero recebe 1 e o MMC continua o mesmo
        }else{
            numero = 1;
            aux++;
        }
        //printf("Depois\na = %d\nb = %d\nc = %d\nd = %d\ne = %d\naux = %d\nnumero = %d\nMMC = %d\n\n",a,b,c,d,e,aux,numero,*MMC);
        *MMC = (*MMC) * numero;
        MMC_sem_pendencia(a,b,c,d,e,aux,MMC);//chama recusivamente sem pendencia até que a flag seja 1 
    }

}

//idem anterior, muda apenas o parametro MMC que agora é retornado pela função e não por parametro
int MMC_com_pendencia(int a,int b,int c,int d,int e, int aux){
    int flag = 0;
    int MMC = 1;
    int numero;
    int numero_2;// é usado para receber o valor retornado na função

    if(a != 1 && a % aux == 0){
        a = a/aux;
        flag = 1;
    }
    if(b != 1 && b % aux == 0){
        b = b/aux;
        flag = 1;
    }
    if(c != 1 && c % aux == 0){
        c = c/aux;
        flag = 1;
    }
    if(d != 1 && d % aux == 0){
        d = d/aux;
        flag = 1;
    }
    if(e != 1 && e % aux == 0){
        e = e/aux;
        flag = 1;
    }
    
    if( a+b+c+d+e == 5){
        MMC = aux;
    }else{
        if(flag == 1){
            numero = aux;
        }else{
            numero = 1;
            aux++;
        }
        //printf("Depois\na = %d\nb = %d\nc = %d\nd = %d\ne = %d\naux = %d\nnumero = %d\n\n",a,b,c,d,e,aux,numero);
        numero_2 = MMC_com_pendencia(a,b,c,d,e,aux);//recursão com pendencia
        MMC = MMC * numero * numero_2; //pendecia
    }


    return MMC; 
}

int main(){

    int a,b,c,d,e;
    int aux = 2;
    int *MMC = (int*)malloc(sizeof(int));
    *MMC = 1;

    printf("Informe o PRIMEIRO numero: ");scanf("%d",&a);
    printf("Informe o SEGUNDO numero: ");scanf("%d",&b);
    printf("Informe o TERCEIRO numero: ");scanf("%d",&c);
    printf("Informe o QUARTO numero: ");scanf("%d",&d);
    printf("Informe o QUINTO numero: ");scanf("%d",&e);

    MMC_sem_pendencia(a,b,c,d,e,aux,MMC);
    printf("MMC sem pendencia: %d\n",*MMC);
    printf("MMC com pendencia: %d\n",MMC_com_pendencia(a,b,c,d,e,aux));

    return 0;
}