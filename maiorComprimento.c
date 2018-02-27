/*
    -Retorna a maior peça que pode ser obtida através do material restante, representado pela variável "perda" 
    -caso não exista peça que possa ser obtida através do material residual, esta função retornará 0
*/
#include<stdlib.h>
#include "IFFPO.H"

int maiorComprimento(Peca *andarilho, int perda)
{
    int maior = -1;
    
    while(andarilho != NULL)
    {
        //Se o valor de maior for negativo, significa que é a primeira iteração
        if(andarilho->tamanho <= perda && (maior < 0 || maior < andarilho->tamanho))
            maior = andarilho->tamanho;

        andarilho = andarilho->proximo;
    }
    
    if(maior < 0) // Se andarilho == NULL ou se a maior peça for maior que a perda
        return 0;
    else
        return maior;
}
