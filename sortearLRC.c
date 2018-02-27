/*
    -Retorna o endereco da estrutura sorteada através do índice
*/
#include <stdio.h>
#include <stdlib.h>
#include "IFFPO.H"

Peca * sortearLRC(Peca *listaCandidatos, int index)
{
    int i=1;
    while(listaCandidatos != NULL && i != index )
    {
        listaCandidatos = listaCandidatos->proximo;
        i++;
    }
  
    if(listaCandidatos == NULL)
    {
      printf("Erro, na funcao sortearLRC() \nSaindo...");
      exit(3);
    }
  
    return listaCandidatos;
}
