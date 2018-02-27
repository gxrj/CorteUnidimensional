/*
    -Atualiza a demanda dos elementos da lista encadeada de peças
    -atualiza cada valor do vetor "arrayDemanda"
*/
#include <stdio.h>
#include <stdlib.h>
#include "IFFPO.H"

void atualizarDemanda(Peca *andarilho,int tamanho, int demandaAtendida, int *arrayDemanda)
{
    while(andarilho != NULL)
    {
            if(andarilho->tamanho == tamanho)
            {
               andarilho->demanda -=demandaAtendida;
               arrayDemanda[andarilho->posicao] = andarilho->demanda;
               return;
            }
            
            andarilho = andarilho->proximo;
    }
    
    printf("Erro em atualizarDemanda()! Comprimento selecionado nao existe no inventario\n");
    exit(7);
}
