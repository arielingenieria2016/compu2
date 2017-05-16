#include <unistd.h> //fork, pipe and I/O primitives (read, write, close, etc.)
#include <stdio.h> //Proporciona el núcleo de las capacidades de entrada/salida del lenguaje C (incluye la función printf).
#include <stdlib.h> //Para realizar ciertas operaciones como conversión de tipos, generación de números pseudo-aleatorios, gestión de memoria dinámica, control de procesos de ordenación y búsqueda.
#include <netinet/in.h> //Define el sockaddr_in estructura usado para IPv6 address
#include <pthread.h> //Usado para los hilos
#include <arpa/inet.h> // hace valido in_port_t y the type in_addr_t definido en netinet/in.h, htonl(), inet_addr() 
#include <netdb.h> //define operaciones para internet
#include <string.h> //Para manipulación de cadenas de caracteres.
#include <fcntl.h> //Creacion de file descriptor
#include <sys/types.h> //Definir distintos tipos de datos como pthread_mutex_t
#include <sys/socket.h> //Necesario para trabajar con socket
#include <sys/wait.h> //Declaraciones para esperar
#include <sys/mman.h> //shm_unlink() es necesario por ejemplo, manejo de memoria
#include <signal.h> //captar señales como control c
#include <ctype.h> //Contiene funciones para clasificar caracteres según sus tipos o para convertir entre mayúsculas y minúsculas
#include <sched.h>


#include "controlador.h"

int main(int argc, char *const *argv) {
  int sd, sd_conn, c, port_num = 8000, thread_num = 10, iteraciones = 100000;
  int reuse = 1;
  socklen_t addrlen;
  struct sockaddr_in6 srv_addr;
  struct sockaddr_in6 cli_addr;
  char client_addr_ipv6[100];
  Mem_compartida *Memoria;

  /*
	Semáforos nombrados: se puede utilizar por el proceso que lo
    crea y por cualquier otro aunque no tenga relación con el
	creador
  */

  sem_t *semaforo;

  while ((c = getopt (argc, argv, "p:u:i:")) != -1)
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

	case 'u':
    if (atoi(optarg) > 0) {
      thread_num = atoi(optarg);
    } else {
      fprintf(stderr, "Numero de Threads Invalido\n");
      exit(EXIT_FAILURE);
    }
    break;

	case 'i':
    if (atoi(optarg) > 0) {
      iteraciones = atoi(optarg);
    } else {
      fprintf(stderr, "Numero de Iteraciones Invalido\n");
      exit(EXIT_FAILURE);
    }
    break;

    default:
    abort();
  }

  printf("\nPuerto: %d \n", port_num);
  printf("\nEl nro de Threads es: %d \n", thread_num);
  printf("\nEl nro de Iteraciones es: %d \n", iteraciones);

  /* Mapeamos el segmento a la memoria */
  //sizeof (Mem_compartida); El segmento debe tener como minimo el tamaño de la estructura.

  Memoria = (Mem_compartida *) mmap (NULL, sizeof (Mem_compartida), PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANON, -1, 0);
  if (Memoria == NULL){
      perror ("Mmap()");
      exit (1);
  }

  Memoria->indice = 0;
  //Inicializamos el semaforo
  /* 
	Crea el semáfono nombrado. El nombre de un semáforo es una cadena de caracteres (con
	las mismas restricciones de un nombre de fichero). Además
	Si el nombre (ruta) es relativa, sólo puede acceder al semáforo
	el proceso que lo crea y sus hijos
	Si el nombre comienza por “/”, el semáforo puede ser
	compartido por cualquier proceso
  */

  if((semaforo=sem_open("/semaforo", O_CREAT, 0644, 1))==(sem_t *)-1){ 
	  perror("No se puede crear el semáforo"); exit(1); 
  }

  //Un socket es un "canal de comunicación" entre dos programas que corren sobre ordenadores distintos o incluso en el mismo ordenador.
  /*En este ejemplo, el servidor de páginas web se llama servidor porque está (o debería de estar) siempre encendido y pendiente de que alguien se conecte a él y le pida una página. El navegador de Internet es el cliente, puesto que se arranca cuando nosotros lo arrancamos y solicita conexión con el servidor cuando nosotros escribimos la direccion de url. Los número bajos, desde 1 a 1023 están reservados para servicios habituales de los sistemas operativos (www, ftp, mail, ping, etc). El resto están a disposición del programador*/
  sd = socket(AF_INET6, SOCK_STREAM, 0); /*La función socket() no hace absolutamente nada, salvo devolvernos y preparar un descriptor de fichero que el sistema posteriormente asociará a una conexión en red.El segundo parámetro indica si el socket es orientado a conexión (SOCK_STREAM) o no lo es (SOCK_DGRAM). De esta forma podremos hacer sockets de red o de Unix tanto orientados a conexión como no orientados a conexión.En el primer caso ambos programas deben conectarse entre ellos con un socket y hasta que no esté establecida correctamente la conexión, ninguno de los dos puede transmitir datos. Esta es la parte TCP del protocolo TCP/IP, y garantiza que todos los datos van a llegar de un programa al otro correctamente. Se utiliza cuando la información a transmitir es importante, no se puede perder ningún dato y no importa que los programas se queden "bloqueados" esperando o transmitiendo datos. Si uno de los programas está atareado en otra cosa y no atiende la comunicación, el otro quedará bloqueado hasta que el primero lea o escriba los datos.
En el segundo caso, no es necesario que los programas se conecten. Cualquiera de ellos puede transmitir datos en cualquier momento, independientemente de que el otro programa esté "escuchando" o no. Es el llamado protocolo UDP, y garantiza que los datos que lleguen son correctos, pero no garantiza que lleguen todos. Se utiliza cuando es muy importante que el programa no se quede bloqueado y no importa que se pierdan datos. */

  if (sd < 0) {
    perror("SOCKET Error");
    exit(EXIT_FAILURE); 
  }

  /* establece las opciones de socket,SO_REUSEADDR
    Especifica que las reglas utilizadas en la validación de direcciones suministradas a bind () deberían permitir la reutilización de direcciones locales, si el protocolo lo admite.Para establecer opciones en el nivel de socket, especifique el argumento de nivel como SOL_SOCKET*/

  if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse, sizeof (reuse)) < 0)
  perror("setsockopt(SO_REUSEADDR) error");

  //Estructura del servidor

  srv_addr.sin6_flowinfo = 0;
  srv_addr.sin6_family = AF_INET6; //Los clientes pueden estar en otros ordenadores distintos del servidor o van a correr en el mismo ordenador, ipv6.
  srv_addr.sin6_addr = in6addr_any; //ipv6 direcciones
  srv_addr.sin6_port = htons(port_num); //Numero de puerto donde va a correr el servicio

  /*Avisar al sistema operativo de que hemos abierto un socket y queremos que asocie nuestro programa a dicho socket. Se consigue mediante la función bind(). El sistema todavía no atenderá a las conexiones de clientes, simplemente anota que cuando empiece a hacerlo, tendrá que avisarnos a nosotros. Es en esta llamada cuando se debe indicar el número de servicio al que se quiere atender.*/
  
  if (bind(sd, (struct sockaddr *) &srv_addr, sizeof (srv_addr)) == -1) {
    perror("BIND Error");
    exit(EXIT_FAILURE); 
  }

  /*Avisar al sistema de que comience a atender dicha conexión de red. Se consigue mediante la función listen(). A partir de este momento el sistema operativo anotará la conexión de cualquier cliente para pasárnosla cuando se lo pidamos. Si llegan clientes más rápido de lo que somos capaces de atenderlos, el sistema operativo hace una "cola" con ellos y nos los irá pasando según vayamos pidiéndolo.*/

  if (listen(sd, 5) < 0) {
    perror("Listen Error.");
    exit(EXIT_FAILURE); 
  }

  addrlen = sizeof(cli_addr);

  /*Pedir y aceptar las conexiones de clientes al sistema operativo. Para ello hacemos una llamada a la función accept(). Esta función le indica al sistema operativo que nos dé al siguiente cliente de la cola. Si no hay clientes se quedará bloqueada hasta que algún cliente se conecte.*/

  while ((sd_conn = accept(sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0) {
    switch (fork()) {
      case 0: // hijo
      controlador(sd_conn, (struct sockaddr *) &cli_addr, Memoria, semaforo, thread_num, iteraciones);
      return 0;

      case -1: // error
      perror("Fork() Error");
      break;

      default: // padre

      if(sd_conn < 0) {
        perror("Accept Error");
        exit(EXIT_FAILURE); 
      }
		/*La función inet_ntop () convertirá una dirección numérica en una cadena de texto adecuada para la presentación.*/        
		inet_ntop(AF_INET6, &(cli_addr.sin6_addr),client_addr_ipv6, 100);
        printf("Conexion Recibida: %s\n",client_addr_ipv6);
        close(sd_conn);
        break;
      }
    }

  return 0;
}
