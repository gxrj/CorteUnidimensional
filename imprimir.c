#include <stdio.h>
#include "IFFPO.H"

void imprimir( ListaDePecasObtidas *padrao ){
  Peca *atual;
  if( padrao != NULL ){
    printf("{");
    atual = padrao->inicio;
    while( atual != NULL ){
      printf("%d ", atual->tamanho);
      atual = atual->proximo;
    }
    printf("}\n");
  }
}
