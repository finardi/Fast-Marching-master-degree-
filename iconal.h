/*........................... :::BIBLIOTECAS::: ..............................*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*............................. :::MACROS::: .................................*/

#define MIN(a,b) (a < b) ? (a) : (b);
#define NULO 0
#define INF (double)exp(10000)
#define INICIA_INF INF
#define RAIZ_HEAP	1
#define F_1(k) 2*k
#define PAI(k) k/2
#define NRO_VIZ 4

/*........................... :::ESTRUTURAS:::	..............................*/

typedef enum {fantasma, ativo, narrow_band, far_away} Tipo;

typedef struct item {
					double	valor, velocidade;
					Tipo		rotulo;
					int			indice;
				} Item;

typedef struct fronteira {
					int	   	tamanho;
					double 	*dados;
				} Fronteira;

/*......................... :::VARIÁVEIS GLOBAIS::: ..........................*/

int	  tam_heap, n1, n1o, n2, n2o, viz[NRO_VIZ];
float d1, d2, o1, o2;
Item		*grid, **heap;
double		h, *velocidade, *solucao;
Fronteira	front;

/*.............................. :::FUNÇÕES::: ...............................*/

void iconalInit(int n1_o, int n2_o, float d1_, float d2_,
                      float o1_, float o2_,
                      double *vel, int ns,
                      float *x_fonte, float *y_fonte, float *amp);
void	fast_marching();
void	config_fonte();
void	config_narrow_band();
void	config_viz(Item *ptr);
void	iconal(Item *ptr);
Item*	remove_heap();
void	insere_heap(Item *ptr);
void	retorna_heap(Item *ptr);
void	inicializa(double valor, Tipo rotulo);
void	armazena_solucao();
