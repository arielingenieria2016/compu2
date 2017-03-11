#ifndef CERRARPROGRAMA_H
#define	CERRARPROGRAMA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/shm.h>

#define SEM_PATH  "/sempath"

#include "controlador.h"

extern sem_t *sem1;
extern int Id_Memoria;
extern Mem_compartida *Memoria;

void cerrarPrograma(int num);

#ifdef	__cplusplus
}
#endif

#endif
