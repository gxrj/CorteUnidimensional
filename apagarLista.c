/*
    -Apaga a lista encadeada de pecas obtidas
*/
#include <stdlib.h>
#include "IFFPO.H"

void apagarLista( ListaDePecasObtidas *lista ){
  Peca *aux, *atual;
  ListaDePecasObtidas *temp;
  if( lista != NULL ){
    atual = lista->inicio;
    while( atual != NULL ){
      aux = atual;
      atual = atual->proximo;
      free(aux);
    }
    temp = lista;
    lista = NULL;
    free(temp);
  }
}
