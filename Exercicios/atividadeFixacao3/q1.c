#include <stdio.h>
#include <stdlib.h>

/*
void inter(int V1[TAM], int V2[TAM], int V3[TAM],int i, int j,int q1, int q2,int *q3)
{
    if(i < q1 || j < q2)
    {
    if(V1[i] < V2[j])
        //q3 deve ser referenciado como o contéudo, logo seria *q3 = ....
        //mesmo que a função seja com retorno, não é necessário/obrigatório q3 receber a função 
        q3 = inter(V1,V2,V3,i,j+1,q1,q2,q3);// se o vetor indicado por i é o menor entao i deve ser incrementado no parametro quando chama a recursão
    else if(V1[i] > V2[j])
        inter(V1,V2,V3,i,j+1,q1,q2,&q3);//&q3 está sendo passado o seu endereço de memória e não para seu conteúdo, logo é necessário apenas o q3
    else {V3[q3] = V1[j];//q3 está passando um endereço de memoria e nao o seu conteúdo o correto é V3[*q3]
        *q3 = q3 + 1;// para incrementar q3 também é necessário o * para indicar seu conteúdo
        inter(V1,V2,V3,i+1,j+1,q1,q2,q3);
        }
    }
    return(q3); // função do tipo void não pode ter retorno logo a função deve ser do tipo int
    //ou entao nao precisaria do return e continuaria sendo void e para isso na linha 12, q3 nao poderia receber a função
}
*/

// recebe os mesmos parâmetros
void inter2(int V1[TAM], int V2[TAM], int V3[TAM], int i, int j,int q1, int q2,int *q3){
    while(i < q1 || j < q2)// um laço de repetição para percorrer v1 e v2
    {
        if(V1[i] < V2[j])
            i++; // se o valor de v1 for maior que v2, o i que referencia a posição de v1 é incrementado
        else if(V1[i] > V2[j])
            j++;// idem anterior só que para o v2
        else{
                V3[*q3] = V1[j];//caso seja iguais adicionam na posição referente a do v3 e incrementa o contador
                *q3 = *q3 + 1;
                i++;
                j++;
                // agora v1 e v2 avançam uma posição
            }
    }
    //como q3 está por referência, na sua impressão basta colocar q3 para tomar como base a quantidade de elementos que contém v3
}


