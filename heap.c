#include "iconal.h"

/* -----------------------------------sobe_heap------------------------------ */
void sobe_heap(int ind) {
	int k;
	Item *ptr;
	k = PAI(ind);
	ptr = heap[ind];

	while(k >= RAIZ_HEAP){
		if(ptr->valor >= heap[k]->valor)
			break;
		heap[ind] = heap[k];
		ptr->indice = ind;
		ind = k;
		k = PAI(ind);
	}

	heap[ind] = ptr;
	ptr->indice = ind;
}

/* ---------------------------------insere_heap------------------------------ */
void insere_heap(Item *ptr){
	++tam_heap;
	heap[tam_heap] = ptr;
	sobe_heap(tam_heap);
}

/* ---------------------------------desce_heap------------------------------- */
void desce_heap(int ind){
	int k;
	Item *ptr;
	k = F_1(ind);
	ptr = heap[ind];

	while(k <= tam_heap){
		if(k < tam_heap && (heap[k + 1]->valor < heap[k]->valor))
			k++;
		if(ptr->valor <= heap[k]->valor)
			break;
		heap[ind] = heap[k];
		ptr->indice = ind;
		ind = k;
		k = F_1(ind);
	}
	heap[ind] = ptr;
	ptr->indice = ind;
}

/* ---------------------------------remove_heap------------------------------ */
Item* remove_heap() {
	Item *ptr;
	ptr = heap[RAIZ_HEAP];
	heap[RAIZ_HEAP] = heap[tam_heap];
	--tam_heap;

desce_heap(RAIZ_HEAP);

	return ptr;
}
