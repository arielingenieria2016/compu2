#ifndef PARIMPAR_H
#define	PARIMPAR_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <semaphore.h>

#define SEM_PATH  "/sempath"

	typedef struct Memoria_compartida{  //Estructura de la memoria compartida
        int valor;
    } Mem_compartida;

#ifdef	__cplusplus
}
#endif

#endif
