/*
    -esquema[0] = maior perda individual
    -esquema[1] = maior perda vezes a quantidade de repetições
    -esquema[2] = maior quantidade de peças gerdas individualmente
    -esquema[3] = maior quantidade de peças geradas vezes as repetoçẽs de sua aplicação 
*/
#include<stdio.h>
#include"IFFPO.H"

void melhoria( EsquemaDeCorte * listaDeEsquemas, int perda, int barrasUtilizadas,int tamanhoArray ){
  
    EsquemaDeCorte *esquema[4];

    obterEsquemas(listaDeEsquemas, esquema[0], esquema[1], esquema[2], esquema[3], tamanhoArray);

  
  
}
