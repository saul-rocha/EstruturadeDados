/*
void inter(int V1[TAM], int V2[TAM], int V3[TAM],int i, int j,int q1, int q2,int *q3)
{// os vetores estão sendo do mesmo tamanho, logo seria melhor serem passado por referência
    if(i < q1 || j < q2)
    {
    if(V1[i] < V2[j])
        q3 = inter(V1,V2,V3,i,j+1,q1,q2,q3);// se o vetor indicado por i é o menor entao i deve ser incrementado no parametro quando chama a recursão
    else if(V1[i] > V2[j])
        inter(V1,V2,V3,i,j+1,q1,q2,&q3);
    else {V3[q3] = V1[j];//q3 está passando um endereço de memoria e nao o seu conteúdo o correto é V3[*q3]
        *q3 = q3 + 1;// para incrementar q3 também é necessário o * para indicar seu conteúdo
        inter(V1,V2,V3,i+1,j+1,q1,q2,q3);
        }
    }
    return(q3); // função do tipo void não pode ter retorno logo a função deve ser do tipo int
}
*/

void inter(int *v1, int *v2, int *v3, int i, int j, int q1, int q2, int *q3){
    while(i < q1 || j < q2){
        if(v1[i] < v2[j]){
            i++;
        }
        else if(v1[i] > v2[j]){
            j++;
        }
            else{
                v3[*q3] = v1[j];
                *q3 += 1;
            }
    }
}

