#include <stdio.h>
#include "IFFPO.H"

void escreverSolucao(EsquemaDeCorte *solucaoFinal,int itens, int compPadrao)
{
    int qtdeBarras = 0, i = 0, soma = 0;
    Peca *andarilho;
    char c;
    
    while(solucaoFinal != NULL)
    {
        printf("\nBarra %d \n", ++qtdeBarras);
        printf("Padrao = [");
        for(i=0;i<itens;i++)
            printf(" %d%c",solucaoFinal->vetorPadraoDeCorte[i], (i == itens-1)?(' '):(';'));
        printf("] ^t \nPlano de corte utilizado: {");

        andarilho = solucaoFinal->pecasObtidas->inicio;
        
        while(andarilho != NULL)
        {
            printf(" %d%c", andarilho->tamanho, c = (andarilho->proximo == NULL)?(' '):(';'));
            andarilho = andarilho->proximo;
        }
        printf("}\n");
        printf("Repeticoes: %d \n",solucaoFinal->repeticoes);
        printf("Perda Individual: %d \n", solucaoFinal->perdaIndividual);
        soma += solucaoFinal->perdaIndividual;
        solucaoFinal = solucaoFinal->proximo;
    }
    
    printf("\nPerda de %d u.m. de %d u.m. de materia prima utilizada \n", soma, compPadrao*qtdeBarras);
}
