/*
    -Cria uma matriz de soluções, onde as soluções de mesma linha apresentam o mesmo alfa e a quantidade de colunas está de acordo as repetições
    -atribuí a solução, através da função construcao(), à cada elemento da matriz
    -executa a melhoria de cada solução construída
    -imprime as saídas nos arquivos
    -contabiliza o tempo de execução
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "IFFPO.H"


void GRASP(ListaDePecasObtidas *padrao, int repeticoes, int L){

    float alpha = 0.1;
    int j;
    listaSolucao *solucoesPorAlpha[10][repeticoes], *melhores[10], *melhor, *auxiliar;
    clock_t start, end;

    for(alpha = 0.1; alpha < 1; alpha+=0.1)
    {
      
      printf("Alpha (%.2f): \n", alpha);
      for(j = 0; j<repeticoes; j++) {
        solucoesPorAlpha[(int)((alpha*10)-1)][j] = construcao(padrao, alpha, L);
        melhoria( solucoesPorAlpha[(int)((alpha*10)-1)][j]->inicio, solucoesPorAlpha[(int)((alpha*10)-1)][j]->perda, solucoesPorAlpha[(int)((alpha*10)-1)][j]->barrasUtilizadas, padrao->quantidade );
        escreverSolucaoTexto( "saida.txt", solucoesPorAlpha[(int)((alpha*10))-1][j]->inicio, padrao->quantidade, L, alpha, solucoesPorAlpha[(int)((alpha*10))-1][j]->perda);
      }

      start = clock();
      auxiliar = obterMelhores(*solucoesPorAlpha+((int)((alpha*10)-1)*(repeticoes)), repeticoes);
      melhores[(int)((alpha*10)-1)] = auxiliar;
      escreverSolucaoTexto( "melhores.txt", auxiliar->inicio, padrao->quantidade, L, alpha, auxiliar->perda);
      end = clock();
      printf("Tempo de execução para obter o melhor: %.2f\n\n", (double)( end - start ) / ((double)CLOCKS_PER_SEC ));      
    }
    
}
