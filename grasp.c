#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tipo_peca{
  int tamanho;
  int demanda;
  int posicao;
  struct tipo_peca *proximo;
};
typedef struct tipo_peca No;

struct inicio{
  struct tipo_peca *inicio;
  int quantidade;
};
typedef struct inicio Peca;

typedef struct solucao{
    Peca * sequenciaDePecasGeradas;
    int * vetorPadraoDeCorte;
    int * vetorDemandaResidual;
    int repeticoes;
    int perdaIndividual;
    struct solucao *proximo;
} ResultadoBarra;

typedef struct{
	int barrasUtilizadas;
	int perda;
	float alpha;
	ResultadoBarra *inicio;
}listaSolucao;

Peca* iniciar(){
  Peca *padrao;
  padrao = (Peca*)malloc(sizeof(Peca));
  padrao->inicio = NULL;
  padrao->quantidade = 0;
  return padrao;
}

void apagarLista( Peca *lista ){
  No *aux, *atual;
  Peca *temp;
  if( lista != NULL ){
    atual = lista->inicio;
    while( atual != NULL ){
      aux = atual;
      atual = atual->proximo;
      free(aux);
    }
    temp = lista;
    lista = NULL;
    free(temp);
  }
}

void apagarElemento(Peca *lista, No *elemento)
{
    No *anterior = NULL, 
       *andarilho = NULL;
  
    if(lista == NULL)
    {
        printf("Erro na funcao apagarElemento() \nSaindo...");
        exit(4);
    }
  
    andarilho = lista->inicio;
  
    while(andarilho != NULL && andarilho->tamanho != elemento->tamanho)
    {
      anterior = andarilho;
      andarilho = andarilho->proximo;
    }
    //Se andarilho for nulo, elemento nao encontrado
    if(andarilho == NULL)
    {
        printf("Erro na funcao apagarElemento(), elemento nao encontrado na lista auxiliar \nSaindo...");
        exit(5);
    }
    //Se anterior for nulo, entao andarilho é o primeiro elemento
    if(anterior == NULL)
        lista->inicio = andarilho->proximo;
    else
      anterior->proximo = andarilho->proximo;
  
    (lista->quantidade)--;
    free(andarilho);
  
}

void inserirNaLista( Peca *padrao, int valor, int posicao, int demanda ){
  No *novo, *atual, *anterior = NULL;
  if( padrao != NULL ){
    novo = (No*)malloc(sizeof(No));
    novo->tamanho = valor;
    novo->demanda = demanda;
    novo->posicao = posicao;

    atual = padrao->inicio;
    while( atual != NULL && atual->tamanho > novo->tamanho ){
      anterior = atual;
      atual = atual->proximo;
    }

    if( anterior == NULL ){
      novo->proximo = padrao->inicio;
      padrao->inicio = novo;
    }
    else{
      anterior->proximo = novo;
      novo->proximo = atual;
    }
    padrao->quantidade += 1;
  }
}

void ler( Peca *padrao, char documento[100] ){
  FILE *arquivo;
  int valor, demanda, i, tamanho;
  arquivo = fopen(documento, "r");
  if( arquivo == NULL )
    printf("Houve um erro ao abrir o arquivo!");
  else{
    fscanf(arquivo, "%d", &tamanho);
    i = 0;
    while( fscanf(arquivo, "%d %d", &valor, &demanda) != EOF ){
      inserirNaLista( padrao, valor, i, demanda );
      i++;
    }
    padrao->quantidade = tamanho;
  }
  fclose( arquivo );
}

void imprimir( Peca *padrao ){
  No *atual;
  if( padrao != NULL ){
    printf("{");
    atual = padrao->inicio;
    while( atual != NULL ){
      printf("%d ", atual->tamanho);
      atual = atual->proximo;
    }
    printf("}\n");
  }
}

void escreverSaida( char *documento, int *demanda, int tamanho, int perda){
  int i;
  FILE *arquivo = fopen( documento, "a");
  if( arquivo == NULL ){
    printf("Não possível abrir o arquivo!\n\n");
  }
  else{
    for( i = 0; i < tamanho; i++ ){
      fprintf(arquivo, "%d ", demanda[i]);
    }
    fprintf(arquivo, "%c", '\n');
    fprintf(arquivo, "Perda: %d\n", perda);
  }  
  fclose(arquivo);
}

void iniciarArray( int *array, int tamanho ){
  int i;
  for( i = 0; i < tamanho; i++ )
    array[i] = 0;
}

Peca* criarInventario(No *andarilho)
{
    Peca * copia = NULL;
  
    if(andarilho == NULL)
    {
        printf("Padrao Inexistente.Necessario definir um padrao \nSaindo...");
        exit(1);
    }
  
    copia = iniciar();
    
    while(andarilho != NULL)
    {
        inserirNaLista(copia, andarilho->tamanho, andarilho->posicao, andarilho->demanda);
        andarilho = andarilho->proximo;
    }
      
    return copia;
}

int menorComprimento(No *andarilho)
{
    int menorTamanho = -1;
    
    while(andarilho != NULL)
    {
        //Se o valor de menor for negativo, significa que é a primeira iteração
        if(menorTamanho < 0 || menorTamanho > andarilho->tamanho)
            menorTamanho = andarilho->tamanho;

        andarilho = andarilho->proximo;
    }
    
    if(menorTamanho < 0)
        return 0;
    else
        return menorTamanho;
}

int maiorComprimento(No *andarilho, int perda)
{
    int maior = -1;
    
    while(andarilho != NULL)
    {
        //Se o valor de maior for negativo, significa que é a primeira iteração
        if(andarilho->tamanho <= perda && (maior < 0 || maior < andarilho->tamanho))
            maior = andarilho->tamanho;

        andarilho = andarilho->proximo;
    }
    
    if(maior < 0)
        return 0;
    else
        return maior;
}
// fator = alpha * beta
Peca * candidatosRestritos(No *andarilho, float fator, int perda)
{
    Peca *lista = iniciar();

    while(andarilho != NULL)
    {
        if(andarilho->tamanho >= fator && andarilho->tamanho <= perda){
          inserirNaLista(lista, andarilho->tamanho, andarilho->posicao, andarilho->demanda);
        }
      
        andarilho = andarilho->proximo; 
    }
  return lista;
}
//Retorna o endereco da estrutura sorteada em lrc
No * sorteio(No *listaCandidatos, int index)
{
    int i=1;
    while(listaCandidatos != NULL && i != index )
    {
        listaCandidatos = listaCandidatos->proximo;
        i++;
    }
  
    if(listaCandidatos == NULL)
    {
      printf("Erro, na funcao sorteio() \nSaindo...");
      exit(3);
    }
  
    return listaCandidatos;
}

void escreverSolucao(ResultadoBarra *solucaoFinal,int itens, int compPadrao)
{
    int qtdeBarras = 0, i = 0, soma = 0;
    No *andarilho;
    char c;
    
    while(solucaoFinal != NULL)
    {
        printf("\nBarra %d \n", ++qtdeBarras);
        printf("Padrao = [");
        for(i=0;i<itens;i++)
            printf(" %d%c",solucaoFinal->vetorPadraoDeCorte[i], (i == itens-1)?(' '):(';'));
        printf("] ^t \nPlano de corte utilizado: {");

        andarilho = solucaoFinal->sequenciaDePecasGeradas->inicio;
        
        while(andarilho != NULL)
        {
            printf(" %d%c", andarilho->tamanho, c = (andarilho->proximo == NULL)?(' '):(';'));
            andarilho = andarilho->proximo;
        }
        printf("}\n");
        printf("Repeticoes: %d \n",solucaoFinal->repeticoes);
        printf("Perda: %d \n", solucaoFinal->perdaIndividual);
        soma += solucaoFinal->perdaIndividual;
        solucaoFinal = solucaoFinal->proximo;
    }
    
    printf("\nPerda de %d u.m. de %d u.m. de materia prima utilizada \n", soma, compPadrao*qtdeBarras);
}
void atualizarDemanda(No *andarilho,int tamanho, int demandaAtendida, int *arrayDemanda)
{
    
    while(andarilho != NULL)
    {
            if(andarilho->tamanho == tamanho)
            {
               andarilho->demanda -=demandaAtendida;
               arrayDemanda[andarilho->posicao] = andarilho->demanda;
               return;
            }
            
            andarilho = andarilho->proximo;
    }
    
    printf("Erro em atualizarDemanda()! Comprimento selecionado nao existe no inventario\n");
    exit(7);
}

ResultadoBarra * concatenar(ResultadoBarra *inicio, ResultadoBarra *temp)
{
    ResultadoBarra *andarilho = inicio;
    
    if(inicio == NULL)
            return temp;
    else
    {
        while(andarilho->proximo != NULL)
            andarilho = andarilho->proximo;

        andarilho->proximo = temp;
        return inicio;
    }
    
}

void atualizarInventario(Peca *lista)
{
    No *anterior = NULL, 
       *andarilho = NULL;
  
    if(lista == NULL)
    {
        printf("Erro na funcao atualizarInventario() \nSaindo...");
        exit(4);
    }
  
    andarilho = lista->inicio;
    
    while(andarilho != NULL)
    {
        if(andarilho->demanda != 0)
        {
            anterior = andarilho;
            andarilho = andarilho->proximo;
        }
        else
        {
            if(anterior == NULL)
            {
                lista->inicio = andarilho->proximo;
                (lista->quantidade)--;
                free(andarilho);
                andarilho = lista->inicio;
            }
            else
            {
                anterior->proximo = andarilho->proximo;
                (lista->quantidade)--;
                free(andarilho);
                andarilho = anterior->proximo;
            }
        }
    }
 
 /* Faz a mesma coisa que o laço acima porém escrito de forma diferente, escolha o que for mais simples, ou aprimore-o 
    while(andarilho != NULL)
    {
        if(andarilho->demanda == 0)
        {
            if(anterior == NULL)
                lista->inicio = andarilho->proximo;
            else
                anterior->proximo = andarilho->proximo;
            
            (lista->quantidade)--;
            free(andarilho);
            
        }
        else
            anterior = andarilho;
        
        if(anterior!=NULL)
            andarilho = anterior->proximo;
        else
            andarilho = lista->inicio;
    }
*/
}
/*
float gerarAlpha(){
  float valor;
  do{
    valor = (float) (rand() % 10 )/10;
  }while( valor <= 0 || valor >= 1 );
  return valor;
}
*/
int repetirPadrao(No *inventario, int *arrayDemanda, int *arrayPadraoDeCorte, int limite)
{
    int i, repetir = 1, repeticoes = 1;
    No *andarilho = inventario;
    
    while(repetir)
    {
        //verifica se o padrao de corte ainda não atendeu a demanda ou seja repetir = 1
        for(i=0;i<limite;i++)
           if(arrayPadraoDeCorte[i] && arrayDemanda[i] == 0)
              repetir = 0;
      
        //Se o padrao de corte pode ser repetido, percorre o inventário e atualiza as demandas
        if(repetir)
        {
            andarilho = inventario;
            while(andarilho != NULL)
            {
              //Se o corte foi aplicado na barra, então sua demanda será atualizada na solucao e no inventario
              if(arrayPadraoDeCorte[andarilho->posicao])
              {
                (arrayDemanda[andarilho->posicao])--;
                (andarilho->demanda)--;
              }
               andarilho = andarilho->proximo;
            }
            repeticoes++;
        }
    }
  return repeticoes;
}

listaSolucao * construcao(Peca *padrao, float alpha, int L)
{
    Peca * inventario = criarInventario(padrao->inicio),
          *cortesPossiveis = NULL,
          *lrc = NULL;
    
    int perda,
        menorPeca,
        indiceSelecionado,
        repeticoes,
        beta,
        qtdeBarras = 0,
        i;
  
    No *escolhido = NULL;

    listaSolucao* lista = (listaSolucao *) malloc(sizeof(listaSolucao));
    lista->inicio = NULL;
    lista->alpha = alpha;
    lista->perda = 0;
    ResultadoBarra *temp = NULL;
    
    if(padrao == NULL || padrao->quantidade == 0)
    {
        printf("Quantidade invalida de itens no inventario \nSaindo...");
        exit(-1);
    }
  
    //imprimir(inventario);
    while(inventario->inicio != NULL)
    {
        perda = L;
               
        temp = (ResultadoBarra *) malloc(sizeof(ResultadoBarra));
        
        if(temp == NULL)
        {       printf("Memoria Insuficiente!\nSaindo... \n");
                exit(-2);
        }
        temp->vetorPadraoDeCorte = (int *) malloc(sizeof(int) * padrao->quantidade);
        temp->vetorDemandaResidual = (int *) malloc(sizeof(int) * padrao->quantidade);
  
        iniciarArray(temp->vetorPadraoDeCorte, padrao->quantidade);
        iniciarArray(temp->vetorDemandaResidual, padrao->quantidade);
      
        temp->sequenciaDePecasGeradas = iniciar(); 
        menorPeca = menorComprimento(inventario->inicio);
    
        cortesPossiveis = criarInventario(inventario->inicio);
      
        while(cortesPossiveis->inicio != NULL && perda >= menorPeca && menorPeca != 0)
        {
            //Define a peca de maior comprimento de acordo com a perda
            beta = maiorComprimento(cortesPossiveis->inicio, perda);
            //Os candidatos serao pecas maiores que alpha*beta e menores que a perda
            lrc = candidatosRestritos(cortesPossiveis->inicio, alpha*beta, perda);
            //Comandos responsaveis pela escolha do item a ser cortado  
            indiceSelecionado = rand() % lrc->quantidade + 1;

            escolhido = sorteio(lrc->inicio, indiceSelecionado);
            repeticoes = perda/escolhido->tamanho;
        
            //Diminui a repetição de peças a serem cortadas se ultrapassar a demanda
            while((escolhido->demanda - repeticoes)<0)
                repeticoes--;
            //Corrige o valor de repeticoes para zero, caso a peca escolhida ser obtida n vezes de perda mas nao haja demanda
            if(repeticoes < 0)
                repeticoes = 0;
            
            //Atualiza o valor restante da barra em perda
            perda -= repeticoes*escolhido->tamanho; 
            //Adiciona a quantidade de itens do tipo escolhido a ser obtido da barra
            //temp->vetorPadraoDeCorte[obterPosicao(padrao->inicio, escolhido->tamanho)] = repeticoes;
            
            temp->vetorPadraoDeCorte[escolhido->posicao] = repeticoes;
            if(repeticoes > 0)
            {
                //Adiciona item selecionado no plano de corte
                
                inserirNaLista(temp->sequenciaDePecasGeradas, escolhido->tamanho, escolhido->posicao, repeticoes);
                //Atualiza a demanda do item escolhido no inventario
                atualizarDemanda(inventario->inicio, escolhido->tamanho, repeticoes, temp->vetorDemandaResidual);
                //Descarta o produto escolhido do restante da barra a ser cortada
                apagarElemento(cortesPossiveis,escolhido);
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

listaSolucao * obterMelhores(listaSolucao *resultado[], int coluna)
{
	listaSolucao * melhor = resultado[0];
	int j;


	for(j=0;j<coluna;j++)
		if(melhor->perda > resultado[j]->perda)
			melhor = resultado[j];
		
	return melhor;
}

void GRASP( Peca *padrao, int repeticoes, int L){

    float alpha = 0.1;
    int j;
    listaSolucao *solucoesPorAlpha[10][repeticoes], *melhores[10], *melhor;

    
    for(alpha = 0.0; alpha< 1; alpha+=0.1)
    {
	printf("Perda para solucoes com o alfa (%.2f) : ", alpha);
	for(j = 0; j<repeticoes; j++)
	{
	    solucoesPorAlpha[(int)(alpha*10)][j] = construcao(padrao, alpha, L);
	    printf("%d ",solucoesPorAlpha[(int)(alpha*10)][j]->perda);
	}

	melhores[(int)(alpha*10)] = obterMelhores(*solucoesPorAlpha+((int)(alpha*10)*(repeticoes)), repeticoes);
	
	printf("\nMenor perda para alfa (%.2f) : %d \n", alpha, melhores[(int)(alpha*10)]->perda);
	
    }
    
    melhor = obterMelhores(melhores, 10);
    //Ainda nao esta otimizado para achar o melhor, se houver resultados iguas, exibe apenas o primeiro encontrado
    printf("\n\nMenor perda encontrada: %d \nCom alpha: %.2f\n", melhor->perda, melhor->alpha);
}

int main(){
 
    Peca *padrao;
    char arquivo[100];
    int repeticoes;

    padrao = iniciar();

    printf("Digite o nome do arquivo a ser lido (.txt): ");
    scanf("%s", arquivo);

    do{
    	printf("Digite a quantidade de repeticoes a cada variacao do alpha: ");
    	scanf("%d", &repeticoes);
    }while(repeticoes <= 0);

    ler(padrao, arquivo);
  
    GRASP(padrao, repeticoes,100 );
  

    return 0;
}
