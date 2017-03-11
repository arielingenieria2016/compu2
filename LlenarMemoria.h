#ifndef LLENARMEMORIA_H
#define	LLENARMEMORIA_H

#ifdef	__cplusplus
extern "C" {
#endif

	#include "controlador.h"

	void LlenarMemoria(Mem_compartida ParImpar, sem_t *sem1, Mem_compartida *Memoria);

#ifdef	__cplusplus
}
#endif

#endif
