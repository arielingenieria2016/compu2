#ifndef RESULTADO_NEWTON_H
#define	RESULTADO_NEWTON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include "controlador.h"


#define LINEMAX 384

    void resultado_newton(int sd_conn, char *funcion, char met, params_Newton result);

#ifdef	__cplusplus
}
#endif

#endif	/* RESULTADO_NEWTON_H */
