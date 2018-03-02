/*
    -esquema[0] = maior perda individual
    -esquema[1] = maior perda vezes a quantidade de repetições
    -esquema[2] = maior quantidade de peças gerdas individualmente
    -esquema[3] = maior quantidade de peças geradas vezes as repetoçẽs de sua aplicação ;
*/
#include<stdlib.h>
#include"IFFPO.H"

void melhoria( EsquemaDeCorte * listaDeEsquemas, int perda, int tamanhoArray, int tamanhoBarraPadrao, float alpha){
  
    EsquemaDeCorte *esquema[4];
    ListaDePecasObtidas *novoInventario = NULL;

    int *demandaPeca = (int *) malloc(sizeof(int) * tamanhoArray),
        barrasUtilizadas = 0, i, j;

    obterEsquemas(listaDeEsquemas, esquema[0], esquema[1], esquema[2], esquema[3], tamanhoArray);

    iniciarArray(demandaPeca, tamanhoArray);
    novoInventario = iniciar();

    for(i=0;i<tamanhoArray;i++)
    {
        barrasUtilizadas += esquema[i]->repeticoes;

        for(j=0;j<4,j++)
            demandaPeca[i] += esquema[j]->vetorPadraoDeCorte[i] * esquema[j]->repeticoes;
    }

}
