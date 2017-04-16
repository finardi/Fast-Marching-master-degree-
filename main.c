#include <assert.h>
#include "iconal.h"

void salva_teste(int n1, int n2, double *solucao, double *velocidade){
	float *sol = calloc(10*n1*n2, sizeof(float));

	/* se não for quadrado, altere */
  for(int i = 0; i < n1*n2; ++i)
		sol[i] = (float)solucao[i];

	FILE *fp;
  fp = fopen("iconal_fin2.bin", "wb");
	/* se não for quadrado, altere */
  fwrite(sol, sizeof(float), n1*n2, fp);
  fclose(fp);

  float *v = calloc(100*n1*n2, sizeof(float));

	/* se não for quadrado, altere */
	for(int i = 0; i < n1*n2; ++i)
		v[i] = (float)velocidade[i];

  FILE *fp1;
  fp1 = fopen("vel_fin.bin", "wb");
	/* se não for quadrado, altere */
  fwrite(v, sizeof(float), n1*n2, fp1);
  fclose(fp1);

	free(sol);
	free(v);
}
double* lerbinario(char *f_name, int n1, int n2) {
		FILE *fp = fopen(f_name, "rb");
	  float *t = malloc(n1*n2*sizeof(float));
		assert(t != NULL);
		fread(t, sizeof(float),n1*n2, fp);
		double *tmp = malloc(n1*n2*sizeof(double));

		for(size_t i = 0; i <n1*n2; i++)
			tmp[i] = (double)t[i];
		free(t);

		return tmp;
}

int main() {
  unsigned const int n = 1000;
	h = 1;
	/* se não for quadrado, altere */
  double *vel = calloc(n*n, sizeof(double));

	for(int i = 0; i < n*n; i++)
		vel[i] = 1;

	const float d1 = 1.0;
	const float d2 = 1.0;
	const float o1 = 0.0;
	const float o2 = 0.0;
	float *s1 = malloc(10*sizeof(float));
	float *s2 = malloc(10*sizeof(float));
	float *t0 = malloc(10*sizeof(float));

	s1[0] = 1;
	s2[0] = 1;

	t0[0] = 0.0;

	iconalInit(n, n, d1, d2, o1, o2, vel, 1, s1, s2, t0);

	free(s1);
	free(s2);
	free(t0);

  fast_marching();
  salva_teste(n, n, solucao, velocidade);
	free(vel);
  return 0;
}
