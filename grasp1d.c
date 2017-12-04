#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tipo_corte{
  int tamanho;
  int demanda;
  int posicao;
  struct tipo_corte *proximo;
};
typedef struct tipo_corte No;

struct inicio{
  struct tipo_corte *inicio;
  int quantidade;
};
typedef struct inicio Corte;

typedef struct solucao{
    Corte * solucaoIndividual;
    int * padraoDeCorte;
    int * demandaResidual;
    int repeticoes;
    int perda;
    struct solucao *proximo;
} Solucao;

Corte* iniciar(){
  Corte *padrao;
  padrao = (Corte*)malloc(sizeof(Corte));
  padrao->inicio = NULL;
  padrao->quantidade = 0;
  return padrao;
}

void apagarLista( Corte *lista ){
  No *aux, *atual;
  Corte *temp;
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

void apagarElemento(Corte *lista, No *elemento)
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

void inserirNaLista( Corte *padrao, int valor, int posicao, int demanda ){
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
  }
}


void inserirNaListaExtend( Corte *padrao, int valor, int posicao, int demanda ){
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


void ler( Corte *padrao, char documento[100] ){
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

void imprimir( Corte *padrao ){
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

Corte* criarInventario(No *andarilho)
{
    Corte * copia = NULL;
  
    if(andarilho == NULL)
    {
        printf("Padrao Inexistente.Necessario definir um padrao \nSaindo...");
        exit(1);
    }
  
    copia = iniciar();
    
    while(andarilho != NULL)
    {
        inserirNaListaExtend(copia, andarilho->tamanho, andarilho->posicao, andarilho->demanda);
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
Corte * candidatosRestritos(No *andarilho, float fator, int perda)
{
    Corte *lista = iniciar();

    while(andarilho != NULL)
    {
        if(andarilho->tamanho >= fator && andarilho->tamanho <= perda){
          inserirNaListaExtend(lista, andarilho->tamanho, andarilho->posicao, andarilho->demanda);
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

void escreverSolucao(Solucao *solucaoFinal,int itens, int compPadrao)
{
    int qtdeBarras = 0, i = 0, soma = 0;
    No *andarilho;
    char c;
    
    while(solucaoFinal != NULL)
    {
        printf("\nBarra %d \n", ++qtdeBarras);
        printf("Padrao = [");
        for(i=0;i<itens;i++)
            printf(" %d%c",solucaoFinal->padraoDeCorte[i], (i == itens-1)?(' '):(';'));
        printf("] ^t \nPlano de corte utilizado: {");

        andarilho = solucaoFinal->solucaoIndividual->inicio;
        
        while(andarilho != NULL)
        {
            printf(" %d%c", andarilho->tamanho, c = (andarilho->proximo == NULL)?(' '):(';'));
            andarilho = andarilho->proximo;
        }
        printf("}\n");
        printf("Repeticoes: %d \n",solucaoFinal->repeticoes);
        printf("Perda: %d \n", solucaoFinal->perda);
        soma += solucaoFinal->perda;
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

Solucao * concatenar(Solucao *inicio, Solucao *temp)
{
    Solucao *andarilho = inicio;
    
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

void atualizarInventario(Corte *lista)
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

float gerarAlpha(){
  float valor;
  do{
    valor = (float) (rand() % 10 )/10;
  }while( valor <= 0 || valor >= 1 );
  return valor;
}
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

void construcao(Corte *padrao, float alpha, int L)
{
    Corte * inventario = criarInventario(padrao->inicio),
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
    
    Solucao *inicio = NULL,
            *temp = NULL;
  
    printf("\nAlpha: %.2f\n\n", alpha);  
    if(padrao == NULL || padrao->quantidade == 0)
    {
        printf("Quantidade invalida de itens no inventario \nSaindo...");
        exit(-1);
    }
  
    imprimir(inventario);
    while(inventario->inicio != NULL)
    {
        perda = L;
               
        temp = (Solucao *) malloc(sizeof(Solucao));
        
        if(temp == NULL)
        {       printf("Memoria Insuficiente!\nSaindo... \n");
                exit(-2);
        }
        temp->padraoDeCorte = (int *) malloc(sizeof(int) * padrao->quantidade);
        temp->demandaResidual = (int *) malloc(sizeof(int) * padrao->quantidade);
  
        iniciarArray(temp->padraoDeCorte, padrao->quantidade);
        iniciarArray(temp->demandaResidual, padrao->quantidade);
      
        temp->solucaoIndividual = iniciar(); 
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
            //temp->padraoDeCorte[obterPosicao(padrao->inicio, escolhido->tamanho)] = repeticoes;
            
            temp->padraoDeCorte[escolhido->posicao] = repeticoes;
            if(repeticoes > 0)
            {
                //Adiciona item selecionado no plano de corte
                
                inserirNaListaExtend(temp->solucaoIndividual, escolhido->tamanho, escolhido->posicao, repeticoes);
                //Atualiza a demanda do item escolhido no inventario
                atualizarDemanda(inventario->inicio, escolhido->tamanho, repeticoes, temp->demandaResidual);
                //Descarta o produto escolhido do restante da barra a ser cortada
                apagarElemento(cortesPossiveis,escolhido);
            }
        
            //Necessario redefinir a menor peça caso já descartada
            menorPeca = menorComprimento(cortesPossiveis->inicio);

            //Limpa as estruturas para a próxima iteração
            escolhido = NULL;
            apagarLista(lrc);
        }
      
        temp->repeticoes = repetirPadrao(inventario->inicio, temp->demandaResidual, temp->padraoDeCorte, padrao->quantidade); 
        qtdeBarras++;
        temp->perda = perda;
        temp->proximo = NULL;
        
        inicio = concatenar(inicio,temp);
        atualizarInventario(inventario);
        apagarLista(cortesPossiveis);
    }
    printf("\n%d barras utilizadas \n", qtdeBarras);
    escreverSolucao(inicio, padrao->quantidade, L);
}

void GRASP( Corte *padrao, float alpha, int L){
    construcao(padrao, gerarAlpha(), L);
}

int main(){
    float alpha;
    Corte *padrao;
    char arquivo[100];

    padrao = iniciar();

    printf("Digite o nome do arquivo a ser lido (.txt): ");
    scanf("%s", arquivo);
    
    ler(padrao, arquivo);
  
    GRASP( padrao, gerarAlpha(), 100 );
  

    return 0;
}
