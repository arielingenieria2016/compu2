#include "funcion_f.h"
#include <string.h>

double f(double x, int tipo){
	double y=0;
	if(tipo==0){
		y= (x*x)-0;
		return y;
	}else if(tipo==1){
		y= (x*x)-1;
		return y;
	}else if(tipo==2){
		y= (x*x)-2;
		return y;
	}else if(tipo==3){
		y= (x*x)-3;
		return y;
	}else if(tipo==4){
		y= (x*x)-4;
		return y;
	}else if(tipo==5){
		y= (x*x)-5;
		return y;
	}else if(tipo==6){
		y= (x*x)-6;
		return y;
	}else if(tipo==7){
		y= (x*x)-7;
		return y;
	}else if(tipo==8){
		y= (x*x)-8;
		return y;
	}else if(tipo==9){
		y= (x*x)-9;
		return y;
	}
	return y;
}
