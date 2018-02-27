/*
    -Cria uma lista encadeada do tipo ListaDePecasObtidas
    -ajusta seus valores iniciais
    -retorna a estrutura
*/
#include <stdlib.h>
#include "IFFPO.H"

ListaDePecasObtidas* iniciar(void){
  ListaDePecasObtidas *padrao;
  padrao = (ListaDePecasObtidas*)malloc(sizeof(Peca));
  padrao->inicio = NULL;
  padrao->quantidade = 0;
  return padrao;
}
