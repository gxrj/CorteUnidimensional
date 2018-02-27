/*
    -Copia os valores da estrutura "padrao" para a estrutura "inventario" através da função criarInventario()

    Enquanto o inventario não estiver vazio: 
        -instacia um novo esquema de corte "temp", 
        -instancia os cortes possíveis através do inventário,
        
        Enquanto a perda for maior que a menor peça do invetário:
            -define um beta, atraves da função maiorComprimento()
            -instanciada pela variável "lrc", define uma lista de candidatos restritos obtida através dos cortes possíveis
            -atribuí um valor randômico para a variável "indiceSelecionado", através da quandidade de elementos distintos inseridos em "lrc"
            -seleciona a peça da lista encadeada "lrc" de acordo com o "índiceSelecionado"
            -armazena em "repeticoes" a quantidade de vezes que a peça pode ser gerada pela barra,  
            -aplica as correções no valor de repetição

            Se a qtde repetições for maior que zero:
                -Adiciona peça no plano de corte
                -Descarta a peça escolhida do restante da barra a ser cortada
            
            -Atualiza os valores e retoma ao loop interno até que sua condição não seja satisfeita

        -Após o fim do loop interno, verifica se o padrao de corte recém gerado pode ser repetido
        -atualiza as repetições do esquema de corte e perda
        -concatena os valores
        -Atualiza os valores e retoma ao loop externo até que sua condição não seja satisfeita

    -Após o fim do loop externo, incrementa a quantidade de barras utilizadas na solução 

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "IFFPO.H"

listaSolucao * construcao(ListaDePecasObtidas *padrao, float alpha, int L)
{
    ListaDePecasObtidas * inventario = criarInventario(padrao->inicio),
          *cortesPossiveis = NULL,
          *lrc = NULL;
    
    int perda,
        menorPeca,
        indiceSelecionado,
        repeticoes,
        beta,
        qtdeBarras = 0;
  
    Peca *escolhido = NULL;

    listaSolucao* lista = (listaSolucao *) malloc(sizeof(listaSolucao));
    lista->inicio = NULL;
    lista->alpha = alpha;
    lista->perda = 0;
    EsquemaDeCorte *temp = NULL;
    
    if(padrao == NULL || padrao->quantidade == 0)
    {
        printf("Quantidade invalida de itens no inventario \nSaindo...");
        exit(-1);
    }
  
    //imprimir(inventario);
    while(inventario->inicio != NULL)
    {
        perda = L;
               
        temp = (EsquemaDeCorte *) malloc(sizeof(EsquemaDeCorte));
        
        if(temp == NULL)
        {       printf("Memoria Insuficiente!\nSaindo... \n");
                exit(-2);
        }
        temp->vetorPadraoDeCorte = (int *) malloc(sizeof(int) * padrao->quantidade);
        temp->vetorDemandaResidual = (int *) malloc(sizeof(int) * padrao->quantidade);
  
        iniciarArray(temp->vetorPadraoDeCorte, padrao->quantidade);
        iniciarArray(temp->vetorDemandaResidual, padrao->quantidade);
      
        temp->pecasObtidas = iniciar(); 
        menorPeca = menorComprimento(inventario->inicio);
        /*Trecho delicado*/
        cortesPossiveis = criarInventario(inventario->inicio);
      
        while(cortesPossiveis->inicio != NULL && perda >= menorPeca && menorPeca != 0)
        {
            //Define a peca de maior comprimento de acordo com a perda
            beta = maiorComprimento(cortesPossiveis->inicio, perda);
            //Os candidatos serao pecas maiores que alpha*beta e menores que a perda
            lrc = candidatosRestritos(cortesPossiveis->inicio, alpha*beta, perda);
            //Comandos responsaveis pela escolha do item a ser cortado  
            indiceSelecionado = rand() % lrc->quantidade + 1;
            /*Trecho delicado*/
            escolhido = sortearLRC(lrc->inicio, indiceSelecionado);
            repeticoes = perda/escolhido->tamanho;
        
            //Diminui a repetição de peças a serem cortadas se ultrapassar a demanda
            while((escolhido->demanda - repeticoes)<0)
                repeticoes--;
            //Corrige o valor de repeticoes para zero, caso a peca escolhida seja obtida n vezes da barra restante [variável "perda"] mas nao haja demanda
            if(repeticoes < 0)
                repeticoes = 0;
            
            //Atualiza o valor restante da barra em perda
            perda -= repeticoes*escolhido->tamanho; 
            //Adiciona a quantidade de itens da peça escolhida a ser obtida da barra
            temp->vetorPadraoDeCorte[escolhido->posicao] = repeticoes;
            
            if(repeticoes > 0)
            {
                //Adiciona item selecionado no plano de corte
                inserirNaLista(temp->pecasObtidas, escolhido->tamanho, escolhido->posicao, repeticoes);
                //Incrementa a quantidade de pecas geradas com o corte 
                temp->pecasObtidas->quantidade += repeticoes;
                //Atualiza a demanda do item escolhido no inventario
                atualizarDemanda(inventario->inicio, escolhido->tamanho, repeticoes, temp->vetorDemandaResidual);
                //Descarta o produto escolhido do restante da barra a ser cortada
                apagarPeca(cortesPossiveis,escolhido);
            }
        
            //Necessario redefinir a menor peça caso já descartada
            menorPeca = menorComprimento(cortesPossiveis->inicio);

            //Limpa as estruturas para a próxima iteração
            escolhido = NULL;
            apagarLista(lrc);
        }
      
        temp->repeticoes = repetirPadrao(inventario->inicio, temp->vetorDemandaResidual, temp->vetorPadraoDeCorte, padrao->quantidade); 
        qtdeBarras++;
        temp->perdaIndividual = perda;
		lista->perda += perda;
        temp->proximo = NULL;
        
        lista->inicio = concatenar(lista->inicio,temp);
        atualizarInventario(inventario);
        apagarLista(cortesPossiveis);
    }
    lista->barrasUtilizadas = qtdeBarras;
    //printf("\n%d barras utilizadas \n", qtdeBarras);
    //escreverSolucao(lista->inicio, padrao->quantidade, L);

    return lista;
}
