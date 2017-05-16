#include "salvar_resultado.h"

void salvar_resultado(resultado_calculado calculo, sem_t *semaforo, Mem_compartida *Memoria){
	int i, contador, contador2;
	
	/********* Sección de entrada ****/
	if (sem_wait(semaforo) == -1){
		perror("Semáforo no válido");
		exit(1);
	}
	/**** Principio de la sección crítica *******/

	if (Memoria->indice == 10){                           // Si la posición a escribir es 10 significa que el arry se termino
		Memoria->indice = 0;
		for (i = 0; i < 9; i++){
			contador2=i+1;
			Memoria->ultimo_resultado[i] = Memoria->ultimo_resultado[contador2];
		}
		Memoria->ultimo_resultado[9]=0.0;
		Memoria->indice=9;
	}
	contador = Memoria->indice;

	Memoria->ultimo_resultado[contador] = calculo.resultado_final;
	Memoria->indice = contador + 1;

	/********** Fin de la sección crítica *******/
	/*********** Sección de salida ************/
	if (sem_post(semaforo) == -1){
		perror("Semáforo no válido");
		exit(1);
	}
	/********* Sección Restante ************/
}
