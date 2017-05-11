#include "simpson.h"

void *simp(void *arg) {
	
	unsigned long long int coef = (*(params_Simpson*) (arg)).coef;

    int id, i, ini, j, integral;
    id = (*(params_Simpson*) (arg)).thr_id;
    extern long double suma;
    long double x = 0.0;
    long double aux = 0.0;
	long double h = (*(params_Simpson*) (arg)).h;
	integral = (*(params_Simpson*) (arg)).integral;

    ini = (coef * (id - 1)) + 1;
    j = coef * (id);

    for (i = ini; i <= j; i++) {
        x = h * ((long double) i - 0.5);
        aux = aux + (integral / (1 + x * x));
    }

	pthread_mutex_lock(&(*(params_Simpson*) (arg)).mutex);
		suma = suma + aux;
 	pthread_mutex_unlock(&(*(params_Simpson*)(arg)).mutex);
	pthread_cond_signal(&(*(params_Simpson*)(arg)).done);

	printf("Hilo: %d (%d - %d)\nResultado Parcial: %Lf\n\n", id, ini, j, aux);
	pthread_exit(NULL);

}
