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
#include <float.h>
#include <math.h>
#include <sys/shm.h>
#include <semaphore.h>

#define RES_LEN 256

    struct sockaddr *cli_addr;

    typedef struct http_req { //Estructura que contiene el parseo del request HTTP
        char method[6];
        char url[RES_LEN];
        char ver[10];
    } http_req_t;

	typedef struct newton { //Estructura de la funcion newton
		char func[10];
		long double xo,eps;
		long max_iter;
		long double resultado;
		int tipo;
	} params_Newton;

	typedef struct simpson { //Estructura de la funcion con mutex
		pthread_mutex_t mutex;
		pthread_cond_t done;
		unsigned long long int coef;
        int thr_id;
        long double h;
		int integral;
	} params_Simpson;

	typedef struct met_it { //Estructura que contiene el calculo a realizar y las iteraciones
        char funcion[10];
        char met;
		unsigned long long int it;
		int integral;
		int newton;
    } met_it_t;

	typedef struct resultado { //Estructura que contiene el los distintos posibles resultados de los cálculos
        long double resultado_final;
        int tipo;
    } resultado_calculado;

	typedef struct Memoria_compartida{  //Estructura de la memoria compartida
        long double ultimo_resultado[10];
      	int indice;
    } Mem_compartida;

    void controlador(int sd_conn, struct sockaddr *cli_addr, Mem_compartida *Memoria, sem_t *semaforo);

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLADOR_H */

