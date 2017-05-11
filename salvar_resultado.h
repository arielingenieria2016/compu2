#ifndef SALVAR_RESULTADO_H
#define	SALVAR_RESULTADO_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "controlador.h"

	void salvar_resultado(resultado_calculado calculo, sem_t *semaforo, Mem_compartida *Memoria);

#ifdef	__cplusplus
}
#endif

#endif
