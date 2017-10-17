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

struct escolha{
  int valor;
  struct escolha *proximo;
};
typedef struct escolha R;

struct conjunto{
	R *inicio;
	int quantidade;
};
typedef struct conjunto Conjunto;

Corte* iniciar(){
  Corte *padrao;
  padrao = (Corte*)malloc(sizeof(Corte));
  padrao->inicio = NULL;
  padrao->quantidade = 0;
  return padrao;
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
    atual = padrao->inicio;
    while( atual != NULL ){
      printf("%d ", atual->tamanho);
      atual = atual->proximo;
    }
    printf("\n\n");
  }
}

float gerarAlpha(){
  float valor;
  do{
    valor = (float) (rand() % 10 )/10;
  }while( valor <= 0 || valor >= 1 );
  return valor;
}

//
void escreverSaida( char *documento, int *demanda, int tamanho, float alpha, int perda){
  int i;
  FILE *arquivo = fopen( documento, "a");
  if( arquivo == NULL ){
    printf("Não possível abrir o arquivo!\n\n");
  }
  else{
    for( i = 0; i < tamanho; i++ ){
      fprintf(arquivo, "%d ", demanda[i]);
    }
    fprintf(arquivo, "\nAlpha: %.2f\n", alpha);
    fprintf(arquivo, "Perda: %d\n", perda);
  }  
  fclose(arquivo);
}

void iniciarArray( int *array, int tamanho ){
  int i;
  for( i = 0; i < tamanho; i++ )
    array[i] = 0;
}

void inserirConjuntoR(Conjunto *conjunto, int valor){
	R *no, *atual;
	no = (R*)malloc(sizeof(R));
	no->valor = valor;
	no->proximo = NULL;
	
	if( conjunto->inicio == NULL )
		conjunto->inicio = no;
	else{
		atual = conjunto->inicio;
		while( atual->proximo != NULL )
			atual = atual->proximo;
		atual->proximo = no;
	}
	conjunto->quantidade += 1;
}

int retornaMelhorR( Conjunto *conjunto ){
	R *atual = conjunto->inicio;
	while( atual->proximo != NULL ){
		atual = atual->proximo;
	}
	return atual->valor;
}

void limparR( Conjunto *conjunto ){
	R* atual, *aux;
	if( conjunto != NULL ){
    	atual = conjunto->inicio;
	    while( atual != NULL ){
      		aux = atual;
      		atual = atual->proximo;
      		free(aux);
    	}
	}
}

void apagarK( Conjunto *r, int K ){
	R *atual = r->inicio;
	R *anterior = NULL;
	if( r->inicio != NULL){
		while( atual->valor != K && atual->proximo != NULL ){
			anterior = atual;
			atual = atual->proximo;
		}
		if( anterior == NULL )
			r->inicio = atual->proximo;
		else
			anterior->proximo = atual->proximo;
		free( atual );
		r->quantidade--;
	}
}

int RandonR( Conjunto *r ){
	int posicao;
	int i = 1;
	R* atual;

	if( r->inicio == NULL )
		return 0;
	posicao = rand() % r->quantidade;
	atual = r->inicio;

	while( i <= posicao && atual != NULL ){
		atual = atual->proximo;
		i++;
	}
	return atual->valor;
}

No* procuraNoLista( Corte *padrao, int valor ){
	No *atual = padrao->inicio;
	while( atual != NULL && atual->tamanho != valor )
		atual = atual->proximo;
	return atual;
}

Conjunto* iniciarR(){
	Conjunto *conjuntoR = (Conjunto*)malloc(sizeof(Conjunto));
  	conjuntoR->inicio = NULL;
  	conjuntoR->quantidade = 0;
  	return conjuntoR;
}

void fazerCopia( Corte *padrao, Corte *auxiliar ){
	No *novo, *atual1, *atual2;
	if( padrao != NULL && auxiliar != NULL ){
		atual1 = padrao->inicio;
		while( atual1 != NULL ){
			novo = (No*)malloc(sizeof(No));
			novo->tamanho = atual1->tamanho;
			novo->posicao = atual1->posicao;
			novo->demanda = atual1->demanda;
			novo->proximo = NULL;
			if( auxiliar->inicio == NULL ){
				auxiliar->inicio = novo;
				atual2 = auxiliar->inicio;
			}
			else{
				atual2->proximo = novo;
				atual2 = atual2->proximo;
			}
			atual1 = atual1->proximo;
		}
	}
}

No* buscaMenorItem( Corte *auxiliar ){
	No *atual;
	if( auxiliar != NULL ){
		atual = auxiliar->inicio;
		while( atual->proximo != NULL )
			atual = atual->proximo;
		return atual;
	}
	return NULL;
}

int calcularRestante( Corte *auxiliar ){
	No *atual;
	int somador = 0;
	if( auxiliar != NULL ){
		atual = auxiliar->inicio;
		while( atual != NULL ){
			somador += atual->demanda * atual->tamanho;
			atual = atual->proximo;
		}
		return somador;
	}
	return -1;
}

void GRASP( Corte *padrao, float alpha, int L ){
  int N, S[padrao->quantidade], perda, beta, K, perdaV; 
  Corte *auxCorte = iniciar();
  fazerCopia( padrao, auxCorte );

  No *atual, *auxiliar, *menorItem;
  Conjunto *conjuntoR = iniciarR();
  R* aux;
  
  N = padrao->quantidade;
  
  iniciarArray( S, padrao->quantidade);
  
  perda = L;
  perdaV = L;
  menorItem = buscaMenorItem( auxCorte );
  beta = padrao->inicio->tamanho;
  atual = auxCorte->inicio;

//colocar uma variável para ter o menor item disponível para a soluçao
//escrever a solução e criar um vetor para a mesma

//for( i = 0; i < padrao->quantidade; i++ )
  while( atual != NULL ){
   	while( atual != NULL && (alpha*beta) <= atual->tamanho ){
   	
	   		inserirConjuntoR( conjuntoR, atual->tamanho );
	   		atual->demanda--;
	   		perdaV -= atual->tamanho;
	   	
			atual = atual->proximo;
    }

    while( conjuntoR->inicio != NULL ){
    	aux = conjuntoR->inicio;
    	while( aux != NULL ){
    		printf("%d ", aux->valor );
    		aux = aux->proximo;
    	}
    	printf("\n");

	    K = RandonR( conjuntoR );
	  
	    if( K <= perda ){
	    	
    		auxiliar = procuraNoLista( padrao, K );
    		if(auxiliar->demanda != 0){
    			auxiliar->demanda -= 1;
	    		S[auxiliar->posicao] += 1;
	    		perda -= auxiliar->tamanho;
	    	}
    	}
    	apagarK( conjuntoR, K );
    }
    if( atual == NULL ){
    	break;
	}
    while( atual->proximo != NULL && atual->proximo->tamanho > perda )
    	atual = atual->proximo;
    
    beta = atual->tamanho;
  }
  printf("\nRestante a ser produzido: %d\n\n", calcularRestante(auxCorte));
  escreverSaida( "saida.txt", S, padrao->quantidade, alpha, perda );
}

int main(){
  float alpha;
  int x;
  Corte *padrao;
  char arquivo[100];

  padrao = iniciar();
  
  srand(time(NULL));
  ler(padrao, "cortes.txt");
  //imprimir(padrao);
  
  do{
    GRASP( padrao, gerarAlpha(), 100 );
    printf("Deseja repetir o processo: ");
    scanf("%d", &x);
  }while( x != 0 );

  return 0;
}