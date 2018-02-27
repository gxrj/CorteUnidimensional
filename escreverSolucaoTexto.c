#include <stdio.h>
#include "IFFPO.H"

void escreverSolucaoTexto(char *texto, EsquemaDeCorte *solucaoFinal,int itens, int compPadrao, float alpha, int perdaTotal )
{
    int qtdeBarras = 0, i = 0, soma = 0, somaBarras = 0, somaPerda = 0;
    Peca *andarilho;
    char c;
    FILE *arquivo = fopen(texto, "a");

    fprintf(arquivo, "Alpha: %.2f\n", alpha);
    while(solucaoFinal != NULL)
    {
        fprintf(arquivo, "\nPadrão de Corte %d \n", ++qtdeBarras);
        fprintf(arquivo, "Padrao = [");
        for(i=0;i<itens;i++)
            fprintf(arquivo, " %d%c",solucaoFinal->vetorPadraoDeCorte[i], (i == itens-1)?(' '):(';'));
        fprintf(arquivo, "] ^t \nPlano de corte utilizado: {");

        andarilho = solucaoFinal->pecasObtidas->inicio;
        
        while(andarilho != NULL)
        {
            fprintf(arquivo, " %d%c", andarilho->tamanho, c = (andarilho->proximo == NULL)?(' '):(';'));
            andarilho = andarilho->proximo;
        }
        fprintf(arquivo, "}\n");
        fprintf(arquivo, "Repeticoes: %d \n",solucaoFinal->repeticoes);
        fprintf(arquivo, "Perda Individual: %d \n", solucaoFinal->perdaIndividual);
        somaBarras += solucaoFinal->repeticoes;
        //somaPerda += solucaoFinal->repeticoes * solucaoFinal->perdaIndividual;
        //soma += solucaoFinal->perdaIndividual;
        solucaoFinal = solucaoFinal->proximo;
    }
    
    fprintf(arquivo, "\nPerda total de %d u.m.", perdaTotal );
    fprintf(arquivo, "\nBarras utilizadas: %d\n\n\n", somaBarras );
    fclose(arquivo);
}
