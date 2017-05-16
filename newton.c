#include "funcion_f.h"
#include "newton.h"
#include "f_prima.h"
#include "absoluto.h"
#include <string.h>
#include "controlador.h"

void *newton(void *args){
	long iter = 0;
	params_Newton *p = (params_Newton *)args;
	int tipo=(p->tipo);
	double x = (p->xo);
	
    /*hasta que sea mayor el resultado de la funcion que el eps(tolerancia de error) y menor las iteraciones que el maximo establecido */
	while(abs_(f(x, tipo))>=(p->eps) && iter<=(p->max_iter)){
		printf("\nResultado: %.14f \n", f(x, tipo));
		x = x - (f(x, tipo)/fprima(x, tipo));
		iter = iter + 1;
	}
	p->resultado = x;
	
	pthread_exit(NULL);
}
