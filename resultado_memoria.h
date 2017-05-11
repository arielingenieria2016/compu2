#ifndef RESULTADO_MEMORIA_H
#define	RESULTADO_MEMORIA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "controlador.h"

#define LINEMAX 384

    void resultado_memoria(int sd_conn, met_it_t met_it, Mem_compartida *Memoria, params_Newton result, long double valor);

#ifdef	__cplusplus
}
#endif

#endif
