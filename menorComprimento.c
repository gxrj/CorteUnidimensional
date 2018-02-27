/*
    -Retorna a menor peça que pode ser obtida através do material restante, representado pela variável "perda" 
    -caso não exista peças, esta função retornará 0
*/
#include<stdlib.h>
#include "IFFPO.H"

int menorComprimento(Peca *andarilho)
{
    int menorTamanho = -1;
    
    while(andarilho != NULL)
    {
        //Se o valor de menor for negativo, significa que é a primeira iteração
        if(menorTamanho < 0 || menorTamanho > andarilho->tamanho)
            menorTamanho = andarilho->tamanho;

        andarilho = andarilho->proximo;
    }
    
    if(menorTamanho < 0) // Se andarilho == NULL, não exite peças
        return 0;
    else
        return menorTamanho;
}
