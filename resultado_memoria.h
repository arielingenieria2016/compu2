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

    void resultado_memoria(int sd_conn, char met, Mem_compartida *Memoria);

#ifdef	__cplusplus
}
#endif

#endif
