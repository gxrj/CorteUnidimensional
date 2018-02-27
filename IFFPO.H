struct tipo_peca{
  int tamanho;
  int demanda;
  int posicao;
  struct tipo_peca *proximo;
};  typedef struct tipo_peca Peca;

struct inicio{
  struct tipo_peca *inicio;
  int quantidade;
};  typedef struct inicio ListaDePecasObtidas;

typedef struct solucao{
    ListaDePecasObtidas * pecasObtidas;
    int * vetorPadraoDeCorte;
    int * vetorDemandaResidual;
    int repeticoes;
    int perdaIndividual;
    struct solucao *proximo;
} EsquemaDeCorte;

typedef struct{
  int barrasUtilizadas;
  int perda;
  float alpha;
  EsquemaDeCorte *inicio;
}listaSolucao;

ListaDePecasObtidas* iniciar(void);
void apagarLista( ListaDePecasObtidas * );
void apagarPeca(ListaDePecasObtidas  *, Peca *);
void inserirNaLista( ListaDePecasObtidas  *, int, int, int );
void ler( ListaDePecasObtidas  *, char[100] );
void imprimir( ListaDePecasObtidas  * );
void iniciarArray( int *, int );
ListaDePecasObtidas * criarInventario( Peca * );
int menorComprimento( Peca * );
int maiorComprimento( Peca *, int );
ListaDePecasObtidas * candidatosRestritos( Peca *, float, int );
Peca * sortearLRC( Peca *, int );
void escreverSolucao(EsquemaDeCorte *,int , int );
void escreverSolucaoTexto(char *, EsquemaDeCorte *,int , int , float, int);
void atualizarDemanda( Peca *,int , int , int *);
EsquemaDeCorte * concatenar(EsquemaDeCorte *, EsquemaDeCorte *);
void atualizarInventario(ListaDePecasObtidas  *);
int repetirPadrao(Peca *, int *, int *, int );
listaSolucao * construcao(ListaDePecasObtidas  *, float , int );
listaSolucao * obterMelhores(listaSolucao *[], int );
void melhoria( EsquemaDeCorte *, int, int, int);
void obterEsquemas(EsquemaDeCorte *, EsquemaDeCorte *, EsquemaDeCorte *, EsquemaDeCorte *, EsquemaDeCorte *, int);
EsquemaDeCorte * copiarEsquema( EsquemaDeCorte *, int);
void copiarArray(int *, int *, int);
void GRASP( ListaDePecasObtidas  *, int , int );
