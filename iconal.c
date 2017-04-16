#include "iconal.h"

/*........................... :::DISCRETIZAÇÃO::: ............................*/

void iconal(Item *ptr) {
  long double T_1, T_2, V, t, d, min;
    V = ptr->velocidade;
    t = ptr->valor;
	  T_1 = MIN((ptr + viz[0])->valor, (ptr + viz[1])->valor);
    T_2 = MIN((ptr + viz[2])->valor, (ptr + viz[3])->valor);
	  min = MIN(T_1, T_2);

    (T_1 >= T_2) ? (d = T_1 - T_2) : (d = T_2 - T_1);

    V = h/V;

    if(d < V ){
      t = (T_1 + T_2 + sqrt(2*(V*V) - (d*d))) / 2;
    }else{
      t = min + V;
    }

    ptr->valor = MIN(ptr->valor, t);
}
