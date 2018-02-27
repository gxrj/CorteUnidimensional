/*
   -Copia o esquema de corte
   -inicializa os elementos da struct, com execeção do elemento "pecasObtidas" que é apontado para "NULL"
   -copia os vetores 
   -retorna a copia
*/
#include<stdlib.h>
#include<stdio.h>
#include"IFFPO.H"

EsquemaDeCorte * copiarEsquema( EsquemaDeCorte * esquema, int tamanho)
{
    EsquemaDeCorte * copia = (EsquemaDeCorte *) malloc(sizeof(EsquemaDeCorte));

    if(copia == NULL)
    {
        printf("Erro na funcao copiarEsquema() \n");
        exit(14);
    }

    copia->repeticoes = esquema->repeticoes;
    copia->proximo = NULL;
    copia->vetorDemandaResidual = (int *) malloc(sizeof(int) * tamanho);
    copia->vetorPadraoDeCorte = (int *) malloc(sizeof(int) * tamanho);
    copia->pecasObtidas = NULL;
    copiarArray(esquema->vetorDemandaResidual, copia->vetorDemandaResidual, tamanho);
    copiarArray(esquema->vetorPadraoDeCorte, copia->vetorPadraoDeCorte, tamanho);
        
    return copia;
}
