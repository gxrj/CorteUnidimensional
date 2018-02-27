/*
    -Lê a quantidade de pecas na primeira linha do arquivo,
    -armazena essa quantidade na variável tamanho,
    -lê o valor e a demanda de cada linha e insere os valores na lista de pecas "padrao" através do procedimento inserirNaLista()
    -após inserir todos os valores pelo loop ,atribuí a quantidade de pecas inseridas através da variável tamanho   
*/

#include <stdio.h>
#include "IFFPO.H"

void ler( ListaDePecasObtidas *padrao, char documento[100] ){
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
