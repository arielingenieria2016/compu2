#ifndef RESULTADO_MUTEX_H
#define	RESULTADO_MUTEX_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include "controlador.h"


#define LINEMAX 384

    void resultado_mutex(int sd_conn, char met, int *datoGuardado, long int *idThreadLector);

#ifdef	__cplusplus
}
#endif

#endif	/* RESULTADO_MUTEX_H */
