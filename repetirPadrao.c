/*
    -Varre o arrayDemanda
    -verifica se o padrao de corte ainda não atendeu a demanda
    -se o padrao de corte puder ser repetido:
        -percorre o inventário e atualiza as demandas na solucao e no inventario
        -incrementa a variável "repeticoes"
    -retorna a quantidade de repetições
*/
#include<stdlib.h>
#include "IFFPO.H"

int repetirPadrao(Peca *inventario, int *arrayDemanda, int *arrayPadraoDeCorte, int limite)
{
    int i, repetir = 1, repeticoes = 1;
    Peca *andarilho = inventario;

    while(repetir)
    {
        //verifica se o padrao de corte ainda não atendeu a demanda ou seja repetir = 1
        for(i=0;i<limite;i++){
           if(arrayPadraoDeCorte[i] != 0 && (arrayDemanda[i] == 0 || arrayDemanda[i] < arrayPadraoDeCorte[i]))
              repetir = 0;
        }
        //Se o padrao de corte puder ser repetido, percorre o inventário e atualiza as demandas
        if(repetir)
        {
            andarilho = inventario;
            while(andarilho != NULL)
            {
              //Se o corte foi aplicado na barra, então sua demanda será atualizada na solucao e no inventario
              if(arrayPadraoDeCorte[andarilho->posicao])
              { 
                arrayDemanda[andarilho->posicao] -= arrayPadraoDeCorte[andarilho->posicao];
                andarilho->demanda -= arrayPadraoDeCorte[andarilho->posicao];
              }
                
               andarilho = andarilho->proximo;
            }
            repeticoes++;
        }
    }
  return repeticoes;
}
