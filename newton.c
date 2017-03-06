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
	
	while(abs_(f(x, tipo))>=(p->eps) && iter<=(p->max_iter)){
		x = x - (f(x, tipo)/fprima(x, tipo));
		iter = iter + 1;
	}
	p->resultado = x;
	
	pthread_exit(NULL);
}
