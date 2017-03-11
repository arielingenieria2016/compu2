#include "cerrarPrograma.h"

void cerrarPrograma(int num){

  printf("\n\nSeñal numero: %d recibida. Cerrando los semaforos y liberando segmento de memoria compartida\n\n", num);

  //
  //  Terminada de usar la memoria compartida, la liberamos.
  //

  shmdt ((char *)Memoria);
  shmctl (Id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);

  if (sem_close (sem1) < 0){
      perror ("Sem_close()");
  }

  if (sem_unlink (SEM_PATH) < 0){
      perror ("Sem_unlink()");
  }

  exit(0);

}
