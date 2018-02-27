/*
    -Adiciona a pecas do invetário na lista cujo tamanho seja maior que o fator e menor que o tamanho da barra restante (identificada pela variável "perda")
    -incrementa a quantidade de pecas distintas na lista,
    -retorna a lista gerada
*/
#include<stdlib.h>
#include "IFFPO.H"

// fator = alpha * beta
ListaDePecasObtidas * candidatosRestritos(Peca *andarilho, float fator, int perda)
{
    ListaDePecasObtidas *lista = iniciar();

    while(andarilho != NULL)
    {
        if(andarilho->tamanho >= fator && andarilho->tamanho <= perda){
          inserirNaLista(lista, andarilho->tamanho, andarilho->posicao, andarilho->demanda);
          lista->quantidade += 1;
        }
      
        andarilho = andarilho->proximo; 
    }
  return lista;
}
