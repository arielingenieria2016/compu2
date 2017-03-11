#include "LlenarMemoria.h"

void LlenarMemoria(Mem_compartida ParImpar, sem_t *sem1, Mem_compartida *Memoria){
	
	sem_wait (sem1);
	
	Memoria->valor=ParImpar.valor;

    printf("\nValor en memoria compartida: %d \n", Memoria->valor);

	sem_post (sem1);

}
