#include <assert.h>
#include "iconal.h"

void cria_malha(int i1, int i2){
  Item *ptr;
  ptr         = grid + i2*(n1) + i1;
  ptr->valor  = INICIA_INF;
  ptr->rotulo = fantasma;
}

void iconalInit(int n1_o, int n2_o, float d1_, float d2_, float o1_, float o2_,
                double *vel, int ns, float *x_fonte, float *y_fonte, float *amp){
	n1  = n1_o + 2;         /* n1 é o n_global (n1_o) + 2  */
  n2  = n2_o + 2;         /* n2 é o n_global (n2_o) + 2  */
  n1o = n1_o;             /* n1o é o n_global (n1_o)     */
  n2o = n2_o;             /* n1o é o n_global (n1_o)     */
  d1  = d1_;              /* comprimento do índice x     */
  d2  = d2_;              /* comprimento do índice y     */
  o1  = o1_;              /* origem do índice x          */
  o2  = o2_;              /* origem do índice y          */

	front.tamanho = ns; /* ns é o índice da fonte  */
	front.dados = calloc(30*ns, sizeof(double));

  for(int c = 0; c < ns; c++) {
    const int k = 3*c;
    front.dados[k+0] = (int)(x_fonte[c]-o1)/d1;
    front.dados[k+1] = (int)(y_fonte[c]-o2)/d2;
	  front.dados[k+2] = (int)amp[c];
  }

	velocidade = calloc(10*(n1o*n2o), sizeof(double));
	solucao    = calloc(10*(n1*n2), sizeof(double));
	memcpy(velocidade, vel, sizeof(double)*n1o*n2o);
}

void inicializa(double valor, Tipo rotulo){
  int contador = 0;
  Item malha;
  malha.valor  = valor;
  malha.rotulo = rotulo;
  malha.indice = NULO;

  tam_heap = NULO;
  viz[0] = -1;
  viz[1] = 1;
  viz[2] = -(n1);
  viz[3] = (n1);

heap = (Item **)calloc(10*(n1+n2), sizeof(Item*));

for(int k = 0; k < 10*(n1+n2); ++k)
  heap[k] = NULO;

grid = (Item *)calloc(10*n1*n2, sizeof(Item));

for(int k = 0; k < (n1*n2); ++k)
  grid[k] = malha;

for(int i1 = 0; i1 < n1; ++i1){
  cria_malha(i1, 0);
  cria_malha(i1, (n2-1));
}
for(int i2 = 0; i2 < n2; ++i2){
  cria_malha(0, i2);
  cria_malha((n1-1), i2);
}

  for(int i2 = 1; i2 <= n2o; ++i2){
    for (int i1 = 1; i1 <= n1o; ++i1){
      grid[i2*n1 + i1].velocidade = velocidade[contador++];
  // printf("velocidade (%d,%d; %d) = %f \n", i1, i2, i2*n1 + i1, grid[i2*n1 + i1].velocidade);
    }
  }
}

void fast_marching(){
  inicializa(INF, far_away);
	config_fonte();
  while (tam_heap >= RAIZ_HEAP)
    config_narrow_band();
  armazena_solucao();
}

void config_fonte(void){
  Item *ptr;
  for(int c = 0; c < front.tamanho; ++c){
    const int k = c*3;
  	ptr = grid + (int)(front.dados[(k+1)]*n1 + front.dados[k]);
    ptr->valor = (int)(front.dados[k+2]);
    insere_heap(ptr);
	}
}

void config_narrow_band(){
	Item *ptr;
  ptr = remove_heap();
  ptr->rotulo = ativo;
	config_viz(ptr);
}

void config_viz(Item *ptr_nb){
	  Item *ptr;
	  for(int k = 0; k < NRO_VIZ; ++k){
       ptr = ptr_nb + viz[k];
       if (ptr->rotulo > ativo){
         iconal(ptr);
         if (ptr->rotulo == far_away){
           ptr->rotulo = narrow_band;
           insere_heap(ptr);
       }
     }
   }
}

void armazena_solucao(){

  int contador = 0;
  for(int i2 = 1; i2 <= n2o; ++i2){
    for(int i1 = 1; i1<= n1o; ++i1){
      solucao[contador++] = (long double)grid[i2*n1 + i1].valor;
      printf("Solução: (%d, %d, %d) = %lf\a\n", i1, i2, i2*n1 + i1, grid[i2*n1 + i1].valor);
    }
  }
  free(heap);
  free(grid);
}
