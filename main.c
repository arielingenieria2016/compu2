#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <ctype.h>
 
#include "controlador.h"
#include "cerrarPrograma.h"

int main(int argc, char *const *argv) {
  int sd, sd_conn, c, port_num = 8000;
  int reuse = 1;
  socklen_t addrlen;
  struct sockaddr_in6 srv_addr;
  struct sockaddr_in6 cli_addr;
  char client_addr_ipv6[100];
  int numero;
  Mem_compartida ParImpar;

  // Semaforo

  sem1 = sem_open (SEM_PATH, O_CREAT, S_IRUSR | S_IWUSR, 1); //Abrimos el semáforo

  // Variables para realizar la memoria compartida.
  key_t Clave;

  signal(SIGINT, cerrarPrograma);

  while ((c = getopt (argc, argv, "p:n:")) != -1)
  switch (c)
  {
    case 'p':
    if (atoi(optarg) > 0) {
      port_num = atoi(optarg);
    } else {
      fprintf(stderr, "Puerto no valido\n");
      exit(EXIT_FAILURE);
    }
    break;
	case 'n':
    if (atoi(optarg) > 0) {
      numero = atoi(optarg);
    } else {
      fprintf(stderr, "Numero no valido\n");
      exit(EXIT_FAILURE);
    }
    break;

    default:
    abort();
  }

  printf("\nPuerto: %d \n", port_num);
  printf("\nNumero para determinar si es par o impar: %d \n", numero);

  ParImpar.valor= numero;
  

  //
  //	Conseguimos una clave para la memoria compartida. Todos los
  //	procesos que quieran compartir la memoria, deben obtener la misma
  //	clave. Esta se puede conseguir por medio de la función ftok.
  //	A esta función se le pasa un fichero cualquiera que exista y esté
  //	accesible (todos los procesos deben pasar el mismo fichero) y un
  //	entero cualquiera (todos los procesos el mismo entero).
  //
	
  Clave = ftok ("/bin/ls", 33);
  if (Clave == -1){
	  printf("No consigo clave para memoria compartida \n");
	  exit(0);
  }

  //
  //	Creamos la memoria con la clave recién conseguida. Para ello llamamos
  //	a la función shmget pasándole la clave, el tamaño de memoria que
  //	queremos reservar (100 enteros en nuestro caso) y unos flags.
  //	Los flags son  los permisos de lectura/escritura/ejecucion 
  //	para propietario, grupo y otros (es el 777 en octal) y el 
  //	flag IPC_CREAT para indicar que cree la memoria.
  //	La función nos devuelve un identificador para la memoria recién
  //	creada.
  //	 

  Id_Memoria = shmget (Clave, sizeof(Mem_compartida), 0777 | IPC_CREAT);
  if (Id_Memoria == -1){
	  printf("No consigo Id para memoria compartida \n");
	  exit (0);
  }

  //
  //	Una vez creada la memoria, hacemos que uno de nuestros punteros
  //	apunte a la zona de memoria recién creada. Para ello llamamos a
  //	shmat, pasándole el identificador obtenido anteriormente y un
  //	par de parámetros extraños, que con ceros vale.
  //
	
  Memoria = (Mem_compartida *)shmat (Id_Memoria, (char *)0, 0);
  if (Memoria == NULL){
	  printf("No consigo memoria compartida \n");
	  exit (0);
  }

  //
  //	Ya podemos utilizar la memoria.
  //
  
  
  sd = socket(AF_INET6, SOCK_STREAM, 0);

  if (sd < 0) {
    perror("SOCKET Error");
    exit(EXIT_FAILURE); }

  if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse, sizeof (reuse)) < 0)
  perror("setsockopt(SO_REUSEADDR) error");

  srv_addr.sin6_flowinfo = 0;
  srv_addr.sin6_family = AF_INET6;
  srv_addr.sin6_addr = in6addr_any;
  srv_addr.sin6_port = htons(port_num);

  if (bind(sd, (struct sockaddr *) &srv_addr, sizeof (srv_addr)) == -1) {
    perror("BIND Error");
    exit(EXIT_FAILURE); }

  if (listen(sd, 5) < 0) {
    perror("Listen Error.");
    exit(EXIT_FAILURE); }

  addrlen = sizeof(cli_addr);

  while ((sd_conn = accept(sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0) {
    switch (fork()) {
      case 0: // hijo
      controlador(sd_conn, (struct sockaddr *) &cli_addr, ParImpar, Memoria, sem1);
      return 0;

      case -1: // error
      perror("Fork() Error");
      break;

      default: // padre

      if(sd_conn < 0) {
        perror("Accept Error");
        exit(EXIT_FAILURE); 
      }
        inet_ntop(AF_INET6, &(cli_addr.sin6_addr),client_addr_ipv6, 100);
        printf("Conexion Recibida: %s\n",client_addr_ipv6);
        close(sd_conn);
        break;
      }
    }

  return 0;
}
