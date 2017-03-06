#include "lector.h"

void *lector(void *arg) {

	extern int dato; // dato inicial
	extern int punteroInicial;
	extern int datoGuardado[2];
	extern long int idThreadLector[2];
	
	pthread_mutex_lock(&(*(params_Leer*) (arg)).mlectores);
		int i = punteroInicial;
		idThreadLector[i]=(unsigned long)pthread_self();
		dato = dato + 2;
		datoGuardado[i]=dato;
		punteroInicial= punteroInicial+1;
 	pthread_mutex_unlock(&(*(params_Leer*) (arg)).mlectores);
	pthread_cond_signal(&(*(params_Leer*)(arg)).done);
	pthread_exit(NULL);

}
