#ifndef CONTROLADOR_H
#define	CONTROLADOR_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <semaphore.h>

#define RES_LEN 256

    struct sockaddr *cli_addr;

    typedef struct http_req { //Estructura que contiene el parseo del request HTTP
        char method[6];
        char url[RES_LEN];
        char ver[10];
    } http_req_t;

    extern http_req_t req;

	typedef struct newton { //Estructura de la funcion newton
		char func[10];
		long double xo,eps;
		long max_iter;
		long double resultado;
		int tipo;
	} params_Newton;

	typedef struct leer { //Estructura de la funcion con mutex
		pthread_mutex_t mlectores;
		pthread_cond_t done;
	} params_Leer;

	extern params_Leer leer;

	typedef struct met_it { //Estructura que contiene el calculo a realizar y las iteraciones
        char funcion[10];
        char met;
    } met_it_t;

	met_it_t met_it;

    void controlador(int sd_conn, struct sockaddr *cli_addr);

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLADOR_H */

