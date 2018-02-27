/*
    -Apaga a peça selecionada de uma lista encademada de peças
*/
#include <stdio.h>
#include <stdlib.h>
#include "IFFPO.H"

void apagarPeca(ListaDePecasObtidas *lista, Peca *elemento)
{
    Peca *anterior = NULL, 
         *andarilho = NULL;
  
    if(lista == NULL)
    {
        printf("Erro na funcao apagarElemento() \nSaindo...");
        exit(4);
    }
  
    andarilho = lista->inicio;
  
    while(andarilho != NULL && andarilho->tamanho != elemento->tamanho)
    {
      anterior = andarilho;
      andarilho = andarilho->proximo;
    }
    //Se andarilho for nulo, elemento nao encontrado
    if(andarilho == NULL)
    {
        printf("Erro na funcao apagarElemento(), elemento nao encontrado na lista auxiliar \nSaindo...");
        exit(5);
    }
    //Se anterior for nulo, entao andarilho é o primeiro elemento
    if(anterior == NULL)
        lista->inicio = andarilho->proximo;
    else
      anterior->proximo = andarilho->proximo;
  
    (lista->quantidade)--;
    free(andarilho);
  
}
