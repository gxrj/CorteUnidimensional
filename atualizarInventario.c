/*
    -Remove peças cuja demanda foi suprida
    -recorganiza a lista de peças do invetário
*/
#include <stdio.h>
#include <stdlib.h>
#include "IFFPO.H"

void atualizarInventario(ListaDePecasObtidas *lista)
{
    Peca *anterior = NULL, 
         *andarilho = NULL;
  
    if(lista == NULL)
    {
        printf("Erro na funcao atualizarInventario() \nSaindo...");
        exit(4);
    }
  
    andarilho = lista->inicio;
    
    while(andarilho != NULL)
    {
        if(andarilho->demanda != 0)
        {
            anterior = andarilho;
            andarilho = andarilho->proximo;
        }
        else
        {
            if(anterior == NULL) //Se for o primeiro elemento da lista 
            {
                lista->inicio = andarilho->proximo;
                (lista->quantidade)--;
                free(andarilho);
                andarilho = lista->inicio;
            }
            else
            {
                anterior->proximo = andarilho->proximo;
                (lista->quantidade)--;
                free(andarilho);
                andarilho = anterior->proximo;
            }
        }
    }
}
