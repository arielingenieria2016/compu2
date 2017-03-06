#include "f_prima.h"
#include "funcion_f.h"

double fprima(double x, int tipo){
	double h = 1E-8;
	return (f(x+h, tipo)-f(x, tipo))/h;
}
