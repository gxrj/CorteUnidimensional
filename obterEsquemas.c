/*
    -Percorre a lista de esquemas de corte
    -armazena o esquema com a maior perda individual na variável "esqMaiorPerdaInd"
    -armazena o esquema com a maior perda vezes sua quantidade de repetições na variável "esqMaiorPerda"
    -armazena o esquema que fornece a maior quantidade de peças individualmente na variável "esqMaiorQtdePecasInd"
    -armazena o esquema que fornece a maior quantidade de peças vezes a quantidade de repetições que é aplicado na variável "esqMaiorQtdePecas"
*/

#include<stdlib.h>
#include"IFFPO.H"

void obterEsquemas(EsquemaDeCorte *listaDeEsquemas, EsquemaDeCorte *esqMaiorPerdaInd, EsquemaDeCorte *esqMaiorPerda, EsquemaDeCorte *esqMaiorQtdePecasInd, EsquemaDeCorte *esqMaiorQtdePecas, int tamanhoArray)
{
    int maiorQtdePecasIndividual = 0, maiorQtdePecas = 0,maiorPerdaIndividual = 0, maiorPerda = 0;

    EsquemaDeCorte *andarilho = listaDeEsquemas;

    while(andarilho != NULL)
    {
        if(maiorPerdaIndividual < andarilho->perdaIndividual)
        {
            maiorPerdaIndividual =  andarilho->perdaIndividual;
            esqMaiorPerdaInd = copiarEsquema(andarilho, tamanhoArray);
        }
        if(maiorPerda < andarilho->perdaIndividual * andarilho->repeticoes)
        {
            maiorPerda = andarilho->perdaIndividual * andarilho->repeticoes;
            esqMaiorPerda = copiarEsquema(andarilho, tamanhoArray);
        }
        if(maiorQtdePecasIndividual < andarilho->pecasObtidas->quantidade)
        {
            maiorQtdePecasIndividual = andarilho->pecasObtidas->quantidade;
            esqMaiorQtdePecasInd = copiarEsquema(andarilho, tamanhoArray);
        }
        if(maiorQtdePecas < andarilho->pecasObtidas->quantidade * andarilho->repeticoes)
        {
            maiorQtdePecas = andarilho->pecasObtidas->quantidade * andarilho->repeticoes;
            esqMaiorQtdePecas = copiarEsquema(andarilho, tamanhoArray);
        }
        andarilho = andarilho->proximo;
    }

}
