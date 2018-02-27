/*
    -Concatena os esquemas de corte para formar um lista encadeada
*/
#include<stdlib.h>
#include "IFFPO.H"

EsquemaDeCorte * concatenar(EsquemaDeCorte *inicio, EsquemaDeCorte *temp)
{
    EsquemaDeCorte *andarilho = inicio;
    
    if(inicio == NULL)
            return temp;
    else
    {
        while(andarilho->proximo != NULL)
            andarilho = andarilho->proximo;

        andarilho->proximo = temp;
        return inicio;
    }
    
}
