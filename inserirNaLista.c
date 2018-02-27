/*
    -Cria uma nova estrutura do tipo Peca,
    -insere os valores de parâmetro na estrutura criada
    -e inclui a nova estrutura na lista encadeada "padrao" organizada de maneira crescente 
*/
#include <stdlib.h>
#include "IFFPO.H"

void inserirNaLista( ListaDePecasObtidas *padrao, int valor, int posicao, int demanda ){
  Peca *novo, *atual, *anterior = NULL;
  if( padrao != NULL ){
    novo = (Peca*)malloc(sizeof(Peca));
    novo->tamanho = valor;
    novo->demanda = demanda;
    novo->posicao = posicao;

    atual = padrao->inicio;
    while( atual != NULL && atual->tamanho > novo->tamanho ){
      anterior = atual;
      atual = atual->proximo;
    }

    if( anterior == NULL ){
      novo->proximo = padrao->inicio;
      padrao->inicio = novo;
    }
    else{
      anterior->proximo = novo;
      novo->proximo = atual;
    }
  }
}
