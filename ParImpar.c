#include "ParImpar.h"

int main(){

	int numero;    
	
	// Variable del semaforo
  	sem_unlink(SEM_PATH);
  	sem_t *sem1; 

  	sem1 = sem_open (SEM_PATH, O_CREAT, S_IRUSR | S_IWUSR, 1); //Abrimos el semáforo

	// Variables para realizar la memoria compartida.

	key_t Clave;
	int Id_Memoria;
	Mem_compartida *Memoria = NULL;

	//
	//	Obtenemos una clave para la memoria compartida
	//

	Clave = ftok ("/bin/ls", 33);
	if (Clave == -1){
		printf("No consigo clave para memoria compartida \n");
		exit(0);
	}

	//
	//	Obtenemos el id de la memoria. Al no poner
	//	el flag IPC_CREAT, estamos suponiendo que dicha memoria ya está
	//	creada.
	//

	Id_Memoria = shmget (Clave, sizeof(Mem_compartida), 0777);
	if (Id_Memoria == -1){
		printf("No consigo Id para memoria compartida \n");
		exit (0);
	}

	//
	//	Obtenemos un puntero a la memoria compartida
	//

	Memoria = (Mem_compartida *)shmat (Id_Memoria, (char *)0, 0);
	if (Memoria == NULL){
		printf("No consigo memoria compartida \n");
		exit (0);
	}

	//
	//	Vamos leyendo el valor de la memoria
	//	

	sem_wait (sem1);
		printf("\n\nValor en memoria compartida: %d \n\n", Memoria->valor);
		numero = Memoria->valor;
		if(numero%2==0){
			printf("\nEs un numero Par\n");
		}else{
			printf("Es un numero Impar\n");
		}
	sem_post (sem1);

	//
	//	Desasociamos nuestro puntero de la memoria compartida.
	//	El proceso que la ha creado, la liberará.
	//

    if (Id_Memoria != -1)
	{
		shmdt ((char *)Memoria);
	}

    return 0;

}
