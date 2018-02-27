/*
    -Obtém do usuário o nome do arquivo a ser lido,
    -Obtém a quantidade de repetições que um corte deve ser aplicado, para gerar possíveis esquemas de corte diferentes,
    -Aplica o GRASP e contabiliza o tempo de execução
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "IFFPO.H"

int main(){
 
    ListaDePecasObtidas *padrao;
    char arquivo[100];
    int repeticoes;
    clock_t start, end;

    padrao = iniciar();

    printf("Digite o nome do arquivo a ser lido (.txt): ");
    scanf("%s", arquivo);

    do{
      printf("Digite a quantidade de repeticoes a cada variacao do alpha: ");
      scanf("%d", &repeticoes);
    }while(repeticoes <= 0);

    start = clock();
      ler(padrao, arquivo);  
      GRASP(padrao, repeticoes, 100 );
    end = clock();

    printf("Tempo de execução: %.2f\n\n", (double)( end - start ) / ((double)CLOCKS_PER_SEC ));
    return 0;
}
