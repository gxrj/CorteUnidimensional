/*
    -Instancia copia de uma lista encadeada de pecas através da função iniciar(), logo após a condicional
    -dentro do loop, insere os valores de cada peça encontrada por "andarilho" na lista encadeada "copia" através do procedimento inserirNaLista()
    -incrementa a quantidade de pecas distintas inseridas na copia
    -retorna a lista encadeada "copia"
*/
#include <stdio.h>
#include <stdlib.h>
#include "IFFPO.H"

ListaDePecasObtidas* criarInventario(Peca *andarilho)
{
    ListaDePecasObtidas * copia = NULL;
  
    if(andarilho == NULL)
    {
        printf("Padrao Inexistente.Necessario definir um padrao \nSaindo...");
        exit(1);
    }
  
    copia = iniciar();
    
    while(andarilho != NULL)
    {
        inserirNaLista(copia, andarilho->tamanho, andarilho->posicao, andarilho->demanda);
        (copia->quantidade)++;
        andarilho = andarilho->proximo;
    }
      
    return copia;
}
