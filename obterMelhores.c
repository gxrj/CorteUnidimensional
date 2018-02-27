#include "IFFPO.H"

listaSolucao * obterMelhores(listaSolucao *resultado[], int coluna)
{
  listaSolucao * melhor = resultado[0];
  int j;


  for(j=0;j<coluna;j++)
    if(melhor->perda > resultado[j]->perda)
      melhor = resultado[j];
    
  return melhor;
}
