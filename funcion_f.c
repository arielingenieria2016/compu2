#include "funcion_f.h"
#include <string.h>

double f(double x, int tipo){
	double y=0;
	if (tipo==1){
		y= (x*x)-3;
		return y;
	}else if(tipo==2){
		y= (x*x)-2;
		return y;
	}else if(tipo==3){
		y= (x*x)-4;
		return y;
	}
	return y;
}
